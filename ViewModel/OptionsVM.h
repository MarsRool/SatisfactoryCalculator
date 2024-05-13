#pragma once

#include <QObject>
#include <QLocale>
#include <QTranslator>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QWindow>
#include <QSettings>

#include "DataModel/Theme.h"

class OptionsVM : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool autosave MEMBER autosaveEnabled NOTIFY autosaveEnabledChanged)
    Q_PROPERTY(ThemeWrapper::ThemeType theme MEMBER theme NOTIFY themeChanged)
    Q_PROPERTY(Language language READ getLanguage WRITE setLanguage NOTIFY languageChanged)

    Q_PROPERTY(int x MEMBER x NOTIFY xChanged)
    Q_PROPERTY(int y MEMBER y NOTIFY yChanged)
    Q_PROPERTY(int width MEMBER width NOTIFY widthChanged)
    Q_PROPERTY(int height MEMBER height NOTIFY heightChanged)
    Q_PROPERTY(QWindow::Visibility visibility MEMBER visibility NOTIFY visibilityChanged)

public:
    enum class Language
    {
        English,
        Russian
    };
    Q_ENUM(Language)
    OptionsVM(QQmlApplicationEngine& engine);
    ~OptionsVM();

    Language getLanguage() const;
    void setLanguage(Language newLanguage);

signals:
    void autosaveEnabledChanged(bool newAutosave);
    void themeChanged(ThemeWrapper::ThemeType newTheme);
    void languageChanged();

    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void visibilityChanged();

private:
    void updateTranslations();
    void loadSettings();
    void saveSettings();

public:
    bool autosaveEnabled = true;

    ThemeWrapper::ThemeType theme = ThemeWrapper::ThemeType::System;

    Language language = Language::English;

    int x = 0;
    int y = 0;
    int width = 1280;
    int height = 800;
    QWindow::Visibility visibility = QWindow::Visibility::AutomaticVisibility;

private:
    QTranslator translator;

    QQmlApplicationEngine& engine;
};
