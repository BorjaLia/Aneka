//#include "Core/Application.h"
//#include "Core/Components/CameraComponent.h"
//#include "Core/Components/UIAnchorComponent.h"
//#include "Core/Components/SpriteComponent.h"
//#include "Core/Components/PlayerMovementComponent.h"
//#include "Core/Components/colliderComponent.h"
//#include "Core/Components/DebugTrackingComponent.h"
//#include "Core/Events/GameEvents.h"
//#include <iostream>

int main()
{
//    // ==========================================
//    // ACTO 1: INICIALIZACIÓN DEL MOTOR
//    // ==========================================
//    Engine::Application app;
//
//    if (!app.Initialize({ 800, 600 }, "Mi Motor 2D - Arquitectura Limpia"))
//    {
//        return -1;
//    }
//
//    Engine::Texture2D playerTex = app.GetResourceManager()->GetTexture("res/sprites/NoTexture.png");
//    Engine::Texture2D wallTex = app.GetResourceManager()->GetTexture("res/sprites/NoTexture.png");
//
//
//    // ==========================================
//    // ACTO 2: CONSTRUCCIÓN DEL MUNDO (Mundo y Jugador)
//    // ==========================================
//
//    // -- El Jugador --
//    auto playerNode = std::make_unique<Engine::Node>("Player");
//    playerNode->transform->SetPosition(Engine::Vector2f(400.0f, 300.0f));
//    playerNode->AddComponent<Engine::SpriteComponent>(playerTex, Engine::Pivot::Center);
//    playerNode->AddComponent<Engine::PlayerMovementComponent>(app.GetInput(), &app.GetEventBus(), 300.0f);
//    playerNode->AddComponent<Engine::CameraComponent>(app.GetInput(), 1.0f);
//
//    Engine::CircleShape colliderPies;
//    colliderPies.radius = 20.0f;
//
//    // Offset Y negativo si queremos que baje respecto al centro (según tu sistema cartesiano)
//    playerNode->AddComponent<Engine::ColliderComponent>(colliderPies, Engine::Vector2f(0.0f, -15.0f), Engine::Color(0, 255, 0, 255));
//
//    // -- La Cámara del Minimapa (Hija del Jugador) --
//    Engine::RenderTexture2D minimapTex = app.GetResourceManager()->CreateRenderTexture(Engine::Vector2i(200, 200));
//    auto minimapCamNode = std::make_unique<Engine::Node>("MinimapCamera");
//    minimapCamNode->transform->SetPosition(Engine::Vector2f(0.0f, 0.0f)); // Localmente centrada en el jugador
//
//    auto* miniCam = minimapCamNode->AddComponent<Engine::CameraComponent>(nullptr, 0.25f);
//    miniCam->SetShowDebug(false);
//    miniCam->SetRenderTarget(minimapTex);
//
//    playerNode->AddChild(std::move(minimapCamNode));
//
//
//#ifdef _DEBUG
//    playerNode->AddComponent<Engine::DebugTrackingComponent>();
//    // minimapCamNode ya no lo necesita si sabemos que sigue al padre perfectamente
//#endif
//
//    // -- Las Paredes (El Nivel) --
//    auto wallsNode = std::make_unique<Engine::Node>("Walls");
//    auto CreateWallBlock = [&](const std::string& name, float x, float y)
//        {
//            auto block = std::make_unique<Engine::Node>(name);
//            block->transform->SetPosition(Engine::Vector2f(x, y));
//            block->transform->SetScale({ 0.25f, 0.25f });
//            block->AddComponent<Engine::SpriteComponent>(wallTex, Engine::Pivot::Center);
//            block->AddComponent<Engine::ColliderComponent>(colliderPies, Engine::Vector2f(0.0f, -0.0f), Engine::Color(0, 255, 0, 255));
//
//            wallsNode->AddChild(std::move(block));
//        };
//
//    int blockSize = 50;
//    for (float x = 150; x <= 500; x += blockSize) CreateWallBlock("WallTop", x, 500);
//    for (float y = 150; y <= 450; y += blockSize) CreateWallBlock("WallLeft", 100, y);
//    for (float y = 150; y <= 300; y += blockSize) CreateWallBlock("WallRight", 700, y);
//    for (float x = 100; x <= 700; x += blockSize) CreateWallBlock("WallBottom", x, 100);
//
//    // Añadimos el Mundo a la escena
//    app.GetRootScene()->AddChild(std::move(wallsNode));
//    app.GetRootScene()->AddChild(std::move(playerNode));
//
//
//    // ==========================================
//    // ACTO 3: CONSTRUCCIÓN DE LA INTERFAZ (UI)
//    // ==========================================
//
//    // -- 1. El Borde Negro (Padre) --
//    auto borderNode = std::make_unique<Engine::Node>("MinimapBorder");
//    borderNode->transform->SetScale(Engine::Vector2f(200.0f, 200.0f));
//    borderNode->AddComponent<Engine::SpriteComponent>(
//        app.GetResourceManager()->GetWhitePixel(), // (O playerTex si sigues probando)
//        Engine::Pivot::Center, // ¡Cambiamos a Center!
//        Engine::Color{ 128, 128, 128, 255 },
//        Engine::RenderLayer::UI
//    );
//    // Lo anclamos a la esquina de la pantalla con 10px de margen
//    auto* borderAnchor = borderNode->AddComponent<Engine::UIAnchorComponent>(
//        Engine::AnchorPreset::TopLeft,
//        Engine::Vector2f(115.0f, 115.0f)
//    );
//    borderAnchor->SetSize(Engine::Vector2f(200.0f, 200.0f));
//
//
//    // -- 2. La Pantalla del Minimapa (Hija del Borde) --
//    auto mapScreenNode = std::make_unique<Engine::Node>("MinimapScreen");
//    mapScreenNode.get()->transform->SetScale(mapScreenNode.get()->transform->GetScale() * 0.9f);
//    auto* mapSprite = mapScreenNode->AddComponent<Engine::SpriteComponent>(
//        minimapTex.texture,
//        Engine::Pivot::Center, // ¡Cambiamos a Center!
//        Engine::Color{ 255, 255, 255, 255 },
//        Engine::RenderLayer::UI
//    );
//    mapSprite->SetFlipY(true);
//
//    // Al anclar al centro, sus pivotes centrales coinciden perfectamente
//    mapScreenNode->AddComponent<Engine::UIAnchorComponent>(
//        Engine::AnchorPreset::Center,
//        Engine::Vector2f(0.0f, 0.0f)
//    );
//
//    // Ensamblamos la UI
//    borderNode->AddChild(std::move(mapScreenNode));
//    app.GetRootScene()->AddChild(std::move(borderNode));
//
//
//    // ==========================================
//    // ACTO 4: EJECUCIÓN
//    // ==========================================
//    app.Run();
//    app.Shutdown();

    return 0;
}