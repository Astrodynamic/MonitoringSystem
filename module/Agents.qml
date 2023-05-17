import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ColumnLayout {
  id: _root

  Column {
    anchors.margins: 10
    anchors.fill: parent
    spacing: 10

    ListView {
      id: view

      width: parent.width
      height: parent.height - button.height - parent.spacing
      spacing: 10
      model: Kernel.agentManager
      clip: true

      delegate: Rectangle {
        width: view.width
        height: 40
        color: model.color || "lightgray"

        Text {
          anchors.centerIn: parent
          renderType: Text.NativeRendering
          text: model.text || "old"
        }

        MouseArea {
          anchors.fill: parent
          onDoubleClicked: model.text = "Edited"
        }
      }
    }

    Rectangle {
      id: button

      width: 100
      height: 40
      anchors.horizontalCenter: parent.horizontalCenter
      border {
        color: "black"
        width: 1
      }

      Text {
        anchors.centerIn: parent
        renderType: Text.NativeRendering
        text: "Add"
      }

      MouseArea {
        anchors.fill: parent
        onClicked: Kernel.agentManager.add()
      }
    }
  }
}
