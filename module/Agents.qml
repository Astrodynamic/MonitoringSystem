import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Frame {
  id: root

  RowLayout {
    anchors.fill: parent

    Frame {
      Layout.fillHeight: true
      Layout.preferredWidth: parent.width * .25
      Layout.minimumWidth: 300
      Layout.maximumWidth: 400
      Layout.bottomMargin: 15

      padding: 5
      background: Rectangle {
        anchors.fill: parent
        color: "white"
        border {
          width: 1
          color: "grey"
        }
        radius: 8
      }

      ListView {
        id: _view

        anchors.fill: parent
        spacing: 5
        clip: true

        model: Kernel.agentManager

        header: Frame {
          width: parent.width

          background: Rectangle {
            anchors {
              fill: parent
              bottomMargin: 5
            }
            color: "white"
            border {
              width: 1
              color: "grey"
            }
            radius: 8
          }

          Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Agents"
            font.pointSize: 24
          }
        }

        delegate: Frame {

          width: ListView.view.width

          background: Rectangle {
            anchors.fill: parent
            color: "white"
            border {
              width: 1
              color: "grey"
            }
            radius: 8
          }

          ColumnLayout {
            width: parent.width

            Text {
              text: "Name: " + model.name
              font {
                pointSize: 12
                bold: Font.Medium
              }
            }

            Text {
              text: "Type: " + model.type
              font.pointSize: 9
            }

            Text {
              text: "Enabled: " + model.enabled
              font.pointSize: 9
            }

            Row {
              spacing: parent.width - _timeTitle.width - _timeValue.width

              Text {
                id: _timeTitle
                font.pointSize: 9
                text: "The operating time: "
              }

              Text {
                id: _timeValue
                font.pointSize: 9
                text: Qt.formatTime(model.timer, "hh:mm:ss")
              }
            }
          }
        }
      }
    }

    ScrollView {
      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.bottomMargin: 15

      background: Rectangle {
        anchors.fill: parent
        color: "#f3f3f3"
        border {
          width: 1
          color: "grey"
        }
        radius: 8
      }

      TextArea {
        wrapMode: TextEdit.NoWrap
        font.pointSize: 16
        padding: 5
      }
    }
  }
}
