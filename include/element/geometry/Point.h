#ifndef ELEMENT_GEOMETRY_POINT_H
#define ELEMENT_GEOMETRY_POINT_H

struct Point
{
    float x;
    float y;

    bool operator==(const Point& point) const;
    Point operator+(const Point& point) const;
    Point operator-(const Point& point) const;
};

#endif  // ELEMENT_GEOMETRY_POINT_H
