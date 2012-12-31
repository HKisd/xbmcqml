import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    tools:    ToolBarLayout {
            id: setTools
            visible: true
            ToolIcon {
                platformIconId: "toolbar-back"
                anchors.left: (parent === undefined) ? undefined : parent.left
                onClicked: appWindow.pageStack.pop()
            }}
    orientationLock: PageOrientation.LockPortrait

    Column {
        width: parent.width
        spacing: 10

        Rectangle {
            width: parent.width
            height: 30
            color: "#000000ff"
        }
        Text {
            id: label0
          //  anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("XBMC Server name")
            //font.pixelSize: 12
        }
        TextField {
            //anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            id: serverName
            text: xbmcHttp.getName();
        }
        Text {
            id: label1
          //  anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("XBMC HTTP Server (without http://)")
            //font.pixelSize: 12
        }
        TextField {
            //anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            id: serverAddr
            text: xbmcHttp.getAddr();
        }
        Text {
            id: label2
            //anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Server port")
            //font.pixelSize: 12
        }
        TextField {
            id: serverPort
            text: xbmcHttp.getPort();
            //inputMethodHints: ImhFormattedNumbersOnly
            //anchors.horizontalCenter: parent.horizontalCenter
        }
        Rectangle {
            width: parent.width
            height: 30
            color: "#000000ff"
        }

        Button {
            text: qsTr("Save")
            onClicked:{
                xbmcHttp.setName(serverName.text)
                xbmcHttp.setAddr(serverAddr.text)
                xbmcHttp.setPort(serverPort.text)
                xbmcHttp.saveSettings();
                connectStatus.text = "Saved"
                connectStatus.visible = true}
        }
        Text {
            id: connectStatus
            text: "Connected!"
            visible: false
            //anchors.horizontalCenter: parent.horizontalCenter
        }
    }

}
