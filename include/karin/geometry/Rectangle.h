#ifndef KARIN_GEOMETRY_RECTANGLE_H
#define KARIN_GEOMETRY_RECTANGLE_H
#include "Point.h"
#include "Size.h"

namespace karin
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

}  // namespace karin

#endif  // KARIN_GEOMETRY_RECTANGLE_H
