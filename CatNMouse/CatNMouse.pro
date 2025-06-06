QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brushdialog.cpp \
    canvasdialog.cpp \
    canvaslayer.cpp \
    canvasview.cpp \
    canvaswidget.cpp \
    catbrush.cpp \
    catbrush_OLD.cpp \
    colordialog.cpp \
    layerlayout.cpp \
    layermodel.cpp \
    main.cpp \
    mainwindow.cpp \
    selectiontool.cpp

HEADERS += \
    brushdialog.h \
    canvasdialog.h \
    canvaslayer.h \
    canvasview.h \
    canvaswidget.h \
    catbrush.h \
    catbrush_OLD.h \
    colordialog.h \
    layerlayout.h \
    layermodel.h \
    mainwindow.h \
    selectiontool.h

FORMS += \
    brushdialog.ui \
    canvasdialog.ui \
    colordialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
