/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openFiles;
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listFiles;
    QPushButton *run;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *displayImage;
    QCheckBox *overlay;
    QMenuBar *menubar;
    QMenu *menu_Files;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(861, 722);
        openFiles = new QAction(MainWindow);
        openFiles->setObjectName(QStringLiteral("openFiles"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(9, 9, 258, 621));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        listFiles = new QListWidget(widget);
        listFiles->setObjectName(QStringLiteral("listFiles"));

        verticalLayout_2->addWidget(listFiles);

        run = new QPushButton(widget);
        run->setObjectName(QStringLiteral("run"));

        verticalLayout_2->addWidget(run);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(334, 9, 501, 611));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        displayImage = new QLabel(widget1);
        displayImage->setObjectName(QStringLiteral("displayImage"));

        verticalLayout_3->addWidget(displayImage);

        overlay = new QCheckBox(widget1);
        overlay->setObjectName(QStringLiteral("overlay"));

        verticalLayout_3->addWidget(overlay);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 861, 25));
        menu_Files = new QMenu(menubar);
        menu_Files->setObjectName(QStringLiteral("menu_Files"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_Files->menuAction());
        menu_Files->addSeparator();
        menu_Files->addAction(openFiles);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        openFiles->setText(QApplication::translate("MainWindow", "Open files", 0));
        run->setText(QApplication::translate("MainWindow", "run", 0));
        displayImage->setText(QString());
        overlay->setText(QApplication::translate("MainWindow", "overlay", 0));
        menu_Files->setTitle(QApplication::translate("MainWindow", "&File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
