import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 2.5

Page {
  id: root

  property QtObject notification: Kernel.notificationManager

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

    ColumnLayout {
      anchors.fill: parent
      spacing: 12

      Label {
        Layout.fillWidth: true
        text: "Telegram Settings"
        font.pointSize: 18

        CheckBox {
          anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
          }
          Component.onCompleted: checked = notification.telegram
          onCheckedChanged: notification.telegram = checked
        }
      }

      GridLayout {
        columns: 2

        Label {
          Layout.preferredWidth: 150
          text: "Token: "
          font.pointSize: 16
        }

        TextField {
          Layout.fillWidth: true
          text: notification.token
          font.pointSize: 16
          onAccepted: notification.token = text
        }

        Label {
          Layout.preferredWidth: 150
          text: "ChatID: "
          font.pointSize: 16
        }

        TextField {
          Layout.fillWidth: true
          text: notification.chat
          font.pointSize: 16
          onAccepted: notification.chat = text
        }
      }

      Label {
        Layout.fillWidth: true
        Layout.topMargin: 24
        text: "Mail Settings"
        font.pointSize: 18

        CheckBox {
          anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
          }
          Component.onCompleted: checked = notification.mail
          onCheckedChanged: notification.mail = checked
        }
      }

      GridLayout {
        columns: 2

        Label {
          Layout.preferredWidth: 150
          text: "URL: "
          font.pointSize: 16
        }

        TextField {
          Layout.fillWidth: true
          text: notification.url
          font.pointSize: 16
          onAccepted: notification.url = text
        }

        Label {
          Layout.preferredWidth: 150
          text: "Username: "
          font.pointSize: 16
        }

        TextField {
          Layout.fillWidth: true
          text: notification.username
          font.pointSize: 16
          onAccepted: notification.username = text
        }

        Label {
          Layout.preferredWidth: 150
          text: "Password: "
          font.pointSize: 16
        }

        TextField {
          Layout.fillWidth: true
          text: notification.password
          font.pointSize: 16
          onAccepted: notification.password = text
        }

        Label {
          Layout.preferredWidth: 150
          text: "From: "
          font.pointSize: 16
        }

        TextField {
          Layout.fillWidth: true
          text: notification.from
          font.pointSize: 16
          onAccepted: notification.from = text
        }

        Label {
          Layout.preferredWidth: 150
          text: "To: "
          font.pointSize: 16
        }

        TextField {
          Layout.fillWidth: true
          text: notification.to
          font.pointSize: 16
          onAccepted: notification.to = text
        }

        Label {
          Layout.preferredWidth: 150
          text: "Subject: "
          font.pointSize: 16
        }

        TextField {
          Layout.fillWidth: true
          text: notification.subject
          font.pointSize: 16
          onAccepted: notification.subject = text
        }

        Label {
          Layout.preferredWidth: 150
          text: "Port: "
          font.pointSize: 16
        }

        TextField {
          Layout.fillWidth: true
          text: notification.port
          font.pointSize: 16
          validator: IntValidator {}
          onAccepted: notification.port = text
        }
      }

      Item {
        Layout.fillHeight: true
      }
    }

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
