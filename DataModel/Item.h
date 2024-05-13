#pragma once

#include <QJsonObject>
#include <QJsonArray>

struct Item
{
    static bool fromJson(const QJsonObject &json, Item& item);
    static QJsonObject toJson(const Item& item);

    inline bool isValid() const
    {
        return resourceId >= 0;
    }

    int resourceId = -1;

    double count = 0.0;
};
