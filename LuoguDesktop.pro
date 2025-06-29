QT += core gui widgets network

CONFIG += c++14

win32-msvc*:QMAKE_CXXFLAGS += /utf-8
# QMAKE_LFLAGS += "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""

SOURCES += \
    $$files($$PWD/src/*.cpp) \
    $$files($$PWD/src/Auth/*.cpp) \
    $$files($$PWD/src/Config/*.cpp) \
    $$files($$PWD/src/Login/*.cpp) \
    $$files($$PWD/src/GetBackground/*.cpp) \
    $$files($$PWD/src/RoundedBlurWidget/*.cpp)

HEADERS += \
    $$files($$PWD/src/*.h) \
    $$files($$PWD/src/Auth/*.h) \
    $$files($$PWD/src/Config/*.h) \
    $$files($$PWD/src/Login/*.h) \
    $$files($$PWD/src/GetBackground/*.h) \
    $$files($$PWD/src/RoundedBlurWidget/*.h)

FORMS += $$PWD/src/LuoguDesktop.ui

RESOURCES += \
    $$files($$PWD/assets.qrc)

INCLUDEPATH += /usr/include/Poco
LIBS += -lPocoFoundation -lPocoNet -lPocoNetSSL -lPocoUtil

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target