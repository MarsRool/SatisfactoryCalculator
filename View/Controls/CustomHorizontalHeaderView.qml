import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

HorizontalHeaderView
{
    id: control

    property real fontPointSize: 8
    property real headerColumnWidth: 200
    clip: true

    delegate: Rectangle
    {
        id: delegate

        required property var model
        readonly property real cellPadding: 8

        implicitWidth: control.headerColumnWidth
        implicitHeight: Math.max(control.height, text.implicitHeight + (cellPadding * 2))
        color: control.palette.mid
        border.color: control.palette.highlight
        border.width: 2

        Label
        {
            id: text

            width: delegate.width
            height: delegate.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: control.palette.buttonText
            font.pointSize: root.fontPointSize

            text: delegate.model[control.textRole]
        }
    }
}
