#ifndef KARIN_FONT_FONT_H
#define KARIN_FONT_FONT_H

#include <cstdint>
#include <string>

namespace karin
{

struct Font
{
    enum class Style : std::uint8_t
    {
        NORMAL,
        ITALIC,
        OBLIQUE,
    };

    enum class Stretch : std::uint8_t
    {
        ULTRA_CONDENSED,
        EXTRA_CONDENSED,
        CONDENSED,
        SEMI_CONDENSED,
        NORMAL,
        SEMI_EXPANDED,
        EXPANDED,
        EXTRA_EXPANDED,
        ULTRA_EXPANDED,
    };

    enum class Weight : std::uint16_t
    {
        THIN = 100,
        EXTRA_LIGHT = 200,
        LIGHT = 300,
        SEMI_LIGHT = 350,
        NORMAL = 400,
        MEDIUM = 500,
        SEMI_BOLD = 600,
        BOLD = 700,
        EXTRA_BOLD = 800,
        BLACK = 900,
        EXTRA_BLACK = 950,
    };

    float size = 0.0f;
    std::wstring family;
    Style style = Style::NORMAL;
    Stretch stretch = Stretch::NORMAL;
    Weight weight = Weight::NORMAL;
    bool underline = false;
    bool line_through = false;
};

}  // namespace karin

#endif  // KARIN_FONT_FONT_H
