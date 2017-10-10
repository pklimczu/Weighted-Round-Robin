import QtQuick 2.7

Rectangle {
    property alias textValue: textInput.text
    property bool validateInt: false

    width: 0.5 * parent.width
    height: 1.2 * throughputCustomLabel.height
    color: "white"
    border {
        color: (textInput.acceptableInput || !validateInt) ? (textInput.activeFocus ? "#f1f1f1" : "#e1e1e1")
                                                           : "red"
        width: 1
    }
    radius: 4

    TextInput {
        id: textInput
        anchors.fill: parent
        horizontalAlignment: TextInput.AlignRight
        verticalAlignment: TextInput.AlignVCenter
        rightPadding: 10
        font.pixelSize: 14
        validator: IntValidator { bottom: 0; top: 1000000000 }
        selectByMouse: true
        activeFocusOnTab: true
        clip: true
    }
}
