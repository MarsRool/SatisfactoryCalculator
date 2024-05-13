#pragma once

#include <string>
#include <vector>

#include <QJsonObject>
#include <QJsonArray>

struct Resource
{
    static bool fromJson(const QJsonObject &json, Resource& resource);
    static QJsonObject toJson(const Resource& resource);

    int id;

    std::string name;
};

struct ResourceRepository
{
    static bool fromJson(const QJsonObject& json, ResourceRepository& resourceRepository);
    static QJsonObject toJson(const ResourceRepository& resourceRepository);

    std::vector<Resource> resources;

    int lastId = -1;
};
