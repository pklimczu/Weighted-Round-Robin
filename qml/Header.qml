import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
        color: "#f2f2f2"
        height: 35

        Text {
            text: qsTr("Weighted Round Robin - Simulation")
            font.pixelSize: 18
            font.weight: Font.Thin
            color: "#545454"
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: 30
            }
        }
}
