#pragma once

#include <QObject>
#include "DataModel/Factory.h"
#include "ViewModel/OptionsVM.h"

class FileVM : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl currentFileUrl READ getCurrentFileUrl NOTIFY currentFilepathChanged)

public:
    FileVM(Factory& factory, std::shared_ptr<OptionsVM> optionsVM);
    ~FileVM();

    QUrl getCurrentFileUrl() const;
    bool setCurrentFilepath(const QString& newFilepath, bool chechPathExistence);

public slots:
    void performNewFile(const QUrl& newFileUrl);
    void performLoad(const QUrl& newFileUrl = QUrl());
    void performSave();
    void performSaveAsJson(const QUrl& newFileUrl);
    void performSaveAsBinary(const QUrl& newFileUrl);

signals:
    void currentFilepathChanged();

    void loaded();
    void loadingFailed();

private:
    void load(const QString& newFilepath = {});
    void save(const QString& newFilepath = {});
    static void saveCopy(Factory& factory, const QString& filepath = {});

    void loadCurrentFilepath();
    void saveCurrentFilepath();

private:
    Factory& factory;
    std::weak_ptr<OptionsVM> optionsVM;

    QString filepath;
};
