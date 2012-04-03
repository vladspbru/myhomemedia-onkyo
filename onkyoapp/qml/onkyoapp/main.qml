import QtQuick 1.1
import vx.home.qmlcomponents 1.0
import "contents"

Rectangle {
    id:window
    width: 400; height: 600

    property Onkyo device : Onkyo {
//        addr:"10.0.2.15"
        port: 60128
        onConnectChanged: {
            console.debug("connect changed = " + connected);
            if(connected)
                device.query_all_parameters_state();
        }
    }

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
        id: cmdDelegate
    }


    ListView{
        id: lisView
        anchors.fill: parent
        anchors.margins: 4
        model: cmdModel      //model: CommandsModel{}
        delegate: cmdDelegate
    }

    ScrollBar{
        scrollArea: lisView
        height: lisView.height
        width: 8
        anchors.right: lisView.right
    }

    LinkIndicator{
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        height: 70; width: 70;
        on: device.connected
        onClicked: device.connected = device.connected ? false : true;
    }

    Component.onCompleted: {
        device.connected=true;
    }
}
