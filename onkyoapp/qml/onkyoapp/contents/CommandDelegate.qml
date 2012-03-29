import QtQuick 1.1


Component{

    Item {
        width: parent.width; height: 44
        Rectangle {
            width: parent.width
            height: 40
            clip: true
            radius: 8
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#505060"
                }

                GradientStop {
                    position: 1
                    color: "#afd1db"
                }
            }
            smooth: true
            border.color: "#8080b0"


            Column {
                id: column1
                anchors.fill: parent
                anchors.bottomMargin: 4
                anchors.topMargin: 4
                anchors.rightMargin: 8
                anchors.leftMargin: 8
                spacing: 4
                Text {
                    id: txt1
                    text: section
                    color: "white"
                    font.bold: true
                    font.pointSize: 10
                    font.underline: true
                }
                Text {
                    text: window.device.takeParameter("PWR").value
                    anchors.left: txt1.right
                    color: "white"
                    font.pointSize: 8
                }


            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                }

            }
        }
    }
}
