import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Dialogs
import Factory

MenuBar
{
    id: root

    property var fileModel: null

    signal optionsRequested()
    signal quitRequested()

    Menu
    {
        title: qsTr("&File")
        Action
        {
            text: qsTr("&New...")
            onTriggered:
            {
                if (root.fileModel)
                {
                    private_.currentAction = newFileAction

                    fileDialog.fileMode = FileDialog.SaveFile
                    fileDialog.nameFilters = fileDialog.allNameFilters
                    fileDialog.selectedFile = root.fileModel.currentFileUrl
                    fileDialog.open()
                }
            }
        }
        Action
        {
            text: qsTr("&Open...")
            onTriggered:
            {
                if (root.fileModel)
                {
                    private_.currentAction = openFileAction

                    fileDialog.fileMode = FileDialog.OpenFile
                    fileDialog.nameFilters = fileDialog.allNameFilters
                    fileDialog.selectedFile = root.fileModel.currentFileUrl
                    fileDialog.open()
                }
            }
        }
        Action
        {
            text: qsTr("&Save")
            onTriggered:
            {
                if (root.fileModel)
                {
                    root.fileModel.performSave()
                }
            }
        }
        Action
        {
            text: qsTr("Save As &Json...")
            onTriggered:
            {
                if (root.fileModel)
                {
                    private_.currentAction = saveAsJsonAction

                    fileDialog.fileMode = FileDialog.SaveFile
                    fileDialog.nameFilters = fileDialog.jsonNameFilters
                    fileDialog.selectedFile = root.fileModel.currentFileUrl
                    fileDialog.open()
                }
            }
        }
        Action
        {
            text: qsTr("Save As &Binary...")
            onTriggered:
            {
                if (root.fileModel)
                {
                    private_.currentAction = saveAsBinaryAction

                    fileDialog.fileMode = FileDialog.SaveFile
                    fileDialog.nameFilters = fileDialog.binaryNameFilters
                    fileDialog.selectedFile = root.fileModel.currentFileUrl
                    fileDialog.open()
                }
            }
        }
        MenuSeparator { }
        Action
        {
            text: qsTr("&Quit")
            onTriggered: root.quitRequested()
        }
    }

    Menu
    {
        title: qsTr("&Edit")
        Action
        {
            text: qsTr("&Options")
            onTriggered: root.optionsRequested()
        }
    }

    FileDialog
    {
        id: fileDialog

        property var allNameFilters: ["Json (*.json)", "Binary (*.data)"]
        property var jsonNameFilters: ["Json (*.json)"]
        property var binaryNameFilters: ["Binary (*.data)"]

        selectedNameFilter.index: 0
        nameFilters: allNameFilters

        onAccepted:
        {
            if (private_.currentAction)
            {
                private_.selectedFilename = selectedFile
                private_.currentAction.trigger()
            }
        }
    }

    Item
    {
        id: private_

        function clear()
        {
            currentAction = undefined
            selectedFilename = undefined
        }

        property var currentAction: undefined
        property var selectedFilename: undefined

        Action
        {
            id: newFileAction
            onTriggered:
            {
                if (root.fileModel)
                {
                    root.fileModel.performNewFile(private_.selectedFilename);
                }
                private_.clear()
            }
        }
        Action
        {
            id: openFileAction
            onTriggered:
            {
                if (root.fileModel)
                {
                    root.fileModel.performLoad(private_.selectedFilename);
                }
                private_.clear()
            }
        }
        Action
        {
            id: saveAsJsonAction
            onTriggered:
            {
                if (root.fileModel)
                {
                    root.fileModel.performSaveAsJson(private_.selectedFilename);
                }
                private_.clear()
            }
        }
        Action
        {
            id: saveAsBinaryAction
            onTriggered:
            {
                if (root.fileModel)
                {
                    root.fileModel.performSaveAsBinary(private_.selectedFilename);
                }
                private_.clear()
            }
        }
    }
}
