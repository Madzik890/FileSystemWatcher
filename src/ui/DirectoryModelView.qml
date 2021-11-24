import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import Dir 1.0

Rectangle {
    property var fileWatcher: fileSystemWatcher
    color: "#f5f5f5"

    DirModel {
        id: dirModel
        fileSystemWatcher: fileWatcher
    }

    ListView {
        implicitWidth: parent.width
        implicitHeight: 150
        clip: true
        model: dirModel

        delegate: RowLayout {
            width: parent.width

            Text {
                text: model.display
                Layout.fillWidth: true
            }

            Button {
                text: "Remove"
                onPressed: fileWatcher.removePath(model.display);
            }
        }
    }
}
