#ifndef LOGIC_H
#define LOGIC_H

#include "cubicsplaincalculator.h"

class Logic
{
public:
    Logic(Real dataStep);

    void setInput(RealPairs const& input);

    Reals const& getInterpolatedData() const;

    void exec();

    Real getLeft() const;
    Real getRight() const;

private:
    void calcInterpolatedData();

    CubicSplainCalculator splineCalc;
    Real dataStep;

    Reals interpolated;
};

// add Points plot to plotter

#endif // LOGIC_H
