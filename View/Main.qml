import QtQuick
import QtQuick.Controls.Basic
import QtCore
import Factory

ApplicationWindow
{
    id: root

    property var mainModel: null
    property var optionsModel: mainModel ? mainModel.optionsVM : null

    visible: true
    x : optionsModel ? optionsModel.x : 0
    y : optionsModel ? optionsModel.y : 0
    width: optionsModel ? optionsModel.width : 1280
    height: optionsModel ? optionsModel.height : 800
    visibility: optionsModel ? optionsModel.visibility : ApplicationWindow.AutomaticVisibility
    title: qsTr("Satisfactory Calculator")

    color: palette.window
    palette: marsPalette.current

    menuBar: MenuView
    {
        fileModel: root.mainModel ? root.mainModel.fileVM : null
        onQuitRequested:
        {
            root.close()
        }

        onOptionsRequested:
        {
            optionsDialog.openOptions()
        }
    }

    MainContent
    {
        id: mainContent
        anchors.fill: parent
        mainModel: root.mainModel
    }

    PaletteManager
    {
        id: themeManager
        anchors.fill: parent

        optionsModel: root.optionsModel
    }

    OptionsDialog
    {
        id: optionsDialog
        anchors.fill: parent

        optionsModel: root.optionsModel
        fontPointSize: mainContent.fontPointSize
    }

    onClosing:
    {
        if (root.optionsModel)
        {
            optionsModel.x = x
            optionsModel.y = y
            optionsModel.width = width
            optionsModel.height = height
            optionsModel.visibility = visibility
        }
    }

    QtObject
    {
        id: marsPalette

        property var current: themeManager.current
    }
}
