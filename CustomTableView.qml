import QtQuick 2.7
import QtQuick.Controls 2.2

ListView {
    id: listView

    contentWidth: headerItem.width
    flickableDirection: Flickable.VerticalFlick
    preferredHighlightEnd: ListView.StrictlyEnforceRange

    headerPositioning: ListView.OverlayHeader
    header: Row {
        spacing: 1
        function itemAt(index) { return repeater.itemAt(index) }
        Repeater {
            id: repeater
            model: [qsTr("Name"), qsTr("Lambda"), qsTr("Avg size"), qsTr("Weight"), qsTr("Bufor size")]
            Label {
                text: modelData
                font.bold: true
                font.pixelSize: 13
                padding: 5
                background: Rectangle { color: "silver" }
            }
        }
    }

    model: 100
    delegate: Column {
        id: delegate
        property int row: index
        Row {
            spacing: 1
            Repeater {
                model: 5
                ItemDelegate {
                    property int column: index
                    text: qsTr("%1x%2").arg(delegate.row).arg(column)
                    width: listView.headerItem.itemAt(column).width
                }
            }
        }
        Rectangle {
            color: "silver"
            width: parent.width
            height: 1
        }
    }

    ScrollIndicator.horizontal: ScrollIndicator { }
    ScrollIndicator.vertical: ScrollIndicator { }

}
