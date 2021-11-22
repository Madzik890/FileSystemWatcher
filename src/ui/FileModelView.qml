import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import File 1.0

Item {
    property var fileWatcher: fileSystemWatcher

    FileModel {
        id: fileModel
        fileSystemWatcher: fileWatcher
    }

    TableView {
        id: fileTable
        width: parent.width
        height: 200
        clip: true
        model: fileModel

        delegate: RowLayout {
            width: parent.width

            Text {
                text: model.event
                Layout.fillWidth: true
            }

            Text {
                text: model.path
                Layout.fillWidth: true
            }

            Text {
                text: model.isFolder
                Layout.fillWidth: true
            }

            Text {
                text: model.timestamp
                Layout.fillWidth: true
            }
        }
    }

}
