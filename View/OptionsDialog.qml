import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Factory
import "Controls"

Item
{
    id: root

    property var optionsModel: null
    property real fontPointSize: 8

    function openOptions()
    {
        optionsDialog.open()
    }

    Dialog
    {
        id: optionsDialog

        anchors.centerIn: parent
        width: 600
        height: 400
        title: qsTr("Options")

        Column
        {
            anchors.fill: parent
            spacing: 15

            RowLayout
            {
                width: parent.width

                Text
                {
                    font.pointSize: root.fontPointSize
                    color: palette.text
                    text: qsTr("Autosave")
                }

                CheckBox
                {
                    checkState: root.optionsModel && root.optionsModel.autosave ? Qt.Checked : Qt.Unchecked

                    onCheckStateChanged:
                    {
                        if (root.optionsModel)
                        {
                            root.optionsModel.autosave = (checkState == Qt.Checked)
                        }
                    }
                }
            }

            ButtonGroup
            {
                id: themeButtonGroup
                buttons: themeRow.children
            }

            ColumnLayout
            {
                Text
                {
                    font.pointSize: root.fontPointSize
                    color: palette.text
                    text: qsTr("Theme")
                }

                RowLayout
                {
                    id: themeRow
                    RadioButton
                    {
                        text: qsTr("System")
                        checked: root.optionsModel && root.optionsModel.theme === Theme.System
                        onCheckedChanged:
                        {
                            if (checked && root.optionsModel)
                            {
                                root.optionsModel.theme = Theme.System
                            }
                        }
                    }
                    RadioButton
                    {
                        text: qsTr("Light")
                        checked: root.optionsModel && root.optionsModel.theme === Theme.Light
                        onCheckedChanged:
                        {
                            if (checked && root.optionsModel)
                            {
                                root.optionsModel.theme = Theme.Light
                            }
                        }
                    }
                    RadioButton
                    {
                        text: qsTr("Dark")
                        checked: root.optionsModel && root.optionsModel.theme === Theme.Dark
                        onCheckedChanged:
                        {
                            if (checked && root.optionsModel)
                            {
                                root.optionsModel.theme = Theme.Dark
                            }
                        }
                    }
                }
            }

            ButtonGroup
            {
                id: languageButtonGroup
                buttons: languageRow.children
            }

            ColumnLayout
            {
                Text
                {
                    font.pointSize: root.fontPointSize
                    color: palette.text
                    text: qsTr("Language")
                }

                RowLayout
                {
                    id: languageRow
                    RadioButton
                    {
                        text: "English"
                        checked: root.optionsModel && root.optionsModel.language === Options.English
                        onCheckedChanged:
                        {
                            if (checked && root.optionsModel)
                            {
                                root.optionsModel.language = Options.English
                            }
                        }
                    }
                    RadioButton
                    {
                        text: "Русский"
                        checked: root.optionsModel && root.optionsModel.language === Options.Russian
                        onCheckedChanged:
                        {
                            if (checked && root.optionsModel)
                            {
                                root.optionsModel.language = Options.Russian
                            }
                        }
                    }
                }
            }
        }
    }
}
