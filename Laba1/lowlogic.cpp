#include "lowlogic.h"

LowLogic::LowLogic(const RealFunc &baseFunc,
             Real beg, Real end,
             size_t numOfIntegralSteps,
             size_t numOfHarmonics) :
    baseFunc(baseFunc),
    beg(beg),
    end(end),
    numOfIntSteps(numOfIntegralSteps),
    numOfHarmonics(numOfHarmonics)
{
    calcAll();
}

void LowLogic::calcAll()
{
    calcEffectiveValue();
    calcMeanValue();
    calcFirstNHarmonics(numOfHarmonics);
    calcFuncHarmonics();
    calcFuncHarmSum();
}

void LowLogic::calcEffectiveValue() {
    intFunc = [this](Real x) {
        return baseFunc(x) * baseFunc(x);
    };
    intLowLimit = beg;
    intHighLimit = end;

    effectiveValue = sqrt(1. / (end - beg) * calcIntegralBySimpson());
}

Real LowLogic::calcIntegralBySimpson() {
    Real width = (intHighLimit - intLowLimit) / numOfIntSteps;

    Real integral = 0;
    for (size_t step = 0; step != numOfIntSteps; step++) {
        const Real x1 = beg + step * width;
        const Real x2 = x1 + width;

        integral += width / 6. * (intFunc(x1) + 4 * intFunc(0.5 * (x1 + x2)) + intFunc(x2));
    }

    return integral;
}

void LowLogic::calcMeanValue() {
    intFunc = baseFunc;
    intLowLimit = 0;
    intHighLimit = end;

    meanValue = 1. / (end - beg)  * calcIntegralBySimpson();
}

void LowLogic::calcFirstNHarmonics(size_t n) {
    for(size_t i = 0; i != n; ++i)
        harmonics.push_back(calcHarmonicComplex(i));
}

RealPair LowLogic::calcHarmonicComplex(size_t k) {
    auto sinFunc = [this, k](Real x) {
        return baseFunc(x) * sin(k * x);
    };
    auto cosFunc = [this, k](Real x) {
        return baseFunc(x) * cos(k * x);
    };

    Real Fsin = calcFurieInt(sinFunc);
    Real Fcos = calcFurieInt(cosFunc);

    RealPair harmonic;
    harmonic.first = sqrt(Fsin * Fsin + Fcos * Fcos);
    harmonic.second = (PI*(Fcos < 0) - atan(Fsin/Fcos));

    return harmonic;
}

Real LowLogic::calcFurieInt(const RealFunc &func) {
    intFunc = func;
    intLowLimit = 0;
    intHighLimit = 2*PI;

    return 1. / PI * calcIntegralBySimpson();
}

void LowLogic::calcFuncHarmonics()
{
    int k = 0;
    for(auto const& harm : harmonics) {
        auto func = [k, harm](Real x)
        {
            return harm.first*cos(k*x + harm.second);
        };
        funcHarmonics.push_back(std::move(func));
        ++k;
    }
}

void LowLogic::calcFuncHarmSum()
{
    funcHarmSum = [this](Real x) {
        Real sum = this->funcHarmonics.front()(x)*(-.5);
        for(auto const& harm : funcHarmonics)
            sum += harm(x);
        return sum;
    };
}

