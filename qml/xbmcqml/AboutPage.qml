import QtQuick 1.1
import com.nokia.meego 1.0
Page {
    tools: commonTools
    orientationLock: PageOrientation.LockPortrait
    Column {
        spacing: 10
        width: parent.width
        height: about1.height + about2.height + 10
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: about1
            width: parent.width
            text: "XBMC Remote controller made with QML"
            wrapMode: Text.Wrap
        }
        Text {
            id: about2
            text: "by Seppo Tomperi"
            wrapMode: Text.Wrap
        }
    }

}

