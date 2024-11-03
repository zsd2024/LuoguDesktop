import sys
import os
from typing import Any, Optional

from UI.LoginWindow import LoginInterface
from lib.user import fetch_user_data
from lib.get_image import get_background_url
from PyQt6.QtWidgets import (
    QApplication,
    QMainWindow,
    QMessageBox,
    QGraphicsDropShadowEffect,
)
from PyQt6.QtGui import QAction, QPixmap, QIcon, QPainter, QColor
from PyQt6.QtSvg import QSvgRenderer
from PyQt6.QtCore import QByteArray
import requests


class MainWindow(QMainWindow):
    cookies: Optional[dict[str, Any]] = None
    username: Optional[str] = None
    avatar_url: Optional[str] = None

    def __init__(self) -> None:
        super().__init__()

        # 设置窗口标题和大小
        self.setWindowTitle("LuoguDesktop")
        self.setGeometry(100, 100, 600, 400)
        self.setAutoFillBackground(True)  # 自动填充背景

        # 加载网络图片作为背景
        self.load_background_image(get_background_url())

        # 设置窗口图标
        pixmap = QPixmap()
        pixmap.loadFromData(
            requests.get("https://www.luogu.com.cn/favicon.ico").content
        )
        self.setWindowIcon(QIcon(pixmap))

        # 创建状态栏
        self.statusbar = self.statusBar()  # 添加状态栏
        if self.statusbar:
            self.statusbar.showMessage(
                "洛谷账号未登录，请先登录！"
            )  # 设置状态栏初始消息

        # 创建菜单栏
        menubar = self.menuBar()
        menubar.setStyleSheet(
            "QMenuBar { background-color: rgba(255, 255, 255, 150); border: none; }"
        )
        # 添加阴影效果
        shadow_effect = QGraphicsDropShadowEffect()
        shadow_effect.setOffset(2, 2)  # 阴影偏移
        shadow_effect.setBlurRadius(10)  # 阴影模糊半径
        shadow_effect.setColor(QColor(0, 0, 0, 160))  # 阴影颜色

        # 应用阴影效果
        menubar.setGraphicsEffect(shadow_effect)

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

                # 直接使用SVG字符串创建图标
                svg_data = """
                <svg aria-hidden="true" focusable="false" data-prefix="fas" data-icon="right-from-bracket" role="img" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 512 512">
                    <path fill="currentColor" d="M377.9 105.9L500.7 228.7c7.2 7.2 11.3 17.1 11.3 27.3s-4.1 20.1-11.3 27.3L377.9 406.1c-6.4 6.4-15 9.9-24 9.9c-18.7 0-33.9-15.2-33.9-33.9l0-62.1-128 0c-17.7 0-32-14.3-32-32l0-64c0-17.7 14.3-32 32-32l128 0 0-62.1c0-18.7 15.2-33.9 33.9-33.9c9 0 17.6 3.6 24 9.9zM160 96L96 96c-17.7 0-32 14.3-32 32l0 256c0 17.7 14.3 32 32 32l64 0c17.7 0 32 14.3 32 32s-14.3 32-32 32l-64 0c-53 0-96-43-96-96L0 128C0 75 43 32 96 32l64 0c17.7 0 32 14.3 32 32s-14.3 32-32 32z"/>
                </svg>
                """

                # 将SVG字符串转换为QPixmap
                pixmap = self.svg_string_to_pixmap(svg_data)

                # 将QPixmap转换为QIcon，并设置为菜单图标
                logout_action.setIcon(QIcon(pixmap))
            # 创建“帮助”菜单
            help_menu = menubar.addMenu("帮助")
            if help_menu:
                # 创建“关于”菜单项
                about_action = QAction("关于", self)
                about_action.triggered.connect(self.about)  # type: ignore
                help_menu.addAction(about_action)  # type: ignore

    def about(self) -> None:
        QMessageBox.about(
            self,
            "关于",
            "LuoguDesktop v1.0\n\n"
            "作者：zsd2024\n"
            "邮箱：zsd2024@outlook.com\n"
            "GitHub：https://github.com/zsd2024/LuoguDesktop",
        )

    def svg_string_to_pixmap(self, svg_data):
        # 使用QSvgRenderer将SVG字符串渲染为QPixmap
        renderer = QSvgRenderer(QByteArray(svg_data.encode()))
        pixmap = QPixmap(32, 32)  # 设置合适的尺寸
        pixmap.fill(QColor(255, 255, 255, 0))  # 填充透明背景
        painter = QPainter(pixmap)
        renderer.render(painter)
        painter.end()
        return pixmap

    def paintEvent(self, event):
        # 处理背景绘制
        painter = QPainter(self)
        painter.drawPixmap(self.rect(), self.background_image)  # 绘制背景图像

        # 继续调用基类的绘制事件
        super().paintEvent(event)

    def load_background_image(self, url: str):
        response = requests.get(url)
        if response.status_code == 200:
            # 创建QPixmap并从数据加载图像
            self.background_image = QPixmap()
            self.background_image.loadFromData(response.content)
            self.update()  # 更新窗口以重新绘制背景
        else:
            QMessageBox.warning(self, "背景加载失败", "无法加载背景图像！")

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
        if not self.cookies:
            QMessageBox.warning(self, "退出登录失败", "您尚未登录！")
            return
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
