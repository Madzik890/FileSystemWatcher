import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    property var fileWatcher: fileSystemWatcher

    ColumnLayout
    {
        width: parent.width
        height: parent.height

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

        DirectoryModelView {
            width: parent.width
            height: 150
        }

        FileModelView {
            width: parent.width
            height: 150
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
