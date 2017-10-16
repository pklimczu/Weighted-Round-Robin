import QtQuick 2.7
import QtQuick.Controls 1.4

Rectangle {
    color: "#f9f9f9"
    anchors {
        left: parent.left
        top: parent.top
    }
    width: 800
    height: 600

    CustomLabel {
        id: resultTitleLabel
        text: qsTr("Results")
        width: 250
        font.weight: Font.DemiBold
        anchors {
            top: parent.top
            left: parent.left
            margins: 10
        }
    }

    RectDivider {
        id: rectDivider1
        width: 750
        anchors {
            top: resultTitleLabel.bottom
            left: parent.left
            leftMargin: 10
            topMargin: 5
        }
    }

    TableView {
        id: tableView
        width: 750
        height: 440
        anchors {
            top: rectDivider1.bottom
            left: parent.left
            margins: 10
        }

        TableViewColumn {
            role: "name"
            title: qsTr("Queue's name")
            width: 149
        }

        TableViewColumn {
            role: "inBuffor"
            title: qsTr("#packets in buffor")
            width: 149
        }

        TableViewColumn {
            role: "processed"
            title: qsTr("#processed packets")
            width: 149
        }

        TableViewColumn {
            role: "rejected"
            title: qsTr("#rejected packets")
            width: 149
        }

        TableViewColumn {
            role: "withoutInQueue"
            title: qsTr("#without being in queue")
            width: 149
        }

        model: simulationPresenter.resultList
    }

    CustomButton {
        id: saveResultsButton
        height: 40
        width: 160
        textLabel: qsTr("Save results")
        anchors {
            bottom: parent.bottom
            left: parent.left
            margins: 20
            bottomMargin: 50
        }
        onClicked: {
            simulationPresenter.saveToFile()
        }
    }
}
