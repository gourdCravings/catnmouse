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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "canvaswidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QWidget *brushWidget;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *colorSelectButton;
    QSpinBox *widthSpin;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_5;
    QWidget *toolButtonWidget;
    QGridLayout *gridLayout_2;
    QToolButton *brushButton;
    QToolButton *panButton;
    QToolButton *liquifyButton;
    QToolButton *textButton;
    QToolButton *smudgeButton;
    QToolButton *selectButton;
    QToolButton *eyedropButton;
    QToolButton *lineButton;
    QToolButton *zoomButton;
    QToolButton *transformButton;
    QToolButton *fillButton;
    QToolButton *eraseButton;
    QWidget *layerWidget;
    QGridLayout *gridLayout;
    QPushButton *addLayerBtn;
    QListView *layerListView;
    QSpacerItem *horizontalSpacer;
    CanvasWidget *canvasWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(883, 574);
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
        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        colorSelectButton = new QPushButton(brushWidget);
        colorSelectButton->setObjectName("colorSelectButton");

        gridLayout_3->addWidget(colorSelectButton, 0, 1, 1, 1);

        widthSpin = new QSpinBox(brushWidget);
        widthSpin->setObjectName("widthSpin");
        widthSpin->setMinimum(1);
        widthSpin->setMaximum(10000);

        gridLayout_3->addWidget(widthSpin, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(60, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 2, 1, 1);


        gridLayout_4->addWidget(brushWidget, 0, 3, 2, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 0, 2, 1, 1);

        toolButtonWidget = new QWidget(centralwidget);
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
        brushButton = new QToolButton(toolButtonWidget);
        brushButton->setObjectName("brushButton");

        gridLayout_2->addWidget(brushButton, 0, 2, 1, 1);

        panButton = new QToolButton(toolButtonWidget);
        panButton->setObjectName("panButton");

        gridLayout_2->addWidget(panButton, 0, 0, 1, 1);

        liquifyButton = new QToolButton(toolButtonWidget);
        liquifyButton->setObjectName("liquifyButton");

        gridLayout_2->addWidget(liquifyButton, 1, 0, 1, 1);

        textButton = new QToolButton(toolButtonWidget);
        textButton->setObjectName("textButton");

        gridLayout_2->addWidget(textButton, 0, 5, 1, 1);

        smudgeButton = new QToolButton(toolButtonWidget);
        smudgeButton->setObjectName("smudgeButton");

        gridLayout_2->addWidget(smudgeButton, 0, 4, 1, 1);

        selectButton = new QToolButton(toolButtonWidget);
        selectButton->setObjectName("selectButton");

        gridLayout_2->addWidget(selectButton, 0, 1, 1, 1);

        eyedropButton = new QToolButton(toolButtonWidget);
        eyedropButton->setObjectName("eyedropButton");

        gridLayout_2->addWidget(eyedropButton, 1, 3, 1, 1);

        lineButton = new QToolButton(toolButtonWidget);
        lineButton->setObjectName("lineButton");

        gridLayout_2->addWidget(lineButton, 1, 4, 1, 1);

        zoomButton = new QToolButton(toolButtonWidget);
        zoomButton->setObjectName("zoomButton");

        gridLayout_2->addWidget(zoomButton, 1, 5, 1, 1);

        transformButton = new QToolButton(toolButtonWidget);
        transformButton->setObjectName("transformButton");

        gridLayout_2->addWidget(transformButton, 1, 1, 1, 1);

        fillButton = new QToolButton(toolButtonWidget);
        fillButton->setObjectName("fillButton");

        gridLayout_2->addWidget(fillButton, 0, 3, 1, 1);

        eraseButton = new QToolButton(toolButtonWidget);
        eraseButton->setObjectName("eraseButton");
        QFont font;
        font.setPointSize(9);
        eraseButton->setFont(font);

        gridLayout_2->addWidget(eraseButton, 1, 2, 1, 1);


        gridLayout_4->addWidget(toolButtonWidget, 0, 0, 1, 2);

        layerWidget = new QWidget(centralwidget);
        layerWidget->setObjectName("layerWidget");
        layerWidget->setMaximumSize(QSize(300, 300));
        gridLayout = new QGridLayout(layerWidget);
        gridLayout->setObjectName("gridLayout");
        addLayerBtn = new QPushButton(layerWidget);
        addLayerBtn->setObjectName("addLayerBtn");

        gridLayout->addWidget(addLayerBtn, 0, 1, 1, 1);

        layerListView = new QListView(layerWidget);
        layerListView->setObjectName("layerListView");

        gridLayout->addWidget(layerListView, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(165, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);


        gridLayout_4->addWidget(layerWidget, 2, 3, 1, 1);

        canvasWidget = new CanvasWidget(centralwidget);
        canvasWidget->setObjectName("canvasWidget");
        sizePolicy.setHeightForWidth(canvasWidget->sizePolicy().hasHeightForWidth());
        canvasWidget->setSizePolicy(sizePolicy);
        canvasWidget->setMinimumSize(QSize(500, 350));

        gridLayout_4->addWidget(canvasWidget, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        brushWidget->raise();
        layerWidget->raise();
        toolButtonWidget->raise();
        canvasWidget->raise();
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
        colorSelectButton->setText(QCoreApplication::translate("MainWindow", "Select Color", nullptr));
        brushButton->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        panButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        liquifyButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        textButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        smudgeButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        selectButton->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        eyedropButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        lineButton->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        zoomButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        transformButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        fillButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        eraseButton->setText(QCoreApplication::translate("MainWindow", "E", nullptr));
        addLayerBtn->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
