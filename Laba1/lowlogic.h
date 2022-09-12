#ifndef LOWLOGIC_H
#define LOWLOGIC_H

#include <QDebug>
#include "shared.h"

class LowLogic
{
public:
    LowLogic(RealFunc const& baseFunc,
          Real beg, Real end,
          size_t numOfIntegralSteps,
          size_t numOfHarmonics);

    void calcAll();

    inline Real getMeanValue() const {
        return meanValue;
    }

    inline Real getEffectiveValue() const {
        return effectiveValue;
    }

    inline RealPairs const& getHarmonics() const {
        return harmonics;
    }

    inline RealFunctions const& getFuncHarmonics() const {
        return funcHarmonics;
    }

    inline RealFunc const& getFuncHarmonicsSum() const {
        return funcHarmSum;
    }

private:
    void calcEffectiveValue();
    Real calcIntegralBySimpson();
    void calcMeanValue();
    void calcFirstNHarmonics(size_t n);
    RealPair calcHarmonicComplex(size_t k);
    Real calcFurieInt(RealFunc const& func);
    void calcFuncHarmonics();
    void calcFuncHarmSum();

    RealFunc baseFunc;
    Real beg;
    Real end;

    RealFunc intFunc;
    Real intLowLimit;
    Real intHighLimit;
    size_t numOfIntSteps;

    Real meanValue;
    Real effectiveValue;
    RealPairs harmonics;
    RealFunctions funcHarmonics;

    RealFunc funcHarmSum;

    const size_t numOfHarmonics;
    const Real stepForData = 0.05;
};

#endif // LOWLOGIC_H
