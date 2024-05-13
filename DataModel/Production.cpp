#include "Production.h"

bool Production::fromJson(const QJsonObject &json, Production &production)
{
    const QJsonValue recipeValue = json["recipe"];
    if (!recipeValue.isObject())
    {
        return false;
    }

    const QJsonObject recipeObject = recipeValue.toObject();
    Recipe recipe;
    if (!Recipe::fromJson(recipeObject, recipe))
    {
        return false;
    }
    production.recipe = recipe;

    const QJsonValue count = json["count"];
    if (!count.isDouble())
    {
        return false;
    }
    production.count = count.toInt();

    const QJsonValue overclocking = json["overclocking"];
    if (!overclocking.isDouble())
    {
        return false;
    }
    production.overclocking = overclocking.toDouble();

    return true;
}

QJsonObject Production::toJson(const Production& production)
{
    QJsonObject json;
    json["recipe"] = Recipe::toJson(production.recipe);
    json["count"] = production.count;
    json["overclocking"] = production.overclocking;
    return json;
}
