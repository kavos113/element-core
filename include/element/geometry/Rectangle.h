#ifndef ELEMENT_GEOMETRY_RECTANGLE_H
#define ELEMENT_GEOMETRY_RECTANGLE_H
#include "Point.h"
#include "Size.h"

namespace element
{

struct Rectangle
{
    float x;
    float y;
    float width;
    float height;

    bool operator==(const Rectangle &rectangle) const;

    [[nodiscard]] Point GetPosition() const;
    void SetPosition(Point position);
    [[nodiscard]] Size GetSize() const;
    void SetSize(Size size);
};

}  // namespace element

#endif  // ELEMENT_GEOMETRY_RECTANGLE_H
