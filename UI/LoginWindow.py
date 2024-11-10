import io
import sys

import requests

from PyQt6.QtWidgets import (
    QApplication,
    QWidget,
    QLabel,
    QLineEdit,
    QPushButton,
    QVBoxLayout,
    QHBoxLayout,
    QMessageBox,
    QSizePolicy,
)
from PyQt6.QtGui import QPixmap, QIcon
from PIL import Image, ImageDraw
from PIL.ImageQt import ImageQt
from lib.user import login
from typing import Optional, Any
from PyQt6.QtCore import Qt


class LoginInterface(QWidget):
    cookies: Optional[dict[str, Any]] = None

    def __init__(self) -> None:
        super().__init__()

        self.username_var: str = ""
        self.password_var: str = ""

        self.initUI()

    def initUI(self) -> None:
        self.setWindowTitle("登录 - LuoguQQ")
        self.setFixedSize(300, 400)  # 设置窗口大小
        self.setStyleSheet("background-color: #f1f1f1;")  # 设置背景颜色

        # 设置窗口图标
        self.setWindowIcon(QIcon(os.path.join(os.path.dirname(__file__),'..', "logo.svg")))

        layout: QVBoxLayout = QVBoxLayout()
        layout.setAlignment(Qt.AlignmentFlag.AlignCenter)

        # Logo
        try:
            response = requests.get("https://fecdn.luogu.com.cn/luogu/logo.png")
            response.raise_for_status()
            logo_image = Image.open(io.BytesIO(response.content))

            logo_image_qt: QPixmap = QPixmap.fromImage(ImageQt(logo_image))

            # 设定最大宽度和高度
            max_size = 160
            logo_image_qt = logo_image_qt.scaled(
                max_size,
                max_size,
                Qt.AspectRatioMode.KeepAspectRatio,
                Qt.TransformationMode.SmoothTransformation,
            )

            logo_label: QLabel = QLabel(self)
            logo_label.setPixmap(logo_image_qt)
            logo_label.setScaledContents(False)
            logo_label.setSizePolicy(
                QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Preferred
            )
            logo_label.setAlignment(Qt.AlignmentFlag.AlignCenter)  # 设置居中对齐
            # logo_label.setMinimumHeight(120)  # 设置最小高度

            layout.addWidget(logo_label)
        except Exception as e:
            print(f"加载logo时出现错误: {e}")

        # 描述信息
        description_label: QLabel = QLabel("在洛谷，享受 Coding 的欢乐！", self)
        description_label.setStyleSheet("font-size: 16px; color: #3498db;")
        description_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(description_label)

        # 用户名输入
        username_label: QLabel = QLabel("用户名:", self)
        username_label.setStyleSheet("font-size: 16px; color: #000000;")
        layout.addWidget(username_label)

        self.username_entry: QLineEdit = QLineEdit(self)
        self.username_entry.setPlaceholderText(
            "用户名、手机号或电子邮箱"
        )  # 修改占位符文本
        layout.addWidget(self.username_entry)

        # 密码输入
        password_label: QLabel = QLabel("密码:", self)
        password_label.setStyleSheet("font-size: 16px; color: #000000;")
        layout.addWidget(password_label)

        self.password_entry: QLineEdit = QLineEdit(self)
        self.password_entry.setPlaceholderText("密码")  # 增加占位符
        self.password_entry.setEchoMode(QLineEdit.EchoMode.Password)  # 密码隐藏
        layout.addWidget(self.password_entry)

        # 登录按钮
        login_button: QPushButton = QPushButton("登录", self)
        login_button.setStyleSheet(
            """
            QPushButton {
                background-color: #3498db; 
                color: white; 
                border: none; 
                border-radius: 5px;
                font-size: 14px;
                padding: 4.382px 14px;
            }
            QPushButton:hover {
                background-color: #3cb0ef;  /* 鼠标悬停时的背景颜色 */
            }
            """
        )  # 增加按钮样式
        login_button.clicked.connect(self.on_login)  # type: ignore # 连接登录事件
        layout.addWidget(login_button)

        # 忘记密码链接
        forgot_password_label: QLabel = QLabel("忘记密码/两步验证", self)
        forgot_password_label.setStyleSheet("color: #3498db; text-align: right;")
        forgot_password_label.setAlignment(Qt.AlignmentFlag.AlignRight)
        layout.addWidget(forgot_password_label)

        # 第三方登录
        third_party_label: QLabel = QLabel("第三方平台登录:", self)
        third_party_label.setStyleSheet("font-size: 14px; color: #888888;")
        layout.addWidget(third_party_label)

        # 第三方登录按钮（可自定义为图标）
        third_party_layout: QHBoxLayout = QHBoxLayout()

        wechat_button: QPushButton = QPushButton("微信")
        wechat_button.setStyleSheet(
            """
            QPushButton {
                background-color: #00bfff;
                color: white;
            }

            QPushButton:hover {
                background-color: #00a2e8;
            }

            """
        )

        wechat_button.clicked.connect(lambda: QMessageBox.information(self, "暂未开放", "微信登录功能暂未开放。"))  # type: ignore

        github_button: QPushButton = QPushButton("GitHub")
        github_button.setStyleSheet(
            """
            QPushButton {
                background-color: #333; 
                color: white; 
            }
            QPushButton:hover {
                background-color: #222;
            }
            """
        )
        github_button.clicked.connect(lambda: QMessageBox.information(self, "暂未开放", "GitHub登录功能暂未开放。"))  # type: ignore

        third_party_layout.addWidget(wechat_button)
        third_party_layout.addWidget(github_button)

        layout.addLayout(third_party_layout)

        # 创建水平布局
        h_layout = QHBoxLayout()

        h_layout.addStretch()

        # 注册链接
        register_label1: QLabel = QLabel("没有账号？", self)
        register_label1.setAlignment(Qt.AlignmentFlag.AlignCenter)
        h_layout.addWidget(register_label1)

        register_label2: QLabel = QLabel("注册", self)
        register_label2.setStyleSheet("color: #3498db; text-align: center;")
        register_label2.setAlignment(Qt.AlignmentFlag.AlignCenter)
        h_layout.addWidget(register_label2)  # 注册链接

        h_layout.addStretch()

        # 将水平布局添加到主布局中
        layout.addLayout(h_layout)

        layout.addStretch()  # 添加空白空间以使布局居中

        self.setLayout(layout)

    def on_login(self) -> None:
        self.username_var = self.username_entry.text()
        self.password_var = self.password_entry.text()

        try:
            cookies = login(self.username_var, self.password_var)  # type: ignore
            if cookies:
                QMessageBox.information(self, "登录成功", "登录成功！")
                self.cookies = cookies
                self.close()
            else:
                self.show_error("登录失败！请检查用户名和密码。")
        except ValueError as e:
            if "验证码错误" == str(e):
                self.show_error("验证码识别错误！请重试。", "内部错误")
            else:
                self.show_error(f"{e}", "登录失败！")

    def show_error(self, message: str, title: str = "错误") -> None:
        """显示错误消息框"""
        QMessageBox.critical(self, title, message)

    def crop_avatar_to_circle(self, avatar_image: Image.Image) -> Image.Image:
        avatar_image = avatar_image.convert("RGBA")
        size = (avatar_image.size[0], avatar_image.size[1])
        mask: Image.Image = Image.new("L", size, 0)
        draw = ImageDraw.Draw(mask)
        draw.ellipse((0, 0) + size, fill=255)
        circular_avatar: Image.Image = Image.new("RGBA", size)
        circular_avatar.paste(avatar_image, (0, 0), mask)
        return circular_avatar


if __name__ == "__main__":
    app = QApplication(sys.argv)
    login_interface = LoginInterface()
    login_interface.show()
    sys.exit(app.exec())
