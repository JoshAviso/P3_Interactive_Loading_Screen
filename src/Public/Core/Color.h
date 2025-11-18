#pragma once

#include <Core/Common.h>
#include <SFML/Graphics.hpp>

class Color {
public:
    union {
        struct { uint8 r, g, b, a; };
        uint8 data[4];
    };
    constexpr Color() noexcept : r(0), g(0), b(0), a(255) {}
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) noexcept
        : r(red), g(green), b(blue), a(alpha) {
    }

    operator sf::Color() const noexcept {
        return sf::Color(r, g, b, a);
    }
    Color& operator=(const Color& other) {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        return *this;
    };
    bool operator==(const Color& other) const noexcept {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
    bool operator!=(const Color& other) const noexcept {
        return !(*this == other);
    }

    // Predefined Colors
    static const Color& White()     { static const Color white  (255, 255, 255, 255);   return white; };
    static const Color& Black()     { static const Color black  (0, 0, 0, 255);         return black; };
    static const Color& Red()       { static const Color red    (255, 0, 0, 255);       return red; };
    static const Color& Green()     { static const Color green  (0, 255, 0, 255);       return green; };
    static const Color& Blue()      { static const Color blue   (0, 0, 255, 255);       return blue; };
    static const Color& Yellow()    { static const Color yellow (255, 255, 0, 255);     return yellow; }
};