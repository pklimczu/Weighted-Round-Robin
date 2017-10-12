import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import SimulationPresenter 1.0

ApplicationWindow {
    property QtObject simulationPresenter: SimulationPresenter {}

    id: appWindow
    visible: true
    width: 800
    height: 630
    title: qsTr("Hello World")
    color: "#f9f9f9"

    header: Header {}

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        interactive: false

        Page {
            title: "HOW DOES IT WORK"
        }

        Page {
            MainView { }
        }

        Page {
            title: "RESULTS"
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.margins: 0
        contentHeight: 30

        CustomTabButton {
            textValue: qsTr("How does it work?")
            orderNumber: 0
            currentIndex: tabBar.currentIndex
        }

        CustomTabButton {
            textValue: qsTr("Main view")
            orderNumber: 1
            currentIndex: tabBar.currentIndex
        }

        CustomTabButton {
            textValue: qsTr("Results")
            orderNumber: 2
            currentIndex: tabBar.currentIndex
            enabled: false
        }
    }

}
