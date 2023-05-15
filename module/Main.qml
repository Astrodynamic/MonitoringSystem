import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.5

ApplicationWindow {
  id: _root

  title: qsTr("Monitoring System 1.0")

  width: 1280
  height: 720

  visible: true

  opacity: 0.95

  SwipeView {
    id: _view
    anchors.fill: parent

    Agents {
      id: _agents
      color: "lightgreen"
    }

    Logs {
      id: _logs
      color: "lightgray"
    }

    Settings {
      id: _settings
      color: "lightblue"
    }
  }

  PageIndicator {
    id: _view_indicator
    scale: 0.9

    count: _view.count
    currentIndex: _view.currentIndex

    anchors.bottom: _view.bottom
    anchors.horizontalCenter: parent.horizontalCenter
  }
}
