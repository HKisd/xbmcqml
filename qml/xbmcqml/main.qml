import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    initialPage: mainPage

    MainPage {
        id: mainPage
    }
    SettingsPage {
        id: settingsPage
    }
    AboutPage {
        id: aboutPage
    }
    AddPage {
        id: addPage
    }
/*
    ToolBarLayout {
        id: commonTools
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
*/


    Menu {
        id: myMenu
        visualParent: pageStack
        width: 300; height: 300


        MenuLayout {
            MenuItem { text: qsTr(xbmcHttp.getNameByIdx(0)); onClicked: xbmcHttp.setActive(0) }
            MenuItem { text: qsTr(xbmcHttp.getNameByIdx(1)); onClicked: xbmcHttp.setActive(1) }
            MenuItem { text: qsTr("Settings"); onClicked: appWindow.pageStack.push(settingsPage) }
            MenuItem { text: qsTr("About"); onClicked: appWindow.pageStack.push(aboutPage) }
        }
    }
}
