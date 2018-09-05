import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

GroupBox{
    Layout.fillWidth: true

    property alias licence: licence
    property alias website: website
    GridLayout{
        rows: 2
        anchors.fill: parent
        columns: 2
        Label {
            text: "Licence:"
            Layout.alignment: Qt.AlignLeft
        }
        Label {
            id: licence
            text: "<licence string>"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft
        }
        Label {
            text: "Website:"
            Layout.alignment: Qt.AlignLeft
        }
        Label {
            id: website
            text: "<website string>"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft
        }
    }
}
