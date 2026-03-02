// qmllint disable unused-imports
// qmllint disable unqualified
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami
import com.github.zsd2024.LuoguDesktop 1.0

Kirigami.ScrollablePage {
    id: page
    title: i18n("Login")

    property string username
    property string password
    property string captcha

    Kirigami.FormLayout {
        anchors.centerIn: parent
        width: Kirigami.Units.gridUnit * 25

        Controls.TextField {
            placeholderText: i18n("Username")
            Layout.fillWidth: true
            text: page.username
            onTextChanged: page.username = text
            enabled: !AuthService.buzyLogin
        }

        Controls.TextField {
            placeholderText: i18n("Password")
            Layout.fillWidth: true
            echoMode: TextInput.Password
            text: page.password
            onTextChanged: page.password = text
            enabled: !AuthService.buzyLogin
        }

        RowLayout {
            spacing: Kirigami.Units.smallSpacing

            Controls.TextField {
                id: captchaField
                placeholderText: i18n("Captcha")
                Layout.fillWidth: true
                text: page.captcha
                onTextChanged: page.captcha = text
                Layout.preferredWidth: Kirigami.Units.gridUnit * 10
                enabled: !AuthService.buzyCaptcha && !AuthService.buzyLogin
            }

            Item {
                id: captchaBox
                Layout.preferredWidth: 90
                Layout.preferredHeight: captchaField.implicitHeight

                Image {
                    id: captchaImage
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    sourceSize.height: captchaBox.height
                    visible: !AuthService.buzyCaptcha
                }

                Controls.BusyIndicator {
                    anchors.centerIn: parent
                    running: AuthService.buzyCaptcha
                    visible: AuthService.buzyCaptcha
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: AuthService.refreshCaptcha()
                    cursorShape: AuthService.buzyCaptcha ? Qt.BusyCursor : Qt.PointingHandCursor
                    enabled: !AuthService.buzyCaptcha && !AuthService.buzyLogin
                }
            }
        }

        Kirigami.InlineMessage {
            id: errorMessage
            Layout.fillWidth: true
            visible: false
            type: Kirigami.MessageType.Error
            showCloseButton: true
        }

        Controls.Button {
            Kirigami.FormData.label: ""
            Layout.fillWidth: true
            text: i18n("Login")
            onClicked: AuthService.login(username, password, captcha)
            enabled: !AuthService.buzyLogin
        }

        Connections {
            target: AuthService

            function onLoginFailed(error) {
                errorMessage.text = error;
                errorMessage.visible = true;
            }

            function onCaptchaRefreshed(captcha) {
                captchaImage.source = captcha;
                console.log(captcha);
            }
        }
    }

    Rectangle {
        id: loginOverlay
        anchors.fill: parent
        color: Qt.rgba(0, 0, 0, 0.5)
        visible: AuthService.buzyLogin
        z: 100

        Column {
            anchors.centerIn: parent
            spacing: Kirigami.Units.largeSpacing

            Controls.BusyIndicator {
                running: AuthService.buzyLogin
                anchors.horizontalCenter: parent.horizontalCenter
                width: Kirigami.Units.gridUnit * 4
                height: Kirigami.Units.gridUnit * 4
            }

            Controls.Label {
                text: i18n("Logging in...")
                color: Kirigami.Theme.textColor
                font.pixelSize: Kirigami.Units.gridUnit * 2
            }
        }
    }

    Component.onCompleted: {
        AuthService.refreshCaptcha();
    }
}
