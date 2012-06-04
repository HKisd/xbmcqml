import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    tools: commonTools
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
            onClicked: xbmcHttp.sendKey("0xf053")}
        Row {
            width: parent.width
            visible: true
            Button { height: b1_height; width: w_4; text: "Subs"
                onClicked: xbmcHttp.sendKey("0xf04c") }
            Button { height: b1_height; width: w_4; text: "Zoom"
                onClicked: xbmcHttp.sendKey("0xf05a")}
            Button { height: b1_height; width: w_4; text: "Full"
                onClicked: xbmcHttp.sendKey("0xf009")}
            Button { height: b1_height; width: w_4; text: "Watched"
                onClicked: xbmcHttp.sendKey("0xf057")}
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

        Row {
            width: parent.width
            spacing: h_spacing
            Button { height: b2_height; width: ws_3; text: "<<"
                onClicked: xbmcHttp.sendKey("0xf052")}
            Button { height: b2_height; width: ws_3; text: "Play"
                onClicked: xbmcHttp.sendKey("256")}
            Button { height: b2_height; width: ws_3; text: ">>"
                onClicked: xbmcHttp.sendKey("0xf046")}
        }
        Row {
            width: parent.width
            spacing: h_spacing
            Button { height: b2_height; width: ws_4; text: "|<"
                onClicked: xbmcHttp.sendKey("0xf05d")}
            Button { height: b2_height; width: ws_4; text: "Stop"
                onClicked: xbmcHttp.sendKey("257")}
            Button { height: b2_height; width: ws_4; text: "||"
                onClicked: xbmcHttp.sendKey("256")}
            Button { height: b2_height; width: ws_4; text: ">|"
                onClicked: xbmcHttp.sendKey("0xf05b")}
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
            Button { height: b3_height; width: ws_3; text: "Title"
            onClicked: xbmcHttp.sendKey("0xf04f")}
            Button { height: b3_height; width: ws_3;
                Text {text: "⇧"
                    anchors.centerIn:parent
                    font.pointSize: 80
                }
                onClicked: xbmcHttp.sendKey("270")
            }
            Button { height: b3_height; width: ws_3; text: "Info"
                onClicked: xbmcHttp.sendKey("0xf049")}
        }
        Row {
            width: parent.width
            spacing: h_spacing
            Button { height: b3_height; width: ws_3;  Text {text: "⇦"
                    anchors.centerIn:parent;font.pointSize: 80
                }
                onClicked: xbmcHttp.sendKey("272")
            }
            Button { height: b3_height; width: ws_3;
                     text: "OK"; onClicked: xbmcHttp.sendKey("256")}
            Button { height: b3_height; width: ws_3; Text {text: "⇨"
                    anchors.centerIn:parent
                    font.pointSize: 80
                }
                onClicked: xbmcHttp.sendKey("273")
            }
        }
        Row {
            width: parent.width
            spacing: h_spacing
            Button { height: b3_height; width: ws_3; text: "Menu";
                     onClicked: xbmcHttp.sendKey("274")}
            Button { height: b3_height; width: ws_3; Text {text: "⇩"
                    anchors.centerIn:parent
                    font.pointSize: 80
                   }
                   onClicked: xbmcHttp.sendKey("271")}
            Button { height: b3_height; width: ws_3; text: "Back";
                   onClicked: xbmcHttp.sendKey("275")}
        }
        Rectangle{
            width: parent.width
            height: 10
            color: "#000000ff"
        }
    }
}

