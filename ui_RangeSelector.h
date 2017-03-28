/********************************************************************************
** Form generated from reading UI file 'RangeSelector.ui'
**
** Created: Wed 24. Oct 14:25:01 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANGESELECTOR_H
#define UI_RANGESELECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDial>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RangeSelector
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButtonApply;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QDial *dialCenterSelector;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_c;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QDial *dialWidthSelector;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_r;
    QSpinBox *spinBox_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *RangeSelector)
    {
        if (RangeSelector->objectName().isEmpty())
            RangeSelector->setObjectName(QString::fromUtf8("RangeSelector"));
        RangeSelector->resize(304, 362);
        RangeSelector->setAutoFillBackground(true);
        gridLayout = new QGridLayout(RangeSelector);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonApply = new QPushButton(RangeSelector);
        pushButtonApply->setObjectName(QString::fromUtf8("pushButtonApply"));

        gridLayout->addWidget(pushButtonApply, 2, 0, 1, 1);

        label = new QLabel(RangeSelector);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAutoFillBackground(false);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        dialCenterSelector = new QDial(RangeSelector);
        dialCenterSelector->setObjectName(QString::fromUtf8("dialCenterSelector"));
        dialCenterSelector->setMinimum(2);
        dialCenterSelector->setMaximum(4095);
        dialCenterSelector->setPageStep(2000);
        dialCenterSelector->setSliderPosition(128);
        dialCenterSelector->setWrapping(true);
        dialCenterSelector->setNotchTarget(16.7);
        dialCenterSelector->setNotchesVisible(true);

        verticalLayout->addWidget(dialCenterSelector);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label_c = new QLabel(RangeSelector);
        label_c->setObjectName(QString::fromUtf8("label_c"));

        horizontalLayout_2->addWidget(label_c);

        spinBox = new QSpinBox(RangeSelector);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(4096);
        spinBox->setValue(128);

        horizontalLayout_2->addWidget(spinBox);

        horizontalSpacer_3 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        dialWidthSelector = new QDial(RangeSelector);
        dialWidthSelector->setObjectName(QString::fromUtf8("dialWidthSelector"));
        dialWidthSelector->setMinimum(1);
        dialWidthSelector->setMaximum(2048);
        dialWidthSelector->setPageStep(1000);
        dialWidthSelector->setValue(128);
        dialWidthSelector->setSliderPosition(128);
        dialWidthSelector->setWrapping(true);
        dialWidthSelector->setNotchTarget(14.7);
        dialWidthSelector->setNotchesVisible(true);

        verticalLayout_2->addWidget(dialWidthSelector);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_r = new QLabel(RangeSelector);
        label_r->setObjectName(QString::fromUtf8("label_r"));

        horizontalLayout->addWidget(label_r);

        spinBox_2 = new QSpinBox(RangeSelector);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(2048);
        spinBox_2->setValue(128);

        horizontalLayout->addWidget(spinBox_2);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        retranslateUi(RangeSelector);
        QObject::connect(dialCenterSelector, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(dialWidthSelector, SIGNAL(valueChanged(int)), spinBox_2, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), dialCenterSelector, SLOT(setValue(int)));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), dialWidthSelector, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(editingFinished()), dialCenterSelector, SLOT(repaint()));
        QObject::connect(spinBox_2, SIGNAL(editingFinished()), dialWidthSelector, SLOT(repaint()));

        QMetaObject::connectSlotsByName(RangeSelector);
    } // setupUi

    void retranslateUi(QWidget *RangeSelector)
    {
        RangeSelector->setWindowTitle(QApplication::translate("RangeSelector", "Form", 0, QApplication::UnicodeUTF8));
        pushButtonApply->setText(QApplication::translate("RangeSelector", "Aplicar", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_c->setText(QApplication::translate("RangeSelector", "Centro", 0, QApplication::UnicodeUTF8));
        label_r->setText(QApplication::translate("RangeSelector", "Rango", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RangeSelector: public Ui_RangeSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANGESELECTOR_H
