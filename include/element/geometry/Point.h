#ifndef ELEMENT_GEOMETRY_POINT_H
#define ELEMENT_GEOMETRY_POINT_H

namespace element
{

struct Point
{
    float x;
    float y;

    bool operator==(const Point& point) const;
    Point operator+(const Point& point) const;
    Point operator-(const Point& point) const;
};

}  // namespace element
#endif  // ELEMENT_GEOMETRY_POINT_H
