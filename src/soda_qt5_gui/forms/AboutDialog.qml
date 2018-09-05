import QtQuick 2.4
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

ApplicationWindow {
    id: aboutDialog
    flags: Qt.Dialog
    visible: true
    AboutDialogForm{
        id: aboutDialogForm
        anchors.fill: parent
        anchors.centerIn: parent;
    }
}


/*##^## Designer {
    D{i:6;anchors_x:120;anchors_y:112}
}
 ##^##*/
