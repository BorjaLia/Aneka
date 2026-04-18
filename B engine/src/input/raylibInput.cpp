#include "RaylibInput.h"
#include <raylib.h>

namespace Engine
{

    // Helper para mapear Teclado
    static int ToRaylibKey(Engine::Key key)
    {
        switch (key)
        {
            // Letras
        case Engine::Key::A: return KEY_A; case Engine::Key::B: return KEY_B; case Engine::Key::C: return KEY_C;
        case Engine::Key::D: return KEY_D; case Engine::Key::E: return KEY_E; case Engine::Key::F: return KEY_F;
        case Engine::Key::G: return KEY_G; case Engine::Key::H: return KEY_H; case Engine::Key::I: return KEY_I;
        case Engine::Key::J: return KEY_J; case Engine::Key::K: return KEY_K; case Engine::Key::L: return KEY_L;
        case Engine::Key::M: return KEY_M; case Engine::Key::N: return KEY_N; case Engine::Key::O: return KEY_O;
        case Engine::Key::P: return KEY_P; case Engine::Key::Q: return KEY_Q; case Engine::Key::R: return KEY_R;
        case Engine::Key::S: return KEY_S; case Engine::Key::T: return KEY_T; case Engine::Key::U: return KEY_U;
        case Engine::Key::V: return KEY_V; case Engine::Key::W: return KEY_W; case Engine::Key::X: return KEY_X;
        case Engine::Key::Y: return KEY_Y; case Engine::Key::Z: return KEY_Z;

            // Números
        case Engine::Key::Zero:  return KEY_ZERO;  case Engine::Key::One:   return KEY_ONE;
        case Engine::Key::Two:   return KEY_TWO;   case Engine::Key::Three: return KEY_THREE;
        case Engine::Key::Four:  return KEY_FOUR;  case Engine::Key::Five:  return KEY_FIVE;
        case Engine::Key::Six:   return KEY_SIX;   case Engine::Key::Seven: return KEY_SEVEN;
        case Engine::Key::Eight: return KEY_EIGHT; case Engine::Key::Nine:  return KEY_NINE;

            // Funciones
        case Engine::Key::F1: return KEY_F1; case Engine::Key::F2: return KEY_F2;
        case Engine::Key::F3: return KEY_F3; case Engine::Key::F4: return KEY_F4;
        case Engine::Key::F5: return KEY_F5; case Engine::Key::F6: return KEY_F6;
        case Engine::Key::F7: return KEY_F7; case Engine::Key::F8: return KEY_F8;
        case Engine::Key::F9: return KEY_F9; case Engine::Key::F10: return KEY_F10;
        case Engine::Key::F11: return KEY_F11; case Engine::Key::F12: return KEY_F12;

            // Direccionales
        case Engine::Key::Up:   return KEY_UP;   case Engine::Key::Down:  return KEY_DOWN;
        case Engine::Key::Left: return KEY_LEFT; case Engine::Key::Right: return KEY_RIGHT;

            // Especiales y Modificadores
        case Engine::Key::Space:     return KEY_SPACE;     case Engine::Key::Escape:       return KEY_ESCAPE;
        case Engine::Key::Enter:     return KEY_ENTER;     case Engine::Key::Tab:          return KEY_TAB;
        case Engine::Key::Backspace: return KEY_BACKSPACE; case Engine::Key::Insert:       return KEY_INSERT;
        case Engine::Key::Delete:    return KEY_DELETE;    case Engine::Key::PrintScreen:  return KEY_PRINT_SCREEN;
        case Engine::Key::PageUp:    return KEY_PAGE_UP;   case Engine::Key::PageDown:     return KEY_PAGE_DOWN;
        case Engine::Key::Home:      return KEY_HOME;      case Engine::Key::End:          return KEY_END;
        case Engine::Key::CapsLock:  return KEY_CAPS_LOCK; case Engine::Key::ScrollLock:   return KEY_SCROLL_LOCK;
        case Engine::Key::NumLock:   return KEY_NUM_LOCK;  case Engine::Key::Pause:        return KEY_PAUSE;

        case Engine::Key::LeftShift:   return KEY_LEFT_SHIFT;   case Engine::Key::RightShift:   return KEY_RIGHT_SHIFT;
        case Engine::Key::LeftControl: return KEY_LEFT_CONTROL; case Engine::Key::RightControl: return KEY_RIGHT_CONTROL;
        case Engine::Key::LeftAlt:     return KEY_LEFT_ALT;     case Engine::Key::RightAlt:     return KEY_RIGHT_ALT;
        case Engine::Key::LeftSuper:   return KEY_LEFT_SUPER;   case Engine::Key::RightSuper:   return KEY_RIGHT_SUPER;

            // Numpad
        case Engine::Key::Kp0: return KEY_KP_0; case Engine::Key::Kp1: return KEY_KP_1; case Engine::Key::Kp2: return KEY_KP_2;
        case Engine::Key::Kp3: return KEY_KP_3; case Engine::Key::Kp4: return KEY_KP_4; case Engine::Key::Kp5: return KEY_KP_5;
        case Engine::Key::Kp6: return KEY_KP_6; case Engine::Key::Kp7: return KEY_KP_7; case Engine::Key::Kp8: return KEY_KP_8;
        case Engine::Key::Kp9: return KEY_KP_9;
        case Engine::Key::KpDecimal:  return KEY_KP_DECIMAL; case Engine::Key::KpDivide: return KEY_KP_DIVIDE;
        case Engine::Key::KpMultiply: return KEY_KP_MULTIPLY; case Engine::Key::KpSubtract: return KEY_KP_SUBTRACT;
        case Engine::Key::KpAdd:      return KEY_KP_ADD;      case Engine::Key::KpEnter:    return KEY_KP_ENTER;
        case Engine::Key::KpEqual:    return KEY_KP_EQUAL;

            // Símbolos
        case Engine::Key::Apostrophe:   return KEY_APOSTROPHE;     case Engine::Key::Comma:        return KEY_COMMA;
        case Engine::Key::Minus:        return KEY_MINUS;          case Engine::Key::Period:       return KEY_PERIOD;
        case Engine::Key::Slash:        return KEY_SLASH;          case Engine::Key::Semicolon:    return KEY_SEMICOLON;
        case Engine::Key::Equal:        return KEY_EQUAL;          case Engine::Key::LeftBracket:  return KEY_LEFT_BRACKET;
        case Engine::Key::Backslash:    return KEY_BACKSLASH;      case Engine::Key::RightBracket: return KEY_RIGHT_BRACKET;
        case Engine::Key::GraveAccent:  return KEY_GRAVE;

        default: return 0; // Desconocido
        }
    }

