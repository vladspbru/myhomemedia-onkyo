import QtQuick 1.0

Image {
    id: container
    property bool on: false
    signal clicked

    source: "images/handle.png";
    rotation: 180
    scale: 0.4
    smooth: true

    visible: container.on


    MouseArea {
        id:mouse
        anchors { fill: parent; leftMargin: -10; topMargin: -10; rightMargin: -10; bottomMargin: -10  }
        onClicked: container.clicked()
    }

    NumberAnimation on rotation { running: mouse.pressed; from: 0; to: 180; duration: 50 }
}
