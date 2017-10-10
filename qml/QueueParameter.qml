import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    width: 450
    height: 130
    color: "#f9f9f9"

    CustomLabel {
        id: lambdaLabel
        text: qsTr("Lambda")
        anchors {
            left: parent.left
            top: parent.top
        }
    }
    CustomInput {
        id: lambdaInput
        width: 100
        height: 23
        anchors {
            left: lambdaLabel.right
            leftMargin: 20
            top: parent.top
        }
    }

    CustomLabel {
        id: lambdaUnit
        text: "[1/s]"
        anchors {
            left: lambdaInput.right
            leftMargin: 5
            top: parent.top
        }
    }

    CustomLabel {
        id: avgSizeLabel
        text: qsTr("Avg size")
        anchors {
            right: avgSizeInput.left
            rightMargin: 30
        }
    }
    CustomInput {
        id: avgSizeInput
        width: 100
        height: 23
        anchors {
            right: avgSizeUnit.left
            rightMargin: 5
            top: parent.top
        }
    }

    CustomLabel {
        id: avgSizeUnit
        text: "[b]"
        anchors {
            right: parent.right
            top: parent.top
        }
    }

    CustomLabel {
        id: weightLabel
        text: qsTr("Weight")
        anchors {
            left: lambdaLabel.left
            top: lambdaLabel.bottom
            topMargin: 10
        }
    }

    CustomInput {
        id: weightInput
        width: 100
        height: 23
        anchors {
            left: lambdaInput.left
            top: weightLabel.top
        }
    }

    QuestionIcon {
        id: weightQuestion
        textInCloud: qsTr("Importance of that queue")
        anchors {
            top: weightLabel.top
            left: weightInput.right
            leftMargin: 5
        }
    }

    CustomLabel {
        text: qsTr("Buffor size")
        anchors {
            left: avgSizeLabel.left
            top: weightLabel.top
        }
    }

    CustomInput {
        id: bufforSizeInput
        width: 100
        height: 23
        anchors {
            top: weightLabel.top
            right: avgSizeInput.right
        }
    }

    QuestionIcon {
        id: bufforSizeQuestion
        textInCloud: qsTr("Number of packets")
        anchors {
            top: weightLabel.top
            left: bufforSizeInput.right
            leftMargin: 5
        }
    }

    CustomLabel {
        id: queuesNameLabel
        text: qsTr("Queue's name")
        anchors {
            left: lambdaLabel.left
            top: weightLabel.bottom
            topMargin: 10
        }
    }

    CustomInput {
        id: queuesNameInput
        textValue: "Default1"
        width: 140
        height: 23
        validateInt: false
        anchors {
            left: queuesNameLabel.right
            leftMargin: 20
            top: queuesNameLabel.top
        }
    }

    CustomButton {
        id: addQueueButton
        textLabel: qsTr("Add")
        anchors {
            right: parent.right
            top: queuesNameLabel.top
        }
        onClicked: {
            var queueArguments = [queuesNameInput.textValue, lambdaInput.textValue,
                                  avgSizeInput.textValue, weightInput.textValue,
                                  bufforSizeInput.textValue];
            simulationPresenter.addQueue(queueArguments)
        }
    }
}
