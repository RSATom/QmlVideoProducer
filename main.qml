import QtQuick 2.2
import QtQuick.Window 2.1
import QtMultimedia 5.0
import DesktopVideoProducer 0.1

Window {
    visible: true
    width: 360
    height: 360

    DesktopVideoProducer {
        id: videoProducer;
    }

    VideoOutput {
        anchors.fill: parent;
        source: videoProducer;
    }
}
