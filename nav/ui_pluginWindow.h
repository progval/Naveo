/********************************************************************************
** Form generated from reading UI file 'pluginWindow.ui'
**
** Created: Sun 10. Oct 13:44:18 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINWINDOW_H
#define UI_PLUGINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pluginWin
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;

    void setupUi(QDialog *pluginWin)
    {
        if (pluginWin->objectName().isEmpty())
            pluginWin->setObjectName(QString::fromUtf8("pluginWin"));
        pluginWin->setWindowModality(Qt::WindowModal);
        pluginWin->resize(390, 310);
        pluginWin->setMinimumSize(QSize(390, 310));
        pluginWin->setMaximumSize(QSize(390, 310));
        pluginWin->setModal(true);
        verticalLayoutWidget = new QWidget(pluginWin);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 371, 291));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(verticalLayoutWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMaximumSize(QSize(55, 16777215));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(pluginWin);
        QObject::connect(pushButton_2, SIGNAL(clicked()), pluginWin, SLOT(accept()));

        QMetaObject::connectSlotsByName(pluginWin);
    } // setupUi

    void retranslateUi(QDialog *pluginWin)
    {
        pluginWin->setWindowTitle(QApplication::translate("pluginWin", "Plug-in disponibles", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("pluginWin", "Installer", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("pluginWin", "Fermer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class pluginWin: public Ui_pluginWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINWINDOW_H
