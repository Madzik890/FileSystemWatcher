import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import File 1.0

Rectangle {
    property var fileWatcher: fileSystemWatcher
    color: "#f5f5f5"

    FileModel {
        id: fileModel
        fileSystemWatcher: fileWatcher
    }

    TableView {
        id: fileTable
        implicitWidth: parent.width
        implicitHeight: 200
        clip: true
        model: fileModel

        delegate: RowLayout {
            width: parent.width

            Text {
                text: model.event
                //Layout.preferredWidth: 50
            }

            Text {
                text: model.path
                //Layout.preferredWidth: 150
            }

            Text {
                text: model.isFolder
                //Layout.preferredWidth: 200
            }

            Text {
                text: model.timestamp
                //Layout.preferredWidth: 250
            }
        }
    }

}
