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

    float size;
    HorizontalAlignment horizontal_alignment;
};

}  // namespace element

#endif  // ELEMENT_FONT_FONT_H
