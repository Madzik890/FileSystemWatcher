import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import File 1.0

Item {
    property var fileWatcher: fileSystemWatcher    

    FileModel {
        id: fileModel
        fileSystemWatcher: fileWatcher
    }

    TableView {
        id: fileTable
        implicitWidth: parent.width
        implicitHeight: 160
        clip: true
        model: fileModel
        backgroundVisible: true
        alternatingRowColors: true

        TableViewColumn {
            role: "event"
            title: "Event type"
            elideMode: Text.ElideLeft
            horizontalAlignment: Text.AlignHCenter
            width: parent.width / 10 + 70
        }
        TableViewColumn {
            role: "path"
            title: "Path"
            elideMode: Text.ElideLeft
            horizontalAlignment: Text.AlignHCenter
            width: parent.width / 10 + 200
        }
        TableViewColumn {
            role: "isFolder"
            title: "Is folder"
            elideMode: Text.ElideLeft
            horizontalAlignment: Text.AlignHCenter
            width: parent.width / 10 + 30
        }
        TableViewColumn {
            role: "timestamp"
            title: "Timestamp"
            elideMode: Text.ElideLeft
            horizontalAlignment: Text.AlignHCenter
            width: parent.width / 10 + 80
        }
    }
}
