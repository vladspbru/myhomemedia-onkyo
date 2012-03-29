import QtQuick 1.1


Component{
    Item {
        width: parent.width; height: 20

        CommandIndicator{
            anchors.verticalCenter: parent.verticalCenter
            on: { subcode=="QSTN" }
            onClicked: {
                console.debug(code+subcode+" clicked")
                window.device.cmd(code+subcode)
            }
        }
        Text {
            x: 60
            text: subcode
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            font.pointSize: 10
        }

        Text {
            x: 160
            text: means
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            font.italic: true
            font.pointSize: 10
        }


    }
}
