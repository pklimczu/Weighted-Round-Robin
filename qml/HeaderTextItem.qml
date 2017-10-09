import QtQuick 2.0

Item {
    property alias textValue: text.text
    property alias realWidth: text.paintedWidth
    id: item
    width: text.paintedWidth

    Text {
        id: text
        text: qsTr("none")
        font.pixelSize: 12
        font.weight: Font.Bold
        color: "#636363"
        anchors.centerIn: parent
    }
}
