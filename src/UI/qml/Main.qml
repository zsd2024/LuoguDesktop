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
    Component { // <==== Component that instantiates the Kirigami.AboutPage
        id: aboutPage

        Kirigami.AboutPage {
            aboutData: About
        }
    }
    pageStack.initialPage: Kirigami.ScrollablePage {
        title: i18nc("@title", "Luogu Desktop")
    }
}
