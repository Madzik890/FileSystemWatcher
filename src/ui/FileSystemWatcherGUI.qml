import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.1

Item {
    property var fileWatcher: fileSystemWatcher

    ColumnLayout
    {
        width: parent.width
        height: parent.height

        RowLayout {
            width: parent.width

            Text {
                height: 30
                text: "Add directory"
            }

            Button {
                text: "Add"
                onPressed: folderDialog.open()

                FolderDialog {
                    id: folderDialog
                    title: "Please choose a file"
                    options: FolderDialog.DontResolveSymlinks
                    onAccepted: {
                        fileSystemWatcher.addPath(this.folder);
                    }
                }
            }
        }

        RowLayout {
            Text {
                text: qsTr("Watched paths")
                font.pixelSize: 12
            }
        }

        DirectoryModelView {
            width: parent.width
            height: 150
        }

        RowLayout {
            spacing: 1
            Text {
                Layout.preferredWidth: 150
                text: "Event type"
            }

            Text {
                Layout.preferredWidth: 150
                text: "Path"
            }

            Text {
                Layout.preferredWidth: 150
                text: "Is folder"
            }

            Text {
                Layout.preferredWidth: 150
                text: "Timestamp"
            }
        }

        FileModelView {
            width: parent.width
            height: 150
        }

        RowLayout {
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
