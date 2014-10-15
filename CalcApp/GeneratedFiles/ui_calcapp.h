/********************************************************************************
** Form generated from reading UI file 'calcapp.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCAPP_H
#define UI_CALCAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "commandline.h"

QT_BEGIN_NAMESPACE

class Ui_CalcAppClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    CommandLine *commandLine;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *console;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CalcAppClass)
    {
        if (CalcAppClass->objectName().isEmpty())
            CalcAppClass->setObjectName(QStringLiteral("CalcAppClass"));
        CalcAppClass->resize(735, 568);
        centralWidget = new QWidget(CalcAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_4 = new QHBoxLayout(centralWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        commandLine = new CommandLine(groupBox);
        commandLine->setObjectName(QStringLiteral("commandLine"));

        horizontalLayout->addWidget(commandLine);

        splitter->addWidget(groupBox);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        console = new QTextEdit(groupBox_2);
        console->setObjectName(QStringLiteral("console"));

        horizontalLayout_2->addWidget(console);

        splitter->addWidget(groupBox_2);

        horizontalLayout_3->addWidget(splitter);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        CalcAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CalcAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 735, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        CalcAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CalcAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CalcAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CalcAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CalcAppClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());

        retranslateUi(CalcAppClass);

        QMetaObject::connectSlotsByName(CalcAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *CalcAppClass)
    {
        CalcAppClass->setWindowTitle(QApplication::translate("CalcAppClass", "CalcApp", 0));
        groupBox->setTitle(QApplication::translate("CalcAppClass", "Command line", 0));
        groupBox_2->setTitle(QApplication::translate("CalcAppClass", "Console", 0));
        menuFile->setTitle(QApplication::translate("CalcAppClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class CalcAppClass: public Ui_CalcAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCAPP_H
