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

    enum class Wrapping : std::uint8_t
    {
        NONE,
        WORD,
        CHARACTER,
    };

    enum class Direction : std::uint8_t
    {
        TOP_TO_BOTTOM,
        BOTTOM_TO_TOP,
        LEFT_TO_RIGHT,
        RIGHT_TO_LEFT,
    };

    HorizontalAlignment horizontal_alignment = HorizontalAlignment::LEADING;
    VerticalAlignment vertical_alignment = VerticalAlignment::TOP;
    float line_spacing = 0.0f;
    Trimming trimming = Trimming::NONE;
    Wrapping wrapping = Wrapping::NONE;
    Direction flow_direction = Direction::TOP_TO_BOTTOM;
    Direction reading_direction = Direction::LEFT_TO_RIGHT;

    Font font;
};

}  // namespace element

#endif  // ELEMENT_FONT_PARAGRAPH_H
