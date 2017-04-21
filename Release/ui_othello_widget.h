/********************************************************************************
** Form generated from reading UI file 'othello_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OTHELLO_WIDGET_H
#define UI_OTHELLO_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Othello_Widget
{
public:
    QPushButton *pushButton;
    QPushButton *about_me;
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_4;

    void setupUi(QWidget *Othello_Widget)
    {
        if (Othello_Widget->objectName().isEmpty())
            Othello_Widget->setObjectName(QStringLiteral("Othello_Widget"));
        Othello_Widget->resize(1300, 700);
        pushButton = new QPushButton(Othello_Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1000, 100, 180, 70));
        pushButton->setMouseTracking(true);
        pushButton->setAcceptDrops(true);
        pushButton->setAutoFillBackground(false);
        pushButton->setStyleSheet(QLatin1String("\n"
"border-radius: 3px;"));
        pushButton->setAutoDefault(true);
        pushButton->setFlat(true);
        about_me = new QPushButton(Othello_Widget);
        about_me->setObjectName(QStringLiteral("about_me"));
        about_me->setGeometry(QRect(1000, 430, 180, 70));
        label = new QLabel(Othello_Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(500, 30, 300, 50));
        label->setStyleSheet(QLatin1String("font-size: 25px;\n"
"color: red"));
        layoutWidget = new QWidget(Othello_Widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(1020, 190, 141, 101));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(layoutWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setChecked(false);
        radioButton->setAutoExclusive(true);

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(layoutWidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setChecked(true);
        radioButton_2->setAutoExclusive(true);

        verticalLayout->addWidget(radioButton_2);

        layoutWidget1 = new QWidget(Othello_Widget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(1020, 310, 141, 111));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        radioButton_3 = new QRadioButton(layoutWidget1);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setCheckable(true);
        radioButton_3->setChecked(true);

        verticalLayout_2->addWidget(radioButton_3);

        radioButton_5 = new QRadioButton(layoutWidget1);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));

        verticalLayout_2->addWidget(radioButton_5);

        radioButton_4 = new QRadioButton(layoutWidget1);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        verticalLayout_2->addWidget(radioButton_4);


        retranslateUi(Othello_Widget);

        pushButton->setDefault(true);


        QMetaObject::connectSlotsByName(Othello_Widget);
    } // setupUi

    void retranslateUi(QWidget *Othello_Widget)
    {
        Othello_Widget->setWindowTitle(QApplication::translate("Othello_Widget", "Othello_Widget", Q_NULLPTR));
        about_me->setText(QString());
        label->setText(QString());
        radioButton->setText(QApplication::translate("Othello_Widget", "Single Player", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("Othello_Widget", "Two Player", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("Othello_Widget", "Easy", Q_NULLPTR));
        radioButton_5->setText(QApplication::translate("Othello_Widget", "Medium", Q_NULLPTR));
        radioButton_4->setText(QApplication::translate("Othello_Widget", "Hard(can be slow)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Othello_Widget: public Ui_Othello_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OTHELLO_WIDGET_H
