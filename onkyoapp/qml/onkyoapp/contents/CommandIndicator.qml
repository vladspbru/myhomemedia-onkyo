import QtQuick 1.0

Image {
    id: container
    signal clicked

    source: "images/face-smile.png";
    smooth: true

    MouseArea {
        id:mouse
        anchors.fill: parent
        onClicked: container.clicked()
    }

    NumberAnimation on rotation { running: mouse.pressed; from: 0; to: 360; duration: 70 }
}
