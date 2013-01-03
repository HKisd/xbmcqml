// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
Page {
    tools:     ToolBarLayout {
        id: mainTools
        visible: true

        ToolIcon {
            platformIconId: "toolbar-back"
            anchors.left: (parent === undefined) ? undefined : parent.left
            onClicked: appWindow.pageStack.pop()
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
    property int ws_2: (width-h_spacing)/2
    property int w_3: width/3
    property int ws_3: (width-2*h_spacing)/3
    property int w_4: width/4
    property int ws_4: (width-3*h_spacing)/4

    Column {
        id: topButtons2
        width: parent.width
        height: parent.height / 2
        anchors.top: parent.top
        spacing: 10
        Button { width: w_3; text: "Off"; id: boff;        anchors {
                horizontalCenter: parent.horizontalCenter
            }
            onClicked: xbmcHttp.activateWindow("shutdownmenu")}
        Row {
            width: parent.width
            visible: true
            Button { height: b1_height; width: w_4; text: "Movies"
                onClicked: xbmcHttp.activateWindow("videos") }
            Button { height: b1_height; width: w_4; text: "Music"
                onClicked: xbmcHttp.activateWindow("music")}
            Button { height: b1_height; width: w_4; text: "Pics"
                onClicked: xbmcHttp.sendAction("pictures")}
            /*Button { height: b1_height; width: w_4; text: "Progs"
                onClicked: xbmcHttp.sendAction("programs")}*/
            Button { height: b1_height; width: w_4; text: "GetVol"
                onClicked: xbmcHttp.getProperty("volume")}
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
            id: playButtons2
            width: parent.width
            spacing: h_spacing
            Button { height: b2_height; width: ws_3; text: "<"
                onClicked: xbmcHttp.sendAction("stepback")}
            Button { height: b2_height; width: ws_3; text: "Play"
                onClicked: xbmcHttp.sendAction("play")}
            Button { height: b2_height; width: ws_3; text: ">"
                onClicked: xbmcHttp.sendAction("stepforward")}
        }
        Row {
            id: stopButtons2
            width: parent.width
            spacing: h_spacing
            Button { height: b2_height; width: ws_4; text: "|<<"
                onClicked: xbmcHttp.sendAction("bigstepback")}
            Button { height: b2_height; width: ws_4; text: "Stop"
                onClicked: xbmcHttp.sendAction("stop")}
            Button { height: b2_height; width: ws_4; text: "||"
                onClicked: xbmcHttp.sendAction("playpause")}
            Button { height: b2_height; width: ws_4; text: ">>|"
                onClicked: xbmcHttp.sendAction("bigstepforward")}
        }
        Row {
            id: ampButtons2
            width: parent.width
            spacing: h_spacing
            Button { height: b2_height; width: ws_2; text: "VolAmp-"
                onClicked: xbmcHttp.sendAction("volampdown")}
            Button { height: b2_height; width: ws_2; text: "VolAmp+"
                onClicked: xbmcHttp.sendAction("volampup")}
        }
        Label {
            text: "Volume: " + volSlider.value
        }
        Slider {
            id: volSlider
            width: parent.width
            minimumValue: 0
            maximumValue: 100
            value: xbmcHttp.getVolume();
            stepSize: 1
            valueIndicatorVisible: true
            onValueChanged: {console.log(value); xbmcHttp.setVolume(value)}
        }
    }

}
