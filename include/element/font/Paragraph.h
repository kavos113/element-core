#ifndef ELEMENT_FONT_PARAGRAPH_H
#define ELEMENT_FONT_PARAGRAPH_H

#include <cstdint>

#include "Font.h"

namespace element
{

struct Paragraph
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

    enum class Trimming : std::uint8_t
    {
        NONE,
        WORD,
        CHARACTER,
    };

    enum class Wrapping
    {
        NONE,
        WORD,
        CHARACTER,
    };

    HorizontalAlignment horizontal_alignment;
    VerticalAlignment vertical_alignment;
    float line_spacing;
    Trimming trimming;
    Wrapping wrapping;

    Font font;
};

}  // namespace element

#endif  // ELEMENT_FONT_PARAGRAPH_H
