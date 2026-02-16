# 使用 Qt 的 CMake 集成创建可执行目标，MANUAL_FINALIZATION 用于在文件末尾调用 qt_finalize_executable
qt_add_executable(LuoguDesktop
    main.cpp
    MANUAL_FINALIZATION
)

# 将生成的可执行文件输出名设置为小写 luogu-desktop
set_target_properties(LuoguDesktop PROPERTIES OUTPUT_NAME "luogu-desktop")

add_subdirectory(Network)
add_subdirectory(Repository)
add_subdirectory(Service)
add_subdirectory(Models)
add_subdirectory(Utils)
include(UI/CMakeLists.txt)

# 将 C++ 源文件加入目标构建列表
target_sources(LuoguDesktop
    PRIVATE
    main.cpp
)

# 链接所需的 Qt6 与 KDE Frameworks 6 库
target_link_libraries(LuoguDesktop
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui
    Qt6::QuickControls2
    Qt6::Widgets
    KF6::Kirigami
    KF6::I18n
    KF6::CoreAddons
    KF6::IconThemes
    hv
)

# 完成 Qt 可执行目标的最终设置
qt_finalize_executable(LuoguDesktop)

# 安装可执行文件，使用 KDE 的默认安装参数（将可执行文件安装到目标系统的 bin 目录）
install(TARGETS LuoguDesktop ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
