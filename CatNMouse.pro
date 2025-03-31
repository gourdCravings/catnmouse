QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brushdialog.cpp \
    canvaslayer.cpp \
    catbrush.cpp \
    catbrush_OLD.cpp \
    colordialog.cpp \
    layerlayout.cpp \
    layermodel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    brushdialog.h \
    canvaslayer.h \
    catbrush.h \
    catbrush_OLD.h \
    colordialog.h \
    layerlayout.h \
    layermodel.h \
    mainwindow.h

FORMS += \
    brushdialog.ui \
    colordialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
