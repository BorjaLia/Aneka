#pragma once

namespace Engine
{

    // Representa las teclas del teclado físico
    enum class Key
    {
        Unknown = 0,

        // Letras
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        // Números (Fila superior)
        Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,

        // Teclas de Función
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        // Direccionales
        Up, Down, Left, Right,

        // Especiales y Modificadores
        Space, Escape, Enter, Tab, Backspace, Insert, Delete,
        PageUp, PageDown, Home, End,
        CapsLock, ScrollLock, NumLock, PrintScreen, Pause,
        LeftShift, LeftControl, LeftAlt, LeftSuper,  // Super = Tecla Windows / Cmd
        RightShift, RightControl, RightAlt, RightSuper,

        // Pad Numérico (Numpad)
        Kp0, Kp1, Kp2, Kp3, Kp4, Kp5, Kp6, Kp7, Kp8, Kp9,
        KpDecimal, KpDivide, KpMultiply, KpSubtract, KpAdd, KpEnter, KpEqual,

        // Símbolos
        Apostrophe, Comma, Minus, Period, Slash, Semicolon, Equal, LeftBracket,
        Backslash, RightBracket, GraveAccent,

        Count // Útil para saber cuántas teclas hay en total
    };

    // Representa los botones del mouse
    enum class MouseButton
    {
        Left = 0,
        Right,
        Middle,
        SideForward, // Botones laterales del mouse
        SideBack
    };
}