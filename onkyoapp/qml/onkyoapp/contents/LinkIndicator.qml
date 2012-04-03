import QtQuick 1.1

Image {
    id: container
    property bool on: true
    signal clicked

    source: container.on ? "images/sun.png" : "images/busy.png";

    NumberAnimation on rotation {
        running: !container.on; from: 0; to: 360; loops: Animation.Infinite; duration: 1200
    }

    MouseArea {
        id:mouse
        anchors.fill: parent
        onClicked: container.clicked()
    }
}
