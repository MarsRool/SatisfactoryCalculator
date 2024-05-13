import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Factory
import "Controls"

Item
{
    id: root

    property var factoryModel: null
    property real fontPointSize: 8

    Component.onCompleted: positionViewAtEnd()

    ProductionListContent
    {
        id: rootList
        anchors.fill: parent
        anchors.bottomMargin: footer.height

        factoryModel: root.factoryModel
        fontPointSize: root.fontPointSize
    }

    RowLayout
    {
        id: footer

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: spacing
        anchors.rightMargin: spacing
        spacing: 10

        height: 100

        CustomButton
        {
            id: addButton

            Layout.preferredHeight: 50
            Layout.preferredWidth: 150

            text: qsTr("Add")
            font.pointSize: root.fontPointSize
            palette: marsPalette.current

            onClicked:
            {
                if (root.factoryModel)
                {
                    root.factoryModel.addProduction()
                }
            }
        }
    }
}
