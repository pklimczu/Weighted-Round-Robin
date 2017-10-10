import QtQuick 2.7

Item {
    id: queuesListItem

    /* HEADER */

    Rectangle {
        id: queuesHeaderRectangle
        width: 750
        height: 20
        color: "#f2f2f2"
        anchors {
            top: queuesListItem.top
            left: parent.left
        }

        HeaderTextItem {
            id: nameTextItem
            textValue: qsTr("name")
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 20
            }
        }

        HeaderTextItem {
            id: lambdaTextItem
            textValue: qsTr("lambda")
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 250
            }
        }

        HeaderTextItem {
            id: dividerTextItem1
            textValue: "|"
            anchors {
                verticalCenter: parent.verticalCenter
                left: lambdaTextItem.right
                leftMargin: 10
            }
        }

        HeaderTextItem {
            id: avgSizeTextItem
            textValue: qsTr("avg size")
            anchors {
                verticalCenter: parent.verticalCenter
                left: dividerTextItem1.right
                leftMargin: 10
            }
        }

        HeaderTextItem {
            id: dividerTextItem2
            textValue: "|"
            anchors {
                verticalCenter: parent.verticalCenter
                left: avgSizeTextItem.right
                leftMargin: 10
            }
        }

        HeaderTextItem {
            id: weightTextItem
            textValue: qsTr("weight")
            anchors {
                verticalCenter: parent.verticalCenter
                left: dividerTextItem2.right
                leftMargin: 10
            }
        }

        HeaderTextItem {
            id: dividerTextItem3
            textValue: "|"
            anchors {
                verticalCenter: parent.verticalCenter
                left: weightTextItem.right
                leftMargin: 10
            }
        }

        HeaderTextItem {
            id: bufforSizeTextItem
            textValue: qsTr("buffor size")
            anchors {
                verticalCenter: parent.verticalCenter
                left: dividerTextItem3.right
                leftMargin: 10
            }
        }

        HeaderTextItem {
            id: removeTextItem
            textValue: qsTr("remove")
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: 20
            }
        }
    }

    /* LIST */

    ListView {
        id: listView
        clip: true
        width: 750
        height: 285
        anchors {
            top: queuesHeaderRectangle.bottom
            left: parent.left
        }


        delegate: QueuesListDelegate {
            lambdaTextRealWidth: lambdaTextItem.realWidth
            avgSizeTextRealWidth: avgSizeTextItem.realWidth
            weightTextRealWidth: weightTextItem.realWidth
            bufforSizeTextRealWidth: bufforSizeTextItem.realWidth

            onClicked: {
                console.log(delegateItem)
            }
        }

        model: simulationPresenter.queueList

            /*ListModel {
            ListElement {
                name: "First queue"
                lambda: "230"
                avgSize: "200"
                weight: "200"
                bufforSize: "50"
            }

            ListElement {
                name: "Second queue"
                lambda: "230"
                avgSize: "200"
                weight: "200"
                bufforSize: "50"
            }

            ListElement {
                name: "My favorite queue"
                lambda: "230"
                avgSize: "200"
                weight: "200"
                bufforSize: "50"
            }

            ListElement {
                name: "Some long string to check how does it work"
                lambda: "230"
                avgSize: "200"
                weight: "200"
                bufforSize: "50"
            }
        }*/

//        MouseArea {
//            anchors.fill: parent
//            preventStealing: true
//            propagateComposedEvents: true
//            onClicked: {
//                console.log(mouseX, mouseY)
//            }
//        }
    }

    /* FOOTER */

    Rectangle {
        id: queuesFooterRectangle
        width: 750
        height: 2
        color: "#636363"
        anchors {
            bottom: queuesListItem.bottom
            left: parent.left
            topMargin: 0
        }
    }
}
