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
      height: parent.height - parent.spacing
      spacing: 10
      model: Kernel.agentManager
      clip: true

      delegate: Rectangle {
        width: view.width
        height: 40
        color: "lightgray"

        Text {
          id: _name
          anchors.centerIn: parent
          renderType: Text.NativeRendering
          text: model.name
        }

        MouseArea {
          anchors.fill: parent
          onDoubleClicked: model.name = "Dima vse easy"
        }
      }
    }
  }
}
