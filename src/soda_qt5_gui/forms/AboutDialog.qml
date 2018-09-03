import QtQuick 2.4
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Window {
    id: aboutDialog
    flags: Qt.Dialog
    width: 500
    height: 500

    visible: true
    AboutDialogForm{
        id: aboutDialogForm
        anchors.fill: parent
    }
}


/*##^## Designer {
    D{i:6;anchors_x:120;anchors_y:112}
}
 ##^##*/
