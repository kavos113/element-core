#include "geometry/Size.h"

namespace karin
{

bool Size::operator==(const Size &size) const
{
    return width == size.width && height == size.height;
}

}  // namespace karin