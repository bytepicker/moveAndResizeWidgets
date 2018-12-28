/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_1;
    QAction *action;
    QAction *action_2;
    QWidget *centralWidget;
    QWidget *iconWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *iconLayout;
    QPushButton *pushButton_1;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_4;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(731, 429);
        action_1 = new QAction(MainWindow);
        action_1->setObjectName(QStringLiteral("action_1"));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        iconWidget = new QWidget(centralWidget);
        iconWidget->setObjectName(QStringLiteral("iconWidget"));
        iconWidget->setGeometry(QRect(10, 10, 491, 91));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(iconWidget->sizePolicy().hasHeightForWidth());
        iconWidget->setSizePolicy(sizePolicy);
        horizontalLayoutWidget = new QWidget(iconWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(-1, -1, 491, 74));
        iconLayout = new QHBoxLayout(horizontalLayoutWidget);
        iconLayout->setSpacing(6);
        iconLayout->setContentsMargins(11, 11, 11, 11);
        iconLayout->setObjectName(QStringLiteral("iconLayout"));
        iconLayout->setSizeConstraint(QLayout::SetMaximumSize);
        iconLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_1 = new QPushButton(horizontalLayoutWidget);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setIconSize(QSize(64, 64));

        iconLayout->addWidget(pushButton_1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        iconLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setIconSize(QSize(64, 64));

        iconLayout->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        iconLayout->addItem(horizontalSpacer_2);

        pushButton_3 = new QPushButton(horizontalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setIconSize(QSize(64, 64));

        iconLayout->addWidget(pushButton_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        iconLayout->addItem(horizontalSpacer_4);

        pushButton_4 = new QPushButton(horizontalLayoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setIconSize(QSize(64, 64));

        iconLayout->addWidget(pushButton_4);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action_1->setText(QApplication::translate("MainWindow", "+1", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214", Q_NULLPTR));
        action_2->setText(QApplication::translate("MainWindow", "\320\241\320\272\321\200\321\213\321\202\321\214", Q_NULLPTR));
        pushButton_1->setText(QApplication::translate("MainWindow", "All label", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Add table", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Add calendar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_4->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_4->setText(QApplication::translate("MainWindow", "Clear all", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
