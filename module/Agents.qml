import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Frame {
  id: _root

  ListView {
    id: _view

    anchors {
      left: parent.left
      top: parent.top
    }

    spacing: 10
    model: Kernel.agentManager
    clip: true

    delegate: Rectangle {
      width: _view.width
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

  TextArea {
    id: _textArea
  }
}
