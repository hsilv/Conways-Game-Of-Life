#include <iostream>
#include <cstdint>

class Color {
public:
Color() : r(0), g(0), b(0) {} 
    Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}

    uint8_t& getBlue() {
        return b;
    }

    const uint8_t& getBlue() const {
        return b;
    }

    uint8_t& getGreen() {
        return g;
    }

    const uint8_t& getGreen() const {
        return g;
    }

    uint8_t& getRed() {
        return r;
    }

    const uint8_t& getRed() const {
        return r;
    }
    
    Color operator+(const Color& other) const {
        return Color(static_cast<uint8_t>(r + other.r), static_cast<uint8_t>(g + other.g), static_cast<uint8_t>(b + other.b));
    }

    Color operator*(float scalar) const {
        return Color(static_cast<uint8_t>(r * scalar), static_cast<uint8_t>(g * scalar), static_cast<uint8_t>(b * scalar));
    }

    friend std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "\033[1;97mColor ->\033[0m ";
        os << "\033[1;31mR:" << static_cast<int>(color.r) << "\033[0m, ";
        os << "\033[1;32mG:" << static_cast<int>(color.g) << "\033[0m, ";
        os << "\033[1;34mB:" << static_cast<int>(color.b) << "\033[0m";
        return os;
    }

private:
    uint8_t r, g, b;
};