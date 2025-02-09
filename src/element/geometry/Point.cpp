#include "geometry/Point.h"

bool Point::operator==(const Point& point) const
{
    return x == point.x && y == point.y;
}
