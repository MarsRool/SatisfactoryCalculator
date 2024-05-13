#include "DarkStyle.h"

DarkStyle DarkStyle::defaultStyle;

DarkStyle::DarkStyle()
    // : palette("#456268", "#D0E8F2", "#FCF8EC", "#79A3B1",
    //           QColor("#D0E8F2").darker(150), "#456268", "#D0E8F2")
    : palette("red")
{
}

QPalette DarkStyle::standardPalette() const
{
    return palette;
}
