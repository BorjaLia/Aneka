#include "RaylibRenderer.h"
#include <raylib.h> // Único lugar donde existe raylib

namespace Engine
{

	// Función auxiliar interna para traducir nuestro Color al Color de Raylib
	static ::Color ToRaylibColor(const Color& color)
	{
		return ::Color{ color.r, color.g, color.b, color.a };
	}

	bool RaylibRenderer::Initialize()
	{
		//// Como size usa int, lo pasamos directo sin static_cast
		//::InitWindow(size.x, size.y, title.c_str());
		//::SetTargetFPS(60);
		//return ::IsWindowReady();

		return true;
	}

	void RaylibRenderer::Shutdown()
	{
		::CloseWindow();
	}

	float RaylibRenderer::GetDeltaTime() const
	{
		return ::GetFrameTime();
	}

	void RaylibRenderer::BeginFrame()
	{
		::BeginDrawing();
	}

	// Fíjate que coincide exacto: const Color&
	void RaylibRenderer::ClearScreen(const Color& color)
	{
		::ClearBackground(ToRaylibColor(color));
	}

	void RaylibRenderer::EndFrame()
	{
		::EndDrawing();
		ClearQueues();
	}

	void RaylibRenderer::BeginCamera(const Vector2f& targetPosition, float zoom)
	{
		float screenW = isRenderingToTexture ? currentTextureSize.x : (float)::GetScreenWidth();
		float screenH = isRenderingToTexture ? currentTextureSize.y : (float)::GetScreenHeight();
		// Configuramos la cámara interna de Raylib
		::Camera2D cam = { 0 };

		// Offset: Colocamos el punto focal en la mitad exacta de la pantalla actual
		cam.offset = { screenW / 2.0f, screenH / 2.0f };

		// Target: Las coordenadas de mundo hacia donde estamos mirando
		cam.target = { targetPosition.x, -targetPosition.y };
		cam.rotation = 0.0f;
		cam.zoom = zoom;

		// Le decimos a la GPU que a partir de ahora aplique esta transformación matemática
		::BeginMode2D(cam);
	}

	void RaylibRenderer::EndCamera()
	{
		// Apagamos la transformación
		::EndMode2D();
	}

	void RaylibRenderer::BeginRenderToTexture(Engine::RenderTexture2D target)
	{
		// 1. Le decimos a Raylib que reconstruya su estructura usando nuestros IDs
		::RenderTexture2D raylibRT = { 0 };
		raylibRT.id = target.id;
		raylibRT.texture.id = target.texture.id;
		raylibRT.texture.width = target.texture.size.x;
		raylibRT.texture.height = target.texture.size.y;

		// 2. Encendemos el lienzo virtual y lo limpiamos
		::BeginTextureMode(raylibRT);
		::ClearBackground({ 0, 0, 0, 0 });

		isRenderingToTexture = true;
		currentTextureSize = {
			static_cast<float>(target.texture.size.x),
			static_cast<float>(target.texture.size.y)
		};
	}

	void RaylibRenderer::EndRenderToTexture()
	{
		// 1. Soltamos el lienzo virtual para que Raylib vuelva a apuntar a la pantalla
		::EndTextureMode();

		isRenderingToTexture = false;
		currentTextureSize = { 0.0f, 0.0f }; // Limpieza por seguridad
	}

	void RaylibRenderer::DrawRenderTexture(Engine::RenderTexture2D target, const Vector2f& position, const Color& tint)
	{
		// Aquí usamos el truco del 'alto negativo' que vimos antes para evitar que salga de cabeza
		::Rectangle sourceRec = {
			0.0f,
			0.0f,
			static_cast<float>(target.texture.size.x),
			-static_cast<float>(target.texture.size.y)
		};

		::Rectangle destRec = {
			position.x,
			position.y,
			static_cast<float>(target.texture.size.x),
			static_cast<float>(target.texture.size.y)
		};

		::Vector2 origin = { 0.0f, 0.0f };
		::Color raylibTint = { tint.r, tint.g, tint.b, tint.a };

		// Dibujamos usando SOLO el id de la textura interna
		::Texture2D raylibTex = { 0 };
		raylibTex.id = target.texture.id;
		raylibTex.width = target.texture.size.x;
		raylibTex.height = target.texture.size.y;

		::DrawTexturePro(raylibTex, sourceRec, destRec, origin, 0.0f, raylibTint);
	}

	// Fíjate que coincide exacto: const Vector2f&, const Vector2f&, const Color&
	//void RaylibRenderer::DrawRectangle(const Vector2f& position, const Vector2f& size, const Color& color)
	//{
	//    ::DrawRectangleV(
	//        ::Vector2{ position.x, position.y },
	//        ::Vector2{ size.x, size.y },
	//        ToRaylibColor(color)
	//    );
	//}

