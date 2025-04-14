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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QUndoView>
#include <QtWidgets/QWidget>
#include "canvasview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QWidget *brushWidget;
    QGridLayout *gridLayout_3;
    QWidget *toolButtonWidget;
    QGridLayout *gridLayout_2;
    QToolButton *lineButton;
    QToolButton *transformButton;
    QToolButton *selectButton;
    QToolButton *brushButton;
    QToolButton *panButton;
    QToolButton *smudgeButton;
    QToolButton *eraseButton;
    QToolButton *liquifyButton;
    QToolButton *eyedropButton;
    QToolButton *fillButton;
    QToolButton *zoomButton;
    QToolButton *textButton;
    QWidget *layerWidget;
    QGridLayout *gridLayout;
    QPushButton *colorSelectButton;
    QPushButton *addLayerBtn;
    QListView *layerListView;
    QUndoView *undoView;
    QSpinBox *widthSpin;
    QWidget *canvasWidget;
    QGridLayout *gridLayout_5;
    CanvasView *canvasView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(883, 662);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName("gridLayout_4");
        brushWidget = new QWidget(centralwidget);
        brushWidget->setObjectName("brushWidget");
        brushWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        gridLayout_3 = new QGridLayout(brushWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        toolButtonWidget = new QWidget(brushWidget);
        toolButtonWidget->setObjectName("toolButtonWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolButtonWidget->sizePolicy().hasHeightForWidth());
        toolButtonWidget->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(toolButtonWidget);
        gridLayout_2->setSpacing(7);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        lineButton = new QToolButton(toolButtonWidget);
        lineButton->setObjectName("lineButton");

        gridLayout_2->addWidget(lineButton, 1, 4, 1, 1);

        transformButton = new QToolButton(toolButtonWidget);
        transformButton->setObjectName("transformButton");

        gridLayout_2->addWidget(transformButton, 1, 1, 1, 1);

        selectButton = new QToolButton(toolButtonWidget);
        selectButton->setObjectName("selectButton");

        gridLayout_2->addWidget(selectButton, 0, 1, 1, 1);

        brushButton = new QToolButton(toolButtonWidget);
        brushButton->setObjectName("brushButton");

        gridLayout_2->addWidget(brushButton, 0, 2, 1, 1);

        panButton = new QToolButton(toolButtonWidget);
        panButton->setObjectName("panButton");

        gridLayout_2->addWidget(panButton, 0, 0, 1, 1);

        smudgeButton = new QToolButton(toolButtonWidget);
        smudgeButton->setObjectName("smudgeButton");

        gridLayout_2->addWidget(smudgeButton, 0, 4, 1, 1);

        eraseButton = new QToolButton(toolButtonWidget);
        eraseButton->setObjectName("eraseButton");
        QFont font;
        font.setPointSize(9);
        eraseButton->setFont(font);

        gridLayout_2->addWidget(eraseButton, 1, 2, 1, 1);

        liquifyButton = new QToolButton(toolButtonWidget);
        liquifyButton->setObjectName("liquifyButton");

        gridLayout_2->addWidget(liquifyButton, 1, 0, 1, 1);

        eyedropButton = new QToolButton(toolButtonWidget);
        eyedropButton->setObjectName("eyedropButton");

        gridLayout_2->addWidget(eyedropButton, 1, 3, 1, 1);

        fillButton = new QToolButton(toolButtonWidget);
        fillButton->setObjectName("fillButton");

        gridLayout_2->addWidget(fillButton, 0, 3, 1, 1);

        zoomButton = new QToolButton(toolButtonWidget);
        zoomButton->setObjectName("zoomButton");

        gridLayout_2->addWidget(zoomButton, 1, 5, 1, 1);

        textButton = new QToolButton(toolButtonWidget);
        textButton->setObjectName("textButton");

        gridLayout_2->addWidget(textButton, 0, 5, 1, 1);


        gridLayout_3->addWidget(toolButtonWidget, 0, 2, 1, 1);

        layerWidget = new QWidget(brushWidget);
        layerWidget->setObjectName("layerWidget");
        layerWidget->setMaximumSize(QSize(300, 300));
        gridLayout = new QGridLayout(layerWidget);
        gridLayout->setObjectName("gridLayout");
        colorSelectButton = new QPushButton(layerWidget);
        colorSelectButton->setObjectName("colorSelectButton");
        colorSelectButton->setMaximumSize(QSize(200, 200));

        gridLayout->addWidget(colorSelectButton, 2, 0, 1, 1);

        addLayerBtn = new QPushButton(layerWidget);
        addLayerBtn->setObjectName("addLayerBtn");
        addLayerBtn->setMaximumSize(QSize(200, 200));

        gridLayout->addWidget(addLayerBtn, 3, 0, 1, 1);

        layerListView = new QListView(layerWidget);
        layerListView->setObjectName("layerListView");
        layerListView->setMaximumSize(QSize(200, 500));

        gridLayout->addWidget(layerListView, 4, 0, 1, 1);

        undoView = new QUndoView(layerWidget);
        undoView->setObjectName("undoView");
        undoView->setMaximumSize(QSize(200, 500));

        gridLayout->addWidget(undoView, 0, 0, 1, 1);

        widthSpin = new QSpinBox(layerWidget);
        widthSpin->setObjectName("widthSpin");
        widthSpin->setMaximumSize(QSize(200, 50));
        widthSpin->setMinimum(1);
        widthSpin->setMaximum(10000);

        gridLayout->addWidget(widthSpin, 1, 0, 1, 1);


        gridLayout_3->addWidget(layerWidget, 1, 3, 1, 1);

        canvasWidget = new QWidget(brushWidget);
        canvasWidget->setObjectName("canvasWidget");
        gridLayout_5 = new QGridLayout(canvasWidget);
        gridLayout_5->setObjectName("gridLayout_5");
        canvasView = new CanvasView(canvasWidget);
        canvasView->setObjectName("canvasView");
        canvasView->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        gridLayout_5->addWidget(canvasView, 0, 0, 1, 1);


        gridLayout_3->addWidget(canvasWidget, 1, 2, 1, 1);


        gridLayout_4->addWidget(brushWidget, 0, 2, 2, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 883, 25));
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
        lineButton->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        transformButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        selectButton->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        brushButton->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        panButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        smudgeButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        eraseButton->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        liquifyButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        eyedropButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        fillButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        zoomButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        textButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        colorSelectButton->setText(QCoreApplication::translate("MainWindow", "Select Color", nullptr));
        addLayerBtn->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
