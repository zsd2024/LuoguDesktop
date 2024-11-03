from PyQt6.QtWidgets import QMainWindow
from _typeshed import Incomplete as Incomplete
from typing import Any

class MainWindow(QMainWindow):
    cookies: dict[str, Any] | None
    username: str | None
    avatar_url: str | None
    statusbar: Incomplete
    def __init__(self) -> None: ...
    def login(self) -> None: ...
    def logout(self) -> None: ...
