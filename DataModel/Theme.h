#pragma once

#include <QObject>

class ThemeWrapper : public QObject
{
    Q_OBJECT
public:
    enum class ThemeType {
        System,
        Light,
        Dark
    };
    Q_ENUM(ThemeType)
};
