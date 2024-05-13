import QtQuick
import Factory

ListView
{
    id: rootList

    property var factoryModel: null
    property real fontPointSize: 8

    model: factoryModel != null ? factoryModel : {}

    delegate: ProductionRow
    {
        width: rootList.width

        factoryModel: rootList.factoryModel
        fontPointSize: rootList.fontPointSize
    }
}
