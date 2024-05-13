#pragma once

#include <QStyle>
#include <QStyleHints>
#include "DarkStyle.h"

inline QStyle* getDefaultStyle(const QStyleHints* styleHints)
{
    if (styleHints)
    {
        switch (styleHints->colorScheme())
        {
        case Qt::ColorScheme::Unknown:
            return &DarkStyle::defaultStyle;
        case Qt::ColorScheme::Light:
            return &DarkStyle::defaultStyle;
        case Qt::ColorScheme::Dark:
            return &DarkStyle::defaultStyle;
        }
    }
    return &DarkStyle::defaultStyle;
}
