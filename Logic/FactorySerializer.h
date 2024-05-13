#pragma once

#include "DataModel/Factory.h"

#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

class FactoryFileWorker
{
public:
    enum Format { Json, Binary };

    FactoryFileWorker(Factory& factory, const QString& filepath, bool keepProductions = true);

    static QString getDefaultFilepath();
    static bool hasFile(const QString& filepath);
    static Format getActualFormat(const QString& filepath);

protected:
    void createDirectories(const QString& filepath);
    bool openFile(const QString& filepath, QFile::OpenMode flags, QFile &file);

    Factory& factory;

    QString filepath;
    Format format;

    bool keepProductions = true;
};

class FactorySerializer : public FactoryFileWorker
{
public:
    FactorySerializer(Factory& factory, const QString& filepath, bool keepProductions = true);

    bool serialize();
    bool deserialize();
};

