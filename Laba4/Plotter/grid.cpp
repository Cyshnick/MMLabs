#include "grid.h"

Grid::Grid()
{

}

void Grid::draw(const Ptr<IGraphVisitor> &visitor)
{
    visitor->visitGrid(this);
}


Rect Grid::getBounding()
{
    return bounding;
}
