import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

ScrollView {
    property alias resourcePanel: resourcePanel
    anchors.fill: parent
    anchors.centerIn: parent
    ColumnLayout {
        id: columnLayout
        x: -2
        y: -2
        anchors.fill: parent
        anchors.margins: 10
        anchors.centerIn: parent
        Image {
            id: logo
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
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

        ColumnLayout {
            id: content
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                id: applicationName
                text: qsTr("Soda - Simple object detection application")
                font.bold: true
                font.pixelSize: 18
            }

            GridLayout {
                id: info
                Layout.fillWidth: true
                columns: 2
                anchors.margins: 10
                rowSpacing: 10
                columnSpacing: 10
                Label {
                    text: "Version:"
                }
                Label {
                    id: versionLabel
                    text: "1.0.0"
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

            GroupBox{
                id: resources
                Layout.fillWidth: true
                title: "Used Libraries and Resources:"

                ColumnLayout {
                    anchors.fill: parent
                    ResourcePanel {
                        id: resourcePanel
                        Layout.fillWidth: true
                        title: "OpenCV:"
                        licence.text: "BSD"
                        website.text: "http://opencv.org"
                    }
                    ResourcePanel {
                        Layout.fillWidth: true
                        title: "Qt:"
                        licence.text: "LGPL"
                        website.text: "http://qt.io"
                    }
                    ResourcePanel {
                        Layout.fillWidth: true
                        title: "Silk Icons:"
                        licence.text: "Creative Commons Attribution 2.5"
                        website.text: "http://www.famfamfam.com/lab/icons/silk"
                    }
                }
            }
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
