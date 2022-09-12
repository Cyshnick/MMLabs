#include "logic.h"

Logic::Logic(Real dataStep) :
    dataStep(dataStep)
{

}

void Logic::setInput(const RealPairs &input)
{
    splineCalc.setInput(input);
}

const Reals &Logic::getInterpolatedData() const
{
    return interpolated;
}

void Logic::exec()
{
    splineCalc.calc();
    calcInterpolatedData();
}

Real Logic::getLeft() const
{
    return splineCalc.getLeftBound();
}

Real Logic::getRight() const
{
    return splineCalc.getRightBound();
}

void Logic::calcInterpolatedData()
{
    interpolated.clear();
    for(Real x = splineCalc.getLeftBound(); x < splineCalc.getRightBound(); x += dataStep) {
        interpolated.push_back(splineCalc.getInterpolated()(x));
    }
}
