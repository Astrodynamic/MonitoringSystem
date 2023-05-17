import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.5

ApplicationWindow {
  id: _root
  
  title: qsTr("Monitoring System 1.0")

  minimumWidth: 1280
  minimumHeight: 720

  visible: true
  
  opacity: 0.95

  SwipeView {
    id: _view
    anchors.fill: parent

    Agents {
      id: _agents
    }

    Logs {
      id: _logs
    }

    Settings {
      id: _settings
    }
  }

  PageIndicator {
    id: _viewIndicator
    scale: 0.9

    count: _view.count
    currentIndex: _view.currentIndex

    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
  }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
