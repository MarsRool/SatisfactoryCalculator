#pragma once

#include <QJsonObject>

#include "Recipe.h"

struct Production
{
    static bool fromJson(const QJsonObject &json, Production& production);
    static QJsonObject toJson(const Production& production);

    Recipe recipe;

    int count = 0;

    double overclocking = 1.0;
};
