// qmllint disable unused-imports
// qmllint disable unqualified
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami
import com.github.zsd2024.LuoguDesktop 1.0

Kirigami.ApplicationWindow {
    id: root
    title: "Luogu Desktop"
    globalDrawer: Kirigami.GlobalDrawer {
        isMenu: true
        actions: [
            Kirigami.Action {
                text: i18n("Quit")
                icon.name: "gtk-quit"
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            },
            Kirigami.Action {
                text: i18n("About")
                icon.name: "help-about"
                onTriggered: pageStack.layers.push(aboutPage)
            }
        ]
    }
    Component { // <==== 实例化 Kirigami.AboutPage 的组件
        id: aboutPage

        Kirigami.AboutPage {
            aboutData: About
        }
    }

    // ===== 实例化页面组件 =====
    Component {
        id: loginPage
        LoginPage {}
    }
    Component {
        id: mainPage
        MainPage {}
    }

    // ===== 根据登录状态切换页面 =====
    pageStack.initialPage: AuthService.isLoggedIn ? mainPage : loginPage

    Connections {
        target: AuthService

        function onLoggedInChanged() {
            root.pageStack.clear();
            if (AuthService.isLoggedIn) {
                root.pageStack.push(mainPage.createObject(root));
            } else {
                root.pageStack.push(loginPage.createObject(root));
            }
        }
    }
}
