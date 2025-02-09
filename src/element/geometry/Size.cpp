#include "geometry/Size.h"

namespace element
{

bool Size::operator==(const Size &size) const
{
    return width == size.width && height == size.height;
}

}  // namespace element