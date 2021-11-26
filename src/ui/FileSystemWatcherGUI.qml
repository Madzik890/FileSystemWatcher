import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.1

Rectangle {
    property var fileWatcher: fileSystemWatcher
    color: "#f5f5f5"

    ColumnLayout {
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
                id: startButton
                text: "Start"
                onPressed: {
                    fileSystemWatcher.start();
                    highlighted = true;
                    stopButton.highlighted = false;
                }
            }
            Button {
                id: stopButton
                text: "Stop"
                highlighted: true
                onPressed: {
                    fileSystemWatcher.stop();
                    highlighted = true;
                    startButton.highlighted = false;
                }
            }
        }
    }
}
