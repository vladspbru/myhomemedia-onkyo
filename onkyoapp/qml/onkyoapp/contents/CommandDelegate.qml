import QtQuick 1.1
import vx.home.qmlcomponents 1.0


Component{
    Item {
        id: container
        property OnkyoParameter parameter: window.device.getParameter( code )

        width: parent.width; height: 44

        Rectangle {
            id: rectangle1
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
                anchors { fill: parent; leftMargin: 8; topMargin: 4; rightMargin: 8; bottomMargin: 4  }
                spacing: 2

                Row{
                    id: row1
                    spacing: 12
                    Text {
                        id: txt1
                        text: code
                        color: "white"
                        font.bold: true
                        font.pointSize: 10
                        font.underline: true
                    }
                    Text {
                        id: txt2
                        text: title
                        color: "white"
                        font.bold: true
                        font.pointSize: 10
                    }

                }

                Row{
                    id: row2
                    height: 15
                    CommandIndicator{
                        height: parent.height
                        width: height
                        fillMode: Image.Stretch
                        onClicked: {
                            console.debug( code + subcode + " clicked" )
                            container.parameter.cmd( subcode )
                        }
                    }

                    Text {
                        text: container.parameter.value
                        color: "white"
                        font.pointSize: 8
                    }
                }


            }
        }
        Component.onCompleted: {
            if(!container.parameter.value)
                if(window.device.connected)
                    container.parameter.query_state()
            console.log( "create parameter: " + code + ",  val: " + container.parameter.value  )
        }
    }
}
