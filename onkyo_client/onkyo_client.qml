import QtQuick 1.1

Rectangle {
    width: 100
    height: 62

    Onkyo {
        id:onky
        addr:"10.0.2.15"
        port:60128
        onConnectChanged:{
            console.log("Connect=" + connected)
        }

        parameters: [
            OnkyoParameter {
                id: power
                nik: "PWR"
                value: "???"
                onValueChanged: {
                    console.log( "value changed=" + value )
                }
            }
        ]
    }

    Component.onCompleted: {
        onky.query_parameters_state()
    }

}
