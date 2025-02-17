import QtQuick
import QtQuick.Layouts
RowLayout {
    spacing: 20
    Image {
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        source: "qrc:/assets/icons/Bluetooth Icon.svg"
    }

    RowLayout {
        property string deviceName: Backend.musicController.connectedDeviceName
        // Update text to use deviceName
        Text {
            text: deviceName
        }
    }

    ColumnLayout {
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        Text {
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            text: qsTr("Bluetooth Connected:")
            font.pixelSize: 14
            font.weight: Font.Light
            font.family: "Lato"
            color: "#FFFFFF"
        }
        Text {
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            text: qsTr("Raymond’s iPhone")
            font.pixelSize: 14
            font.weight: Font.Bold
            font.family: "Lato"
            color: "#FFFFFF"
        }
    }
}