	//void RaylibRenderer::DrawTexture(const Texture2D& texture, const Vector2f& position, const Vector2f& scale, float rotation, const Color& tint, Pivot pivot)
	//{
	//    ::Texture2D rlTex = { texture.id, texture.size.x, texture.size.y, texture.mipmaps, texture.format };

	//    // 1. Origen: Toda la textura
	//    ::Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.size.x, (float)texture.size.y };

	//    // 2. Destino: Aplicamos la escala al tamaño final en pantalla
	//    ::Rectangle destRec = {
	//        position.x,
	//        position.y,
	//        texture.size.x * scale.x,
	//        texture.size.y * scale.y
	//    };

	//    // 3. Pivote: El punto de origen también debe escalarse para que el centro siga siendo el centro
	//    ::Vector2 origin = { 0.0f, 0.0f };
	//    float scaledWidth = texture.size.x * scale.x;
	//    float scaledHeight = texture.size.y * scale.y;

	//    switch (pivot)
	//    {
	//    case Pivot::Center:
	//        origin = { scaledWidth / 2.0f, scaledHeight / 2.0f };
	//        break;
	//    case Pivot::BottomCenter:
	//        origin = { scaledWidth / 2.0f, scaledHeight };
	//        break;
	//    case Pivot::TopLeft:
	//    default:
	//        origin = { 0.0f, 0.0f };
	//        break;
	//    }

	//    // Dibujamos con rotación (Raylib usa grados, igual que nuestro Transform)
	//    ::DrawTexturePro(rlTex, sourceRec, destRec, origin, rotation, ToRaylibColor(tint));
	//}

	void RaylibRenderer::Flush(RenderLayer layer)
	{
		// 1. Obtenemos la referencia a la cola que toca dibujar ahora mismo
		std::vector<SpriteRenderCommand>& queue = (layer == RenderLayer::World) ? worldQueue : uiQueue;

		for (const auto& cmd : queue)
		{
			// 2. Reconstruir la textura de Raylib a partir de nuestro ID genérico
			::Texture2D raylibTex = {
				cmd.texture.id,
				cmd.texture.size.x,
				cmd.texture.size.y,
				1, // mipmaps por defecto
				7  // formato por defecto (PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
			};

			// 3. Rectángulo de origen (Qué parte de la imagen original dibujamos)
			::Rectangle sourceRec;

			if (cmd.useSourceRect)
			{
				// Usamos el recorte (Ideal para Texto y animaciones de Spritesheets)
				// Raylib voltea la imagen si el width/height es negativo
				sourceRec = {
					cmd.sourceRect.pos.x,
					cmd.sourceRect.pos.y,
					cmd.flipX ? -cmd.sourceRect.size.x : cmd.sourceRect.size.x,
					cmd.flipY ? -cmd.sourceRect.size.y : cmd.sourceRect.size.y
				};
			}
			else
			{
				// Usamos toda la textura original (Sprites normales)
				sourceRec = {
					0.0f,
					0.0f,
					cmd.flipX ? -static_cast<float>(cmd.texture.size.x) : static_cast<float>(cmd.texture.size.x),
					cmd.flipY ? -static_cast<float>(cmd.texture.size.y) : static_cast<float>(cmd.texture.size.y)
				};
			}

			// 4. Rectángulo de destino (Dónde lo dibujamos en pantalla y de qué tamaño)
			// La base matemática depende de si recortamos o usamos toda la imagen
			float baseWidth = cmd.useSourceRect ? cmd.sourceRect.size.x : static_cast<float>(cmd.texture.size.x);
			float baseHeight = cmd.useSourceRect ? cmd.sourceRect.size.y : static_cast<float>(cmd.texture.size.y);

			float destWidth = baseWidth * cmd.scale.x;
			float destHeight = baseHeight * cmd.scale.y;

			float finalY = (layer == RenderLayer::World) ? -cmd.position.y : cmd.position.y;

			::Rectangle destRec = {
				cmd.position.x,
				finalY,  // ¡Aplicamos la corrección de coordenadas aquí!
				destWidth,
				destHeight
			};

			// 5. Calcular el punto de anclaje (Pivot)
			Engine::Vector2f pivotMult = Engine::GetPivotMultiplier(cmd.pivot);

			::Vector2 origin = {
				destWidth * pivotMult.x,
				destHeight * pivotMult.y
			};

			// 6. Convertir el color
			::Color raylibTint = { cmd.tint.r, cmd.tint.g, cmd.tint.b, cmd.tint.a };

			// 7. ¡La llamada final a la GPU!
			::DrawTexturePro(raylibTex, sourceRec, destRec, origin, cmd.rotation, raylibTint);
		}
	}

