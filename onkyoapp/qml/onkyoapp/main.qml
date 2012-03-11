import QtQuick 1.1
import "contents"

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello Onkyo")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    BusyIndicator {
        scale: 0.6
        on: true
        anchors { right: parent.right; rightMargin: 10; verticalCenter: parent.verticalCenter }
    }
}
