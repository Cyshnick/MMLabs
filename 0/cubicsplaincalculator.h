#ifndef CUBICSPLAINCALCULATOR_H
#define CUBICSPLAINCALCULATOR_H

#include "../Laba1/shared.h"

class CubicSplainCalculator
{
public:
    CubicSplainCalculator();

    inline void setInput(RealPairs const& input) {
        sourceTable = input;
    }

    inline RealFunc const& getInterpolated() const {
        return interpolatedFunc;
    }

    void calc();

private:
    using SplineCoefs = std::array<Real, 4>;
    using Splines = Container<SplineCoefs>;

    void prepareForCalculation();

    void calcAuxularyValues();
    void calcHAndI();
    void calcA();

    void solveMatrixForC();
    void calcMatrixCoefs();
    void calcACoef(size_t j);
    void calcBCoef(size_t j);
    void calcCCoef(size_t j);
    void calcDCoef(size_t j);
    void calcAlphaAndBeta();
    void calcC();

    void calcBAndD();

    void putResultToSplines();
    void freeCalcTimeMemory();
    void buildInterpolatedFunc();

    Real interpolated(Real x) const;
    size_t findSplineIndex(Real x) const;
    Real splineFunc(Real x, SplineCoefs const& splain) const;

    Real checkForZero(Real x) const;



    RealPairs sourceTable;
    Splines splines;

    size_t size;
    size_t matSize;

    Reals h;
    Reals I;
    Reals a;
    Reals b;
    Reals c;
    Reals d;
    Reals A;
    Reals B;
    Reals C;
    Reals D;
    Reals alpha;
    Reals beta;



    RealFunc interpolatedFunc;
};

#endif // CUBICSPLAINCALCULATOR_H
