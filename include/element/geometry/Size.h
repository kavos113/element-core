#ifndef ELEMENT_GEOMETRY_SIZE_H
#define ELEMENT_GEOMETRY_SIZE_H

namespace element
{

struct Size
{
    float width;
    float height;

    bool operator==(const Size &size) const;
};

}  // namespace element

#endif  // ELEMENT_GEOMETRY_SIZE_H
