/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QLabel *label;
    QTableWidget *tableWidget;
    QLabel *savedLabel;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *compressBtn;
    QPushButton *deCompBtn;
    QPushButton *prettyBtn;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *jsonBtn;
    QPushButton *miniBtn;
    QPlainTextEdit *plainTextEdit;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1048, 632);
        MainWindow->setStyleSheet(QString::fromUtf8("MainWindow{\n"
"background-color: #EEEEEE;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe UI Semibold"));
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);

        verticalLayout->addWidget(pushButton);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Segoe UI Semibold"));
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        verticalLayout->addWidget(label);

        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMinimumSize(QSize(312, 0));
        tableWidget->setBaseSize(QSize(0, 0));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget{\n"
"min-width:310px;\n"
"}"));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout->addWidget(tableWidget);

        savedLabel = new QLabel(centralwidget);
        savedLabel->setObjectName(QString::fromUtf8("savedLabel"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Segoe UI Semibold"));
        font2.setPointSize(10);
        savedLabel->setFont(font2);

        verticalLayout->addWidget(savedLabel);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Consolas"));
        font3.setPointSize(10);
        groupBox->setFont(font3);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	min-height:135px;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        compressBtn = new QPushButton(groupBox);
        compressBtn->setObjectName(QString::fromUtf8("compressBtn"));
        compressBtn->setFont(font);

        horizontalLayout->addWidget(compressBtn);

        deCompBtn = new QPushButton(groupBox);
        deCompBtn->setObjectName(QString::fromUtf8("deCompBtn"));
        deCompBtn->setFont(font);

        horizontalLayout->addWidget(deCompBtn);

        prettyBtn = new QPushButton(groupBox);
        prettyBtn->setObjectName(QString::fromUtf8("prettyBtn"));
        prettyBtn->setFont(font);

        horizontalLayout->addWidget(prettyBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        jsonBtn = new QPushButton(groupBox);
        jsonBtn->setObjectName(QString::fromUtf8("jsonBtn"));
        jsonBtn->setFont(font);

        horizontalLayout_3->addWidget(jsonBtn);

        miniBtn = new QPushButton(groupBox);
        miniBtn->setObjectName(QString::fromUtf8("miniBtn"));
        miniBtn->setFont(font);

        horizontalLayout_3->addWidget(miniBtn);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(groupBox);


        horizontalLayout_2->addLayout(verticalLayout);

        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setEnabled(true);
        QFont font4;
        font4.setFamily(QString::fromUtf8("Consolas"));
        plainTextEdit->setFont(font4);
        plainTextEdit->setReadOnly(false);

        horizontalLayout_2->addWidget(plainTextEdit);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setFont(font4);
        textBrowser->setUndoRedoEnabled(true);
        textBrowser->setReadOnly(false);

        horizontalLayout_2->addWidget(textBrowser);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1048, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "XML Editor", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Open Files", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "File Name", nullptr));
        savedLabel->setText(QCoreApplication::translate("MainWindow", "No Opened Files", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
        compressBtn->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        deCompBtn->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        prettyBtn->setText(QCoreApplication::translate("MainWindow", "Prettifying", nullptr));
        jsonBtn->setText(QCoreApplication::translate("MainWindow", "Convert to JSON", nullptr));
        miniBtn->setText(QCoreApplication::translate("MainWindow", "Minifying", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
