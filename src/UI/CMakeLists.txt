# 将该应用作为一个 QML 模块导出，URI 使用反向域名命名法，与 .desktop 的 Application ID 保持一致
ecm_add_qml_module(LuoguDesktop
    URI
    com.github.zsd2024.LuoguDesktop
)

# 将 QML 源文件注册到目标，便于安装到正确的 QML 模块目录
ecm_target_qml_sources(LuoguDesktop
    SOURCES
    UI/qml/Main.qml
)
