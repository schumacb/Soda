import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import QtQuick.Controls.Styles 1.4

import Qt.labs.settings 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    menuBar: MenuBar {
        id: mainMenu
        Menu {
            id: fileMenu
            title: qsTr("&File")
            MenuItem { action: quitAction }
            MenuSeparator {}
            MenuItem { action: reloadQmlAction }
        }
        Menu {
            id: extrasMenu
            title: qsTr("&Extras")
            MenuBarItem {action: openSettingsDialogAction}
//        }

//        Menu {
//            id: helpMenu
//            title: qsTr("&Help")
            MenuItem { action: openAboutDialogAction }
        }
    }

    Settings {
        id: settings
        property string style: "fusion"
    }

    ApplicationWindow {
        id: settingsDialog
        title: qsTr("Settings")
        width: settingsDialogForm.implicitWidth
        height: 500
        Rectangle {
            anchors.fill: parent
            ScrollView {
                clip: true
                ColumnLayout {
                    id: settingsDialogForm
                    anchors.fill: parent
                    GroupBox {
                        Layout.fillWidth: true
                        title: qsTr("Apearance")
                        ColumnLayout {
                            anchors.fill: parent
                            GridLayout{
                                Layout.fillWidth: true
                                columns: 2
                                Text {
                                    text: qsTr("Style: ")
                                }

                                ComboBox {
                                    Layout.alignment: Qt.AlignRight
                                    property int styleIndex: -1
                                    model: availableStyles
                                    Component.onCompleted: {
                                        styleIndex = find(settings.style, Qt.MatchFixedString)
                                        if (styleIndex !== -1)
                                        {
                                            currentIndex = styleIndex
                                        }
                                    }
                                    onCurrentTextChanged: {
                                        console.log("settings.style=" + currentText)
                                        settings.style = currentText
                                    }
                                }
                            }
                            Text {
                                text: qsTr("Changing the style requires a restart.")
                            }

                        }
                    }
                }
            }
        }
    }

    ApplicationWindow{

        id: aboutDialog
        width: aboutDialogForm.implicitWidth+20
        height: aboutDialogForm.implicitHeight+20
        Rectangle {
            anchors.fill: parent
            ScrollView {
                clip: true
                x: Math.max(0.5*(parent.width - aboutDialogForm.implicitWidth), 0)
                width: Math.min(aboutDialogForm.implicitWidth, parent.width)
                height: parent.height
                ColumnLayout {
                    id: aboutDialogForm
                    Image {
                        id: logo
                        antialiasing: true
                        smooth: true
                        fillMode: Image.PreserveAspectFit
                        source: "images/robotik-logo.svg"
                    }

                    ToolSeparator {
                        id: toolSeparator
                        Layout.fillWidth: true
                        orientation: Qt.Horizontal
                    }

                    Text {
                        id: applicationName
                        text: qsTr("Soda - Simple object detection application")
                        font {
                            bold: true
                            pixelSize: 12
                        }
                        Layout.fillWidth: true
                    }
                    Grid {
                        id: info
                        Layout.fillWidth: true
                        Layout.topMargin: 5
                        Layout.leftMargin: 5
                        spacing: 0
                        columns: 2
                        rowSpacing: 10
                        columnSpacing: 10
                        Label {
                            text: "Version:"
                        }
                        Label {
                            id: versionLabel
                            text: "1.0.1"
                        }
                        Label {
                            text: "Licence:"
                        }
                        Label {
                            id: licenceLabel
                            text: "LGPLv3"
                        }
                        Label {

                            text: "Authors:"
                        }
                        Label {
                            id: authorsLabel
                            text: "Bastian Schumacher"
                        }
                        Label {
                            text: "Distributor:"
                        }
                        Label {
                            id: distributorLabel
                            text: "Hochschule Trier"
                        }
                        Label {
                            text: "Website:"
                        }
                        Label {
                            id: websiteLabel
                            text: "http://www.Hochschule-Trier.de"
                        }
                    }

                    ToolSeparator {
                        id: toolSeparator1
                        orientation: Qt.Horizontal
                        Layout.fillWidth: true
                    }

                    GroupBox {
                        id: resources
                        title: "Used Libraries and Resources:"
                        Layout.fillWidth: true
                        Column {
                            spacing: 5
                            anchors.fill: parent
                            ResourcePanel {
                                id: resourcePanel
                                anchors.left: parent.left
                                anchors.right: parent.right
                                title: "OpenCV:"
                                licence.text: "BSD"
                                website.text: "http://opencv.org"
                            }
                            ResourcePanel {
                                id: resourcePanel1
                                anchors.left: parent.left
                                anchors.right: parent.right
                                title: "Qt:"
                                licence.text: "LGPL"
                                website.text: "http://qt.io"
                            }
                            ResourcePanel {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                title: "Silk Icons:"
                                licence.text: "Creative Commons Attribution 2.5"
                                website.text: "http://www.famfamfam.com/lab/icons/silk"
                            }
                        }
                    }
                }
            }
        }
    }

    Action {
        id: reloadQmlAction
        text: qsTr("DEBUG &Reload Qml")
        onTriggered: {
            console.log("reload qml")
            application.load()
            mainWindow.close()
        }
    }
    Action {
        id: quitAction
        icon {
            source: "icons/door_out.png"
        }
        text: qsTr("E&xit")
        onTriggered: Qt.quit()
    }
    Action {
        id: openAboutDialogAction
        icon {
            source: "icons/information.png"
        }
        text: qsTr("&About Soda")
        onTriggered: aboutDialog.show()
    }
    Action {
        id: openSettingsDialogAction
        icon {
            source: "icons/cog.png"
        }
        text: qsTr("&Settings")
        onTriggered: settingsDialog.show()
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
