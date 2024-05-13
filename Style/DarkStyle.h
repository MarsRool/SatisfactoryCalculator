#pragma once

#include <QProxyStyle>

class DarkStyle : public QProxyStyle
{
    Q_OBJECT

public:
    DarkStyle();

    QPalette standardPalette() const override;

    static DarkStyle defaultStyle;

private:
    QPalette palette;
};
