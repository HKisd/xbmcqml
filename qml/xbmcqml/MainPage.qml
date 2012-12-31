import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    tools:     ToolBarLayout {
        id: mainTools
        visible: true

        ToolIcon {
            platformIconId: "toolbar-select-text"
            anchors.right: (parent === undefined) ? undefined : parent.center
            onClicked: {
                bottomButtons.visible = false
                playButtons.visible = false
                stopButtons.visible = false
                inputText.text = ""
                texti.visible = true
                inputText.forceActiveFocus()
                inputText.openSoftwareInputPanel()
            }
        }

        ToolIcon {
            platformIconId: "toolbar-next"
            anchors.right: (parent === undefined) ? undefined : parent.center
            onClicked: appWindow.pageStack.push(addPage)
        }

        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: (myMenu.status == DialogStatus.Closed) ? myMenu.open() : myMenu.close()
        }
    }
    orientationLock: PageOrientation.LockPortrait

    property int b1_height: height/10 //80
    property int b2_height: height/8 //100
    property int b3_height: height/7 //100
    property int h_spacing: 10
    property int w_3: width/3
    property int ws_3: (width-2*h_spacing)/3
    property int w_4: width/4
    property int ws_4: (width-3*h_spacing)/4

    Column {
        id: topButtons
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        spacing: 10
        Button { width: w_3; text: "Off"; id: boff;        anchors {
                horizontalCenter: parent.horizontalCenter
            }
            onClicked: xbmcHttp.activateWindow("shutdownmenu")}
        Row {
            width: parent.width
            visible: true
            Button { height: b1_height; width: w_4; text: "Subs"
                onClicked: xbmcHttp.sendAction("nextsubtitle") }
            Button { height: b1_height; width: w_4; text: "Audio"
                onClicked: xbmcHttp.sendAction("audionextlanguage")}
            Button { height: b1_height; width: w_4; text: "Full"
                onClicked: xbmcHttp.sendAction("fullscreen")}
            Button { height: b1_height; width: w_4; text: "CMenu"
                onClicked: xbmcHttp.sendKey("Input.ContextMenu")}
            /*Button { height: b1_height; width: w_4; text: "Watched"
                onClicked: xbmcHttp.sendKey("0xf057")}*/
            /*Button { height: b1_height; width: w_4; text: "Video"}
            Button { height: b1_height; width: w_4; text: "Music"}
            Button { height: b1_height; width: w_4; text: "Image"}
            Button { height: b1_height; width: w_4; text: "TV"}*/
        }

        Rectangle{
            width: parent.width
            height: 10
            color: "#000000ff"
        }

        Rectangle {
            id: texti
            visible: false
            width: parent.width
            height: b2_height
            TextInput {
                id: inputText

                color: "#888888"
                font.pixelSize: 40
                text: ""
                focus: true
                //activeFocusOnPress: false
                width: parent.width-16
                anchors.centerIn: parent

                onAccepted: {
                    xbmcHttp.sendText(inputText.text)
                    inputText.closeSoftwareInputPanel()
                    texti.visible = false
                    bottomButtons.visible = true
                    playButtons.visible = true
                    stopButtons.visible = true
                }
            }
        }

        Row {
            id: playButtons
            width: parent.width
            spacing: h_spacing
            Button { height: b2_height; width: ws_3; text: "<<"
                onClicked: xbmcHttp.sendAction("rewind")}
            Button { height: b2_height; width: ws_3; text: "Play"
                onClicked: xbmcHttp.sendAction("play")}
            Button { height: b2_height; width: ws_3; text: ">>"
                onClicked: xbmcHttp.sendAction("fastforward")}
        }
        Row {
            id: stopButtons
            width: parent.width
            spacing: h_spacing
            Button { height: b2_height; width: ws_4; text: "|<"
                onClicked: xbmcHttp.sendAction("previousscene")}
            Button { height: b2_height; width: ws_4; text: "Stop"
                onClicked: xbmcHttp.sendAction("stop")}
            Button { height: b2_height; width: ws_4; text: "||"
                onClicked: xbmcHttp.sendAction("playpause")}
            Button { height: b2_height; width: ws_4; text: ">|"
                onClicked: xbmcHttp.sendAction("nextscene")}
        }
    }
    Column {
        id: bottomButtons
        width: parent.width
        spacing: 10
        anchors.bottom: parent.bottom
        Row {
            width: parent.width
            spacing: h_spacing
            Button { height: b3_height; width: ws_3; text: "Home"
            //onClicked: xbmcHttp.sendKey("Input.ShowCodec")
                onClicked: xbmcHttp.sendKey("Input.Home")
            }
            Button { height: b3_height; width: ws_3;
                Text {text: "⇧"
                    anchors.centerIn:parent
                    font.pointSize: 80
                }
                onClicked: xbmcHttp.sendKey("Input.Up")
            }
            Button { height: b3_height; width: ws_3; text: "Info"
                onClicked: xbmcHttp.sendKey("Input.Info")}
        }
        Row {
            width: parent.width
            spacing: h_spacing
            Button { height: b3_height; width: ws_3;  Text {text: "⇦"
                    anchors.centerIn:parent;font.pointSize: 80
                }
                onClicked: xbmcHttp.sendKey("Input.Left")
            }
            Button { height: b3_height; width: ws_3;
                     text: "OK"; onClicked: xbmcHttp.sendKey("Input.Select")}
            Button { height: b3_height; width: ws_3; Text {text: "⇨"
                    anchors.centerIn:parent
                    font.pointSize: 80
                }
                onClicked: xbmcHttp.sendKey("Input.Right")
            }
        }
        Row {
            width: parent.width
            spacing: h_spacing
            Button { height: b3_height; width: ws_3; text: "Menu";
                     onClicked: xbmcHttp.sendKey("Input.ShowOSD")}
            Button { height: b3_height; width: ws_3; Text {text: "⇩"
                    anchors.centerIn:parent
                    font.pointSize: 80
                   }
                   onClicked: xbmcHttp.sendKey("Input.Down")}
            Button { height: b3_height; width: ws_3; text: "Back";
                   onClicked: xbmcHttp.sendKey("Input.Back")}
        }
        Rectangle{
            width: parent.width
            height: 10
            color: "#000000ff"
        }
    }
}

