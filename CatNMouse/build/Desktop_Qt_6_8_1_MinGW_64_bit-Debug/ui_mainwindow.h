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
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layerWidget;
    QGridLayout *gridLayout;
    QPushButton *addLayerBtn;
    QListView *layerListView;
    QWidget *canvasWidget;
    QWidget *toolBarWidget;
    QWidget *toolButtonWidget;
    QGridLayout *gridLayout_2;
    QToolButton *panButton;
    QToolButton *selectButton;
    QToolButton *brushButton;
    QToolButton *fillButton;
    QToolButton *smudgeButton;
    QToolButton *textButton;
    QToolButton *liquifyButton;
    QToolButton *transformButton;
    QToolButton *eraseButton;
    QToolButton *eyedropButton;
    QToolButton *lineButton;
    QToolButton *zoomButton;
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

        layerListView = new QListView(layerWidget);
        layerListView->setObjectName("layerListView");

        gridLayout->addWidget(layerListView, 1, 0, 1, 1);

        canvasWidget = new QWidget(centralwidget);
        canvasWidget->setObjectName("canvasWidget");
        canvasWidget->setGeometry(QRect(11, 91, 581, 411));
        toolBarWidget = new QWidget(centralwidget);
        toolBarWidget->setObjectName("toolBarWidget");
        toolBarWidget->setGeometry(QRect(9, 0, 581, 80));
        toolButtonWidget = new QWidget(toolBarWidget);
        toolButtonWidget->setObjectName("toolButtonWidget");
        toolButtonWidget->setGeometry(QRect(0, 0, 207, 83));
        gridLayout_2 = new QGridLayout(toolButtonWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        panButton = new QToolButton(toolButtonWidget);
        panButton->setObjectName("panButton");

        gridLayout_2->addWidget(panButton, 0, 0, 1, 1);

        selectButton = new QToolButton(toolButtonWidget);
        selectButton->setObjectName("selectButton");

        gridLayout_2->addWidget(selectButton, 0, 1, 1, 1);

        brushButton = new QToolButton(toolButtonWidget);
        brushButton->setObjectName("brushButton");

        gridLayout_2->addWidget(brushButton, 0, 2, 1, 1);

        fillButton = new QToolButton(toolButtonWidget);
        fillButton->setObjectName("fillButton");

        gridLayout_2->addWidget(fillButton, 0, 3, 1, 1);

        smudgeButton = new QToolButton(toolButtonWidget);
        smudgeButton->setObjectName("smudgeButton");

        gridLayout_2->addWidget(smudgeButton, 0, 4, 1, 1);

        textButton = new QToolButton(toolButtonWidget);
        textButton->setObjectName("textButton");

        gridLayout_2->addWidget(textButton, 0, 5, 1, 1);

        liquifyButton = new QToolButton(toolButtonWidget);
        liquifyButton->setObjectName("liquifyButton");

        gridLayout_2->addWidget(liquifyButton, 1, 0, 1, 1);

        transformButton = new QToolButton(toolButtonWidget);
        transformButton->setObjectName("transformButton");

        gridLayout_2->addWidget(transformButton, 1, 1, 1, 1);

        eraseButton = new QToolButton(toolButtonWidget);
        eraseButton->setObjectName("eraseButton");
        QFont font;
        font.setPointSize(9);
        eraseButton->setFont(font);

        gridLayout_2->addWidget(eraseButton, 1, 2, 1, 1);

        eyedropButton = new QToolButton(toolButtonWidget);
        eyedropButton->setObjectName("eyedropButton");

        gridLayout_2->addWidget(eyedropButton, 1, 3, 1, 1);

        lineButton = new QToolButton(toolButtonWidget);
        lineButton->setObjectName("lineButton");

        gridLayout_2->addWidget(lineButton, 1, 4, 1, 1);

        zoomButton = new QToolButton(toolButtonWidget);
        zoomButton->setObjectName("zoomButton");

        gridLayout_2->addWidget(zoomButton, 1, 5, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 881, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addLayerBtn->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        panButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        selectButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        brushButton->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        fillButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        smudgeButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        textButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        liquifyButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        transformButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        eraseButton->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        eyedropButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        lineButton->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        zoomButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
