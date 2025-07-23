QT += core gui widgets webenginewidgets svg

CONFIG += c++14

win32-msvc*:QMAKE_CXXFLAGS += /utf-8
# QMAKE_LFLAGS += "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""

SOURCES += \
    $$files($$PWD/src/*.cpp) \
    $$files($$PWD/src/Auth/*.cpp) \
    $$files($$PWD/src/Common/*.cpp) \
    $$files($$PWD/src/Config/*.cpp) \
    $$files($$PWD/src/Contest/*.cpp) \
    $$files($$PWD/src/Discuss/*.cpp) \
    $$files($$PWD/src/Latex/*.cpp) \
    $$files($$PWD/src/Login/*.cpp) \
    $$files($$PWD/src/MarkdownViewer/*.cpp) \
    $$files($$PWD/src/GetBackground/*.cpp) \
    $$files($$PWD/src/RoundedWidget/*.cpp)

HEADERS += \
    $$files($$PWD/src/*.h) \
    $$files($$PWD/src/Auth/*.h) \
    $$files($$PWD/src/Common/*.h) \
    $$files($$PWD/src/Config/*.h) \
    $$files($$PWD/src/Contest/*.h) \
    $$files($$PWD/src/Discuss/*.h) \
    $$files($$PWD/src/Latex/*.h) \
    $$files($$PWD/src/Login/*.h) \
    $$files($$PWD/src/MarkdownViewer/*.h) \
    $$files($$PWD/src/GetBackground/*.h) \
    $$files($$PWD/src/RoundedWidget/*.h)

FORMS += $$PWD/src/LuoguDesktop.ui

RESOURCES += \
    $$files($$PWD/assets.qrc)

win32 {
    INCLUDEPATH += "../Poco/include" "C:/Program Files/OpenSSL-Win64/include"
    LIBS += -L"../Poco/lib64"\
            -lPocoFoundation -lPocoNet -lPocoNetSSL -lPocoUtil\
            -L"C:/Program Files/OpenSSL-Win64/lib/VC/x64/MD"\
            -llibssl -llibcrypto
}

unix {
    INCLUDEPATH += /usr/include/Poco
    LIBS += -lPocoFoundation -lPocoNet -lPocoNetSSL -lPocoUtil
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target