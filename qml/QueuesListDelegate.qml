import QtQuick 2.0

Rectangle {
    id: mainRectangle

    property double lambdaTextRealWidth: 0
    property double avgSizeTextRealWidth: 0
    property double weightTextRealWidth: 0
    property double bufforSizeTextRealWidth: 0

    signal clicked(var delegateItem)

    width: 750
    height: 45
    color: "#e5e5e5"

    Text {
        text: name
        width: 220
        elide: Text.ElideRight
        anchors {
            verticalCenter: parent.verticalCenter
            left: mainRectangle.left
            leftMargin: 10
        }
    }

    ListTextItem {
        id: lambdaItem
        textValue: lambda
        width: lambdaTextRealWidth
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 250
        }
    }

    Text {
        id: dividerItem1
        text: "|"
        anchors {
            verticalCenter: parent.verticalCenter
            left: lambdaItem.right
            leftMargin: 10
        }
    }

    ListTextItem {
        id: avgSizeItem
        textValue: avgSize
        width: avgSizeTextRealWidth
        anchors {
            verticalCenter: parent.verticalCenter
            left: dividerItem1.right
            leftMargin: 10
        }
    }

    Text {
        id: dividerItem2
        text: "|"
        anchors {
            verticalCenter: parent.verticalCenter
            left: avgSizeItem.right
            leftMargin: 10
        }
    }

    ListTextItem {
        id: weightItem
        textValue: weight
        width: weightTextRealWidth
        anchors {
            verticalCenter: parent.verticalCenter
            left: dividerItem2.right
            leftMargin: 10
        }
    }

    Text {
        id: dividerItem3
        text: "|"
        anchors {
            verticalCenter: parent.verticalCenter
            left: weightItem.right
            leftMargin: 10
        }
    }

    ListTextItem {
        id: bufforSizeItem
        textValue: bufforSize
        width: bufforSizeTextRealWidth
        anchors {
            verticalCenter: parent.verticalCenter
            left: dividerItem3.right
            leftMargin: 10
        }
    }

    Component.onCompleted: {
        timer.start()
    }

    Timer {
        id: timer
        interval: 500; repeat: false;
        onTriggered: {
            lambdaItem.width = lambdaTextRealWidth
            avgSizeItem.width = avgSizeTextRealWidth
            weightItem.width = weightTextRealWidth
            bufforSizeItem.width = bufforSizeTextRealWidth
        }
    }

    /* TOP AND BOTTOM BORDERS */

    RemoveIcon {
        anchors {
            right: parent.right
            rightMargin: 30
            verticalCenter: parent.verticalCenter
        }
        onClicked: {
            mainRectangle.clicked(parent)
        }
    }

    Rectangle {
        width: 750
        height: 2
        color: "#f9f9f9"
        anchors {
            top: parent.top
            left: parent.left
        }
    }

    Rectangle {
        width: 750
        height: 2
        color: "#f9f9f9"
        anchors {
            top: parent.bottom
            left: parent.left
        }
    }
}
