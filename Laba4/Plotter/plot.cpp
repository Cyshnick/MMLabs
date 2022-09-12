#include "plot.h"

Plot::Plot()
{

}


void Plot::draw(const Ptr<IGraphVisitor> &visit)
{
    visit->visitPlot(this);
}

Rect Plot::getBounding()
{
    return bounding;
}