    // Helper para mapear Mouse
    static int ToRaylibMouse(Engine::MouseButton button)
    {
        switch (button)
        {
        case Engine::MouseButton::Left:        return MOUSE_BUTTON_LEFT;
        case Engine::MouseButton::Right:       return MOUSE_BUTTON_RIGHT;
        case Engine::MouseButton::Middle:      return MOUSE_BUTTON_MIDDLE;
        case Engine::MouseButton::SideForward: return MOUSE_BUTTON_FORWARD;
        case Engine::MouseButton::SideBack:    return MOUSE_BUTTON_BACK;
        default: return -1;
        }
    }

    // --- Lógica de Teclado ---
    bool RaylibInput::IsKeyDown(Key key) const { return ::IsKeyDown(ToRaylibKey(key)); }
    bool RaylibInput::IsKeyPressed(Key key) const { return ::IsKeyPressed(ToRaylibKey(key)); }
    bool RaylibInput::IsKeyReleased(Key key) const { return ::IsKeyReleased(ToRaylibKey(key)); }

    // --- Lógica de Mouse ---
    bool RaylibInput::IsMouseButtonDown(MouseButton button) const
    {
        return ::IsMouseButtonDown(ToRaylibMouse(button));
    }

    bool RaylibInput::IsMouseButtonPressed(MouseButton button) const
    {
        return ::IsMouseButtonPressed(ToRaylibMouse(button));
    }

    bool RaylibInput::IsMouseButtonReleased(MouseButton button) const
    {
        return ::IsMouseButtonReleased(ToRaylibMouse(button));
    }

    Vector2f RaylibInput::GetMousePosition() const
    {
        return Vector2f(::GetMousePosition().x, -::GetMousePosition().y);
    }

    std::optional<Vector2f> RaylibInput::GetMouseDelta() const
    {
        ::Vector2 delta = ::GetMouseDelta();
        if (delta.x == 0 && delta.y == 0) return std::nullopt; // [C++17]
        return Vector2f(delta.x, -delta.y);
    }

    float RaylibInput::GetMouseWheel() { return ::GetMouseWheelMove(); }

}