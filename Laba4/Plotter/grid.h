#ifndef GRID_H
#define GRID_H

#include "glyph.h"

class Grid : public Glyph
{
public:
    Grid();

    virtual void draw(const Ptr<IGraphVisitor> &) override;
    virtual Rect getBounding() override;

private:
    size_t numberOfMainLabels;
    size_t numberOfSubLabels;

    RangeD values;
    Rect bounding;
};

#endif // GRID_H
