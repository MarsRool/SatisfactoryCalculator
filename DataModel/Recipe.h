#pragma once

#include <vector>
#include <QJsonObject>
#include <QJsonArray>

#include "Item.h"

struct Recipe
{
    static bool fromJson(const QJsonObject &json, Recipe& recipe);
    static QJsonObject toJson(const Recipe& recipe);

    std::vector<Item> inputs;

    std::vector<Item> outputs;
};
