/********************************************************************************
** Form generated from reading UI file 'colordialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORDIALOG_H
#define UI_COLORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *redLabel;
    QLabel *greenLabel;
    QLabel *blueLabel;
    QVBoxLayout *verticalLayout_2;
    QSlider *redSlider;
    QSlider *greenSlider;
    QSlider *blueSlider;
    QVBoxLayout *verticalLayout_3;
    QSpinBox *redSpinBox;
    QSpinBox *greenSpinBox;
    QSpinBox *blueSpinBox;
    QFrame *colorPreviewFrame;
    QLabel *colorPreview;

    void setupUi(QDialog *ColorDialog)
    {
        if (ColorDialog->objectName().isEmpty())
            ColorDialog->setObjectName("ColorDialog");
        ColorDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(ColorDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        layoutWidget = new QWidget(ColorDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 20, 341, 105));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        redLabel = new QLabel(layoutWidget);
        redLabel->setObjectName("redLabel");

        verticalLayout->addWidget(redLabel);

        greenLabel = new QLabel(layoutWidget);
        greenLabel->setObjectName("greenLabel");

        verticalLayout->addWidget(greenLabel);

        blueLabel = new QLabel(layoutWidget);
        blueLabel->setObjectName("blueLabel");

        verticalLayout->addWidget(blueLabel);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        redSlider = new QSlider(layoutWidget);
        redSlider->setObjectName("redSlider");
        redSlider->setMaximum(255);
        redSlider->setSliderPosition(0);
        redSlider->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_2->addWidget(redSlider);

        greenSlider = new QSlider(layoutWidget);
        greenSlider->setObjectName("greenSlider");
        greenSlider->setMaximum(255);
        greenSlider->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_2->addWidget(greenSlider);

        blueSlider = new QSlider(layoutWidget);
        blueSlider->setObjectName("blueSlider");
        blueSlider->setMaximum(255);
        blueSlider->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout_2->addWidget(blueSlider);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        redSpinBox = new QSpinBox(layoutWidget);
        redSpinBox->setObjectName("redSpinBox");
        redSpinBox->setMaximum(255);

        verticalLayout_3->addWidget(redSpinBox);

        greenSpinBox = new QSpinBox(layoutWidget);
        greenSpinBox->setObjectName("greenSpinBox");
        greenSpinBox->setMaximum(255);

        verticalLayout_3->addWidget(greenSpinBox);

        blueSpinBox = new QSpinBox(layoutWidget);
        blueSpinBox->setObjectName("blueSpinBox");
        blueSpinBox->setMaximum(255);

        verticalLayout_3->addWidget(blueSpinBox);


        horizontalLayout->addLayout(verticalLayout_3);

        colorPreviewFrame = new QFrame(ColorDialog);
        colorPreviewFrame->setObjectName("colorPreviewFrame");
        colorPreviewFrame->setGeometry(QRect(20, 119, 161, 151));
        colorPreviewFrame->setAutoFillBackground(false);
        colorPreviewFrame->setFrameShape(QFrame::Shape::StyledPanel);
        colorPreviewFrame->setFrameShadow(QFrame::Shadow::Raised);
        colorPreview = new QLabel(ColorDialog);
        colorPreview->setObjectName("colorPreview");
        colorPreview->setGeometry(QRect(30, 130, 141, 131));
        colorPreview->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(ColorDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ColorDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ColorDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ColorDialog);
    } // setupUi

    void retranslateUi(QDialog *ColorDialog)
    {
        ColorDialog->setWindowTitle(QCoreApplication::translate("ColorDialog", "Dialog", nullptr));
        redLabel->setText(QCoreApplication::translate("ColorDialog", "R", nullptr));
        greenLabel->setText(QCoreApplication::translate("ColorDialog", "G", nullptr));
        blueLabel->setText(QCoreApplication::translate("ColorDialog", "B", nullptr));
        colorPreview->setText(QCoreApplication::translate("ColorDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ColorDialog: public Ui_ColorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORDIALOG_H