	void RaylibRenderer::FlushDebug(RenderLayer layer)
	{
		std::vector<DebugRenderCommand>& queue = (layer == RenderLayer::World) ? debugWorldQueue : debugUIQueue;

		for (const auto& cmd : queue)
		{
			::Color raylibColor = ToRaylibColor(cmd.color);

			// std::visit es el "switch" moderno de C++ para std::variant.
			// Revisa de forma súper eficiente qué tipo de figura está guardada.
			std::visit([&](auto&& shape)
				{
					using T = std::decay_t<decltype(shape)>;

					// 1. ¿Es un Rectángulo?
					if constexpr (std::is_same_v<T, RectangleShape>)
					{
						float hw = shape.size.x / 2.0f;
						float hh = shape.size.y / 2.0f;

						// Convertimos a radianes (Raylib usa un sistema de Y invertido, así que invertimos el ángulo)
						float rad = -cmd.rotation * (3.14159265f / 180.0f);
						float c = std::cos(rad);
						float s = std::sin(rad);

						// Esquinas locales
						::Vector2 corners[4] = {
							{ -hw, -hh }, {  hw, -hh },
							{  hw,  hh }, { -hw,  hh }
						};

						// Rotamos y trasladamos al mundo
						for (int i = 0; i < 4; ++i)
						{
							float rx = corners[i].x * c - corners[i].y * s;
							float ry = corners[i].x * s + corners[i].y * c;

							corners[i].x = cmd.position.x + rx;
							// Cuidado con la Y invertida de Raylib
							corners[i].y = -(cmd.position.y + ry);
						}

						// Dibujamos las 4 líneas conectando las esquinas
						for (int i = 0; i < 4; ++i)
						{
							::DrawLineV(corners[i], corners[(i + 1) % 4], raylibColor);
						}
					}
					// 2. ¿Es un Círculo?
					else if constexpr (std::is_same_v<T, CircleShape>)
					{
						// Los círculos ya se dibujan desde el centro por defecto, no hay que desfasarlos
						::DrawCircleLines(
							static_cast<int>(cmd.position.x),
							static_cast<int>(-cmd.position.y),
							shape.radius,
							raylibColor
						);
					}
					// 3. ¿Es una Línea?
					else if constexpr (std::is_same_v<T, LineShape>)
					{
						::Vector2 start = { cmd.position.x + shape.start.x, -(cmd.position.y + shape.start.y) };
						::Vector2 end = { cmd.position.x + shape.end.x, -(cmd.position.y + shape.end.y) };
						::DrawLineV(start, end, raylibColor);
					}
					// 4. ¿Es un Polígono Custom?
					else if constexpr (std::is_same_v<T, PolygonShape>)
					{
						size_t vertexCount = shape.localVertices.size();

						if (vertexCount > 1)
						{
							for (size_t i = 0; i < vertexCount; ++i)
							{
								size_t next = (i + 1) % vertexCount;

								::Vector2 start = {
									cmd.position.x + shape.localVertices[i].x,
									-(cmd.position.y + shape.localVertices[i].y)
								};
								::Vector2 end = {
									cmd.position.x + shape.localVertices[next].x,
									-(cmd.position.y + shape.localVertices[next].y)
								};

								::DrawLineV(start, end, raylibColor);
							}
						}
					}
				}, cmd.shape); // Pasamos el variant que queremos analizar
		}
	}

	Texture2D RaylibRenderer::LoadTexture(const char* filepath)
	{
		::Texture2D rlTex = ::LoadTexture(filepath);

		Texture2D engTex;
		engTex.id = rlTex.id;
		// Ahora usamos Vector2i para el tamaño de la textura
		engTex.size = Vector2i(rlTex.width, rlTex.height);
		engTex.mipmaps = rlTex.mipmaps;
		engTex.format = rlTex.format;

		return engTex;
	}

	void RaylibRenderer::UnloadTexture(Texture2D texture)
	{
		// Reconstruimos usando texture.size.x y texture.size.y
		::Texture2D rlTex = { texture.id, texture.size.x, texture.size.y, texture.mipmaps, texture.format };
		::UnloadTexture(rlTex);
	}

