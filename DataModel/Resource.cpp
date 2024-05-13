#include "Resource.h"

bool Resource::fromJson(const QJsonObject &json, Resource &resource)
{
    const QJsonValue id = json["id"];
    if (!id.isDouble())
    {
        return false;
    }
    resource.id = id.toInt();

    const QJsonValue name = json["name"];
    if (!name.isString())
    {
        return false;
    }
    resource.name = name.toString().toStdString();

    return true;
}

QJsonObject Resource::toJson(const Resource& resource)
{
    QJsonObject json;
    json["id"] = resource.id;
    json["name"] = QString::fromStdString(resource.name);
    return json;
}


bool ResourceRepository::fromJson(const QJsonObject& json, ResourceRepository& resourceRepository)
{
    const QJsonValue lastId = json["lastId"];
    if (!lastId.isDouble())
    {
        return false;
    }
    resourceRepository.lastId = lastId.toInt();

    const QJsonValue resources = json["resources"];
    if (!resources.isArray())
    {
        return false;
    }

    const auto resourcesArray = resources.toArray();
    for (const auto& resourceItem : resourcesArray)
    {
        if (!resourceItem.isObject())
        {
            return false;
        }

        Resource resource;
        if (!Resource::fromJson(resourceItem.toObject(), resource))
        {
            return false;
        }

        resourceRepository.resources.push_back(resource);
    }

    return true;
}

QJsonObject ResourceRepository::toJson(const ResourceRepository& resourceRepository)
{
    QJsonObject json;
    json["lastId"] = resourceRepository.lastId;

    QJsonArray resources;
    for (const auto& resource : resourceRepository.resources)
    {
        resources.append(Resource::toJson(resource));
    }

    json["resources"] = resources;

    return json;
}
