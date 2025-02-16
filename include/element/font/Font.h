#ifndef ELEMENT_FONT_FONT_H
#define ELEMENT_FONT_FONT_H

namespace element
{

struct Font
{
    enum class HorizontalAlignment : std::uint8_t
    {
        LEADING,
        TRAILING,
        CENTER,
        JUSTIFIED,
    };

    enum class VerticalAlignment : std::uint8_t
    {
        TOP,
        CENTER,
        BOTTOM,
    };

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

    float size;
    HorizontalAlignment horizontal_alignment;
    VerticalAlignment vertical_alignment;
    std::wstring family;
    Style style;
    Stretch stretch;
    Weight weight;
    float line_spacing;
};

}  // namespace element

#endif  // ELEMENT_FONT_FONT_H
