# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.16)

# 在配置阶段前执行脚本
execute_process(
    COMMAND ${CMAKE_COMMAND} -E env bash ${CMAKE_SOURCE_DIR}/Craft/craft/craftenv.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE result
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR "Pre-configure script failed with exit code ${result}")
endif()


# 定义项目名称和语言
project(LuoguDesktop LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Craft/share/ECM/find-modules)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# 基础设置
# -----------------------------

# 启用 C++14 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用 Qt6 的自动化功能
# CMake 会自动运行 moc, uic, rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# -----------------------------
# 查找并链接 Qt6 模块
# -----------------------------

# 查找 Qt6 及其必需的组件
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    WebEngineWidgets
    Svg
    LinguistTools
)

# 查找 KF6 及其必需的组件
find_package(KF6 REQUIRED COMPONENTS
    CoreAddons
    WidgetsAddons
    I18n
    XmlGui
    TextWidgets
)

# -----------------------------
# 自动收集源文件
# -----------------------------

# 递归查找 src 目录下的所有 .cpp 和 .h 文件
file(GLOB_RECURSE SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

# 查找 UI 文件
file(GLOB_RECURSE UI_FILES
    "${CMAKE_SOURCE_DIR}/src/*.ui"
)

# 查找资源文件
file(GLOB QRC_FILES
    "${CMAKE_SOURCE_DIR}/*.qrc"
)

# 查找翻译文件
file(GLOB TS_FILES
    "${CMAKE_SOURCE_DIR}/translations/*.ts"
)

# 指定 qm 输出目录
set(QM_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/assets/translations)

# 如果输出目录不存在，则创建输出目录
if(NOT EXISTS ${QM_OUTPUT_DIR})
    file(MAKE_DIRECTORY ${QM_OUTPUT_DIR})
endif()

set_source_files_properties(${TS_FILES}
    PROPERTIES OUTPUT_LOCATION ${QM_OUTPUT_DIR})

# 生成 .qm 文件
qt_add_lrelease(
    TS_FILES ${TS_FILES}
)

# 复制到 QM_OUTPUT_DIR 中
# add_custom_target(translations_target ALL DEPENDS ${QM_FILES})
# add_custom_command(TARGET translations_target POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         ${QM_FILES}
#         ${QM_OUTPUT_DIR}
# )

# -----------------------------
# 创建可执行文件目标
# -----------------------------

# 使用收集到的文件创建可执行文件
add_executable(LuoguDesktop
    ${SRC_FILES}
    ${UI_FILES}
    ${QRC_FILES}
    ${TS_FILES}
)

# -----------------------------
# 链接 Qt6 模块
# -----------------------------

# 将 Qt6 的库链接到我们的目标
target_link_libraries(LuoguDesktop PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::WebEngineWidgets
    Qt6::Svg
)

# 将 KF6 的库链接到我们的目标
target_link_libraries(LuoguDesktop PRIVATE
    KF6::CoreAddons
    KF6::WidgetsAddons
    KF6::I18n
    KF6::XmlGui
    KF6::TextWidgets
)

target_include_directories(LuoguDesktop PRIVATE
    "${CMAKE_SOURCE_DIR}/Craft/include/KF6/KWidgetsAddons"
)

# -----------------------------
# 平台特定的配置
# -----------------------------

if(WIN32)
    # Windows (MSVC) 特定设置
    # 设置编译器标志，确保源文件为 UTF-8 编码
    target_compile_options(LuoguDesktop PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)

    # 添加 Poco 和 OpenSSL 的头文件路径
    target_include_directories(LuoguDesktop PRIVATE
        "${CMAKE_SOURCE_DIR}/Poco/include"
        "C:/Program Files/OpenSSL-Win64/include"
    )

    # 链接 Poco 和 OpenSSL 的库
    target_link_libraries(LuoguDesktop PRIVATE
        -L"${CMAKE_SOURCE_DIR}/Poco/lib64"
        -lPocoFoundation -lPocoNet -lPocoNetSSL -lPocoUtil
        -L"C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD"
        -llibssl -llibcrypto
    )

elseif(UNIX AND NOT APPLE)
    # Linux/Unix (非 macOS) 特定设置
    target_include_directories(LuoguDesktop PRIVATE
        /usr/include/Poco
    )
    target_link_libraries(LuoguDesktop PRIVATE
        -lPocoFoundation -lPocoNet -lPocoNetSSL -lPocoUtil
    )

elseif(APPLE)
    # macOS 特定设置
    target_include_directories(LuoguDesktop PRIVATE
        /usr/local/opt/poco/include
        /usr/local/opt/openssl/include
    )
    target_link_libraries(LuoguDesktop PRIVATE
        -L/usr/local/opt/poco/lib
        -L/usr/local/opt/openssl/lib
        -lPocoFoundation -lPocoNet -lPocoNetSSL -lPocoUtil
        -lcrypto -lssl
    )
endif()
