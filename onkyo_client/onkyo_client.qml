import QtQuick 1.1

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

    Onkyo {
	id:onky
	addr:"10.0.2.15"
	port:60128
	onConnectChanged:{
	    console.log("Connect Changed")    
	}
    }
	OnkyoParameter {
	    id: param
//	    nik: "PWD"
//	    value: "empty..."
	    
	}  
    
    function readValues( anObject) {
              for (var prop in anObject) {
                  console.log("Object item:", prop, "=", anObject[prop])
              }
    }
    
    Component.onCompleted: {
//         mousearea.clicked.connect( param.query_status )
	 readValues(param)
    }
  
}
