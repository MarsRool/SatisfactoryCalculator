#include "Calculator.h"
#include <cmath>

Calculator::Calculator(Factory& factory)
    : factory(factory)
{
    calculate();
}

void Calculator::calculate()
{
    qDebug() << __FUNCTION__;

    factory.productionResults.clear();

    for (const auto& production : factory.productions)
    {
        for (const auto& input : production.recipe.inputs)
        {
            if (input.isValid())
            {
                if (factory.productionResults.count(input.resourceId) == 0)
                {
                    factory.productionResults.emplace(input.resourceId, ProductionResult{ input.resourceId });
                }

                int deltaConsumption = static_cast<int>(std::round(input.count * production.count * production.overclocking));
                factory.productionResults[input.resourceId].consumption += deltaConsumption;
                factory.productionResults[input.resourceId].result -= deltaConsumption;
            }
        }

        for (const auto& output : production.recipe.outputs)
        {
            if (output.isValid())
            {
                if (factory.productionResults.count(output.resourceId) == 0)
                {
                    factory.productionResults.emplace(output.resourceId, ProductionResult{ output.resourceId });
                }

                int deltaProduction = static_cast<int>(std::round(output.count * production.count * production.overclocking));
                factory.productionResults[output.resourceId].production += deltaProduction;
                factory.productionResults[output.resourceId].result += deltaProduction;
            }
        }
    }

    for (auto& [id, productionResult] : factory.productionResults)
    {
        productionResult.efficiency = productionResult.consumption != 0
            ? std::clamp(static_cast<double>(productionResult.production) / productionResult.consumption, 0.0, 1.0) : 1.0;
    }
}
