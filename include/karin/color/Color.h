#ifndef KARIN_COLOR_COLOR_H
#define KARIN_COLOR_COLOR_H

#include <cstdint>

namespace karin
{

struct Color
{
    enum class Colors : std::uint8_t
    {
        White,
        Black,
        Red,
        Green,
        Blue,
        Yellow,
        Magenta,
        Cyan,
        Transparent
    };

    float r;
    float g;
    float b;
    float a;

    Color() = default;

    Color(const float r, const float g, const float b, const float a = 1.0f)
        : r(r), g(g), b(b), a(a)
    {
    }

    explicit Color(Colors color);

    bool operator==(const Color& color) const;
};

}  // namespace karin

#endif  // KARIN_COLOR_COLOR_H
