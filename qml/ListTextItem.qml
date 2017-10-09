import QtQuick 2.0

Item {
    property alias textValue: text.text

    id: item
    height: 50

    Text {
        id: text
        text: qsTr("none")
        font.pixelSize: 13
        anchors.centerIn: parent
    }
}
