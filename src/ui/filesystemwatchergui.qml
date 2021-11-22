import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import File 1.0

Item {
    id: root

    ColumnLayout
    {
        FileModel {
            id: fileModel
        }

        TableView {
            id: fileTable
            width: 300
            height: 300
            model: fileModel
        }

        TextEdit {
            id: textEdit
            width: root.width
            height: 30
            text: "Add path to watch"

            Button {
                    text: "Add"
            }
        }

        RowLayout
        {
            Button {
                text: "Clear"
                onPressed:  {
                    fileSystemWatcher.clear();
                }
            }
            Button {
                text: "Start"
                onPressed:  {
                    fileModel.fileSystemWatcher = fileSystemWatcher;
                    fileSystemWatcher.start();
                }
            }
            Button {
                text: "Stop"
                onPressed:  {
                    fileSystemWatcher.stop();
                }
            }
        }
    }
}
