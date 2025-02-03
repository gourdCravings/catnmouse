/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layerWidget;
    QGridLayout *gridLayout;
    QPushButton *addLayerBtn;
    QListWidget *layerListW;
    QWidget *canvasWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(881, 574);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layerWidget = new QWidget(centralwidget);
        layerWidget->setObjectName("layerWidget");
        layerWidget->setGeometry(QRect(592, 263, 278, 250));
        gridLayout = new QGridLayout(layerWidget);
        gridLayout->setObjectName("gridLayout");
        addLayerBtn = new QPushButton(layerWidget);
        addLayerBtn->setObjectName("addLayerBtn");

        gridLayout->addWidget(addLayerBtn, 0, 0, 1, 1, Qt::AlignmentFlag::AlignLeft);

        layerListW = new QListWidget(layerWidget);
        layerListW->setObjectName("layerListW");
        layerListW->setSortingEnabled(false);

        gridLayout->addWidget(layerListW, 1, 0, 1, 1);

        canvasWidget = new QWidget(centralwidget);
        canvasWidget->setObjectName("canvasWidget");
        canvasWidget->setGeometry(QRect(11, 11, 581, 491));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 881, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        layerListW->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addLayerBtn->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
