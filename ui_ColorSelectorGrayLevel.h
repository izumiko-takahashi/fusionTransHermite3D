/********************************************************************************
** Form generated from reading UI file 'ColorSelectorGrayLevel.ui'
**
** Created: Fri 14. Sep 11:02:33 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORSELECTORGRAYLEVEL_H
#define UI_COLORSELECTORGRAYLEVEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorSelector
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBoxInitGrayLevel;
    QLabel *labelColorInit;
    QPushButton *pushButtonDialogColorInit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *spinBoxLastGrayLevel;
    QLabel *labelColorLast;
    QPushButton *pushButtonColorDialogLast;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonApplyColor;
    QPushButton *buttonCloseWidget;

    void setupUi(QWidget *ColorSelector)
    {
        if (ColorSelector->objectName().isEmpty())
            ColorSelector->setObjectName(QString::fromUtf8("ColorSelector"));
        ColorSelector->resize(275, 197);
        layoutWidget = new QWidget(ColorSelector);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 12, 251, 171));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        spinBoxInitGrayLevel = new QSpinBox(layoutWidget);
        spinBoxInitGrayLevel->setObjectName(QString::fromUtf8("spinBoxInitGrayLevel"));
        spinBoxInitGrayLevel->setMinimum(1);
        spinBoxInitGrayLevel->setMaximum(4096);
        spinBoxInitGrayLevel->setSingleStep(64);

        horizontalLayout->addWidget(spinBoxInitGrayLevel);

        labelColorInit = new QLabel(layoutWidget);
        labelColorInit->setObjectName(QString::fromUtf8("labelColorInit"));

        horizontalLayout->addWidget(labelColorInit);

        pushButtonDialogColorInit = new QPushButton(layoutWidget);
        pushButtonDialogColorInit->setObjectName(QString::fromUtf8("pushButtonDialogColorInit"));

        horizontalLayout->addWidget(pushButtonDialogColorInit);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setTextFormat(Qt::AutoText);

        horizontalLayout_2->addWidget(label_2);

        spinBoxLastGrayLevel = new QSpinBox(layoutWidget);
        spinBoxLastGrayLevel->setObjectName(QString::fromUtf8("spinBoxLastGrayLevel"));
        spinBoxLastGrayLevel->setMinimum(1);
        spinBoxLastGrayLevel->setMaximum(4096);
        spinBoxLastGrayLevel->setSingleStep(64);

        horizontalLayout_2->addWidget(spinBoxLastGrayLevel);

        labelColorLast = new QLabel(layoutWidget);
        labelColorLast->setObjectName(QString::fromUtf8("labelColorLast"));

        horizontalLayout_2->addWidget(labelColorLast);

        pushButtonColorDialogLast = new QPushButton(layoutWidget);
        pushButtonColorDialogLast->setObjectName(QString::fromUtf8("pushButtonColorDialogLast"));

        horizontalLayout_2->addWidget(pushButtonColorDialogLast);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonApplyColor = new QPushButton(layoutWidget);
        buttonApplyColor->setObjectName(QString::fromUtf8("buttonApplyColor"));

        horizontalLayout_3->addWidget(buttonApplyColor);

        buttonCloseWidget = new QPushButton(layoutWidget);
        buttonCloseWidget->setObjectName(QString::fromUtf8("buttonCloseWidget"));

        horizontalLayout_3->addWidget(buttonCloseWidget);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ColorSelector);
        QObject::connect(buttonCloseWidget, SIGNAL(clicked()), ColorSelector, SLOT(close()));

        QMetaObject::connectSlotsByName(ColorSelector);
    } // setupUi

    void retranslateUi(QWidget *ColorSelector)
    {
        ColorSelector->setWindowTitle(QApplication::translate("ColorSelector", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ColorSelector", "Punto Inicial", 0, QApplication::UnicodeUTF8));
        labelColorInit->setText(QString());
        pushButtonDialogColorInit->setText(QApplication::translate("ColorSelector", "...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ColorSelector", "Punto   Final", 0, QApplication::UnicodeUTF8));
        labelColorLast->setText(QString());
        pushButtonColorDialogLast->setText(QApplication::translate("ColorSelector", "...", 0, QApplication::UnicodeUTF8));
        buttonApplyColor->setText(QApplication::translate("ColorSelector", "Aplicar", 0, QApplication::UnicodeUTF8));
        buttonCloseWidget->setText(QApplication::translate("ColorSelector", "Cerrar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ColorSelector: public Ui_ColorSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORSELECTORGRAYLEVEL_H
