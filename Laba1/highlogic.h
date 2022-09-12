#ifndef HIGHLOGIC_H
#define HIGHLOGIC_H

#include "lowlogic.h"

class HighLogic
{
public:
    struct Input {
        Real begin;
        Real end;
        RealFunc baseFunc;
    };

    struct Parameters {
        size_t numOfIntegralSteps;
        size_t numOfHarmonics;
        Real dataStep;
    };

    HighLogic(Input const& input,
              Parameters const& params);

    inline Real getMeanValue() const {
        return logic.getMeanValue();
    }

    inline Real getEffectiveValue() const {
        return logic.getEffectiveValue();
    }

    inline Reals getBaseFunc() const {
        return baseData;
    }

    inline Reals getHarmonicsSum() const {
        return sumHarmData;
    }

    inline RealsContainer const& getHarmonics() const {
        return harmData;
    }

    inline Real getBegin() const {
        return input.begin;
    }

    inline Real getEnd() const {
        return input.end;
    }

private:
    void calcAllData();


    Input input;
    Parameters parameters;
    LowLogic logic;

    Reals baseData;
    Reals sumHarmData;
    RealsContainer harmData;
};

#endif // HIGHLOGIC_H
