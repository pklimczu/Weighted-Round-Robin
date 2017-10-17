import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: mainRect
    anchors.fill: parent
    color: "white"

    Item {
        height: textItem.paintedHeight + bussyIndicator.height + procentValue.paintedHeight
        anchors.centerIn: parent

        Text {
            id: textItem
            text: qsTr("Simulation in progress, please wait")
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }

        BusyIndicator {
            id: bussyIndicator
            running: true
            anchors.centerIn: parent
        }

        Text {
            id: procentValue
            text: Number(simulationPresenter.progressValue).toFixed(2) + "%"
            anchors.top: bussyIndicator.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    MouseArea {
        anchors.fill: parent
    }
}
