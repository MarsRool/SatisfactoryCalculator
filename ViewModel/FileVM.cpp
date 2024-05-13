#include "FileVM.h"

#include "Logic/FactorySerializer.h"

FileVM::FileVM(Factory& factory, std::shared_ptr<OptionsVM> optionsVM)
    : factory(factory),
    optionsVM(optionsVM),
    filepath(FactorySerializer::getDefaultFilepath())
{
    loadCurrentFilepath();
}

FileVM::~FileVM()
{
    saveCurrentFilepath();
}

QUrl FileVM::getCurrentFileUrl() const
{
    return QUrl::fromLocalFile(filepath);
}

bool FileVM::setCurrentFilepath(const QString& newFilepath, bool chechPathExistence)
{
    if (newFilepath.isEmpty())
    {
        qWarning() << __FUNCTION__ << "failed to set current empty filepath";
        return false;
    }

    if (chechPathExistence && !FactorySerializer::hasFile(newFilepath))
    {
        qWarning() << __FUNCTION__ << "file does not exist by filepath=" << newFilepath;
        return false;
    }

    filepath = newFilepath;
    return true;
}

void FileVM::performNewFile(const QUrl &newFileUrl)
{
    factory = Factory{};

    save(newFileUrl.toLocalFile());

    emit loaded();

    qDebug() << __FUNCTION__;
}

void FileVM::performLoad(const QUrl &newFileUrl)
{
    load(newFileUrl.toLocalFile());

    qDebug() << __FUNCTION__;
}

void FileVM::performSave()
{
    if (!optionsVM.expired())
    {
        auto optionsVMShared = optionsVM.lock();

        if (optionsVMShared->autosaveEnabled)
        {
            static const QRegularExpression anySlashRegex("[\\\\/]");
            static const QRegularExpression pointRegex("\\.");

            const auto pathStringList = filepath.split(anySlashRegex, Qt::SkipEmptyParts);
            const QString filename = !pathStringList.isEmpty() ? pathStringList.last() : FactorySerializer::getDefaultFilepath();

            auto filenameStringList = filename.split(pointRegex, Qt::SkipEmptyParts);

            QString extension = !filenameStringList.isEmpty() ? '.' + filenameStringList.last() : QString();
            filenameStringList.removeLast();

            QString filenameWithoutExt = filenameStringList.join('.');

            const QString currentDateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh.mm.ss");

            const QString autosaveFilename = "data/autosave/" + filenameWithoutExt + ' ' + currentDateTime + extension;

            saveCopy(factory, autosaveFilename);
        }
    }

    saveCopy(factory, filepath);

    qDebug() << __FUNCTION__;
}

void FileVM::performSaveAsJson(const QUrl &newFileUrl)
{
    save(newFileUrl.toLocalFile());

    qDebug() << __FUNCTION__;
}

void FileVM::performSaveAsBinary(const QUrl &newFileUrl)
{
    save(newFileUrl.toLocalFile());

    qDebug() << __FUNCTION__;
}

void FileVM::load(const QString& newFilepath)
{
    setCurrentFilepath(newFilepath, true);

    if (FactorySerializer::hasFile(filepath))
    {
        FactorySerializer serializer(factory, filepath, true);

        if (!serializer.deserialize())
        {
            emit loadingFailed();
            return;
        }
    }

    emit loaded();

    qDebug() << __FUNCTION__;
}

void FileVM::save(const QString& newFilepath)
{
    setCurrentFilepath(newFilepath, false);
    saveCopy(factory, filepath);

    qDebug() << __FUNCTION__;
}

void FileVM::saveCopy(Factory& factory, const QString& filepath)
{
    FactorySerializer serializer(factory, filepath, true);
    serializer.serialize();

    qDebug() << __FUNCTION__;
}

void FileVM::loadCurrentFilepath()
{
    const QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                             QGuiApplication::organizationName(), QGuiApplication::applicationName());

    const QString newFilepath = settings.value("filepath", QString()).toString();
    setCurrentFilepath(newFilepath, true);

    qDebug() << __FUNCTION__;
}

void FileVM::saveCurrentFilepath()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QGuiApplication::organizationName(), QGuiApplication::applicationName());

    settings.setValue("filepath", filepath);

    qDebug() << __FUNCTION__;
}
