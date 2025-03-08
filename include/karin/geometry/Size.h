#ifndef KARIN_GEOMETRY_SIZE_H
#define KARIN_GEOMETRY_SIZE_H

namespace karin
{

struct Size
{
    float width;
    float height;

    bool operator==(const Size &size) const;
};

}  // namespace karin

#endif  // KARIN_GEOMETRY_SIZE_H
