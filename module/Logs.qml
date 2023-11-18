import QtQuick 2.9
import QtQuick.Controls 2.5

Frame {
  id: root

  ListView {
    anchors {
      fill: parent
      margins: 0
      bottomMargin: 15
    }
    clip: true
    spacing: 5

    model: 20

    header: Label {
      padding: 20

      text: "Logs"
      font.pointSize: 24
    }

    delegate: Label {
      width: ListView.view.width
      padding: 5

      text: "Logs"
      font.pointSize: 16

      background: Rectangle {
        anchors.fill: parent
        color: "white"
        border {
          width: 1
          color: "grey"
        }
        radius: 4
      }
    }
  }
}
