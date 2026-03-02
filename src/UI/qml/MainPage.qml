// qmllint disable unused-imports
// qmllint disable unqualified
import QtQuick
import org.kde.kirigami as Kirigami
import com.github.zsd2024.LuoguDesktop 1.0

Kirigami.ScrollablePage {
    id: page
    title: i18n("Home")

    actions: Kirigami.Action {
        text: i18n("Logout")
        onTriggered: AuthService.logout()
    }

    Column {
        anchors.centerIn: parent
        spacing: Kirigami.Units.largeSpacing

        Kirigami.Heading {
            text: i18n("Welcome, %1. ", AuthService.currentUser.profile.name)
        }
    }
}
