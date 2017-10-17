import QtQuick 2.7
import QtQuick.Layouts 1.3

Rectangle {
    anchors {
        left: parent.left
        top: parent.top
    }
    width: 800
    height: 600

    color: "#f9f9f9"

    /* Basic parameters area */

    CustomLabel {
        id: basicParametersCustomLabel
        text: qsTr("Basic parameters")
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
        width: 250
        anchors {
            top: basicParametersCustomLabel.bottom
            left: parent.left
            leftMargin: 10
            topMargin: 5
        }
    }

    Rectangle {
        id: throughputDurationRectangle
        color: "#f9f9f9"
        width: 250
        height: 70
        anchors {
            top: rectDivider1.bottom
            left: parent.left
            margins: 10
        }

        GridLayout {
            columns: 3
            columnSpacing: 0
            anchors.fill: parent

            CustomLabel {
                id: throughputCustomLabel
                text: qsTr("Throughput")
                Layout.preferredWidth: 0.35 * parent.width
            }

            CustomInput {
                id: throughputCustomInput
                textValue: "10"
            }

            CustomLabel {
                text: "[kb/s]"
                Layout.preferredWidth: 0.1 * parent.width
            }

            CustomLabel {
                text: qsTr("Duration")
            }

            CustomInput {
                id: durationCustomInput
                textValue: "1000"
            }

            CustomLabel {
                text: "[s]"
            }

        }
    }

    /* Queues area */

    CustomLabel {
        id: queuesCustomLabel
        text: qsTr("Queues")
        font.weight: Font.DemiBold
        anchors {
            top: parent.top
            left: basicParametersCustomLabel.right
            margins: 10
            leftMargin: 50
        }
    }

    RectDivider {
        id: rectDivider2
        width: 450
        anchors {
            top: basicParametersCustomLabel.bottom
            left: basicParametersCustomLabel.right
            leftMargin: 50
            topMargin: 5
        }
    }

    QueueParameter {
        id: queueParameter
        anchors {
            top: rectDivider2.bottom
            left: basicParametersCustomLabel.right
            leftMargin: 50
            topMargin: 5
        }
    }

    /* Queues list */
    CustomLabel {
        id: queuesListCustomLabel
        text: qsTr("Queues' list")
        font.weight: Font.DemiBold
        anchors {
            top: queueParameter.bottom
            left: parent.left
            margins: 10
            topMargin: -25
        }
    }

    RectDivider {
        id: rectDivider3
        width: 750
        anchors {
            top: queuesListCustomLabel.bottom
            left: parent.left
            leftMargin: 10
            topMargin: 5
        }
    }

    QueuesList {
        id: queuesList
        width: 750
        height: 307
        anchors {
            top: rectDivider3.bottom
            left: parent.left
            margins: 10
            topMargin: 2
        }
    }

    CustomButton {
        id: startButton
        height: 40
        textLabel: qsTr("Start")
        anchors {
            bottom: parent.bottom
            left: parent.left
            margins: 20
            bottomMargin: 50
        }
        onClicked: {
            simulationPresenter.startSimulation(throughputCustomInput.textValue, durationCustomInput.textValue)
        }
    }

    /* Layer visible during simulation */

    WaitingLayer {
        z: parent.parent.z + 50
        visible: simulationPresenter.simulationInProgress ? true : false
        opacity: simulationPresenter.simulationInProgress ? 0.6 : 0.0
    }
}
