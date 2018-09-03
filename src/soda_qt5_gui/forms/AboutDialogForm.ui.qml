import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Item {
    id: aboutDialog
    anchors.fill: parent

    Image {
        id: logo
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        fillMode: Image.PreserveAspectFit
        source: "images/Logo_Hochschule_Trier.png"
    }

    ColumnLayout {
        id: content
        anchors.top: logo.bottom
        anchors.left: parent.left

        Text {
            id: applicationName
            text: qsTr("Soda - Simple object detection application")
            font.pixelSize: 18
        }


        GridLayout {
            id: info
            columns: 2
            anchors.margins: 10
            rowSpacing: 10
            columnSpacing: 10
            Label {
                        text: "Authors:"
                    }
            Label {
                        text: "Bastian Schumacher"
                    }
        }

        Item{
            id: resources
        }
    }

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
