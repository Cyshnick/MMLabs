#include "highlogic.h"

HighLogic::HighLogic(Input const& input,
                     Parameters const& params) :
    input(input),
    parameters(params),
    logic(input.baseFunc, input.begin, input.end,
          params.numOfIntegralSteps, params.numOfHarmonics)
{
    calcAllData();
}

void HighLogic::calcAllData()
{
    baseData.clear();
    sumHarmData.clear();
    harmData = RealsContainer(parameters.numOfHarmonics);

    for(Real x = input.begin; x < input.end; x += parameters.dataStep) {
        baseData.push_back(input.baseFunc(x));
        sumHarmData.push_back(logic.getFuncHarmonicsSum()(x));
        for(size_t i = 0; i != parameters.numOfHarmonics; i++)
            harmData[i].push_back(logic.getFuncHarmonics()[i](x));
    }
}
