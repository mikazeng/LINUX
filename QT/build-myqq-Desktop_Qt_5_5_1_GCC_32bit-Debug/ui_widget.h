/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *qq;
    QLabel *youxi;
    QWidget *layoutWidget;
    QVBoxLayout *info;
    QLabel *ID;
    QLabel *psswd;
    QWidget *layoutWidget1;
    QVBoxLayout *EditInfo;
    QLineEdit *IDEdit;
    QLineEdit *pass_Edit;
    QWidget *layoutWidget2;
    QHBoxLayout *Layout;
    QPushButton *registbtn;
    QPushButton *loginBtn;
    QPushButton *eixtBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(413, 319);
        Widget->setMinimumSize(QSize(413, 319));
        Widget->setMaximumSize(QSize(413, 319));
        qq = new QLabel(Widget);
        qq->setObjectName(QStringLiteral("qq"));
        qq->setEnabled(true);
        qq->setGeometry(QRect(0, 0, 421, 121));
        qq->setPixmap(QPixmap(QString::fromUtf8(":/images/images/qq.png")));
        qq->setScaledContents(false);
        youxi = new QLabel(Widget);
        youxi->setObjectName(QStringLiteral("youxi"));
        youxi->setGeometry(QRect(10, 130, 111, 111));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 130, 71, 101));
        info = new QVBoxLayout(layoutWidget);
        info->setSpacing(6);
        info->setContentsMargins(11, 11, 11, 11);
        info->setObjectName(QStringLiteral("info"));
        info->setContentsMargins(0, 0, 0, 0);
        ID = new QLabel(layoutWidget);
        ID->setObjectName(QStringLiteral("ID"));
        QFont font;
        font.setPointSize(14);
        ID->setFont(font);

        info->addWidget(ID);

        psswd = new QLabel(layoutWidget);
        psswd->setObjectName(QStringLiteral("psswd"));
        psswd->setEnabled(true);
        psswd->setFont(font);

        info->addWidget(psswd);

        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(200, 110, 191, 141));
        EditInfo = new QVBoxLayout(layoutWidget1);
        EditInfo->setSpacing(6);
        EditInfo->setContentsMargins(11, 11, 11, 11);
        EditInfo->setObjectName(QStringLiteral("EditInfo"));
        EditInfo->setContentsMargins(0, 0, 0, 0);
        IDEdit = new QLineEdit(layoutWidget1);
        IDEdit->setObjectName(QStringLiteral("IDEdit"));

        EditInfo->addWidget(IDEdit);

        pass_Edit = new QLineEdit(layoutWidget1);
        pass_Edit->setObjectName(QStringLiteral("pass_Edit"));

        EditInfo->addWidget(pass_Edit);

        layoutWidget2 = new QWidget(Widget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 271, 381, 32));
        Layout = new QHBoxLayout(layoutWidget2);
        Layout->setSpacing(6);
        Layout->setContentsMargins(11, 11, 11, 11);
        Layout->setObjectName(QStringLiteral("Layout"));
        Layout->setContentsMargins(0, 0, 0, 0);
        registbtn = new QPushButton(layoutWidget2);
        registbtn->setObjectName(QStringLiteral("registbtn"));

        Layout->addWidget(registbtn);

        loginBtn = new QPushButton(layoutWidget2);
        loginBtn->setObjectName(QStringLiteral("loginBtn"));

        Layout->addWidget(loginBtn);

        eixtBtn = new QPushButton(layoutWidget2);
        eixtBtn->setObjectName(QStringLiteral("eixtBtn"));

        Layout->addWidget(eixtBtn);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "QQ_by ZRL", 0));
        qq->setText(QString());
        youxi->setText(QString());
        ID->setText(QApplication::translate("Widget", "\347\224\250\346\210\267ID:", 0));
        psswd->setText(QApplication::translate("Widget", "\345\257\206\347\240\201:", 0));
        registbtn->setText(QApplication::translate("Widget", "\346\263\250\345\206\214", 0));
        loginBtn->setText(QApplication::translate("Widget", "\347\231\273\345\275\225", 0));
        eixtBtn->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
