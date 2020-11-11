QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/choseobj.cpp \
    src/createlist.cpp \
    src/createobj.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/tinyxml2.cpp

HEADERS += \
    src/choseobj.h \
    src/createlist.h \
    src/createobj.h \
    src/mainwindow.h \
    src/tinyxml2.h

FORMS += \
    ui_forms/choseobj.ui \
    ui_forms/createlist.ui \
    ui_forms/createobj.ui \
    ui_forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
