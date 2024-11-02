import sys
import os

sys.path.append(
    os.path.dirname(os.path.abspath(__file__)) + "/../..",
)  # 添加项目根目录到搜索路径

from typing import Any, Optional


from LupguDesktop.UI.LoginWindow import LoginInterface
from LuoguDesktop.lib.user import fetch_user_data
from PyQt6.QtWidgets import QApplication, QMainWindow, QMessageBox
from PyQt6.QtGui import QAction


class MainWindow(QMainWindow):
    cookies: Optional[dict[str, Any]] = None
    username: Optional[str] = None
    avatar_url: Optional[str] = None

    def __init__(self) -> None:
        super().__init__()

        # 设置窗口标题和大小
        self.setWindowTitle("LuoguDesktop")
        self.setGeometry(100, 100, 600, 400)

        # 创建状态栏
        self.statusbar = self.statusBar()  # 添加状态栏
        if self.statusbar:
            self.statusbar.showMessage(
                "洛谷账号未登录，请先登录！"
            )  # 设置状态栏初始消息

        # 创建菜单栏
        menubar = self.menuBar()

        if menubar:
            # 创建“账号”菜单
            account_menu = menubar.addMenu("账号")

            if account_menu:
                # 创建“登录”菜单项
                login_action = QAction("登录", self)
                login_action.triggered.connect(self.login)  # type: ignore
                account_menu.addAction(login_action)  # type: ignore

                # 创建“退出登录”菜单项
                logout_action = QAction("退出登录", self)
                logout_action.triggered.connect(self.logout)  # type: ignore
                account_menu.addAction(logout_action)  # type: ignore

    def login(self) -> None:
        if self.cookies:
            QMessageBox.warning(self, "登录失败", "您已登录！")
            return
        login_interface = LoginInterface()
        login_interface.show()
        while login_interface.isVisible():
            app.processEvents()
        self.cookies = login_interface.cookies
        if not self.cookies:
            QMessageBox.warning(self, "登录失败", "登录失败！")
            if self.statusbar:
                self.statusbar.showMessage(
                    "洛谷账号登录失败，请先登录！"
                )  # 更新状态栏信息
            return
        else:
            if self.statusbar:
                self.username, self.avatar_url = fetch_user_data(self.cookies["_uid"])
                self.statusbar.showMessage(
                    f"已登录，用户名：{self.username}"
                )  # 更新状态栏信息

    def logout(self) -> None:
        self.cookies = None
        QMessageBox.information(self, "退出登录", "您已退出登录！")
        if self.statusbar:
            self.statusbar.showMessage(
                "洛谷账号已退出登录，请先登录！"
            )  # 更新状态栏信息


if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.showMaximized()  # 设置窗口默认最大化
    sys.exit(app.exec())
