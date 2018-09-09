import QtQuick 2.4
import QtQuick.Controls 2.4

GroupBox {
    property alias licence: licence
    property alias website: website
    Grid {
        anchors.fill: parent
        spacing: 5
        rows: 2
        columns: 2
        Label {
            text: "Licence:"
        }
        Label {
            id: licence
            text: "<licence string>"
        }
        Label {
            text: "Website:"
        }
        Label {
            id: website
            text: "<website string>"
        }
    }
}
