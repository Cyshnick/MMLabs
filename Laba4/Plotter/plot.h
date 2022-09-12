#ifndef PLOT_H
#define PLOT_H

#include "glyph.h"

class Plot : public Glyph
{
public:
    Plot();

    virtual void draw(const Ptr<IGraphVisitor> &) override;
    virtual Rect getBounding() override;

private:
    Rect bounding;


};

#endif // PLOT_H
