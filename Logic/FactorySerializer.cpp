#include "FactorySerializer.h"

#include <QGuiApplication>
#include <QDir>
#include <QJsonDocument>
#include <QCborMap>

FactoryFileWorker::FactoryFileWorker(Factory &factory, const QString &filepath, bool keepProductions)
    : factory(factory),
    filepath(filepath),
    format(getActualFormat(filepath)),
    keepProductions(keepProductions)
{}

QString FactoryFileWorker::getDefaultFilepath()
{
#ifdef WIN32
    QString prefix = qApp->applicationDirPath();
#elif __ANDROID__
    QString prefix = "/sdcard/" + qApp->applicationName();
#endif
    return prefix + "/data/data.json";
}

bool FactoryFileWorker::hasFile(const QString &filepath)
{
    return QFile::exists(filepath);
}

FactoryFileWorker::Format FactoryFileWorker::getActualFormat(const QString &filepath)
{
    if (filepath.endsWith(".json"))
    {
        return Format::Json;
    }
    else if (filepath.endsWith(".data"))
    {
        return Format::Binary;
    }

    qWarning() << __FUNCTION__ << "filepath is incorrect: Json is assumed";
    return Format::Json;
}

void FactoryFileWorker::createDirectories(const QString &filepath)
{
    QString folderpath;

    if (filepath.contains('.'))
    {
        static const QRegularExpression anySlashRegex("[\\\\/]");
        auto pathStringList = filepath.split(anySlashRegex, Qt::SkipEmptyParts);
        pathStringList.removeLast();
        folderpath = pathStringList.join('/');
    }
    else
    {
        folderpath = filepath;
    }

    QDir(folderpath).mkpath(".");
}

bool FactoryFileWorker::openFile(const QString &filepath, QFile::OpenMode flags, QFile& file)
{
    file.setFileName(filepath);

    if (!file.open(flags))
    {
        qCritical() << __FUNCTION__ << "couldn't open file by filepath=" << filepath;
        return false;
    }

    return true;
}

FactorySerializer::FactorySerializer(Factory& factory, const QString& filepath, bool keepProductions)
    : FactoryFileWorker(factory, filepath, keepProductions)
{}

bool FactorySerializer::serialize()
{
    createDirectories(filepath);

    QFile file;
    if (!openFile(filepath, QIODevice::WriteOnly, file))
    {
        return false;
    }

    QJsonObject factoryObject = Factory::toJson(factory, keepProductions);
    file.write(format == Json
        ? QJsonDocument(factoryObject).toJson()
        : QCborValue::fromJsonValue(factoryObject).toCbor());

    qDebug() << __FUNCTION__ << "successful saving";
    return true;
}

bool FactorySerializer::deserialize()
{
    QFile file;
    if (!openFile(filepath, QIODevice::ReadOnly, file))
    {
        return false;
    }

    QByteArray data = file.readAll();
    QJsonObject loadObject(format == Json
        ? QJsonDocument::fromJson(data).object()
        : QCborValue::fromCbor(data).toMap().toJsonObject());

    Factory loadFactory;
    if (!Factory::fromJson(loadObject, loadFactory))
    {
        qCritical() << __FUNCTION__ << "deserialization falure";
        return false;
    }
    factory = loadFactory;

    qDebug() << __FUNCTION__ << "successful loading";
    return true;
}
