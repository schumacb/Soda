import QtQuick 2.4
import QtQuick.Controls 2.4

Item {
    anchors.fill: parent
    Column {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 10
        Image {
            id: logo
            anchors.left: parent.left
            anchors.right: parent.right
            antialiasing: true
            smooth: true
            fillMode: Image.PreserveAspectFit
            source: "images/robotik-logo.svg"
        }

        ToolSeparator {
            id: toolSeparator
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            orientation: Qt.Horizontal
        }

        GroupBox {
            id: applicationName
            anchors.right: parent.right
            anchors.rightMargin: 0
            title: qsTr("Soda - Simple object detection application")
            anchors.left: parent.left
            anchors.leftMargin: 0

            Grid {
                id: info
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10
                spacing: 0
                columns: 2
                anchors.margins: 10
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
        }
        ToolSeparator {
            id: toolSeparator1
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            orientation: Qt.Horizontal
        }

        GroupBox {
            id: resources
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            title: "Used Libraries and Resources:"

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

/*##^## Designer {
    D{i:0;autoSize:true;height:550;width:400}
}
 ##^##*/
