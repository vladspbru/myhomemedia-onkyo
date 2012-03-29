import QtQuick 1.1
import vx.home.qmlcomponents 1.0
import "contents"

Rectangle {
    id:window
    width: 500; height: 400

    property variant device : Onkyo {
            addr:"10.0.2.15"
            port: 60128
            onConnectChanged: {
                console.debug("connect changed = " + connected)
            }
    }

    property bool connected: device.connected

    XmlListModel {
        id:cmdModel
        source: "contents/commandsNR609.xml"
        query: "/commands/command"
        XmlRole{ name: "code";      query: "code/string()" }
        XmlRole{ name: "title";     query: "title/string()" }
        XmlRole{ name: "subcode";   query: "subcode/string()"  }
        XmlRole{ name: "means";     query: "means/string()"  }
    }

    CommandDelegate{
        id: sectionHeading
    }
    SubCommandDelegate{
        id: cmdDelegate
    }

    Component {
        id: highlight
        Rectangle {
            color: "lightsteelblue"; radius: 3
            y: lisView.currentItem.y
            width: lisView.currentItem.width; height: lisView.currentItem.height
            Behavior on y {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
        }
    }

    ListView{
        id: lisView
        anchors.fill: parent
        anchors.margins: 4
        model: cmdModel
        //        model: CommandsModel{}
        delegate:  cmdDelegate

        section.property: "title"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading

        highlight: highlight
        highlightFollowsCurrentItem: false
        focus: true
    }

    ScrollBar{
        scrollArea: lisView
        height: lisView.height
        width: 8
        anchors.right: lisView.right
    }

}
