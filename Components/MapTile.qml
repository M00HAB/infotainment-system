import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import Style 1.0
import QtLocation
import QtPositioning
import "../controls"





Rectangle {
    color: "#151515"
    radius: 15

    // Map plugin configuration
    Plugin {
        id: mapPlugin
        name: "osm"
        // Direct tile server configuration
        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://tile.openstreetmap.org/"
        }
        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: "true" // Disable default repository
        }
        PluginParameter {
            name: "osm.useragent"
            value: "YourAppName/1.0"
        }
    }

    PluginParameter {
        name: "osm.mapping.cache.directory"
        value: Qt.application.persistentDataPath + "/osm_cache"
    }

    Component.onCompleted: {
        if (!mapPlugin.available) {
            console.error("OSM Plugin failed to initialize!");
        }
    }

    // Map view
    Map {
        id: map
        z: 4
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(28.4595, 77.0266) // Gurugram coordinates
        zoomLevel: 14
        copyrightsVisible: false

        // Pinch-to-zoom and rotation
        PinchHandler {
            id: pinch
            target: null
            onActiveChanged: if (active) {
                                 map.startCentroid = map.toCoordinate(pinch.centroid.position, false)
                             }
            onScaleChanged: (delta) => {
                                map.zoomLevel += Math.log2(delta)
                                map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
                            }
            onRotationChanged: (delta) => {
                                   map.bearing -= delta
                                   map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
                               }
            grabPermissions: PointerHandler.TakeOverForbidden
        }

        // Mouse wheel zoom
        WheelHandler {
            id: wheel
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                             ? PointerDevice.Mouse | PointerDevice.TouchPad
                             : PointerDevice.Mouse
            rotationScale: 1/120
            property: "zoomLevel"
        }

        // Drag to pan the map
        DragHandler {
            id: drag
            target: null
            onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
        }

        // Keyboard shortcuts for zooming
        Shortcut {
            enabled: map.zoomLevel < map.maximumZoomLevel
            sequence: StandardKey.ZoomIn
            onActivated: map.zoomLevel = Math.round(map.zoomLevel + 1)
        }

        Shortcut {
            enabled: map.zoomLevel > map.minimumZoomLevel
            sequence: StandardKey.ZoomOut
            onActivated: map.zoomLevel = Math.round(map.zoomLevel - 1)
        }
    }

    // Border around the map
    Rectangle {
        z: 55
        color: "#00000000"
        anchors.centerIn: parent
        width: parent.width + 15
        height: parent.height + 15
        radius: 15
        border.width: 10
        border.color: "#000000"
    }

    // Search bar
    TextField {
        z: 6
        width: 509
        height: 45
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#FFFFFF"
        font.family: "Lato"
        font.pixelSize: 14
        font.weight: Font.Bold
        placeholderText: qsTr("Enter an address")
        leftPadding: 15
        placeholderTextColor: Style.alphaColor("#FFFFFF", 0.5)
        background: Rectangle {
            anchors.fill: parent
            radius: 45
            color: Style.alphaColor("#252525", 0.9)
        }
    }
}
