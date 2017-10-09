import QtQuick 2.0

Rectangle {
    id: mainRect
    property alias textLabel: text.text
    signal clicked()

    width: 100
    height: 50
    color: "#e5e5e5"
    radius: 10

    Text {
        id: text
        anchors.centerIn: parent
        text: qsTr("none")
        font.pixelSize: 18
        color: "#474747"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            mainRect.clicked()
        }
        onPressedChanged: {
            mainRect.color = mouseArea.pressed ? "#474747" : "#e5e5e5"
            text.color = mouseArea.pressed ? "#e5e5e5" : "#474747"
        }
    }
}
