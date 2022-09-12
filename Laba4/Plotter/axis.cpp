#include "axis.h"

Axis::Axis()
{

}


void Axis::draw(const Ptr<IGraphVisitor> &visitor)
{
    visitor->visitAxis(this);
}
