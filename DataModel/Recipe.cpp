#include "Recipe.h"

bool Recipe::fromJson(const QJsonObject &json, Recipe &recipe)
{
    const QJsonValue inputs = json["inputs"];
    if (!inputs.isArray())
    {
        return false;
    }

    const auto inputsArray = inputs.toArray();
    for (const auto& inputItem : inputsArray)
    {
        if (!inputItem.isObject())
        {
            return false;
        }

        Item item;
        if (!Item::fromJson(inputItem.toObject(), item))
        {
            return false;
        }

        recipe.inputs.push_back(item);
    }

    const QJsonValue outputs = json["outputs"];
    if (!outputs.isArray())
    {
        return false;
    }

    const auto outputsArray = outputs.toArray();
    for (const auto& outputItem : outputsArray)
    {
        if (!outputItem.isObject())
        {
            return false;
        }

        Item item;
        if (!Item::fromJson(outputItem.toObject(), item))
        {
            return false;
        }

        recipe.outputs.push_back(item);
    }

    return true;
}

QJsonObject Recipe::toJson(const Recipe &recipe)
{
    QJsonObject json;

    QJsonArray inputs;
    for (const auto& input : recipe.inputs)
    {
        inputs.append(Item::toJson(input));
    }

    QJsonArray outputs;
    for (const auto& output : recipe.outputs)
    {
        outputs.append(Item::toJson(output));
    }

    json["inputs"] = inputs;
    json["outputs"] = outputs;

    return json;
}
