import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import Style 1.0
import "../controls"
Rectangle {
    color: "#151515"
    Layout.preferredWidth: 270
    Layout.preferredHeight: 270
    radius: 15
    ColumnLayout {
        spacing: 10
        anchors.centerIn: parent

        Text {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            text: qsTr("Spotify Music")
            font.pixelSize: 20
            font.weight: Font.Bold
            font.family: "Lato"
            color: Style.alphaColor("#FFFFFF",0.5)
        }

        Image {
            sourceSize: Qt.size(55,55)
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            source: "qrc:/assets/icons/logos--spotify-icon.svg"
        }

        Text {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            text: musicPlayer.currentSongTitle
            font.pixelSize: 14
            font.weight: Font.Bold
            font.family: "Lato"
            color: "#FFFFFF"
        }
        Text {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            text: musicPlayer.currentArtist
            font.pixelSize: 14
            font.family: "Lato"
            color: Style.alphaColor("#FFFFFF",0.5)
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            spacing: 10
            Text {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text: Qt.formatTime(new Date(musicPlayer.position), "mm:ss")
                font.pixelSize: 14
                font.weight: Font.Light
                font.family: "Lato"
                color: "#FFFFFF"
            }

            ProgressBar {
                Layout.preferredWidth: 108
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                from: 0
                to: musicPlayer.duration > 0 ? musicPlayer.duration : 100
                value: musicPlayer.position
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        let newPosition = (mouse.x / progressBar.width) * musicPlayer.duration;
                        musicPlayer.setPosition(newPosition);
                    }
            }
        }

            Text {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text: Qt.formatTime(new Date(musicPlayer.duration), "mm:ss")
                font.pixelSize: 14
                font.weight: Font.Light
                font.family: "Lato"
                color: "#FFFFFF"
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            spacing: 10
            PrefsButton {
                setIcon: "qrc:/assets/icons/mingcute--shuffle-2-fill.svg"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                onClicked: playerController.shuffle()
            }
            PrefsButton {
                setIcon: "qrc:/assets/icons/mage--previous-fill.svg"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                onClicked: musicPlayer.previousTrack()
            }
            PrefsButton {
                property bool playing: false
                setIcon: playing ?  "qrc:/assets/icons/mage--pause-fill.svg" : "qrc:/assets/icons/mage--play-fill.svg"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                onClicked: {
                           playing = !playing;
                           musicPlayer.playPause();
                       }
            }
            PrefsButton {
                setIcon: "qrc:/assets/icons/mage--next-fill.svg"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                onClicked: musicPlayer.nextTrack()
            }
            PrefsButton {
                setIcon: "qrc:/assets/icons/mi--repeat.svg"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                onClicked: playerController.repeat()
            }
        }
    }
}
