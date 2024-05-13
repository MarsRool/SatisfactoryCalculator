import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

ComboBox
{
    id: control

    property real fontPointSize: 8
    property alias placeholderText: textField.placeholderText

    delegate: ItemDelegate
    {
        required property var model
        required property int index

        width: ListView.view.width
        text: model[control.textRole]
        font.pointSize: root.fontPointSize
        palette.text: control.palette.text
        palette.highlightedText: control.palette.highlightedText
        font.weight: control.currentIndex === index ? Font.DemiBold : Font.Normal
        highlighted: control.highlightedIndex === index
        hoverEnabled: control.hoverEnabled
    }

    contentItem: TextField
    {
        id: textField
        leftPadding: !control.mirrored ? 12 : control.editable && activeFocus ? 3 : 1
        rightPadding: control.mirrored ? 12 : control.editable && activeFocus ? 3 : 1
        topPadding: 6 - control.padding
        bottomPadding: 6 - control.padding

        text: control.editable ? control.editText : control.displayText

        font.pointSize: root.fontPointSize
        enabled: control.editable
        autoScroll: control.editable
        readOnly: control.down
        inputMethodHints: control.inputMethodHints
        validator: control.validator
        selectByMouse: control.selectTextByMouse

        color: control.editable ? control.palette.text : control.palette.buttonText
        selectionColor: control.palette.highlight
        selectedTextColor: control.palette.highlightedText
        verticalAlignment: Text.AlignVCenter

        background: Rectangle
        {
            visible: control.enabled && control.editable && !control.flat
            border.width: parent && parent.activeFocus ? 2 : 1
            border.color: parent && parent.activeFocus ? control.palette.highlight : control.palette.button
            color: control.palette.base
        }
    }

    background: Rectangle
    {
        implicitWidth: 140
        implicitHeight: 40

        color: control.down ? control.palette.mid : control.palette.button
        border.color: control.palette.highlight
        border.width: !control.editable && control.visualFocus ? 2 : 1
        visible: !control.flat || control.down
    }
}
