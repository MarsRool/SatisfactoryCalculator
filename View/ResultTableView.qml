import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Factory
import "Controls"

Item
{
    id: root

    property var calculatorModel: null
    property real fontPointSize: 8

    property int removeResourceColumnWidth: 100
    property int elementWidth: tableView.columns > 1 ? (root.width - removeResourceColumnWidth) / (tableView.columns - 1) : 200
    property int elementHeight: 50

    CustomHorizontalHeaderView
    {
        id: horizontalHeader

        anchors.top: parent.top
        anchors.left: tableView.left
        anchors.right: tableView.right

        syncView: tableView
        fontPointSize: root.fontPointSize
        headerColumnWidth: root.elementWidth
    }

    TableView
    {
        id: tableView

        anchors.top: horizontalHeader.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        clip: true
        columnSpacing: 1
        rowSpacing: 1

        model: calculatorModel != null ? calculatorModel : {}

        ScrollBar.vertical: ScrollBar {}

        delegate: Rectangle
        {
            readonly property bool isDataColumn: column < tableView.columns - 1

            implicitWidth: isDataColumn ? root.elementWidth : removeResourceColumnWidth
            implicitHeight: root.elementHeight
            color: palette.base
            border.color: horizontalHeader.palette.highlight
            border.width: 1

            Rectangle
            {
                anchors.fill: parent
                color: r_background_color
            }

            // Text
            // {
            //     anchors.fill: parent
            //     text: r_data
            //     font.pointSize: root.fontPointSize
            //     color: palette.text
            // }

            Loader
            {
                anchors.fill: parent
                anchors.margins: 10
                sourceComponent: isDataColumn ? textComponent : removeResourceButtonComponent
            }

            Component
            {
                id: textComponent

                Text
                {
                    text: r_data
                    font.pointSize: root.fontPointSize
                    color: palette.text
                }
            }

            Component
            {
                id: removeResourceButtonComponent

                CustomButton
                {
                    id: removeButton

                    text: "X"
                    font.pointSize: root.fontPointSize
                    palette: marsPalette.current

                    onClicked:
                    {
                        if (root.calculatorModel)
                        {
                            private_.rowToRemove = row
                            removeResourceDialog.open()
                        }
                    }
                }
            }
        }
    }

    Dialog
    {
        id: removeResourceDialog

        anchors.centerIn: parent
        implicitWidth: 600
        implicitHeight: 200
        title: qsTr("Confirmation")

        Text
        {
            anchors.fill: parent

            font.pointSize: root.fontPointSize
            color: palette.text
            text: qsTr("Are you sure you want to delete resource?\nIt may result in data loss.")
        }

        footer: DialogButtonBox
        {
            id: removeResourceButtons
            standardButtons: DialogButtonBox.Yes | DialogButtonBox.No

            onAccepted:
            {
                if (root.calculatorModel)
                {
                    root.calculatorModel.removeResource(private_.rowToRemove)
                }
            }
        }

        onClosed:
        {
            private_.rowToRemove = -1
        }
    }

    QtObject
    {
        id: private_

        property int rowToRemove: -1
    }
}
