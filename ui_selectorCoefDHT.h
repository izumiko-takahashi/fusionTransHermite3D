/********************************************************************************
** Form generated from reading UI file 'selectorCoefDHT.ui'
**
** Created: Tue 2. Oct 14:01:17 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTORCOEFDHT_H
#define UI_SELECTORCOEFDHT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_selectorCoefDHT
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QRadioButton *rbOriginal;
    QRadioButton *rb000;
    QRadioButton *rb010;
    QRadioButton *rb100;
    QRadioButton *rb001;
    QRadioButton *rb110;
    QRadioButton *rb101;
    QRadioButton *rb020;
    QRadioButton *rb011;
    QRadioButton *rb002;
    QRadioButton *rb200;
    QRadioButton *rbGradient;

    void setupUi(QWidget *selectorCoefDHT)
    {
        if (selectorCoefDHT->objectName().isEmpty())
            selectorCoefDHT->setObjectName(QString::fromUtf8("selectorCoefDHT"));
        selectorCoefDHT->resize(298, 179);
        gridLayout_2 = new QGridLayout(selectorCoefDHT);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        rbOriginal = new QRadioButton(selectorCoefDHT);
        rbOriginal->setObjectName(QString::fromUtf8("rbOriginal"));

        gridLayout->addWidget(rbOriginal, 0, 0, 1, 1);

        rb000 = new QRadioButton(selectorCoefDHT);
        rb000->setObjectName(QString::fromUtf8("rb000"));

        gridLayout->addWidget(rb000, 0, 1, 1, 2);

        rb010 = new QRadioButton(selectorCoefDHT);
        rb010->setObjectName(QString::fromUtf8("rb010"));

        gridLayout->addWidget(rb010, 0, 3, 1, 3);

        rb100 = new QRadioButton(selectorCoefDHT);
        rb100->setObjectName(QString::fromUtf8("rb100"));

        gridLayout->addWidget(rb100, 1, 0, 1, 1);

        rb001 = new QRadioButton(selectorCoefDHT);
        rb001->setObjectName(QString::fromUtf8("rb001"));

        gridLayout->addWidget(rb001, 1, 1, 1, 2);

        rb110 = new QRadioButton(selectorCoefDHT);
        rb110->setObjectName(QString::fromUtf8("rb110"));

        gridLayout->addWidget(rb110, 1, 3, 1, 3);

        rb101 = new QRadioButton(selectorCoefDHT);
        rb101->setObjectName(QString::fromUtf8("rb101"));

        gridLayout->addWidget(rb101, 2, 0, 1, 1);

        rb020 = new QRadioButton(selectorCoefDHT);
        rb020->setObjectName(QString::fromUtf8("rb020"));

        gridLayout->addWidget(rb020, 3, 0, 1, 1);

        rb011 = new QRadioButton(selectorCoefDHT);
        rb011->setObjectName(QString::fromUtf8("rb011"));

        gridLayout->addWidget(rb011, 2, 1, 1, 2);

        rb002 = new QRadioButton(selectorCoefDHT);
        rb002->setObjectName(QString::fromUtf8("rb002"));

        gridLayout->addWidget(rb002, 3, 1, 1, 2);

        rb200 = new QRadioButton(selectorCoefDHT);
        rb200->setObjectName(QString::fromUtf8("rb200"));

        gridLayout->addWidget(rb200, 2, 3, 1, 3);

        rbGradient = new QRadioButton(selectorCoefDHT);
        rbGradient->setObjectName(QString::fromUtf8("rbGradient"));

        gridLayout->addWidget(rbGradient, 3, 3, 1, 3);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(selectorCoefDHT);

        QMetaObject::connectSlotsByName(selectorCoefDHT);
    } // setupUi

    void retranslateUi(QWidget *selectorCoefDHT)
    {
        selectorCoefDHT->setWindowTitle(QApplication::translate("selectorCoefDHT", "Coeficientes de la Transformada Hermite", 0, QApplication::UnicodeUTF8));
        rbOriginal->setText(QApplication::translate("selectorCoefDHT", "Volumen Original", 0, QApplication::UnicodeUTF8));
        rb000->setText(QApplication::translate("selectorCoefDHT", "000", 0, QApplication::UnicodeUTF8));
        rb010->setText(QApplication::translate("selectorCoefDHT", "010", 0, QApplication::UnicodeUTF8));
        rb100->setText(QApplication::translate("selectorCoefDHT", "100", 0, QApplication::UnicodeUTF8));
        rb001->setText(QApplication::translate("selectorCoefDHT", "001", 0, QApplication::UnicodeUTF8));
        rb110->setText(QApplication::translate("selectorCoefDHT", "110", 0, QApplication::UnicodeUTF8));
        rb101->setText(QApplication::translate("selectorCoefDHT", "101", 0, QApplication::UnicodeUTF8));
        rb020->setText(QApplication::translate("selectorCoefDHT", "020", 0, QApplication::UnicodeUTF8));
        rb011->setText(QApplication::translate("selectorCoefDHT", "011", 0, QApplication::UnicodeUTF8));
        rb002->setText(QApplication::translate("selectorCoefDHT", "002", 0, QApplication::UnicodeUTF8));
        rb200->setText(QApplication::translate("selectorCoefDHT", "200", 0, QApplication::UnicodeUTF8));
        rbGradient->setText(QApplication::translate("selectorCoefDHT", "Gradiente", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class selectorCoefDHT: public Ui_selectorCoefDHT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTORCOEFDHT_H
