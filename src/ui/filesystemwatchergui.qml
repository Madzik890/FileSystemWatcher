import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import File 1.0
import Dir 1.0

Item {
    property var fileWatcher: fileSystemWatcher

    ColumnLayout
    {
        width: parent.width
        height: parent.height

        FileModel {
            id: fileModel
            fileSystemWatcher: fileWatcher
        }

        DirModel {
            id: dirModel
            fileSystemWatcher: fileWatcher
        }

        RowLayout {
            width: parent.width

            TextField {
                id: textEdit
                height: 30
                text: "C:\\Users\\Marcin\\Desktop\\powder toy"
            }

            Button {
                text: "Add"
                onPressed: fileSystemWatcher.addPath(textEdit.text);
            }
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
                    onPressed: fileSystemWatcher.removePath(model.display);
                }
            }
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

        RowLayout
        {
            Button {
                text: "Clear"
                onPressed: fileSystemWatcher.clear();
            }
            Button {
                text: "Start"
                onPressed: fileSystemWatcher.start();
            }
            Button {
                text: "Stop"
                onPressed: fileSystemWatcher.stop();
            }
        }
    }
}
