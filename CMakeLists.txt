cmake_minimum_required(VERSION 3.20)
# 指定最低 CMake 版本为 3.20，构建系统在低于此版本时会报错并停止。

project(LuoguDesktop)
# 定义项目名称为 LuoguDesktop，CMake 会使用该名称作为默认构建目录和生成器相关信息的标识。

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
# 查找 Extra CMake Modules (ECM) 版本至少为 6.0.0，查找失败则终止配置。
# NO_MODULE 表示使用 ECM 提供的 CMake 包配置，而不是查找模块文件。

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
# 将 ECM 提供的模块路径追加到 CMake 的模块搜索路径中，后续 include(...) 能找到 ECM 的辅助模块。

include(KDEInstallDirs)
# 引入 KDE 安装目录变量，提供 ${KDE_INSTALL_APPDIR}、${KDE_INSTALL_ICONDIR} 等变量。

include(KDECMakeSettings)
# 引入 KDE 的 CMake 全局设置，设置默认的编译选项和安装参数。

include(KDECompilerSettings NO_POLICY_SCOPE)
# 引入 KDE 的编译器设置，统一处理编译器相关的警告和选项。
# NO_POLICY_SCOPE 保持策略作用域为全局，确保设置立即生效。

include(ECMFindQmlModule)
# 引入 ECM 提供的 QML 模块查找与处理辅助宏。

include(ECMQmlModule)
# 引入 ECM 的 QML 模块支持，提供 ecm_add_qml_module、ecm_target_qml_sources 等宏。

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Quick
    Gui
    QuickControls2
    Widgets
)
# 查找 Qt6 并要求以下组件可用：Core、Quick、Gui、QuickControls2、Widgets。
# 查找失败则终止配置。

find_package(KF6 REQUIRED COMPONENTS
    Kirigami
    I18n
    CoreAddons
    QQC2DesktopStyle
    IconThemes
)
# 查找 KDE Frameworks 6 并要求以下组件可用：Kirigami、I18n、CoreAddons、QQC2DesktopStyle、IconThemes。
# 查找失败则终止配置。

ecm_find_qmlmodule(org.kde.kirigami REQUIRED)
# 使用 ECM 的辅助宏查找 QML 模块 org.kde.kirigami，查找失败则终止配置。

ecm_find_qmlmodule(org.kde.ki18n REQUIRED)
# 使用 ECM 的辅助宏查找 QML 模块 org.kde.ki18n，查找失败则终止配置.

add_subdirectory(src)
# 将 src 子目录加入构建，src 目录中的 CMakeLists.txt 定义可执行目标、源文件和链接库。

install(FILES com.github.zsd2024.LuoguDesktop.desktop DESTINATION ${KDE_INSTALL_APPDIR})
# 将 com.github.zsd2024.LuoguDesktop.desktop 安装到桌面应用目录，使用 KDE 提供的 ${KDE_INSTALL_APPDIR} 变量作为目标路径。
# .desktop 文件的 Exec 字段必须与可执行文件名 luogu-desktop 对应。

install(FILES assets/luogu-desktop.svg DESTINATION ${KDE_INSTALL_ICONDIR}/hicolor/scalable/apps)
# 将 SVG 图标安装到图标主题的 scalable/apps 目录，使用 ${KDE_INSTALL_ICONDIR} 变量定位图标根目录。
# 安装路径为 ${KDE_INSTALL_ICONDIR}/hicolor/scalable/apps/luogu-desktop.svg。

ki18n_install(i18n)
# 安装国际化翻译文件目录 i18n 下的翻译文件，ki18n_install 会处理 .po/.mo 的安装和路径布局。

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
# 打印配置摘要，列出已找到的包和启用的特性。
# FATAL_ON_MISSING_REQUIRED_PACKAGES 参数在有必需包缺失时使配置失败并给出明确错误信息。
