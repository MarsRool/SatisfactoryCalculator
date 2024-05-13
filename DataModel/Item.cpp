#include "Item.h"

bool Item::fromJson(const QJsonObject &json, Item &item)
{
    const QJsonValue resourceId = json["resourceId"];
    if (!resourceId.isDouble())
    {
        return false;
    }
    item.resourceId = resourceId.toInt();

    const QJsonValue count = json["count"];
    if (!count.isDouble())
    {
        return false;
    }
    item.count = count.toInt();

    return true;
}

QJsonObject Item::toJson(const Item &item)
{
    QJsonObject json;
    json["resourceId"] = item.resourceId;
    json["count"] = item.count;
    return json;
}
