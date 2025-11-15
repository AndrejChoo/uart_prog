#ifndef UART_PROG_H
#define UART_PROG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class UART_Prog; }
QT_END_NAMESPACE

class UART_Prog : public QMainWindow
{
    Q_OBJECT

public:
    UART_Prog(QWidget *parent = nullptr);
    ~UART_Prog();

void openDataFile();

uchar strToByte(QString hStr);
QString hbyteToString(uchar hData);
QString print_array(char *arr, int arrSize);
void deassemble_frame();
void verifyData();

private slots:
    void readInBuff();

    void on_pScanBTN_clicked();

    void on_pOpenBTN_clicked();

    void on_eeLoadBTN_clicked();

    void on_checkBTN_clicked();

    void on_eeDevCB_currentIndexChanged(int index);

    void on_eeReadBTN_clicked();

    void on_eeWriteBTN_clicked();

    void on_eeVerifiBTN_clicked();

    void on_eeSaveBTN_clicked();

    void on_fDevCB_currentIndexChanged(int index);

    void on_fReadBTN_clicked();

    void on_fWriteBTN_clicked();

    void on_fEraseBTN_clicked();

    void on_fVerifyBTN_clicked();

    void on_fGetIdBTN_clicked();

    void on_fRdSregBTN_clicked();

    void on_fWrSregBTN_clicked();

    void on_fLoadBTN_clicked();

    void on_fSaveBTN_clicked();

    void on_eeDevCB_currentTextChanged(const QString &arg1);

    void on_MW_ModelCB_currentIndexChanged(int index);

    void on_MW_ReadBTN_clicked();

    void on_MW_WriteBTN_clicked();

    void on_MW_VerifyBTN_clicked();

    void on_MW_LoadBTN_clicked();

    void on_MW_SaveBTN_clicked();

    void on_MW_EraseBTN_clicked();

private:
    Ui::UART_Prog *ui;


};
#endif // UART_PROG_H
