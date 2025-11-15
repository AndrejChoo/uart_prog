/********************************************************************************
** Form generated from reading UI file 'uart_prog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UART_PROG_H
#define UI_UART_PROG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UART_Prog
{
public:
    QWidget *centralwidget;
    QComboBox *portCB;
    QPushButton *pScanBTN;
    QPushButton *pOpenBTN;
    QComboBox *baudCB;
    QPushButton *checkBTN;
    QTextEdit *consoleTB;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *fReadBTN;
    QPushButton *fEraseBTN;
    QPushButton *fWriteBTN;
    QPushButton *fVerifyBTN;
    QPushButton *fGetIdBTN;
    QPushButton *fRdSregBTN;
    QPushButton *fWrSregBTN;
    QPushButton *fLoadBTN;
    QPushButton *fSaveBTN;
    QLineEdit *fIdTB;
    QLineEdit *lSregTB;
    QLineEdit *hSregTB;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *fDevCB;
    QWidget *tab_3;
    QLabel *label_5;
    QComboBox *MW_ModelCB;
    QPushButton *MW_ReadBTN;
    QPushButton *MW_WriteBTN;
    QPushButton *MW_VerifyBTN;
    QPushButton *MW_LoadBTN;
    QPushButton *MW_SaveBTN;
    QPushButton *MW_EraseBTN;
    QWidget *tab_2;
    QPushButton *eeLoadBTN;
    QPushButton *eeSaveBTN;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *eeDevCB;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QPushButton *eeReadBTN;
    QPushButton *eeWriteBTN;
    QPushButton *eeVerifiBTN;
    QProgressBar *mainPB;
    QPlainTextEdit *mainTB;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UART_Prog)
    {
        if (UART_Prog->objectName().isEmpty())
            UART_Prog->setObjectName(QString::fromUtf8("UART_Prog"));
        UART_Prog->resize(730, 508);
        UART_Prog->setMinimumSize(QSize(730, 508));
        UART_Prog->setMaximumSize(QSize(730, 508));
        QFont font;
        font.setPointSize(9);
        UART_Prog->setFont(font);
        centralwidget = new QWidget(UART_Prog);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        portCB = new QComboBox(centralwidget);
        portCB->setObjectName(QString::fromUtf8("portCB"));
        portCB->setGeometry(QRect(640, 10, 72, 24));
        pScanBTN = new QPushButton(centralwidget);
        pScanBTN->setObjectName(QString::fromUtf8("pScanBTN"));
        pScanBTN->setGeometry(QRect(570, 10, 61, 24));
        pOpenBTN = new QPushButton(centralwidget);
        pOpenBTN->setObjectName(QString::fromUtf8("pOpenBTN"));
        pOpenBTN->setGeometry(QRect(500, 10, 61, 24));
        baudCB = new QComboBox(centralwidget);
        baudCB->addItem(QString());
        baudCB->addItem(QString());
        baudCB->addItem(QString());
        baudCB->addItem(QString());
        baudCB->addItem(QString());
        baudCB->addItem(QString());
        baudCB->addItem(QString());
        baudCB->addItem(QString());
        baudCB->setObjectName(QString::fromUtf8("baudCB"));
        baudCB->setGeometry(QRect(640, 40, 72, 24));
        checkBTN = new QPushButton(centralwidget);
        checkBTN->setObjectName(QString::fromUtf8("checkBTN"));
        checkBTN->setGeometry(QRect(500, 40, 131, 24));
        consoleTB = new QTextEdit(centralwidget);
        consoleTB->setObjectName(QString::fromUtf8("consoleTB"));
        consoleTB->setGeometry(QRect(500, 399, 211, 61));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(500, 80, 211, 291));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        fReadBTN = new QPushButton(tab);
        fReadBTN->setObjectName(QString::fromUtf8("fReadBTN"));
        fReadBTN->setGeometry(QRect(10, 40, 80, 24));
        fEraseBTN = new QPushButton(tab);
        fEraseBTN->setObjectName(QString::fromUtf8("fEraseBTN"));
        fEraseBTN->setGeometry(QRect(110, 40, 80, 24));
        fWriteBTN = new QPushButton(tab);
        fWriteBTN->setObjectName(QString::fromUtf8("fWriteBTN"));
        fWriteBTN->setGeometry(QRect(10, 70, 80, 24));
        fVerifyBTN = new QPushButton(tab);
        fVerifyBTN->setObjectName(QString::fromUtf8("fVerifyBTN"));
        fVerifyBTN->setGeometry(QRect(110, 70, 80, 24));
        fGetIdBTN = new QPushButton(tab);
        fGetIdBTN->setObjectName(QString::fromUtf8("fGetIdBTN"));
        fGetIdBTN->setGeometry(QRect(10, 110, 80, 24));
        fRdSregBTN = new QPushButton(tab);
        fRdSregBTN->setObjectName(QString::fromUtf8("fRdSregBTN"));
        fRdSregBTN->setGeometry(QRect(10, 150, 80, 24));
        fWrSregBTN = new QPushButton(tab);
        fWrSregBTN->setObjectName(QString::fromUtf8("fWrSregBTN"));
        fWrSregBTN->setGeometry(QRect(10, 180, 80, 24));
        fLoadBTN = new QPushButton(tab);
        fLoadBTN->setObjectName(QString::fromUtf8("fLoadBTN"));
        fLoadBTN->setGeometry(QRect(10, 230, 80, 24));
        fSaveBTN = new QPushButton(tab);
        fSaveBTN->setObjectName(QString::fromUtf8("fSaveBTN"));
        fSaveBTN->setGeometry(QRect(110, 230, 80, 24));
        fIdTB = new QLineEdit(tab);
        fIdTB->setObjectName(QString::fromUtf8("fIdTB"));
        fIdTB->setGeometry(QRect(130, 110, 61, 24));
        lSregTB = new QLineEdit(tab);
        lSregTB->setObjectName(QString::fromUtf8("lSregTB"));
        lSregTB->setGeometry(QRect(160, 180, 31, 24));
        hSregTB = new QLineEdit(tab);
        hSregTB->setObjectName(QString::fromUtf8("hSregTB"));
        hSregTB->setGeometry(QRect(160, 150, 31, 24));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 150, 21, 16));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(130, 180, 21, 16));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 180, 28));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        fDevCB = new QComboBox(layoutWidget);
        fDevCB->addItem(QString());
        fDevCB->addItem(QString());
        fDevCB->addItem(QString());
        fDevCB->addItem(QString());
        fDevCB->addItem(QString());
        fDevCB->addItem(QString());
        fDevCB->addItem(QString());
        fDevCB->addItem(QString());
        fDevCB->addItem(QString());
        fDevCB->setObjectName(QString::fromUtf8("fDevCB"));

        horizontalLayout_2->addWidget(fDevCB);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 10, 63, 20));
        MW_ModelCB = new QComboBox(tab_3);
        MW_ModelCB->addItem(QString());
        MW_ModelCB->addItem(QString());
        MW_ModelCB->addItem(QString());
        MW_ModelCB->addItem(QString());
        MW_ModelCB->addItem(QString());
        MW_ModelCB->addItem(QString());
        MW_ModelCB->setObjectName(QString::fromUtf8("MW_ModelCB"));
        MW_ModelCB->setGeometry(QRect(110, 10, 76, 26));
        MW_ReadBTN = new QPushButton(tab_3);
        MW_ReadBTN->setObjectName(QString::fromUtf8("MW_ReadBTN"));
        MW_ReadBTN->setGeometry(QRect(50, 50, 93, 29));
        MW_WriteBTN = new QPushButton(tab_3);
        MW_WriteBTN->setObjectName(QString::fromUtf8("MW_WriteBTN"));
        MW_WriteBTN->setGeometry(QRect(50, 90, 93, 29));
        MW_VerifyBTN = new QPushButton(tab_3);
        MW_VerifyBTN->setObjectName(QString::fromUtf8("MW_VerifyBTN"));
        MW_VerifyBTN->setGeometry(QRect(50, 130, 93, 29));
        MW_LoadBTN = new QPushButton(tab_3);
        MW_LoadBTN->setObjectName(QString::fromUtf8("MW_LoadBTN"));
        MW_LoadBTN->setGeometry(QRect(10, 220, 93, 29));
        MW_SaveBTN = new QPushButton(tab_3);
        MW_SaveBTN->setObjectName(QString::fromUtf8("MW_SaveBTN"));
        MW_SaveBTN->setGeometry(QRect(110, 220, 93, 29));
        MW_EraseBTN = new QPushButton(tab_3);
        MW_EraseBTN->setObjectName(QString::fromUtf8("MW_EraseBTN"));
        MW_EraseBTN->setGeometry(QRect(50, 170, 93, 29));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        eeLoadBTN = new QPushButton(tab_2);
        eeLoadBTN->setObjectName(QString::fromUtf8("eeLoadBTN"));
        eeLoadBTN->setGeometry(QRect(14, 230, 80, 24));
        eeSaveBTN = new QPushButton(tab_2);
        eeSaveBTN->setObjectName(QString::fromUtf8("eeSaveBTN"));
        eeSaveBTN->setGeometry(QRect(100, 230, 80, 24));
        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 186, 28));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        eeDevCB = new QComboBox(layoutWidget1);
        eeDevCB->addItem(QString());
        eeDevCB->addItem(QString());
        eeDevCB->addItem(QString());
        eeDevCB->addItem(QString());
        eeDevCB->addItem(QString());
        eeDevCB->addItem(QString());
        eeDevCB->addItem(QString());
        eeDevCB->addItem(QString());
        eeDevCB->addItem(QString());
        eeDevCB->addItem(QString());
        eeDevCB->setObjectName(QString::fromUtf8("eeDevCB"));

        horizontalLayout->addWidget(eeDevCB);

        layoutWidget2 = new QWidget(tab_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(50, 90, 95, 103));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        eeReadBTN = new QPushButton(layoutWidget2);
        eeReadBTN->setObjectName(QString::fromUtf8("eeReadBTN"));

        verticalLayout->addWidget(eeReadBTN);

        eeWriteBTN = new QPushButton(layoutWidget2);
        eeWriteBTN->setObjectName(QString::fromUtf8("eeWriteBTN"));

        verticalLayout->addWidget(eeWriteBTN);

        eeVerifiBTN = new QPushButton(layoutWidget2);
        eeVerifiBTN->setObjectName(QString::fromUtf8("eeVerifiBTN"));

        verticalLayout->addWidget(eeVerifiBTN);

        tabWidget->addTab(tab_2, QString());
        mainPB = new QProgressBar(centralwidget);
        mainPB->setObjectName(QString::fromUtf8("mainPB"));
        mainPB->setGeometry(QRect(500, 373, 211, 20));
        mainPB->setValue(0);
        mainPB->setTextVisible(false);
        mainTB = new QPlainTextEdit(centralwidget);
        mainTB->setObjectName(QString::fromUtf8("mainTB"));
        mainTB->setGeometry(QRect(10, 0, 481, 461));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Ubuntu Sans Mono"));
        font1.setPointSize(10);
        mainTB->setFont(font1);
        UART_Prog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UART_Prog);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 730, 19));
        UART_Prog->setMenuBar(menubar);
        statusbar = new QStatusBar(UART_Prog);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        UART_Prog->setStatusBar(statusbar);

        retranslateUi(UART_Prog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(UART_Prog);
    } // setupUi

    void retranslateUi(QMainWindow *UART_Prog)
    {
        UART_Prog->setWindowTitle(QCoreApplication::translate("UART_Prog", "UART_Prog", nullptr));
        pScanBTN->setText(QCoreApplication::translate("UART_Prog", "Scan", nullptr));
        pOpenBTN->setText(QCoreApplication::translate("UART_Prog", "Open", nullptr));
        baudCB->setItemText(0, QCoreApplication::translate("UART_Prog", "57600", nullptr));
        baudCB->setItemText(1, QCoreApplication::translate("UART_Prog", "921600", nullptr));
        baudCB->setItemText(2, QCoreApplication::translate("UART_Prog", "256000", nullptr));
        baudCB->setItemText(3, QCoreApplication::translate("UART_Prog", "115200", nullptr));
        baudCB->setItemText(4, QCoreApplication::translate("UART_Prog", "57600", nullptr));
        baudCB->setItemText(5, QCoreApplication::translate("UART_Prog", "38400", nullptr));
        baudCB->setItemText(6, QCoreApplication::translate("UART_Prog", "19200", nullptr));
        baudCB->setItemText(7, QCoreApplication::translate("UART_Prog", "9600", nullptr));

        checkBTN->setText(QCoreApplication::translate("UART_Prog", "Check progger", nullptr));
        fReadBTN->setText(QCoreApplication::translate("UART_Prog", "Read", nullptr));
        fEraseBTN->setText(QCoreApplication::translate("UART_Prog", "Erase", nullptr));
        fWriteBTN->setText(QCoreApplication::translate("UART_Prog", "Write", nullptr));
        fVerifyBTN->setText(QCoreApplication::translate("UART_Prog", "Verify", nullptr));
        fGetIdBTN->setText(QCoreApplication::translate("UART_Prog", "Get ID", nullptr));
        fRdSregBTN->setText(QCoreApplication::translate("UART_Prog", "RD Sreg", nullptr));
        fWrSregBTN->setText(QCoreApplication::translate("UART_Prog", "WR Sreg", nullptr));
        fLoadBTN->setText(QCoreApplication::translate("UART_Prog", "Load", nullptr));
        fSaveBTN->setText(QCoreApplication::translate("UART_Prog", "Save", nullptr));
        label_3->setText(QCoreApplication::translate("UART_Prog", "HI", nullptr));
        label_4->setText(QCoreApplication::translate("UART_Prog", "LO", nullptr));
        label_2->setText(QCoreApplication::translate("UART_Prog", "Flash model", nullptr));
        fDevCB->setItemText(0, QString());
        fDevCB->setItemText(1, QCoreApplication::translate("UART_Prog", "W25Q20", nullptr));
        fDevCB->setItemText(2, QCoreApplication::translate("UART_Prog", "W25Q40", nullptr));
        fDevCB->setItemText(3, QCoreApplication::translate("UART_Prog", "W25Q80", nullptr));
        fDevCB->setItemText(4, QCoreApplication::translate("UART_Prog", "W25Q16", nullptr));
        fDevCB->setItemText(5, QCoreApplication::translate("UART_Prog", "W25Q32", nullptr));
        fDevCB->setItemText(6, QCoreApplication::translate("UART_Prog", "W25Q64", nullptr));
        fDevCB->setItemText(7, QCoreApplication::translate("UART_Prog", "W25Q128", nullptr));
        fDevCB->setItemText(8, QCoreApplication::translate("UART_Prog", "W25Q256", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("UART_Prog", "25xx", nullptr));
        label_5->setText(QCoreApplication::translate("UART_Prog", "Model", nullptr));
        MW_ModelCB->setItemText(0, QCoreApplication::translate("UART_Prog", "93c46", nullptr));
        MW_ModelCB->setItemText(1, QCoreApplication::translate("UART_Prog", "93c56", nullptr));
        MW_ModelCB->setItemText(2, QCoreApplication::translate("UART_Prog", "93c57", nullptr));
        MW_ModelCB->setItemText(3, QCoreApplication::translate("UART_Prog", "93c66", nullptr));
        MW_ModelCB->setItemText(4, QCoreApplication::translate("UART_Prog", "93c76", nullptr));
        MW_ModelCB->setItemText(5, QCoreApplication::translate("UART_Prog", "93c86", nullptr));

        MW_ReadBTN->setText(QCoreApplication::translate("UART_Prog", "READ", nullptr));
        MW_WriteBTN->setText(QCoreApplication::translate("UART_Prog", "WRITE", nullptr));
        MW_VerifyBTN->setText(QCoreApplication::translate("UART_Prog", "VERIFY", nullptr));
        MW_LoadBTN->setText(QCoreApplication::translate("UART_Prog", "LOAD", nullptr));
        MW_SaveBTN->setText(QCoreApplication::translate("UART_Prog", "SAVE", nullptr));
        MW_EraseBTN->setText(QCoreApplication::translate("UART_Prog", "ERASE", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("UART_Prog", "93xx", nullptr));
        eeLoadBTN->setText(QCoreApplication::translate("UART_Prog", "Load", nullptr));
        eeSaveBTN->setText(QCoreApplication::translate("UART_Prog", "Save", nullptr));
        label->setText(QCoreApplication::translate("UART_Prog", "EEPROM model", nullptr));
        eeDevCB->setItemText(0, QString());
        eeDevCB->setItemText(1, QCoreApplication::translate("UART_Prog", "24x01", nullptr));
        eeDevCB->setItemText(2, QCoreApplication::translate("UART_Prog", "24x02", nullptr));
        eeDevCB->setItemText(3, QCoreApplication::translate("UART_Prog", "24x04", nullptr));
        eeDevCB->setItemText(4, QCoreApplication::translate("UART_Prog", "24x08", nullptr));
        eeDevCB->setItemText(5, QCoreApplication::translate("UART_Prog", "24x16", nullptr));
        eeDevCB->setItemText(6, QCoreApplication::translate("UART_Prog", "24x32", nullptr));
        eeDevCB->setItemText(7, QCoreApplication::translate("UART_Prog", "24x64", nullptr));
        eeDevCB->setItemText(8, QCoreApplication::translate("UART_Prog", "24x128", nullptr));
        eeDevCB->setItemText(9, QCoreApplication::translate("UART_Prog", "24x256", nullptr));

        eeReadBTN->setText(QCoreApplication::translate("UART_Prog", "Read", nullptr));
        eeWriteBTN->setText(QCoreApplication::translate("UART_Prog", "Write", nullptr));
        eeVerifiBTN->setText(QCoreApplication::translate("UART_Prog", "Verify", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("UART_Prog", "24xx", nullptr));
        mainPB->setFormat(QCoreApplication::translate("UART_Prog", "%p%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UART_Prog: public Ui_UART_Prog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UART_PROG_H
