import QtQuick 2.12
import QtQuick.Window 2.3
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

ApplicationWindow {
  visible: true
  width: 720
  height: 480

  title: qsTr("Game of Life")

  Button {
      id: button
      x: 350
      y: 233
      text: qsTr("Button")
  }
}
