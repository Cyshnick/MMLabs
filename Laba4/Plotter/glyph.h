#ifndef GLYPH_H
#define GLYPH_H

#include "igraphvisitor.h"

class Glyph
{
public:
    virtual ~Glyph();

    virtual void draw(Ptr<IGraphVisitor> const&);

    virtual Rect getBounding();
};

#endif // GLYPH_H
