#pragma once

#include <map>

#include <QJsonObject>
#include <QJsonArray>

#include "DataModel/Resource.h"
#include "Production.h"

struct ProductionResult
{
    int resourceId = -1;

    double production = 0;

    double consumption = 0;

    double result = 0;

    double efficiency = 1.0;
};

class Factory
{
public:
    static bool fromJson(const QJsonObject &json, Factory& factory);
    static QJsonObject toJson(const Factory& factory, bool keepProductions);

    std::map<int, ProductionResult> productionResults;

    std::vector<Production> productions;

    ResourceRepository resourceRepository;
};
