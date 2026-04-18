#include "ButtonComponent.h"
#include "../Node.h"
#include "../Application.h"
#include "SpriteComponent.h" // Necesario para leer el pivote y la textura
#include "renderer/IRenderer.h" // Necesario para el debug draw
#include <cmath>

#include"../debug.h"

namespace Engine
{
    ButtonComponent::ButtonComponent(const RectangleShape& initialShape,RenderLayer layer, const Vector2f& offset, bool autoFit)
        : shape(initialShape),layer(layer), offset(offset), autoFitToSprite(autoFit)
    {
        auto& bus = Application::Get().GetEventBus();

        mousePressedEventId = bus.Subscribe<MouseButtonPressedEvent>(
            [this](MouseButtonPressedEvent& e) { this->OnMousePressed(e);}
        );

        mouseReleasedEventId = bus.Subscribe<MouseButtonReleasedEvent>(
            [this](MouseButtonReleasedEvent& e) { this->OnMouseReleased(e);}
        );
    }

    ButtonComponent::~ButtonComponent()
    {
        // Nos damos de baja de los eventos
        auto& bus = Application::Get().GetEventBus();
        bus.Unsubscribe(MouseButtonPressedEvent::GetStaticType(), mousePressedEventId);
        bus.Unsubscribe(MouseButtonReleasedEvent::GetStaticType(), mouseReleasedEventId);
    }


    void ButtonComponent::Start()
    {
        // El mismo Early Exit del ColliderComponent
        if (owner == nullptr) return;

        if (auto* sprite = owner->GetComponent<SpriteComponent>())
        {
            layer = sprite->GetLayer();

            if (!autoFitToSprite) return;
            // 1. Obtenemos la escala final del Transform
            Vector2f scale = owner->transform->GetScale();

            // 2. Calculamos el tamaño real escalado
            float finalWidth = sprite->texture.size.x * std::abs(scale.x);
            float finalHeight = sprite->texture.size.y * std::abs(scale.y);

            // 3. Horneamos el tamaño final en la figura (RectangleShape)
            shape = RectangleShape{ {finalWidth, finalHeight} };

            // 4. ¡LA MAGIA DEL PIVOTE!
            // Calculamos el desfase para que el centro matemático del botón coincida con el dibujo
            Vector2f pivotMult = GetPivotMultiplier(sprite->pivot);

            offset.x = (0.5f - pivotMult.x) * finalWidth;
            offset.y = (0.5f - pivotMult.y) * finalHeight;
        }
    }

    void ButtonComponent::Update(float)
    {
        if (owner == nullptr) return;

        auto* input = Application::Get().GetInput();
        if (!input) return;

        Vector2f mousePos = input->GetMousePosition();

        if (layer == RenderLayer::UI)
        {
            mousePos.y = -mousePos.y; // Convertimos -450 de vuelta a +450
        }

        Vector2f globalPos = owner->GetGlobalPosition();

        Vector2f centerPos = { globalPos.x + offset.x, globalPos.y + offset.y };

        float halfW = shape.size.x / 2.0f;
        float halfH = shape.size.y / 2.0f;

        isHovered = (mousePos.x >= centerPos.x - halfW && mousePos.x <= centerPos.x + halfW &&
            mousePos.y >= centerPos.y - halfH && mousePos.y <= centerPos.y + halfH);

        if (input->IsKeyPressed(Key::L))
        {
            ENGINE_LOG("==== BOTON: " << owner->name << " ====");
            ENGINE_LOG("1. GlobalPos (Donde se dibuja el Sprite): " << globalPos.x << ", " << globalPos.y);
            ENGINE_LOG("2. Offset calculado: " << offset.x << ", " << offset.y);
            ENGINE_LOG("3. CenterPos (Centro matemático de la Hitbox): " << centerPos.x << ", " << centerPos.y);
            ENGINE_LOG("4. Tamaño de la Hitbox: " << shape.size.x << "x" << shape.size.y);
            ENGINE_LOG("5. Posicion del Mouse: " << mousePos.x << ", " << mousePos.y);
            ENGINE_LOG("===============================");
        }

        //if (owner == nullptr) return;

        //auto* input = Application::Get().GetInput();
        //if (!input) return;

        //Vector2f mousePos = input->GetMousePosition();
        //Vector2f globalPos = owner->GetGlobalPosition();

        //// El centro matemático de nuestro botón, considerando el offset calculado en Start()
        //Vector2f centerPos = { globalPos.x + offset.x, globalPos.y + offset.y };

        //// Calculamos los bordes asumiendo que RectangleShape tiene un Vector2f 'size' internamente
        //float halfW = shape.size.x / 2.0f;
        //float halfH = shape.size.y / 2.0f;

        //// Verificamos colisión desde el centro matemático (AABB)
        //bool inside = (mousePos.x >= centerPos.x - halfW && mousePos.x <= centerPos.x + halfW &&
        //    mousePos.y >= centerPos.y - halfH && mousePos.y <= centerPos.y + halfH);

        //isHovered = inside;

        //// Si estamos adentro y hacemos clic izquierdo
        //if (inside && input->IsMouseButtonPressed(MouseButton::Left))
        //{
        //    isPressed = true;

        //    // 1. Disparamos la función directa si existe
        //    if (onClickCallback)
        //    {
        //        onClickCallback();
        //    }

        //    // 2. Disparamos el evento global a través del EventBus
        //    ButtonPressedEvent event(owner->name);
        //    Application::Get().GetEventBus().Publish(event);
        //}
        //else if (input->IsMouseButtonReleased(MouseButton::Left))
        //{
        //    isPressed = false;
        //}
    }

    void ButtonComponent::OnMousePressed(MouseButtonPressedEvent& e)
    {
        // Validamos que sea el botón izquierdo
        if (e.GetButton() != MouseButton::Left) return;

        // Si tenemos el ratón encima, procesamos el clic y ¡LO CONSUMIMOS!
        if (isHovered)
        {
            isPressed = true;
            e.handled = true; // <--- ¡LA MAGIA! El evento muere aquí.

            if (onClickCallback)
            {
                onClickCallback();
            }

            ButtonPressedEvent event(owner->name);
            Application::Get().GetEventBus().Publish(event);
        }
    }

    void ButtonComponent::OnMouseReleased(MouseButtonReleasedEvent& e)
    {
        if (e.GetButton() == MouseButton::Left)
        {
            isPressed = false;
            // No consumimos el Release para que otros sistemas puedan detectarlo si quieren
        }
    }

    void ButtonComponent::Draw(IRenderer* renderer)
    {
        if (owner == nullptr || renderer == nullptr) return;

        Vector2f globalPos = owner->GetGlobalPosition();
        Vector2f centerPos = { globalPos.x + offset.x, globalPos.y - offset.y };
        float rot = owner->transform->GetRotation();

        // Colores dinámicos para el debug: Amarillo (Normal), Verde (Hover), Rojo (Click)
        Color debugColor = { 255, 255, 0, 255 };
        if (isPressed)
        {
            debugColor = { 255, 0, 0, 255 };
        }
        else if (isHovered)
        {
            debugColor = { 0, 255, 0, 255 };
        }

        renderer->SubmitDebugShape(layer,shape, centerPos, rot, debugColor);
    }
}