import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Factory
import "Controls"

Rectangle
{
    id: root

    property var mainModel: null
    property var factoryModel: mainModel ? mainModel.factoryVM : null
    property var calculatorModel: mainModel ? mainModel.calculatorVM : null
    readonly property real fontPointSize: Math.min(Math.max(Math.min(root.height / 36, root.width / 75), 6), 16)

    palette: marsPalette.current
    color: palette.base

    TabBar
    {
        id: bar
        width: parent.width
        CustomTabButton
        {
            text: qsTr("Production")
            width: implicitWidth
            palette: marsPalette.current
        }
        CustomTabButton
        {
            text: qsTr("Result")
            width: implicitWidth
            palette: marsPalette.current
        }
    }

    StackLayout
    {
        id: stackLayout
        anchors.topMargin: bar.height
        anchors.fill: parent
        currentIndex: bar.currentIndex

        ProductionView
        {
            id: productionTab

            width: stackLayout.width
            height: stackLayout.height

            factoryModel: root.factoryModel
            fontPointSize: root.fontPointSize
        }
        ResultView
        {
            id: resultTab

            width: stackLayout.width
            height: stackLayout.height

            calculatorModel: root.calculatorModel
            fontPointSize: root.fontPointSize
        }
    }
}