	Engine::Font* RaylibRenderer::LoadFont(const char* filepath, int baseSize)
	{
		// 1. Le pedimos a Raylib que lea el archivo y genere el Atlas.
		// El 'nullptr' y '0' le dicen que cargue los 95 caracteres ASCII estándar.
		::Font rlFont = ::LoadFontEx(filepath, baseSize, nullptr, 0);

		if (rlFont.texture.id == 0)
		{
			std::cerr << "RaylibRenderer ERROR: No se pudo cargar la fuente: " << filepath << "\n";
			return nullptr;
		}

		// 2. Creamos nuestra fuente pura del Engine
		Engine::Font* engFont = new Font();
		engFont->SetBaseSize(baseSize);
		// Usualmente el alto de línea es el tamaño base más un pequeño margen, 
		// o podemos usar el baseSize directamente.
		engFont->SetLineHeight((float)rlFont.baseSize);

		// 3. Extraemos el Texture Atlas y se lo damos a nuestro Font
		engFont->atlas.id = rlFont.texture.id;
		engFont->atlas.size = Vector2i(rlFont.texture.width, rlFont.texture.height);
		engFont->atlas.mipmaps = rlFont.texture.mipmaps;
		engFont->atlas.format = rlFont.texture.format;

		// 4. ¡El Robo de Datos! Extraemos la matemática de cada letra
		for (int i = 0; i < rlFont.glyphCount; i++)
		{
			// Raylib guarda el código ASCII en 'value'
			int codepoint = rlFont.glyphs[i].value;
			::Rectangle rec = rlFont.recs[i];       // Dónde está en el Atlas
			::GlyphInfo info = rlFont.glyphs[i];    // Cómo se posiciona

			Glyph g;

			// CAMBIO 1: Usamos llaves dobles para inicializar los dos Vector2f (pos y size)
			g.sourceRect = { {rec.x, rec.y}, {rec.width, rec.height} };

			g.offset = Vector2(info.offsetX, info.offsetY);

			// CAMBIO 2: Borré la línea duplicada. Solo necesitamos esto una vez:
			// Si Raylib no nos da un advanceX (pasa con algunas fuentes raras), usamos el ancho
			g.advanceX = (info.advanceX == 0) ? rec.width : (float)info.advanceX;

			// Guardamos la letra en nuestro diccionario
			engFont->AddGlyph((char)codepoint, g);
		}

		// 5. El Engaño: Borramos el ID de la textura en el struct de Raylib
		// para que UnloadFont no la borre de la tarjeta gráfica.
		rlFont.texture.id = 0;

		// Ahora sí, liberamos la memoria RAM que usaba Raylib (los arrays originales)
		::UnloadFont(rlFont);

		return engFont;
	}

	void RaylibRenderer::UnloadFont(Engine::Font* font)
	{
		if (font != nullptr)
		{
			// Reconstruimos el struct temporal de Raylib solo para matar la textura en la VRAM
			::Texture2D rlTex = { font->atlas.id, font->atlas.size.x, font->atlas.size.y, font->atlas.mipmaps, font->atlas.format };
			::UnloadTexture(rlTex);

			// Nota: No hacemos 'delete font' aquí. Eso es trabajo del ResourceManager.
		}
	}

	Engine::RenderTexture2D RaylibRenderer::CreateRenderTexture(const Vector2i& size)
	{
		// 1. Raylib crea su textura de renderizado nativa
		::RenderTexture2D raylibRT = ::LoadRenderTexture(size.x, size.y);

		// 2. Traducimos los datos a nuestra estructura del motor
		Engine::RenderTexture2D engineRT;
		engineRT.id = raylibRT.id;

		// Mapeamos los datos de la textura interna
		engineRT.texture.id = raylibRT.texture.id;
		engineRT.texture.size.x = raylibRT.texture.width;
		engineRT.texture.size.y = raylibRT.texture.height;

		return engineRT;
	}

	void RaylibRenderer::UnloadRenderTexture(Engine::RenderTexture2D target)
	{
		// Reconstruimos temporalmente la estructura de Raylib para destruirla
		::RenderTexture2D raylibRT = { 0 };
		raylibRT.id = target.id;
		raylibRT.texture.id = target.texture.id;

		::UnloadRenderTexture(raylibRT);
	}

	

	Texture2D RaylibRenderer::CreateWhitePixel()
	{
		// Generamos una imagen de 1x1 píxel de color blanco puro
		::Image img = ::GenImageColor(1, 1, ::WHITE);
		// La subimos a la tarjeta gráfica
		::Texture2D tex = ::LoadTextureFromImage(img);
		// Borramos la imagen de la RAM para que no consuma memoria
		::UnloadImage(img);

		// Convertimos al tipo de textura de nuestro motor
		return Engine::Texture2D{ tex.id, {tex.width, tex.height} };
	}
}