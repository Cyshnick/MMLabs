#ifndef ARROW_H
#define ARROW_H

#include "glyph.h"

class Arrow : public Glyph
{
public:
    enum class Type
    {
        TwoLines,
        VoidTriangle,
        FillTriangle,
        Nothing
    };

    Arrow();

    virtual void draw(const Ptr<IGraphVisitor> &) override;
    virtual Rect getBounding() override;

    const List<Line>& getDrawLines();

private:
    Rect bounding;
    Type type;

    List<Line> drawLines;


};

#endif // ARROW_H
