import QtQuick 2.7
import QtQuick.Controls 2.2

TabButton {
    id: tabButton
    property int orderNumber: -1
    property int currentIndex: 0
    property alias textValue: tabButton.text
    height: 30

    contentItem: Text {
        text: tabButton.text
        anchors.centerIn: tabButton
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        anchors.fill: parent
        color: (currentIndex == orderNumber) ? "#f9f9f9" : "#e5e5e5"
    }

}
