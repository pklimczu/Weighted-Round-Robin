import QtQuick 2.0

Rectangle {
    id: mainRect
    anchors.fill: parent
    color: "white"
    opacity: 0.6

    Text {
        anchors.centerIn: parent
        text: qsTr("Simulation in progress, please wait")
    }

    MouseArea {
        anchors.fill: parent
    }

}
