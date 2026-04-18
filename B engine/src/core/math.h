#pragma once
#include <cmath>
#include <type_traits> // Para validaciones de tipos si quisieras
#include <iostream>

namespace Engine
{
    template <typename T>
    struct Vector2
    {
        T x;
        T y;

        constexpr Vector2(T x = 0, T y = 0) : x(x), y(y) {}

        // --- [C++17] Constructor de Conversión ---
        // Permite hacer: Vector2f v = Vector2i(10, 10);
        template <typename U>
        constexpr Vector2(const Vector2<U>& other)
            : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
        {
        }

        // --- Operadores de Asignación ---
        constexpr Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
        constexpr Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }

        // --- Operadores Aritméticos ---
        constexpr Vector2 operator+(const Vector2& other) const { return { x + other.x, y + other.y }; }
        constexpr Vector2 operator-(const Vector2& other) const { return { x - other.x, y - other.y }; }

        // Multiplicación de vectores (Componente a componente)
        constexpr Vector2 operator*(const Vector2& other) const { return { x * other.x, y * other.y }; }

        // --- Operadores con Escalares de distinto tipo ---
        // Usamos auto y decltype para que (Vector2i / 2.0f) devuelva un Vector2f automáticamente
        template <typename U>
        constexpr auto operator*(U scalar) const
        {
            using ResultType = decltype(std::declval<T>()* std::declval<U>());
            return Vector2<ResultType>(x * scalar, y * scalar);
        }

        template <typename U>
        constexpr auto operator/(U scalar) const
        {
            using ResultType = decltype(std::declval<T>() / std::declval<U>());
            return Vector2<ResultType>(x / scalar, y / scalar);
        }

        constexpr Vector2 operator-() const { return { -x, -y }; }

        // 1. Longitud del vector
        float Magnitude() const
        {
            return std::sqrt(static_cast<float>(x * x + y * y));
        }

        // Longitud al cuadrado (mucho más rápida, útil para comparaciones)
        constexpr T MagnitudeSquared() const
        {
            return x * x + y * y;
        }

        // 2. [C++17] Método Adjetivo: Devuelve una copia normalizada
        [[nodiscard]] Vector2<float> Normalized() const
        {
            float len = Magnitude();
            if (len > 0)
            {
                return Vector2<float>(static_cast<float>(x) / len, static_cast<float>(y) / len);
            }
            return Vector2<float>(0, 0);
        }

        // 3. Método Verbo: Modifica el vector actual
        void Normalize()
        {
            float len = Magnitude();
            if (len > 0)
            {
                x = static_cast<T>(static_cast<float>(x) / len);
                y = static_cast<T>(static_cast<float>(y) / len);
            }
        }
        // 1. Producto Punto (Dot Product): ¿Qué tanto apuntan en la misma dirección?
        constexpr T Dot(const Vector2& other) const
        {
            return (x * other.x) + (y * other.y);
        }

        // 2. Producto Cruzado 2D (Vector vs Vector): Devuelve un escalar (El eje Z imaginario)
        // Útil para saber cuánto torque genera un impacto
        constexpr T Cross(const Vector2& other) const
        {
            return (x * other.y) - (y * other.x);
        }

        // 3. Producto Cruzado 2D (Vector vs Escalar): Devuelve un Vector perpendicular
        // Útil para calcular la velocidad angular de un punto específico
        constexpr Vector2 Cross(T scalar) const
        {
            return Vector2(- scalar * y, scalar * x);
        }
    };

    // Alias
    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>; 

    inline std::ostream& operator<<(std::ostream& os, const Vector2f& v)
    {
        return os << "(" << v.x << ", " << v.y << ")";
    }

    // Sobrecarga para Vector2i
    inline std::ostream& operator<<(std::ostream& os, const Vector2i& v)
    {
        return os << "(" << v.x << ", " << v.y << ")";
    }

    template <typename T>
    constexpr Vector2<T> Cross(T scalar, const Vector2<T>& vec)
    {
        return Vector2<T>(-scalar * vec.y, scalar * vec.x);
    }

    struct Matrix3x3
    {
        // Matriz de 3x3 almacenada como un array bidimensional [fila][columna]
        float m[3][3];

        // El constructor por defecto crea la "Matriz Identidad" (el equivalente al número 1 en matrices)
        Matrix3x3()
        {
            m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
            m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
            m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
        }

        // ----------------------------------------------------
        // OPERACIONES MATEMÁTICAS
        // ----------------------------------------------------

        // Multiplicar Matriz x Matriz (Para combinar transformaciones jerárquicas)
        Matrix3x3 operator*(const Matrix3x3& other) const
        {
            Matrix3x3 result;
            // Para la optimización del juego, hacemos el cálculo directo de la matriz 3x3
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    result.m[i][j] = m[i][0] * other.m[0][j] +
                        m[i][1] * other.m[1][j] +
                        m[i][2] * other.m[2][j];
                }
            }
            return result;
        }

        // Multiplicar Matriz x Vector2f (Para aplicar la transformación a un punto en el espacio)
        Vector2f operator*(const Vector2f& vec) const
        {
            return Vector2f(
                m[0][0] * vec.x + m[0][1] * vec.y + m[0][2], // Cálculo de la X transformada
                m[1][0] * vec.x + m[1][1] * vec.y + m[1][2]  // Cálculo de la Y transformada
            );
        }

        // ----------------------------------------------------
        // FUNCIONES ESTÁTICAS DE CREACIÓN (Fábricas)
        // ----------------------------------------------------

        static Matrix3x3 Translation(const Vector2f& pos)
        {
            Matrix3x3 result;
            result.m[0][2] = pos.x;
            result.m[1][2] = pos.y;
            return result;
        }

        static Matrix3x3 Rotation(float angleRadians)
        {
            Matrix3x3 result;
            float c = std::cos(angleRadians);
            float s = std::sin(angleRadians);
            result.m[0][0] = c;   result.m[0][1] = -s;
            result.m[1][0] = s;   result.m[1][1] = c;
            return result;
        }

        static Matrix3x3 Scale(const Vector2f& scale)
        {
            Matrix3x3 result;
            result.m[0][0] = scale.x;
            result.m[1][1] = scale.y;
            return result;
        }
    };
}