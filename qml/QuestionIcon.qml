import QtQuick 2.7

Rectangle {
    property int posX: 0
    property int posY: 0
    property string textInCloud: "none text is given"

    width: 15
    height: 15
    radius: 3
    z: 100

    color: "#ffda7f"
    Text {
        text: "?"
        anchors {
            centerIn: parent
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onHoveredChanged: {
            if (containsMouse) {
                calculatPosHelpfulCloud(mouseX, mouseY);
                helpfulCloud.state = "visible"
            } else {
                helpfulCloud.state = "hidden"
            }
        }
    }

    Rectangle {
        id: helpfulCloud
        width: 100
        height: textInHelpfulCloud.paintedHeight + 2 * textInHelpfulCloud.anchors.margins
        color: "#ffda7f"
        radius: 10
        x: posX
        y: posY
        z: 100
        state: "hidden"

        states: [
            State {
                name: "hidden"
                PropertyChanges { target: helpfulCloud; opacity: 0.0 }
            },
            State {
                name: "visible"
                PropertyChanges { target: helpfulCloud; opacity: 1.0 }
            }
        ]

        transitions: [
            Transition {
                from: "hidden"
                to: "visible"
                NumberAnimation { target: helpfulCloud; properties: "opacity"; duration: 200 }
            }
        ]

        Text {
            id: textInHelpfulCloud
            text: textInCloud
            wrapMode: Text.WordWrap
            font.pixelSize: 10
            anchors {
                fill: parent
                margins: 5
            }
        }
    }

    function calculatPosHelpfulCloud(mouseX, mouseY)
    {
        var globalPosition = mapToItem(appWindow.contentItem, mouseX, mouseY)
        posX = (globalPosition.x + helpfulCloud.width > appWindow.width) ? (mouseX - helpfulCloud.width)
                                                                         : mouseX
        posY = mouseY - helpfulCloud.height
    }
}
