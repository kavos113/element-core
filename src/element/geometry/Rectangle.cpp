#include "geometry/Rectangle.h"

namespace element
{

bool Rectangle::operator==(const Rectangle& rectangle) const
{
    return x == rectangle.x && y == rectangle.y && width == rectangle.width
           && height == rectangle.height;
}

Point Rectangle::GetPosition() const
{
    return Point{x, y};
}

}  // namespace element