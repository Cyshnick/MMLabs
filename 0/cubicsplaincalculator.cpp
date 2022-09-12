#include "cubicsplaincalculator.h"
#include <limits>
#include <iostream>
#include <algorithm>

CubicSplainCalculator::CubicSplainCalculator()
{

}

void CubicSplainCalculator::calc()
{
    prepareForCalculation();
    calcAuxularyValues();
    solveMatrixForC();
    calcBAndD();

    putResultToSplines();
    freeCalcTimeMemory();
    buildInterpolatedFunc();
}

void CubicSplainCalculator::prepareForCalculation()
{
    size = sourceTable.size() - 1;
    matSize = size - 1;

    h = Reals(size, 0);
    I = Reals(size, 0);

    a = Reals(size, 0);
    b = Reals(size, 0);
    c = Reals(size, 0);
    d = Reals(size, 0);

    A = Reals(matSize, 0);
    B = Reals(matSize, 0);
    C = Reals(matSize, 0);
    D = Reals(matSize, 0);

    alpha = Reals(matSize, 0);
    beta = Reals(matSize, 0);
}

void CubicSplainCalculator::calcAuxularyValues()
{
    calcHAndI();
    calcA();
}

void CubicSplainCalculator::calcHAndI()
{
    for(size_t i = 0; i != size; i++) {
        h[i] = sourceTable[i+1].first - sourceTable[i].first;
        I[i] = (sourceTable[i+1].second - sourceTable[i].second) / h[i];
    }
}

void CubicSplainCalculator::calcA()
{
    for(size_t i = 0; i != size; i++)
        a[i] = sourceTable[i].second;
}

void CubicSplainCalculator::solveMatrixForC()
{
    calcMatrixCoefs();
    calcAlphaAndBeta();
    calcC();
}

void CubicSplainCalculator::calcMatrixCoefs()
{
    for(size_t j = 0; j != matSize; j++) {
        calcACoef(j);
        calcBCoef(j);
        calcCCoef(j);
        calcDCoef(j);
    }
}

void CubicSplainCalculator::calcACoef(size_t j)
{
    if(j != 0)
        A[j] = h[j]/3.;
}

void CubicSplainCalculator::calcBCoef(size_t j)
{
    B[j] = 2.*(h[j+1] + h[j])/3.;
}

void CubicSplainCalculator::calcCCoef(size_t j)
{
    if(j != matSize - 1)
        C[j] = h[j+1]/3.;
}

void CubicSplainCalculator::calcDCoef(size_t j)
{
    D[j] = I[j+1] - I[j];
}

void CubicSplainCalculator::calcAlphaAndBeta()
{
    alpha[0] = -C[0] / B[0];
    beta[0] = D[0] / B[0];
    for(size_t j = 1; j != matSize; j++) {
        Real y = B[j] + A[j]*alpha[j-1];
        alpha[j] = -C[j] / y;
        beta[j] = (D[j] - A[j]*beta[j-1]) / y;
    }
}

void CubicSplainCalculator::calcC()
{
    c.back() = beta.back();
    for(int j = matSize - 2; j >= 0; j--) {
        c[j+1] = alpha[j]*c[j] + beta[j];
    }
    c.push_back(0);
}

void CubicSplainCalculator::calcBAndD()
{
    for(size_t i = 0; i != size; i++) {
        b[i] = I[i] - (2*c[i] + c[i+1])*h[i]/3.;
        d[i] = (c[i+1] - c[i]) / (3*h[i]);
    }
}

void CubicSplainCalculator::putResultToSplines()
{
    splines.clear();
    for(size_t k = 0; k != size; k++)
        splines.push_back(
                    {
                        checkForZero(a[k]),
                        checkForZero(b[k]),
                        checkForZero(c[k]),
                        checkForZero(d[k])
                    });
}

void CubicSplainCalculator::freeCalcTimeMemory()
{
    h.clear();
    I.clear();

    a.clear();
    b.clear();
    c.clear();
    d.clear();

    A.clear();
    B.clear();
    C.clear();
    D.clear();

    alpha.clear();
    beta.clear();
}

void CubicSplainCalculator::buildInterpolatedFunc()
{
    interpolatedFunc = [this](Real x) -> Real
    {
        return interpolated(x);
    };
}

Real CubicSplainCalculator::interpolated(Real x) const
{
    if(x < sourceTable.front().first || x > sourceTable.back().first)
        return 0.;

    size_t i = findSplineIndex(x);
    Real xSpline = x - sourceTable[i].first;
    return splineFunc(xSpline, splines[i]);
}

size_t CubicSplainCalculator::findSplineIndex(Real x) const
{
    auto findFunction =  [x](RealPair val) -> bool
    {
        return val.first > x;
    };
    auto iter = std::find_if(sourceTable.cbegin(), sourceTable.cend(), findFunction);
    size_t dist = std::distance(sourceTable.cbegin(), iter);
    return dist - 1;
}

Real CubicSplainCalculator::splineFunc(Real x, SplineCoefs const& spline) const
{
    return spline[0] + spline[1]*x + spline[2]*x*x + spline[3]*x*x*x;
}

Real CubicSplainCalculator::checkForZero(Real x) const
{
    return (fabs(x) > std::numeric_limits<Real>::epsilon()) ? x : 0;
}
