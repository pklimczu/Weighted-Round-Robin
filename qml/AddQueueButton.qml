import QtQuick 2.0

Rectangle {
    id: rectangle
    width: 100
    height: 50
    color: "#e5e5e5"
    radius: 10

    Text {
        id: text
        anchors.centerIn: parent
        text: qsTr("Add")
        font.pixelSize: 18
        color: "#474747"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            console.log("TEST")
        }
        onPressedChanged: {
            rectangle.color = mouseArea.pressed ? "#474747" : "#e5e5e5"
            text.color = mouseArea.pressed ? "#e5e5e5" : "#474747"
        }
    }
}
