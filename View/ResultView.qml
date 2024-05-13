import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Factory

Item
{
    id: root

    property var calculatorModel: null
    property real fontPointSize: 8

    ResultTableView
    {
        anchors.fill: parent
        calculatorModel: root.calculatorModel
        fontPointSize: root.fontPointSize
    }
}
