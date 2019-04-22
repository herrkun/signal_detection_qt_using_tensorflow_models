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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_9;
    QPushButton *pushButton_5;
    QLabel *label_10;
    QLineEdit *lineEdit_10;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1161, 751);
        Dialog->setStyleSheet(QStringLiteral("background-color: rgb(81, 81, 121);"));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(430, 660, 161, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QStringLiteral("background-color: rgb(85, 85, 127);"));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(330, 20, 141, 21));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(530, 20, 81, 21));
        label_2->setFont(font1);
        label_2->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(330, 50, 151, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(13);
        lineEdit->setFont(font2);
        lineEdit_2 = new QLineEdit(Dialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(530, 50, 151, 31));
        lineEdit_2->setFont(font2);
        comboBox = new QComboBox(Dialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(70, 60, 181, 31));
        comboBox->setFont(font1);
        comboBox->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_2 = new QPushButton(Dialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(770, 660, 151, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(13);
        font3.setBold(false);
        font3.setWeight(50);
        pushButton_2->setFont(font3);
        pushButton_2->setStyleSheet(QStringLiteral("background-color: rgb(85, 85, 127);"));
        comboBox_2 = new QComboBox(Dialog);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(70, 130, 181, 31));
        comboBox_2->setFont(font1);
        comboBox_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineEdit_3 = new QLineEdit(Dialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(70, 330, 181, 31));
        QFont font4;
        font4.setPointSize(13);
        font4.setBold(true);
        font4.setWeight(75);
        lineEdit_3->setFont(font4);
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 300, 101, 20));
        QFont font5;
        font5.setPointSize(11);
        font5.setBold(true);
        font5.setWeight(75);
        label_3->setFont(font5);
        label_3->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        comboBox_3 = new QComboBox(Dialog);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(70, 190, 181, 31));
        comboBox_3->setFont(font1);
        comboBox_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lineEdit_4 = new QLineEdit(Dialog);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(70, 260, 61, 28));
        lineEdit_4->setFont(font4);
        lineEdit_5 = new QLineEdit(Dialog);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(180, 260, 61, 28));
        lineEdit_5->setFont(font4);
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(145, 265, 21, 16));
        label_4->setFont(font5);
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 230, 81, 20));
        label_5->setFont(font5);
        label_5->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        pushButton_3 = new QPushButton(Dialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(40, 380, 151, 31));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font6.setPointSize(13);
        font6.setBold(false);
        font6.setWeight(50);
        pushButton_3->setFont(font6);
        pushButton_3->setStyleSheet(QStringLiteral("background-color: rgb(85, 85, 127);"));
        lineEdit_6 = new QLineEdit(Dialog);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(40, 430, 271, 31));
        QFont font7;
        font7.setPointSize(11);
        lineEdit_6->setFont(font7);
        pushButton_4 = new QPushButton(Dialog);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(40, 480, 151, 31));
        pushButton_4->setFont(font6);
        pushButton_4->setStyleSheet(QStringLiteral("background-color: rgb(85, 85, 127);"));
        lineEdit_7 = new QLineEdit(Dialog);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(40, 530, 271, 31));
        lineEdit_7->setFont(font7);
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 20, 101, 31));
        label_6->setFont(font5);
        label_6->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 90, 101, 31));
        label_7->setFont(font5);
        label_7->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_8 = new QLabel(Dialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 160, 101, 31));
        label_8->setFont(font5);
        label_8->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_9 = new QLabel(Dialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(720, 20, 101, 20));
        label_9->setFont(font1);
        label_9->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lineEdit_8 = new QLineEdit(Dialog);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(720, 50, 151, 31));
        lineEdit_8->setFont(font2);
        progressBar = new QProgressBar(Dialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(330, 570, 751, 31));
        progressBar->setValue(24);
        verticalLayoutWidget = new QWidget(Dialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(329, 109, 761, 431));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_9 = new QLineEdit(Dialog);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(40, 630, 271, 31));
        lineEdit_9->setFont(font7);
        pushButton_5 = new QPushButton(Dialog);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(40, 580, 151, 31));
        pushButton_5->setFont(font6);
        pushButton_5->setStyleSheet(QStringLiteral("background-color: rgb(85, 85, 127);"));
        label_10 = new QLabel(Dialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(920, 20, 101, 20));
        label_10->setFont(font1);
        label_10->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        lineEdit_10 = new QLineEdit(Dialog);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        lineEdit_10->setGeometry(QRect(920, 50, 151, 31));
        lineEdit_10->setFont(font2);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Dialog", "Run_Model", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "Model_Run_State", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog", "PyStatues", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("Dialog", "Run_State", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Dialog", "Refresh_signal", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("Dialog", "10000", Q_NULLPTR));
        label_3->setText(QApplication::translate("Dialog", "Batch Size", Q_NULLPTR));
        lineEdit_4->setText(QApplication::translate("Dialog", "0", Q_NULLPTR));
        lineEdit_5->setText(QApplication::translate("Dialog", "0", Q_NULLPTR));
        label_4->setText(QApplication::translate("Dialog", "--", Q_NULLPTR));
        label_5->setText(QApplication::translate("Dialog", "Fre_Range", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Dialog", "File Path", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("Dialog", "Model Path", Q_NULLPTR));
        label_6->setText(QApplication::translate("Dialog", "Pre_process", Q_NULLPTR));
        label_7->setText(QApplication::translate("Dialog", "Filter_meth", Q_NULLPTR));
        label_8->setText(QApplication::translate("Dialog", "Wavelets", Q_NULLPTR));
        label_9->setText(QApplication::translate("Dialog", "Pred Proces", Q_NULLPTR));
        lineEdit_8->setText(QApplication::translate("Dialog", "non_process", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("Dialog", "Data Save Path", Q_NULLPTR));
        label_10->setText(QApplication::translate("Dialog", "Temp State", Q_NULLPTR));
        lineEdit_10->setText(QApplication::translate("Dialog", "non_process", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
