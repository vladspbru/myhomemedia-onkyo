import QtQuick 1.1

Image {
    id: container
    property bool on: true

    source: container.on ? "images/sun.png" : "images/busy.png";

    NumberAnimation on rotation {
        running: !container.on; from: 0; to: 360; loops: Animation.Infinite; duration: 1200
    }
}
