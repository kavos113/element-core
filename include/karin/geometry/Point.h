#ifndef KARIN_GEOMETRY_POINT_H
#define KARIN_GEOMETRY_POINT_H

namespace karin
{

struct Point
{
    float x;
    float y;

    bool operator==(const Point& point) const;
    Point operator+(const Point& point) const;
    Point operator-(const Point& point) const;
};

}  // namespace karin
#endif  // KARIN_GEOMETRY_POINT_H
