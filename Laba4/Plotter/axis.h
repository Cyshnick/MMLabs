#ifndef AXIS_H
#define AXIS_H
#include "shared.h"
#include "arrow.h"


class Axis : public Glyph
{
public:
    enum class SubTitleLocation {
        Center,
        NearArrow
    };

    Axis();

    virtual void draw(const Ptr<IGraphVisitor> &) override;


private:
    double min;
    double max;
    Rect bounding;
    std::string subTitle;
    SubTitleLocation subTitleLocation;
    Arrow arrow;


};

#endif // AXIS_H
