#include "arrow.h"

Arrow::Arrow()
{

}

void Arrow::draw(const Ptr<IGraphVisitor> &visitor)
{
    visitor->visitArrow(this);
}

Rect Arrow::getBounding()
{
    return bounding;
}

const List<Line> &Arrow::getDrawLines()
{
    return drawLines;
}
