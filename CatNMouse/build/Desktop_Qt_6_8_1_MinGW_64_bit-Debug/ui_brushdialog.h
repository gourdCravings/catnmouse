/********************************************************************************
** Form generated from reading UI file 'brushdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRUSHDIALOG_H
#define UI_BRUSHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_BrushDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidget;

    void setupUi(QDialog *BrushDialog)
    {
        if (BrushDialog->objectName().isEmpty())
            BrushDialog->setObjectName("BrushDialog");
        BrushDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(BrushDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        listWidget = new QListWidget(BrushDialog);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(20, 30, 351, 201));

        retranslateUi(BrushDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, BrushDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, BrushDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(BrushDialog);
    } // setupUi

    void retranslateUi(QDialog *BrushDialog)
    {
        BrushDialog->setWindowTitle(QCoreApplication::translate("BrushDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BrushDialog: public Ui_BrushDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRUSHDIALOG_H
