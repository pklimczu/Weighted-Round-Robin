import QtQuick 2.0

Item {
    id: mainItem
    width: 25
    height: 25
    signal clicked()

    Rectangle {
        id: r1
        width: 20
        height: 3
        rotation: 45
        color: "#efefef"
        anchors.centerIn: parent
    }

    Rectangle {
        id: r2
        width: 20
        height: 3
        rotation: 135
        color: "#efefef"
        anchors.centerIn: parent
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        propagateComposedEvents: true
        onClicked: {
            mainItem.clicked()
        }
        onPressedChanged: {
            r1.color = mouseArea.pressed ? "#636363" : "#efefef"
            r2.color = mouseArea.pressed ? "#636363" : "#efefef"
        }
    }
}
