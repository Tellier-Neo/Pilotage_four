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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QGroupBox *statsBox;
    QLabel *powerStatLabel;
    QLabel *consigneStatLabel;
    QLabel *tempStatLabel;
    QListWidget *graphicBox;
    QSlider *consigneSlider;
    QLabel *consigneValue;
    QListWidget *cardLogBox;
    QLabel *cardLogLabel;
    QLabel *label;
    QGraphicsView *temperatureGraphView;
    QLabel *tempGraphLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FourClass)
    {
        if (FourClass->objectName().isEmpty())
            FourClass->setObjectName(QString::fromUtf8("FourClass"));
        FourClass->resize(568, 923);
        centralWidget = new QWidget(FourClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        powerSlider = new QSlider(centralWidget);
        powerSlider->setObjectName(QString::fromUtf8("powerSlider"));
        powerSlider->setGeometry(QRect(220, 60, 111, 22));
        powerSlider->setMaximum(100);
        powerSlider->setOrientation(Qt::Horizontal);
        powerLabel = new QLabel(centralWidget);
        powerLabel->setObjectName(QString::fromUtf8("powerLabel"));
        powerLabel->setGeometry(QRect(80, 60, 131, 21));
        powerLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        powerValue = new QLabel(centralWidget);
        powerValue->setObjectName(QString::fromUtf8("powerValue"));
        powerValue->setGeometry(QRect(340, 60, 61, 21));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(230, 100, 81, 31));
        tempLabel = new QLabel(centralWidget);
        tempLabel->setObjectName(QString::fromUtf8("tempLabel"));
        tempLabel->setGeometry(QRect(80, 30, 131, 21));
        tempLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        statsBox = new QGroupBox(centralWidget);
        statsBox->setObjectName(QString::fromUtf8("statsBox"));
        statsBox->setGeometry(QRect(19, 159, 241, 91));
        powerStatLabel = new QLabel(statsBox);
        powerStatLabel->setObjectName(QString::fromUtf8("powerStatLabel"));
        powerStatLabel->setGeometry(QRect(10, 20, 221, 21));
        consigneStatLabel = new QLabel(statsBox);
        consigneStatLabel->setObjectName(QString::fromUtf8("consigneStatLabel"));
        consigneStatLabel->setGeometry(QRect(10, 40, 221, 21));
        tempStatLabel = new QLabel(statsBox);
        tempStatLabel->setObjectName(QString::fromUtf8("tempStatLabel"));
        tempStatLabel->setGeometry(QRect(10, 60, 221, 21));
        graphicBox = new QListWidget(centralWidget);
        graphicBox->setObjectName(QString::fromUtf8("graphicBox"));
        graphicBox->setGeometry(QRect(270, 180, 281, 261));
        consigneSlider = new QSlider(centralWidget);
        consigneSlider->setObjectName(QString::fromUtf8("consigneSlider"));
        consigneSlider->setGeometry(QRect(220, 30, 111, 22));
        consigneSlider->setMinimum(20);
        consigneSlider->setMaximum(65);
        consigneSlider->setOrientation(Qt::Horizontal);
        consigneValue = new QLabel(centralWidget);
        consigneValue->setObjectName(QString::fromUtf8("consigneValue"));
        consigneValue->setGeometry(QRect(340, 30, 61, 21));
        cardLogBox = new QListWidget(centralWidget);
        cardLogBox->setObjectName(QString::fromUtf8("cardLogBox"));
        cardLogBox->setGeometry(QRect(20, 270, 241, 171));
        cardLogLabel = new QLabel(centralWidget);
        cardLogLabel->setObjectName(QString::fromUtf8("cardLogLabel"));
        cardLogLabel->setGeometry(QRect(20, 250, 231, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 160, 281, 21));
        temperatureGraphView = new QGraphicsView(centralWidget);
        temperatureGraphView->setObjectName(QString::fromUtf8("temperatureGraphView"));
        temperatureGraphView->setGeometry(QRect(20, 470, 531, 391));
        tempGraphLabel = new QLabel(centralWidget);
        tempGraphLabel->setObjectName(QString::fromUtf8("tempGraphLabel"));
        tempGraphLabel->setGeometry(QRect(26, 450, 521, 21));
        FourClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FourClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 568, 22));
        FourClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FourClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        FourClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FourClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FourClass->setStatusBar(statusBar);

        retranslateUi(FourClass);
        QObject::connect(pushButton, SIGNAL(clicked()), FourClass, SLOT(OnFourButtonClicked()));
        QObject::connect(powerSlider, SIGNAL(valueChanged(int)), FourClass, SLOT(SetPower(int)));
        QObject::connect(consigneSlider, SIGNAL(valueChanged(int)), FourClass, SLOT(SetConsigne(int)));

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
        consigneStatLabel->setText(QCoreApplication::translate("FourClass", "Consigne: 20.C", nullptr));
        tempStatLabel->setText(QCoreApplication::translate("FourClass", "Temperature actuelle: 0\302\260C", nullptr));
        consigneValue->setText(QCoreApplication::translate("FourClass", "20.C", nullptr));
        cardLogLabel->setText(QCoreApplication::translate("FourClass", "Console carte", nullptr));
        label->setText(QCoreApplication::translate("FourClass", "R\303\251sultats temp\303\251rature", nullptr));
        tempGraphLabel->setText(QCoreApplication::translate("FourClass", "Interpr\303\251tation graphique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FourClass: public Ui_FourClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOUR_H
