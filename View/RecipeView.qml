import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import "Controls"

ListView
{
    id: root

    property var resourceListModel: null
    property var recipeListModel: null
    property real fontPointSize: 8
    property string placeholderText: ""

    readonly property int rowHeight: 35

    model: root.recipeListModel ? root.recipeListModel : []

    height: contentItem.childrenRect.height

    delegate: RowLayout
    {
        width: root.width
        height: root.rowHeight + 10
        spacing: 5

        CustomComboBox
        {
            id: comboBox

            function setupCurrentResource()
            {
                if (root.resourceListModel)
                {
                    var itemResourceId = root.resourceListModel.addResource(editText)
                    r_recipe_resource_id = itemResourceId

                    var correspondingName = root.resourceListModel.getNameById(itemResourceId)
                    editText = correspondingName

                    console.log("setupCurrentResource: ", editText, itemResourceId, correspondingName)

                    updateCurrentData()
                }
            }

            function chooseCurrentResource()
            {
                if (root.resourceListModel)
                {
                    var itemResourceId = root.resourceListModel.getIdByIndex(currentIndex)
                    r_recipe_resource_id = itemResourceId

                    var correspondingName = root.resourceListModel.getNameById(itemResourceId)
                    editText = correspondingName

                    console.log("chooseCurrentResource: ", editText, itemResourceId, correspondingName)
                }
            }

            function updateCurrentData()
            {
                if (root.resourceListModel)
                {
                    var oldCurrentIndex = comboBox.currentIndex
                    var oldCurrentText = comboBox.currentText
                    var oldEditText = comboBox.editText

                    var correspondingIndex = root.resourceListModel.getIndexById(r_recipe_resource_id)
                    comboBox.currentIndex = correspondingIndex

                    var correspondingName = root.resourceListModel.getNameById(r_recipe_resource_id)
                    editText = correspondingName

                    console.log("updateCurrentIndex: ",
                                "oldCurrentIndex", oldCurrentIndex,
                                "oldCurrentText", oldCurrentText,
                                "oldEditText", oldEditText,
                                "currentIndex", comboBox.currentIndex,
                                "currentText", comboBox.currentText,
                                "editText", comboBox.editText,
                                "ListView.count", root.count)
                }
            }

            Component.onCompleted: updateCurrentData()

            Layout.fillWidth: true
            Layout.preferredHeight: root.rowHeight
            Layout.margins: 5

            palette: marsPalette.current
            fontPointSize: root.fontPointSize

            placeholderText: root.placeholderText
            textRole: "r_resource_name"
            editable: true
            model: root.resourceListModel ? root.resourceListModel : []
            currentIndex: -1

            Keys.onReturnPressed: setupCurrentResource()
            Keys.onEnterPressed: setupCurrentResource()

            onCurrentIndexChanged: chooseCurrentResource()

            Connections
            {
                enabled: root.resourceListModel
                target: root.resourceListModel

                function onUpdated()
                {
                    comboBox.updateCurrentData()
                }
            }
        }

        TextField
        {
            Layout.preferredWidth: root.fontPointSize * 5
            Layout.preferredHeight: root.rowHeight
            Layout.rightMargin: 5

            palette: marsPalette.current
            font.pointSize: root.fontPointSize

            text: r_recipe_count

            onEditingFinished:
            {
                r_recipe_count = text
            }
        }
    }
}
