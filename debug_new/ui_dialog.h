/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QPushButton *pushButton_2;
    QComboBox *comboBox_2;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_3;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit_7;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_8;
    QProgressBar *progressBar;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(698, 541);
        Dialog->setStyleSheet(QStringLiteral("background-color: rgb(81, 81, 121);"));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(80, 450, 161, 41));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 40, 71, 21));
        label->setFont(font);
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 90, 81, 31));
        label_2->setFont(font);
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(150, 30, 113, 31));
        QFont font1;
        font1.setPointSize(10);
        lineEdit->setFont(font1);
        lineEdit_2 = new QLineEdit(Dialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(150, 90, 113, 31));
        lineEdit_2->setFont(font1);
        comboBox = new QComboBox(Dialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(410, 30, 181, 31));
        QFont font2;
        font2.setPointSize(11);
        comboBox->setFont(font2);
        pushButton_2 = new QPushButton(Dialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 450, 151, 41));
        pushButton_2->setFont(font);
        comboBox_2 = new QComboBox(Dialog);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(410, 90, 181, 31));
        comboBox_2->setFont(font2);
        lineEdit_3 = new QLineEdit(Dialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(150, 150, 113, 31));
        lineEdit_3->setFont(font1);
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 150, 101, 20));
        label_3->setFont(font);
        comboBox_3 = new QComboBox(Dialog);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(410, 150, 181, 31));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(false);
        font3.setWeight(50);
        comboBox_3->setFont(font3);
        lineEdit_4 = new QLineEdit(Dialog);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(370, 220, 41, 21));
        lineEdit_4->setFont(font1);
        lineEdit_5 = new QLineEdit(Dialog);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(470, 220, 41, 21));
        lineEdit_5->setFont(font1);
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(430, 220, 21, 16));
        label_4->setFont(font);
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(410, 190, 71, 20));
        label_5->setFont(font2);
        pushButton_3 = new QPushButton(Dialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(60, 282, 151, 31));
        pushButton_3->setFont(font2);
        lineEdit_6 = new QLineEdit(Dialog);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(250, 279, 321, 31));
        lineEdit_6->setFont(font2);
        pushButton_4 = new QPushButton(Dialog);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(60, 332, 151, 31));
        pushButton_4->setFont(font2);
        lineEdit_7 = new QLineEdit(Dialog);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(250, 330, 321, 31));
        lineEdit_7->setFont(font2);
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(300, 30, 101, 31));
        label_6->setFont(font);
        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(300, 90, 101, 31));
        label_7->setFont(font);
        label_8 = new QLabel(Dialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(300, 150, 101, 31));
        label_8->setFont(font);
        label_9 = new QLabel(Dialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(50, 210, 101, 20));
        label_9->setFont(font);
        lineEdit_8 = new QLineEdit(Dialog);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(150, 210, 161, 31));
        lineEdit_8->setFont(font1);
        progressBar = new QProgressBar(Dialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(60, 400, 541, 23));
        progressBar->setValue(24);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Dialog", "LoadRun", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "TempParam1", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog", "PyStatues", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Dialog", "Refresh", Q_NULLPTR));
        label_3->setText(QApplication::translate("Dialog", "Batch Size", Q_NULLPTR));
        label_4->setText(QApplication::translate("Dialog", "--", Q_NULLPTR));
        label_5->setText(QApplication::translate("Dialog", "\351\242\221\347\216\207\350\214\203\345\233\264", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Dialog", "File Path", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("Dialog", "Model Path", Q_NULLPTR));
        label_6->setText(QApplication::translate("Dialog", "Pre_process", Q_NULLPTR));
        label_7->setText(QApplication::translate("Dialog", "Filter_meth", Q_NULLPTR));
        label_8->setText(QApplication::translate("Dialog", "Wavelets", Q_NULLPTR));
        label_9->setText(QApplication::translate("Dialog", "Pred Proces", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
