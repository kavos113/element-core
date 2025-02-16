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

    float size;
    HorizontalAlignment horizontal_alignment;
    VerticalAlignment vertical_alignment;
    std::wstring family;
    Style style;
};

}  // namespace element

#endif  // ELEMENT_FONT_FONT_H
