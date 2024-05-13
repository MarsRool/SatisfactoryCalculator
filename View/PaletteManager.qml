import QtQuick
import Factory

Item
{
    id: root

    property var optionsModel: null

    readonly property int themeType: optionsModel ? optionsModel.theme : Theme.System
    readonly property var current: themeType == Theme.Light ? lightPalette
        : (themeType == Theme.Dark ? darkPalette : system)

    readonly property var system: Qt.styleHints.appearance === Qt.Light ? lightPalette : darkPalette
    readonly property var light: lightPalette
    readonly property var dark: darkPalette

    Palette
    {
        id: lightPalette

        base: "#D0E8F2"
        window: "#D0E8F2"

        windowText: "#4E6470"
        text: "#4E6470"
        buttonText: "#4E6470"
        highlightedText: "#4E6470"
        brightText: "#4E6470"
        placeholderText: "#879FAB"

        light: "#FCF8EC"
        dark: "#8DA8B0"
        highlight: "#8DA8B0"

        button: "#B7D4DF" // slightly darker than base
        mid: "#A2BEC8" //  button and dark
        midlight: "#DAE6E6" // button and light

        shadow: "red"
        alternateBase: "yellow"
    }

    Palette
    {
        id: darkPalette

        base: "#2D2B40"
        window: "#2D2B40"

        windowText: "#9290C3"
        text: "#9290C3"
        buttonText: "#9290C3"
        highlightedText: "#9290C3"
        brightText: "#9290C3"
        placeholderText: "#373663"

        light: "#0B1126" // dark and light are reverted
        dark: "#3A4166"
        highlight: "#3A4166"

        button: "#31314B" // slightly lighter than base (between base and dark)
        mid: "#363959" //  button and dark
        midlight: "#17121D" // button and light

        shadow: "red"
        alternateBase: "yellow"
    }
}
