#include "OptionsVM.h"
#include <QScreen>

OptionsVM::OptionsVM(QQmlApplicationEngine& engine)
    : engine(engine)
{
    if (QScreen *screen = QGuiApplication::primaryScreen())
    {
        QRect screenGeometry = screen->geometry();
        x = screenGeometry.width() / 2 - width / 2;
        y = screenGeometry.height() / 2 - height / 2;
    }

    loadSettings();

    connect(this,
            &OptionsVM::languageChanged,
            this,
            &OptionsVM::updateTranslations);

    connect(&engine, &QQmlApplicationEngine::objectCreated,
            this, [this](QObject *obj, const QUrl &objUrl)
        {
            if (obj && !objUrl.isEmpty())
            {
                updateTranslations();
            }
        }, Qt::QueuedConnection);

    qDebug() << __FUNCTION__;
}

OptionsVM::~OptionsVM()
{
    saveSettings();
}

OptionsVM::Language OptionsVM::getLanguage() const
{
    return language;
}

void OptionsVM::setLanguage(Language newLanguage)
{
    if (language != newLanguage)
    {
        language = newLanguage;
        emit languageChanged();

        qDebug() << __FUNCTION__;
    }
}

void OptionsVM::updateTranslations()
{
    switch (language)
    {
    case Language::English:
    {
        QGuiApplication::removeTranslator(&translator);
        break;
    }
    case Language::Russian:
    {
        QLocale locale(QLocale::Language::Russian);

        if (translator.load(locale, "SatisfactoryCalculator", "_", qApp->applicationDirPath(), ".qm"))
        {
            QGuiApplication::installTranslator(&translator);
            qDebug() << __FUNCTION__ << "successfully loaded Qt translator by name=" << locale.name();
        }
        else
        {
            qCritical() << __FUNCTION__ << "failed to load translator by name=" << locale.name();
        }
        break;
    }
    }

    engine.retranslate();
}

void OptionsVM::loadSettings()
{
    const QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                             QGuiApplication::organizationName(), QGuiApplication::applicationName());

    autosaveEnabled = settings.value("autosaveEnabled", true).toBool();
    emit autosaveEnabledChanged(autosaveEnabled);

    if (auto themeStr = settings.value("theme", QString()).toString(); !themeStr.isEmpty())
    {
        bool success = false;
        QMetaEnum themeMetaEnum = QMetaEnum::fromType<ThemeWrapper::ThemeType>();
        if (auto newTheme = static_cast<ThemeWrapper::ThemeType>(themeMetaEnum.keyToValue(themeStr.toStdString().c_str(), &success));
            success)
        {
            theme = newTheme;
            emit themeChanged(theme);
        }
    }

    if (auto languageStr = settings.value("language", QString()).toString(); !languageStr.isEmpty())
    {
        bool success = false;
        QMetaEnum languageMetaEnum = QMetaEnum::fromType<OptionsVM::Language>();
        if (auto newLanguage = static_cast<OptionsVM::Language>(languageMetaEnum.keyToValue(languageStr.toStdString().c_str(), &success));
            success)
        {
            setLanguage(newLanguage);
        }
    }

    if (settings.contains("x"))
    {
        bool success = false;
        if (int newX = settings.value("x", x).toInt(&success); success)
        {
            x = newX;
            emit xChanged();
        }
    }

    if (settings.contains("y"))
    {
        bool success = false;
        if (int newY = settings.value("y", y).toInt(&success); success)
        {
            y = newY;
            emit yChanged();
        }
    }

    if (settings.contains("width"))
    {
        bool success = false;
        if (int newWidth = settings.value("width", width).toInt(&success); success)
        {
            width = newWidth;
            emit widthChanged();
        }
    }

    if (settings.contains("height"))
    {
        bool success = false;
        if (int newHeight = settings.value("height", height).toInt(&success); success)
        {
            height = newHeight;
            emit heightChanged();
        }
    }

    if (auto visibilityStr = settings.value("visibility", QString()).toString(); !visibilityStr.isEmpty())
    {
        bool success = false;
        QMetaEnum visibilityMetaEnum = QMetaEnum::fromType<QWindow::Visibility>();
        if (auto newvisibility = static_cast<QWindow::Visibility>(visibilityMetaEnum.keyToValue(visibilityStr.toStdString().c_str(), &success));
            success)
        {
            visibility = newvisibility;
            emit visibilityChanged();
        }
    }

    qDebug() << __FUNCTION__;
}

void OptionsVM::saveSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QGuiApplication::organizationName(), QGuiApplication::applicationName());

    settings.setValue("autosaveEnabled", autosaveEnabled);

    QMetaEnum themeMetaEnum = QMetaEnum::fromType<ThemeWrapper::ThemeType>();
    if (const auto* themePtr = themeMetaEnum.valueToKey(static_cast<int>(theme)))
    {
        if (const auto themeStr = QString::fromStdString(std::string(themePtr)); !themeStr.isEmpty())
        {
            settings.setValue("theme", themeStr);
        }
    }

    QMetaEnum languageMetaEnum = QMetaEnum::fromType<OptionsVM::Language>();
    if (const auto* languagePtr = languageMetaEnum.valueToKey(static_cast<int>(language)))
    {
        if (const auto languageStr = QString::fromStdString(std::string(languagePtr)); !languageStr.isEmpty())
        {
            settings.setValue("language", languageStr);
        }
    }

    settings.setValue("x", x);
    settings.setValue("y", y);
    settings.setValue("width", width);
    settings.setValue("height", height);

    QMetaEnum visibilityMetaEnum = QMetaEnum::fromType<QWindow::Visibility>();
    if (const auto* visibilityPtr = visibilityMetaEnum.valueToKey(static_cast<int>(visibility)))
    {
        if (const auto visibilityStr = QString::fromStdString(std::string(visibilityPtr)); !visibilityStr.isEmpty())
        {
            settings.setValue("visibility", visibilityStr);
        }
    }

    qDebug() << __FUNCTION__;
}
