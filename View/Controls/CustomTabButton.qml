import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

TabButton
{
    id: control

    background: Rectangle
    {
        implicitHeight: 35
        color: Color.blend(control.checked ? control.palette.mid : control.palette.window,
                                             control.palette.mid, control.down ? 0.5 : 0.0)
    }
}
