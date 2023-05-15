import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.5

ApplicationWindow {
  id: root

  title: qsTr("Monitoring System 1.0")

  width: 1280
  height: 720

  visible: true

  opacity: 0.95

  Button {
    id: button
    x: 626
    y: 191
    text: qsTr("Button")
  }
}
