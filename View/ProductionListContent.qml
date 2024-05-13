import QtQuick
import QtQuick.Controls.Basic
import Factory

ListView
{
    id: rootList

    property var factoryModel: null
    property real fontPointSize: 8
    property real scrollSensitivity: 1.5

    model: factoryModel != null ? factoryModel : {}
    clip: true

    boundsBehavior: Flickable.StopAtBounds
    maximumFlickVelocity: 4000
    flickDeceleration: 20000

    ScrollBar.vertical: ScrollBar
    {
        id: productionScrollBar
        width: 15
        policy: rootList.contentHeight > rootList.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
    }

    delegate: ProductionRow
    {
        width: rootList.width - productionScrollBar.width

        factoryModel: rootList.factoryModel
        fontPointSize: rootList.fontPointSize
    }

    onCountChanged:
    {
        currentIndex = count - 1
    }

    MouseArea
    {
        anchors.fill: parent
        anchors.rightMargin: productionScrollBar.width

        acceptedButtons: Qt.NoButton

        onWheel:
        {
            rootList.flick(0, wheel.y * wheel.angleDelta.y * rootList.scrollSensitivity)
        }
    }
}
