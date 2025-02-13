#include "color/Color.h"

namespace element
{

Color::Color(const Colors color)
{
    switch (color)
    {
        case Colors::White:
            r = 1.0f;
            g = 1.0f;
            b = 1.0f;
            a = 1.0f;
            break;
        case Colors::Black:
            r = 0.0f;
            g = 0.0f;
            b = 0.0f;
            a = 1.0f;
            break;
        case Colors::Red:
            r = 1.0f;
            g = 0.0f;
            b = 0.0f;
            a = 1.0f;
            break;
        case Colors::Green:
            r = 0.0f;
            g = 1.0f;
            b = 0.0f;
            a = 1.0f;
            break;
        case Colors::Blue:
            r = 0.0f;
            g = 0.0f;
            b = 1.0f;
            a = 1.0f;
            break;
        case Colors::Yellow:
            r = 1.0f;
            g = 1.0f;
            b = 0.0f;
            a = 1.0f;
            break;
        case Colors::Magenta:
            r = 1.0f;
            g = 0.0f;
            b = 1.0f;
            a = 1.0f;
            break;
        case Colors::Cyan:
            r = 0.0f;
            g = 1.0f;
            b = 1.0f;
            a = 1.0f;
            break;
        case Colors::Transparent:
            r = 0.0f;
            g = 0.0f;
            b = 0.0f;
            a = 0.0f;
            break;
    }
}

bool Color::operator==(const Color& color) const
{
    return r == color.r && g == color.g && b == color.b && a == color.a;
}

}  // namespace element