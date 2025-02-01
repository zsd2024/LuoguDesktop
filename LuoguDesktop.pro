QT += core gui widgets network

CONFIG += c++14

win32-msvc*:QMAKE_CXXFLAGS += /utf-8
# QMAKE_LFLAGS += "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""

SOURCES += \
    $$files($$PWD/src/*.cpp) \
    $$files($$PWD/src/Login/*.cpp)

HEADERS += \
    $$files($$PWD/src/*.h) \
    $$files($$PWD/src/Login/*.h)

FORMS += $$PWD/src/LuoguDesktop.ui

RESOURCES += \
    $$files($$PWD/assets.qrc)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target