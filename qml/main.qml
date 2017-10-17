import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import SimulationPresenter 1.0

ApplicationWindow {
    property QtObject simulationPresenter: SimulationPresenter {}

    id: appWindow
    visible: true
    maximumWidth: 800
    maximumHeight: 630
    minimumWidth: 800
    minimumHeight: 630
    title: qsTr("Weighted Round Robint - Event Simulation")
    color: "#f9f9f9"


    header: Header {}

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        interactive: false

        Page {
            HelpView { }
        }

        Page {
            MainView { }
        }

        Page {
            ResultsView { }
        }
    }

    Rectangle {
        id: errorRect
        width: parent.width
        height: 50
        color: "#f73b3b"
        opacity: simulationPresenter.showErrors ? 0.85 : 0.0
        anchors {
            centerIn: parent
        }

        Text {
            anchors.centerIn: parent
            text: simulationPresenter.listOfErrors
        }

        Text {
            anchors {
                right: parent.right
                top: parent.top
                margins: 5
                rightMargin: 10
            }
            text: "X"
            font.pixelSize: 15

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    simulationPresenter.showErrors = false
                }
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.margins: 0
        contentHeight: 30

        Component.onCompleted: {
            tabBar.currentIndex = 1
        }

        CustomTabButton {
            textValue: qsTr("How does it work?")
            orderNumber: 0
            currentIndex: tabBar.currentIndex
        }

        CustomTabButton {
            textValue: qsTr("Main view")
            orderNumber: 1
            currentIndex: tabBar.currentIndex
            width: 320
        }

        CustomTabButton {
            textValue: qsTr("Results")
            orderNumber: 2
            currentIndex: tabBar.currentIndex
            width: 320
        }
    }
}
