import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Factory
import "Controls"

Rectangle
{
    id: root

    property var factoryModel: null
    property real fontPointSize: 8

    palette: marsPalette.current
    radius: 10
    border.width: 2
    border.color: palette.dark
    color: palette.window

    height: productionLayout.height + productionLayout.spacing

    Column
    {
        id: productionLayout

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5

        height: countLayout.height + recipesLayout.height + spacing
        spacing: 10

        RowLayout
        {
            id: countLayout

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: spacing
            spacing: 5

            Text
            {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight

                palette: marsPalette.current
                color: palette.text
                font.pointSize: root.fontPointSize
                horizontalAlignment: Text.AlignRight

                text: qsTr("Count")
            }

            TextField
            {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter

                palette: marsPalette.current
                font.pointSize: root.fontPointSize

                text: r_count

                onEditingFinished:
                {
                    r_count = text
                }
            }

            Text
            {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter

                palette: marsPalette.current
                color: palette.text
                font.pointSize: root.fontPointSize
                horizontalAlignment: Text.AlignRight

                text: qsTr("Overclocking")
            }

            TextField
            {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                Layout.rightMargin: parent.spacing

                palette: marsPalette.current
                font.pointSize: root.fontPointSize

                text: r_overclocking

                onEditingFinished:
                {
                    r_overclocking = text
                }
            }

            CustomButton
            {
                id: removeButton
                Layout.fillHeight: true
                implicitWidth: implicitHeight

                text: "X"
                font.pointSize: root.fontPointSize
                palette: marsPalette.current

                onClicked:
                {
                    if (root.factoryModel)
                    {
                        root.factoryModel.removeProduction(index)
                    }
                }
            }
        }

        Rectangle
        {
            id: border

            anchors.left: parent.left
            anchors.right: parent.right

            height: 3
            radius: 1
            palette: marsPalette.current

            color: palette.dark
        }

        Row
        {
            id: recipesLayout

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: spacing
            spacing: 5

            height: Math.max(inputs.height, outputs.height) + 10

            RecipeView
            {
                id: inputs
                width: parent.width / 2 - spacing

                resourceListModel: root.factoryModel ? root.factoryModel.resources : null
                recipeListModel: r_inputs
                fontPointSize: root.fontPointSize
                placeholderText: qsTr("type input resource name and press Enter")
            }

            RecipeView
            {
                id: outputs
                width: parent.width / 2 - spacing

                resourceListModel: root.factoryModel ? root.factoryModel.resources : null
                recipeListModel: r_outputs
                fontPointSize: root.fontPointSize
                placeholderText: qsTr("type output resource name and press Enter")
            }
        }
    }
}
