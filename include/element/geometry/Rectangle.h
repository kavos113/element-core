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

    Point GetPosition() const;
    Size GetSize() const;
};

}  // namespace element

#endif  // ELEMENT_GEOMETRY_RECTANGLE_H
