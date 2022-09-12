#ifndef IGRAPHVISITOR_H
#define IGRAPHVISITOR_H

#include "shared.h"

class Arrow;
class Axis;
class Grid;
class Plot;

class IGraphVisitor
{
public:
    virtual ~IGraphVisitor() {}

    virtual void visitArrow(Arrow*) = 0;

    virtual void visitAxis(Axis*) = 0;

    virtual void visitGrid(Grid*) = 0;

    virtual void visitPlot(Plot*) = 0;
};

#endif // IGRAPHVISITOR_H
