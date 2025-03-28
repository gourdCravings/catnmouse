/********************************************************************************
** Form generated from reading UI file 'canvasdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANVASDIALOG_H
#define UI_CANVASDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CanvasDialog
{
public:
    QDialogButtonBox *buttonBox;
    QFrame *sizeFrame;
    QGridLayout *gridLayout;
    QLabel *widthLabel;
    QSpinBox *widthSpin;
    QLabel *heightLabel;
    QSpinBox *heightSpin;

    void setupUi(QDialog *CanvasDialog)
    {
        if (CanvasDialog->objectName().isEmpty())
            CanvasDialog->setObjectName("CanvasDialog");
        CanvasDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(CanvasDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Orientation::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        sizeFrame = new QFrame(CanvasDialog);
        sizeFrame->setObjectName("sizeFrame");
        sizeFrame->setGeometry(QRect(0, 0, 281, 301));
        sizeFrame->setFrameShape(QFrame::Shape::NoFrame);
        sizeFrame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout = new QGridLayout(sizeFrame);
        gridLayout->setObjectName("gridLayout");
        widthLabel = new QLabel(sizeFrame);
        widthLabel->setObjectName("widthLabel");

        gridLayout->addWidget(widthLabel, 0, 0, 1, 1);

        widthSpin = new QSpinBox(sizeFrame);
        widthSpin->setObjectName("widthSpin");
        widthSpin->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        widthSpin->setMinimum(1);
        widthSpin->setMaximum(9999);

        gridLayout->addWidget(widthSpin, 0, 1, 1, 1);

        heightLabel = new QLabel(sizeFrame);
        heightLabel->setObjectName("heightLabel");

        gridLayout->addWidget(heightLabel, 1, 0, 1, 1);

        heightSpin = new QSpinBox(sizeFrame);
        heightSpin->setObjectName("heightSpin");
        heightSpin->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        heightSpin->setMinimum(1);
        heightSpin->setMaximum(9999);

        gridLayout->addWidget(heightSpin, 1, 1, 1, 1);

        sizeFrame->raise();
        buttonBox->raise();

        retranslateUi(CanvasDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, CanvasDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, CanvasDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(CanvasDialog);
    } // setupUi

    void retranslateUi(QDialog *CanvasDialog)
    {
        CanvasDialog->setWindowTitle(QCoreApplication::translate("CanvasDialog", "Dialog", nullptr));
        widthLabel->setText(QCoreApplication::translate("CanvasDialog", "Width", nullptr));
        heightLabel->setText(QCoreApplication::translate("CanvasDialog", "Height", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CanvasDialog: public Ui_CanvasDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANVASDIALOG_H
