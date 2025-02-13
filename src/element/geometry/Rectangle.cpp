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
    return Point{.x=x, .y=y};
}

Size Rectangle::GetSize() const
{
    return Size{.width=width, .height=height};
}

void Rectangle::SetPosition(const Point position)
{
    x = position.x;
    y = position.y;
}

void Rectangle::SetSize(const Size size)
{
    width = size.width;
    height = size.height;
}

}  // namespace element