import QtQuick 2.9
import QtQuick.Controls 2.5

Page {
  id: root

  header: Label {
    padding: 20

    text: "Settings"
    font.pointSize: 24
  }

  Frame {
    anchors {
      fill: parent
      leftMargin: padding
      rightMargin: padding
      bottomMargin: padding * 2
    }
    padding: 10

    Column {}

    background: Rectangle {
      anchors.fill: parent
      border {
        width: 1
        color: "grey"
      }
      radius: 8
    }
  }
}
