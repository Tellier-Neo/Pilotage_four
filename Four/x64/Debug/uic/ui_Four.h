/********************************************************************************
** Form generated from reading UI file 'Four.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOUR_H
#define UI_FOUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FourClass
{
public:
    QWidget *centralWidget;
    QSlider *powerSlider;
    QLabel *powerLabel;
    QLabel *powerValue;
    QPushButton *pushButton;
    QLabel *tempLabel;
    QSpinBox *consigneLine;
    QGroupBox *statsBox;
    QLabel *powerStatLabel;
    QLabel *consigneStatLabel;
    QLabel *tempStatLabel;
    QListWidget *graphicBox;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FourClass)
    {
        if (FourClass->objectName().isEmpty())
            FourClass->setObjectName(QString::fromUtf8("FourClass"));
        FourClass->resize(491, 429);
        centralWidget = new QWidget(FourClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        powerSlider = new QSlider(centralWidget);
        powerSlider->setObjectName(QString::fromUtf8("powerSlider"));
        powerSlider->setGeometry(QRect(170, 60, 111, 22));
        powerSlider->setMaximum(100);
        powerSlider->setOrientation(Qt::Horizontal);
        powerLabel = new QLabel(centralWidget);
        powerLabel->setObjectName(QString::fromUtf8("powerLabel"));
        powerLabel->setGeometry(QRect(30, 60, 131, 21));
        powerLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        powerValue = new QLabel(centralWidget);
        powerValue->setObjectName(QString::fromUtf8("powerValue"));
        powerValue->setGeometry(QRect(290, 60, 61, 21));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(130, 100, 81, 31));
        tempLabel = new QLabel(centralWidget);
        tempLabel->setObjectName(QString::fromUtf8("tempLabel"));
        tempLabel->setGeometry(QRect(30, 30, 131, 21));
        tempLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        consigneLine = new QSpinBox(centralWidget);
        consigneLine->setObjectName(QString::fromUtf8("consigneLine"));
        consigneLine->setGeometry(QRect(170, 30, 121, 22));
        statsBox = new QGroupBox(centralWidget);
        statsBox->setObjectName(QString::fromUtf8("statsBox"));
        statsBox->setGeometry(QRect(19, 159, 191, 191));
        powerStatLabel = new QLabel(statsBox);
        powerStatLabel->setObjectName(QString::fromUtf8("powerStatLabel"));
        powerStatLabel->setGeometry(QRect(10, 20, 141, 21));
        consigneStatLabel = new QLabel(statsBox);
        consigneStatLabel->setObjectName(QString::fromUtf8("consigneStatLabel"));
        consigneStatLabel->setGeometry(QRect(10, 40, 141, 21));
        tempStatLabel = new QLabel(statsBox);
        tempStatLabel->setObjectName(QString::fromUtf8("tempStatLabel"));
        tempStatLabel->setGeometry(QRect(10, 60, 141, 21));
        graphicBox = new QListWidget(centralWidget);
        graphicBox->setObjectName(QString::fromUtf8("graphicBox"));
        graphicBox->setGeometry(QRect(220, 160, 256, 192));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 100, 81, 31));
        FourClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FourClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 491, 22));
        FourClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FourClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        FourClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FourClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FourClass->setStatusBar(statusBar);

        retranslateUi(FourClass);
        QObject::connect(pushButton, SIGNAL(clicked()), FourClass, SLOT(startHeat()));
        QObject::connect(powerSlider, SIGNAL(valueChanged(int)), FourClass, SLOT(SetPower(int)));
        QObject::connect(consigneLine, SIGNAL(valueChanged(int)), FourClass, SLOT(SetConsigne(int)));
        QObject::connect(pushButton_2, SIGNAL(clicked()), FourClass, SLOT(stopHeat()));

        QMetaObject::connectSlotsByName(FourClass);
    } // setupUi

    void retranslateUi(QMainWindow *FourClass)
    {
        FourClass->setWindowTitle(QCoreApplication::translate("FourClass", "Four", nullptr));
        powerLabel->setText(QCoreApplication::translate("FourClass", "Puissance temp\303\251rature", nullptr));
        powerValue->setText(QCoreApplication::translate("FourClass", "0%", nullptr));
        pushButton->setText(QCoreApplication::translate("FourClass", "Chauffer", nullptr));
        tempLabel->setText(QCoreApplication::translate("FourClass", "Consigne", nullptr));
        statsBox->setTitle(QCoreApplication::translate("FourClass", "Statistiques", nullptr));
        powerStatLabel->setText(QCoreApplication::translate("FourClass", "Puissance: 0%", nullptr));
        consigneStatLabel->setText(QCoreApplication::translate("FourClass", "Consigne: 0\302\260C", nullptr));
        tempStatLabel->setText(QCoreApplication::translate("FourClass", "Temp\303\251rature actuelle: 0\302\260C", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FourClass", "Arr\303\252t", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FourClass: public Ui_FourClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOUR_H
