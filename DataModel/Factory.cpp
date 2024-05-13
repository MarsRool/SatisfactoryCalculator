#include "Factory.h"

bool Factory::fromJson(const QJsonObject &json, Factory &factory)
{
    const QJsonValue productions = json["productions"];

    if (productions != QJsonValue::Undefined)
    {
        if (!productions.isArray())
        {
            return false;
        }

        const auto productionsArray = productions.toArray();
        for (const auto& productionItem : productionsArray)
        {
            if (!productionItem.isObject())
            {
                return false;
            }

            Production production;
            if (!Production::fromJson(productionItem.toObject(), production))
            {
                return false;
            }

            factory.productions.push_back(production);
        }
    }
    else
    {
        qDebug() << __FUNCTION__ << "factory json doesn't contain productions";
    }

    const QJsonValue resourceRepositoryValue = json["resourceRepository"];
    if (!resourceRepositoryValue.isObject())
    {
        return false;
    }

    const QJsonObject resourceRepositoryObject = resourceRepositoryValue.toObject();
    ResourceRepository resourceRepository;
    if (!ResourceRepository::fromJson(resourceRepositoryObject, resourceRepository))
    {
        return false;
    }
    factory.resourceRepository = resourceRepository;

    return true;
}

QJsonObject Factory::toJson(const Factory &factory, bool keepProductions)
{
    QJsonObject json;

    if (keepProductions)
    {
        QJsonArray productions;
        for (const auto& production : factory.productions)
        {
            productions.append(Production::toJson(production));
        }
        json["productions"] = productions;
    }

    json["resourceRepository"] = ResourceRepository::toJson(factory.resourceRepository);

    return json;
}
