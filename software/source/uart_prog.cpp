#include "uart_prog.h"
#include "ui_uart_prog.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QIODevice>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QTextStream>


//Глобальные переменные
QSerialPort serial;
bool isOpen = false;

char *wbuf;
char *rbuf;
char *tbuf;
char *wr_arr;
char *rd_arr;
int data_ofset;
int wbuf_size;

int w_index = 0;
int wrsize = 0;

int ee_size;
int fl_size;
int fl_psize;
int f_type;

//Microwire
int mw_size = 128;
int mw_type = 0;

bool vrf = false;

QStringList digs;

QString file_name;

//прототипы




UART_Prog::UART_Prog(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UART_Prog)
{
    ui->setupUi(this);

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
#ifdef Q_OS_LINUX
        ui->portCB->addItem("/dev/" + serialPortInfo.portName());
#else
        ui->portCB->addItem(serialPortInfo.portName());
#endif
    }
    digs << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
    digs << "A" << "B" << "C" << "D" << "E" << "F";

    rbuf = new char[280];
    wbuf = new char[280];

    ui->mainPB->setMinimum(0);
}

UART_Prog::~UART_Prog()
{
    delete ui;
}

//Перевод строки в byte
uchar UART_Prog::strToByte(QString hStr)
{
    uchar tmp = 0x00;

    if(hStr[0] == '0') tmp = 0x00;
    else if(hStr[0] == '1') tmp = 0x10;
    else if(hStr[0] == '2') tmp = 0x20;
    else if(hStr[0] == '3') tmp = 0x30;
    else if(hStr[0] == '4') tmp = 0x40;
    else if(hStr[0] == '5') tmp = 0x50;
    else if(hStr[0] == '6') tmp = 0x60;
    else if(hStr[0] == '7') tmp = 0x70;
    else if(hStr[0] == '8') tmp = 0x80;
    else if(hStr[0] == '9') tmp = 0x90;
    else if(hStr[0] == 'a') tmp = 0xA0;
    else if(hStr[0] == 'A') tmp = 0xA0;
    else if(hStr[0] == 'b') tmp = 0xB0;
    else if(hStr[0] == 'B') tmp = 0xB0;
    else if(hStr[0] == 'c') tmp = 0xC0;
    else if(hStr[0] == 'C') tmp = 0xC0;
    else if(hStr[0] == 'd') tmp = 0xD0;
    else if(hStr[0] == 'D') tmp = 0xD0;
    else if(hStr[0] == 'e') tmp = 0xE0;
    else if(hStr[0] == 'E') tmp = 0xE0;
    else if(hStr[0] == 'f') tmp = 0xF0;
    else if(hStr[0] == 'F') tmp = 0xF0;
    else tmp = 0x00;

    if(hStr[1] == '0') tmp |= 0x00;
    else if(hStr[1] == '1') tmp |= 0x01;
    else if(hStr[1] == '2') tmp |= 0x02;
    else if(hStr[1] == '3') tmp |= 0x03;
    else if(hStr[1] == '4') tmp |= 0x04;
    else if(hStr[1] == '5') tmp |= 0x05;
    else if(hStr[1] == '6') tmp |= 0x06;
    else if(hStr[1] == '7') tmp |= 0x07;
    else if(hStr[1] == '8') tmp |= 0x08;
    else if(hStr[1] == '9') tmp |= 0x09;
    else if(hStr[1] == 'a') tmp |= 0x0A;
    else if(hStr[1] == 'A') tmp |= 0x0A;
    else if(hStr[1] == 'b') tmp |= 0x0B;
    else if(hStr[1] == 'B') tmp |= 0x0B;
    else if(hStr[1] == 'c') tmp |= 0x0C;
    else if(hStr[1] == 'C') tmp |= 0x0C;
    else if(hStr[1] == 'd') tmp |= 0x0D;
    else if(hStr[1] == 'D') tmp |= 0x0D;
    else if(hStr[1] == 'e') tmp |= 0x0E;
    else if(hStr[1] == 'E') tmp |= 0x0E;
    else if(hStr[1] == 'f') tmp |= 0x0F;
    else if(hStr[1] == 'F') tmp |= 0x0F;
    else tmp |= 0x00;

    return tmp;
}

//Перевод байта в строку (HEX без "0x")
QString UART_Prog::hbyteToString(uchar hData)
{
    QString result = "XY";
    result = digs.at(hData >> 4) + digs.at(hData & 0xF);
    return result;
}

QString UART_Prog::print_array(char *arr, int arrSize)
{
    QString rd;
    QString tmp;

    rd = "OFFSET   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n";


    for (int m = 0; m < arrSize; m += 16)
    {
        tmp = "0";
        tmp += hbyteToString(m >> 16 & 0xFF);
        tmp += hbyteToString(m >> 8 & 0xFF);
        tmp += hbyteToString(m & 0xFF) + "  ";

        for (int n = 0; n < 16; n++)
        {
            tmp += hbyteToString(arr[m + n]) + " ";
        }
        tmp += "\r\n";
        rd += tmp;
    }

    return rd;
}

void UART_Prog::openDataFile()
{
    int fileSize = 0, oldSize;

    file_name = QFileDialog :: getOpenFileName (NULL, "Title", ".", "*");
    QFile rFile(file_name);

    //If *.HEX
    if(file_name.endsWith(".hex") || file_name.endsWith(".HEX"))
    {
        if(!rFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ui->consoleTB->setText("Open File Error");
            return;
        }

        //Открываем файл для чтения
        QTextStream in(&rFile);

        int offset = 0, bofs = 0;
        int curr_offset = 0;
        int tmp_offs = 0;
        int fil_size = 0, oldSize;

        QString rds;

        //Рассчитываем дополнительный адрес смещения
        while (!in.atEnd())
        {
            rds = in.readLine();

            if (rds.mid(7, 2) == "04")
            {
                tmp_offs = (int)((strToByte(rds.mid(9, 2)) << 8) | strToByte(rds.mid(11, 2)));
                tmp_offs = tmp_offs << 16;
            }
            if (rds.mid(7, 2) == "00")
            {
                curr_offset = (int)((strToByte(rds.mid(3, 2)) << 8) | strToByte(rds.mid(5, 2)));
                curr_offset = curr_offset | tmp_offs;
                if (curr_offset >= offset)
                {
                    offset = curr_offset;
                    bofs = (int)(strToByte(rds.mid(1, 2)));
                }
            }
        }
        in.seek(0);

        fil_size = offset + bofs;
        oldSize = fil_size;
        if ((fil_size % 16) > 0) fil_size = fil_size + (16 - (fil_size % 16));

        //Конвертируем HEX
        wr_arr = new char[fil_size];
        wrsize = fil_size;

        for (int i = 0; i < fil_size; i++)
        {
            wr_arr[i] = 0xFF;
        }

        offset = 0;

        while (!in.atEnd())
        {
            rds = in.readLine();

            if (rds.mid(7, 2) == "04")
            {
                offset = (int)(((strToByte(rds.mid(9, 2)) << 8) | (strToByte(rds.mid(11, 2)))));
            }
            if (rds.mid(7, 2) == "00")
            {
                char str_size = strToByte(rds.mid(1, 2));
                int arr_offset = (int)(strToByte(rds.mid(5, 2)) | (strToByte(rds.mid(3, 2)) << 8));
                arr_offset |= (offset << 16);
                rds = rds.mid(9, str_size * 2);

                for (int h = 0; h < str_size; h++)
                {
                    wr_arr[arr_offset + h] = strToByte(rds.mid(h * 2, 2));
                }
            }
        }
        in.reset();

        ui->mainTB->setPlainText(print_array(wr_arr, fil_size));
        ui->consoleTB->setText("File size " + QString::number(oldSize) + " bytes");

        wbuf_size = fil_size;

        rFile.close();

    }
    else //ANY OTHER
    {
        QFileInfo info(file_name);
        fileSize = info.size();
        oldSize = fileSize;
        if((fileSize % 16) > 0) fileSize = fileSize + (16 - (fileSize % 16));
        wr_arr = new char[fileSize];
        wrsize = fileSize;

        ui->consoleTB->setText("File size " + QString::number(oldSize) + " bytes");

        if(!rFile.open(QIODevice::ReadOnly))
        {
            ui->consoleTB->setText("Open File Error");
            return;
        }

        for(int i = 0; i < fileSize; i++) wr_arr[i] = 0xFF;

        rFile.read(wr_arr, oldSize);

        ui->mainTB->setPlainText(print_array(wr_arr, fileSize));
        rFile.close();

        wbuf_size = fileSize;
    }
}


void UART_Prog::verifyData()
{
    if (rd_arr != NULL && wr_arr != NULL)
    {
        int fl_error = 0;

        if (strlen(rd_arr) >= wbuf_size)
        {
            //Сравниваем массив EEPROM
            for (int k = 0; k < wbuf_size; k++)
            {
                if (wr_arr[k] != rd_arr[k]) fl_error++;
            }
        }
        else
        {
            ui->consoleTB->setText("Loaded file largest as readed!");
            fl_error = wbuf_size;
        }
        //Если есть ошибки
        if (fl_error > 0)
        {
            ui->consoleTB->setText("Flash errors: " + QString::number(fl_error));
        }
        //Иначе
        else
        {
            ui->consoleTB->setText("No errors");
        }
    }
    else
    {
        ui->consoleTB->setText("Perform Read flash!");
    }
}

//Событие по приёму по UART
void UART_Prog::readInBuff()
{

    char *tbuf;
    int bufSize;
    tbuf = new char[256];

    bufSize = serial.read(tbuf, 260);
    for(int i = 0; i < bufSize; i++) rbuf[i + w_index] = tbuf[i];
    w_index += bufSize;
    if(w_index > 2 && w_index >= (static_cast<unsigned int>(rbuf[1] & 0x000000FF) + 3))
    {
        w_index = 0;
        serial.clearError();
        serial.clear();
        deassemble_frame();
    }
}

void UART_Prog::deassemble_frame()
{
    if(rbuf[0] != (char)0xFE)
    {
        ui->consoleTB->setText("Frame error");
    }
    else
    {
        switch(rbuf[2])
        {
            case (char)0xCC:
            {
                ui->consoleTB->setText("Programmer present");
                break;
            }
            case (char)0xF0:
            {
                ui->fIdTB->setText(hbyteToString(rbuf[5]) + " " + hbyteToString(rbuf[3]) + hbyteToString(rbuf[4]));
                break;
            }
            case (char)0xF1:
            {
                ui->hSregTB->setText(hbyteToString(rbuf[4]));
                ui->lSregTB->setText(hbyteToString(rbuf[3]));
                break;
            }
            case (char)0xF2:
            {
                int tmp = static_cast<unsigned int>(rbuf[1] & 0x000000FF);
                for (int i = 0; i < tmp; i++) rd_arr[data_ofset + i] = rbuf[i + 3];
                data_ofset += tmp;

                ui->mainPB->setValue(data_ofset);

                if (data_ofset >= fl_size)
                {
                    if(vrf)
                    {
                        vrf = false;
                        verifyData();
                    }
                    else
                    {
                        ui->mainTB->setPlainText(print_array(rd_arr, fl_size));
                        ui->consoleTB->setText("Finish");
                    }
                    ui->mainPB->setValue(0);

                    wbuf[0] = 0xFE;
                    wbuf[1] = 0x01;
                    wbuf[2] = 0x3D;
                    wbuf[3] = 0x00;
                    serial.write(wbuf, 4);

                    return;
                }
                else
                {
                    wbuf[0] = 0xFE;
                    wbuf[1] = 0x01;
                    wbuf[2] = 0x3D;
                    wbuf[3] = 0x00;
                    serial.write(wbuf, 4);
                }

                break;
            }
            case (char)0xF3:
            {
                ui->consoleTB->setText("Write Sreg finish");
                break;
            }
            case (char)0xF4:
            {
                ui->consoleTB->setText("Erasing complete");
                break;
            }
            case (char)0xF6:
            {
                if(data_ofset >= wrsize)
                {
                    ui->consoleTB->setText("Writing complete");
                    ui->mainPB->setValue(0);
                    return;
                }

                wbuf[0] = 0xFE;
                wbuf[1] = 0x80;
                wbuf[2] = 0xF6;

                for (int i = 0; i < 128; i++) wbuf[i + 3] = wr_arr[i + data_ofset];

                data_ofset += 128;
                ui->mainPB->setValue(data_ofset);

                serial.write(wbuf, 131);

                break;
            }
            ////////////////////////////////////////////EEPROM/////////////////////////////////////
            case (char)0xE0: //Read I2C EEPROM
            {
                int tmp = (rbuf[1] & 0xFF);

                for (int i = 0; i < tmp; i++)
                {
                    rd_arr[data_ofset + i] = rbuf[i + 3];
                }
                data_ofset += tmp;

                ui->mainPB->setValue(data_ofset);

                if (data_ofset >= ee_size)
                {
                    ui->mainTB->setPlainText(print_array(rd_arr, ee_size));
                    ui->consoleTB->setText("Чтение завершено\r\n");
                    ui->mainPB->setValue(0);

                    wbuf[0] = 0xFE;
                    wbuf[1] = 0x01;
                    wbuf[2] = 0x3D;
                    wbuf[3] = 0x00;
                    serial.write(wbuf, 4);
                    return;
                }
                else
                {
                    wbuf[0] = 0xFE;
                    wbuf[1] = 0x01;
                    wbuf[2] = 0x3D;
                    wbuf[3] = 0x00;
                    serial.write(wbuf, 4);
                }
                break;
            }
            case (char)0xE2: //Write I2C EEPROM
            {
                if(data_ofset >= wrsize)
                {
                    ui->consoleTB->setText("Запись завершена\r\n");
                    ui->mainPB->setValue(0);
                    return;
                }

                wbuf[0] = 0xFE;
                wbuf[1] = 0x22;
                wbuf[2] = 0xE2;
                wbuf[3] = (char)((data_ofset >> 8) & 0xFF);
                wbuf[4] = (char)(data_ofset & 0xFF);

                for(int i = 0; i < 32; i++)
                {
                    wbuf[i + 5] = wr_arr[i + data_ofset];
                }
                serial.write(wbuf, 37);
                data_ofset += 32;
                ui->mainPB->setValue(data_ofset);
                break;
            }
            ///////////////////////////////////MicroWire//////////////////////////////////
            case (char)0xB0: //Read MW EEPROM
            {
                int tmp = (rbuf[1] & 0xFF);

                for (int i = 0; i < tmp; i++) rd_arr[data_ofset + i] = rbuf[i + 3];

                data_ofset += tmp;

                ui->mainPB->setValue(data_ofset);

                if (data_ofset >= mw_size)
                {
                    ui->mainTB->setPlainText(print_array(rd_arr, mw_size));
                    ui->consoleTB->setText("Чтение завершено\r\n");
                    ui->mainPB->setValue(0);

                    wbuf[0] = 0xFE;
                    wbuf[1] = 0x01;
                    wbuf[2] = 0x3D;
                    wbuf[3] = 0x00;
                    serial.write(wbuf, 4);
                    return;
                }
                else
                {
                    wbuf[0] = 0xFE;
                    wbuf[1] = 0x01;
                    wbuf[2] = 0x3D;
                    wbuf[3] = 0x00;
                    serial.write(wbuf, 4);
                }
                break;
            }
            case (char)0xB2: //Write MW EEPROM
            {
                if(data_ofset >= wrsize)
                {
                    ui->consoleTB->setText("Запись завершена\r\n");
                    ui->mainPB->setValue(0);
                    return;
                }

                wbuf[0] = 0xFE;
                wbuf[1] = 0x22;
                wbuf[2] = 0xB2;
                wbuf[3] = (char)((data_ofset >> 8) & 0xFF);
                wbuf[4] = (char)(data_ofset & 0xFF);

                for(int i = 0; i < 32; i++)wbuf[i + 5] = wr_arr[i + data_ofset];

                serial.write(wbuf, 37);
                data_ofset += 32;
                ui->mainPB->setValue(data_ofset);
                break;
            }
            case (char)0xBC: //Erasee MW EEPROM
            {
                ui->consoleTB->setText("Стирание завершено\r\n");
                break;
            }

            default: break;
        }
    }
}

//Scan COM Ports
void UART_Prog::on_pScanBTN_clicked()
{
    ui->portCB->clear();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
#ifdef Q_OS_LINUX
        ui->portCB->addItem("/dev/" + serialPortInfo.portName());
#else
        ui->portCB->addItem(serialPortInfo.portName());
#endif
    }
}

//Open port
void UART_Prog::on_pOpenBTN_clicked()
{
    if(isOpen) //Close port
    {
        serial.close();
        isOpen = false;
        ui->pOpenBTN->setText("Open");
        ui->consoleTB->setText("Port closed");
    }
    else //Open port
    {
        if(ui->portCB->currentText() != "" && ui->baudCB->currentText() != "")
        {
            serial.setPortName(ui->portCB->currentText());
            serial.setBaudRate(ui->baudCB->currentText().toInt());
            serial.setDataBits(QSerialPort::Data8);
            serial.setParity(QSerialPort::NoParity);
            serial.setStopBits(QSerialPort::OneStop);
            serial.setFlowControl(QSerialPort::NoFlowControl);
            serial.open(QSerialPort::ReadWrite);
            isOpen = true;

            ui->pOpenBTN->setText("Close");
            ui->consoleTB->setText("Port open");

            connect(&serial, SIGNAL(readyRead()), this, SLOT(readInBuff()));
        }
        else
        {
            ui->consoleTB->setText("Choose Port num and BaudeRate");
        }
    }
}


//Проверка программатора
void UART_Prog::on_checkBTN_clicked()
{
    if(isOpen)
    {
        wbuf[0] = 0xFE;
        wbuf[1] = 0x01;
        wbuf[2] = 0xCC;
        wbuf[3] = 0x00;

        serial.write(wbuf, 4);
    }
    else
    {
        ui->consoleTB->setText("Port clossed");
    }
}


//////////////////////////////////////EEPROM////////////////////////////////////
void UART_Prog::on_eeDevCB_currentTextChanged(const QString &arg1)
{
    if(arg1 == "24x01") ee_size = 128;
    else if(arg1 == "24x02") ee_size = 256;
    else if(arg1 == "24x04") ee_size = 512;
    else if(arg1 == "24x08") ee_size = 1024;
    else if(arg1 == "24x16") ee_size = 2048;
    else if(arg1 == "24x32") ee_size = 4096;
    else if(arg1 == "24x64") ee_size = 8192;
    else if(arg1 == "24x128") ee_size = 16384;
    else if(arg1 == "24x256") ee_size = 32768;
    else ee_size = 128;
}


//Open ee data
void UART_Prog::on_eeLoadBTN_clicked()
{
    openDataFile();
}

void UART_Prog::on_eeSaveBTN_clicked()
{
    if(rd_arr != NULL)
    {
        int file_size = ee_size;
        //Обрезаем пустые ячейки 0xFF начиная с конца файла
        while(rd_arr[file_size - 1] == (char)0xFF) file_size --;

        QString path = QFileDialog :: getSaveFileName (NULL, "Title", ".", "*.bin");
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly))
        {
            ui->consoleTB->setText("Creating file ERROR");
        }
        else
        {
            file.write(rd_arr, file_size);
            file.close();
        }
    }
    else ui->consoleTB->setText("Нечего сохранять");
}

//Выбор модели EEPROM
void UART_Prog::on_eeDevCB_currentIndexChanged(int index)
{

}


void UART_Prog::on_eeReadBTN_clicked()
{
    if(ui->eeDevCB->currentText() != "" && isOpen == true)
    {
        ui->mainPB->setMaximum(ee_size);
        ui->mainPB->setValue(0);
        ui->consoleTB->setText("Чтение...");

        data_ofset = 0;
        rd_arr = new char[ee_size];

        wbuf[0] = 0xFE;
        wbuf[1] = 0x02;
        wbuf[2] = 0xE0;
        wbuf[3] = (char)(ee_size >> 8);
        wbuf[4] = (char)(ee_size & 0xFF);
        serial.write(wbuf, 5);
    }
    else
    {
        ui->consoleTB->setText("Не выбрана модель EEPROM\r\nили закрыт COM порт!");
    }
}


void UART_Prog::on_eeWriteBTN_clicked()
{
    if (ui->eeDevCB->currentText() != "" && isOpen == true && wr_arr != NULL)
    {
        int new_size = wrsize;
        ui->consoleTB->setText("Запись...");

        if ((new_size % 32) > 0)
        {
            char *temp_arr;
            new_size = new_size + (32 - (new_size % 32));
            temp_arr = new char[new_size];

            for (int i = 0; i < new_size; i++) temp_arr[i] = 0xFF;           //Заполняем 0xFF
            for (int i = 0; i < wrsize; i++) temp_arr[i] = wr_arr[i]; //Копируем wr_arr в temp_arr

            wr_arr = new char[new_size];
            for (int i = 0; i < new_size; i++) wr_arr[i] = temp_arr[i];      //Переписываем обратно
            wrsize = new_size;
        }
        data_ofset = 0;
        ui->mainPB->setMaximum(wrsize);
        ui->mainPB->setValue(0);

        wbuf[0] = 0xFE;
        wbuf[1] = 0x02;
        wbuf[2] = 0xE1;
        wbuf[3] = (char)(ee_size >> 8);
        wbuf[4] = (char)(ee_size & 0xFF);
        serial.write(wbuf, 5);
    }
    else
    {
        ui->consoleTB->setText("Не выбрана модель EEPROM\r\nили закрыт COM порт!");
    }
}


void UART_Prog::on_eeVerifiBTN_clicked()
{
    verifyData();
}



/////////////////////////////////SPI FLASH/////////////////////////////////


void UART_Prog::on_fDevCB_currentIndexChanged(int index)
{

    if(ui->fDevCB->currentText() == "W25Q20")
    {
        fl_size = 262144;
        fl_psize = 256;
        f_type = 1;
    }
    else if(ui->fDevCB->currentText() == "W25Q40")
    {
        fl_size = 524288;
        fl_psize = 256;
        f_type = 1;
    }
    else if(ui->fDevCB->currentText() == "W25Q80")
    {
        fl_size = 1048576;
        fl_psize = 256;
    }
    else if(ui->fDevCB->currentText() == "W25Q16")
    {
        fl_size = 2097152;
        fl_psize = 256;
        f_type = 1;
    }
    else if(ui->fDevCB->currentText() == "W25Q32")
    {
        fl_size = 4194304;
        fl_psize = 256;
        f_type = 1;
    }
    else if(ui->fDevCB->currentText() == "W25Q64")
    {
        fl_size = 8388608;
        fl_psize = 256;
        f_type = 1;
    }
    else if(ui->fDevCB->currentText() == "W25Q128")
    {
        fl_size = 16777216;
        fl_psize = 256;
        f_type = 1;
    }
    else if(ui->fDevCB->currentText() == "W25Q256")
    {
        fl_size = 33554432;
        fl_psize = 256;
        f_type = 2;
    }
    else
    {
        fl_size = 0;
        fl_psize = 0;
        f_type = 1;
    }
}


void UART_Prog::on_fReadBTN_clicked()
{
    if(ui->fDevCB->currentText() != "" && isOpen)
    {
        data_ofset = 0;
        rd_arr = new char[fl_size];
        ui->mainPB->setMaximum(fl_size);
        ui->mainPB->setValue(0);

        ui->consoleTB->setText("Чтение...");

        wbuf[0] = 0xFE;
        wbuf[1] = 0x04;
        wbuf[2] = 0xF2;
        wbuf[3] = (char)((fl_size >> 24) & 0xFF);
        wbuf[4] = (char)((fl_size >> 16) & 0xFF);
        wbuf[5] = (char)((fl_size >> 8) & 0xFF);
        wbuf[6] = (char)(fl_size & 0xFF);
        serial.write(wbuf, 7);
    }
    else
    {
        ui->consoleTB->setText("Port clossed or flash model not changed");
    }
}


void UART_Prog::on_fWriteBTN_clicked()
{
    if(ui->fDevCB->currentText() != "" && isOpen && wr_arr != NULL)
    {
        int new_size = wrsize;
        char *tbuf;
        data_ofset = 0;

        if ((new_size % fl_psize) > 0)
        {
            new_size = new_size + (fl_psize - (new_size % fl_psize));
            tbuf = new char[new_size];

            for (int i = 0; i < new_size; i++) tbuf[i] = 0xFF;           //Заполняем 0xFF
            for (int i = 0; i < wrsize; i++) tbuf[i] = wr_arr[i]; //Копируем wr_arr в temp_arr

            wr_arr = new char[new_size];
            for (int i = 0; i < new_size; i++) wr_arr[i] = tbuf[i];      //Переписываем обратно
            wrsize = new_size;
        }

        ui->mainPB->setMaximum(wrsize);
        ui->mainPB->setValue(0);

        ui->consoleTB->setText("Запись...");

        wbuf[0] = 0xFE;
        wbuf[1] = 0x03;
        wbuf[2] = 0xF5;
        wbuf[3] = (char)((fl_psize >> 8) & 0xFF);
        wbuf[4] = (char)((fl_size & 0xFF) & 0xFF);
        wbuf[5] = (char)((f_type) & 0xFF);
        serial.write(wbuf, 6);
    }
    else
    {
        ui->consoleTB->setText("Port clossed or flash model not changed");
    }
}


void UART_Prog::on_fEraseBTN_clicked()
{
    if(ui->fDevCB->currentText() != "" && isOpen)
    {
        ui->consoleTB->setText("Erasing...");

        wbuf[0] = 0xFE;
        wbuf[1] = 0x01;
        wbuf[2] = 0xF4;
        wbuf[3] = 0x00;
        serial.write(wbuf, 4);
    }
    else
    {
        ui->consoleTB->setText("Port clossed or flash model not changed");
    }
}

//
void UART_Prog::on_fVerifyBTN_clicked()
{
    if(ui->fDevCB->currentText() != "" && isOpen && wr_arr != NULL)
    {
        vrf = true;

        data_ofset = 0;
        rd_arr = new char[fl_size];
        ui->mainPB->setMaximum(fl_size);
        ui->mainPB->setValue(0);

        ui->consoleTB->setText("Reading...");

        wbuf[0] = 0xFE;
        wbuf[1] = 0x04;
        wbuf[2] = 0xF2;
        wbuf[3] = (char)((fl_size >> 24) & 0xFF);
        wbuf[4] = (char)((fl_size >> 16) & 0xFF);
        wbuf[5] = (char)((fl_size >> 8) & 0xFF);
        wbuf[6] = (char)(fl_size & 0xFF);
        serial.write(wbuf, 7);
    }
    else
    {
        ui->consoleTB->setText("Port clossed or flash model not changed or file not loaded");
    }
}

//Get ID
void UART_Prog::on_fGetIdBTN_clicked()
{
    if(ui->fDevCB->currentText() != "" && isOpen)
    {
        wbuf[0] = 0xFE;
        wbuf[1] = 0x01;
        wbuf[2] = 0xF0;
        wbuf[3] = 0x00;
        serial.write(wbuf, 4);
    }
    else
    {
        ui->consoleTB->setText("Port clossed or flash model not changed");
    }
}

//Read Sreg
void UART_Prog::on_fRdSregBTN_clicked()
{
    if(ui->fDevCB->currentText() != "" && isOpen)
    {
        wbuf[0] = 0xFE;
        wbuf[1] = 0x01;
        wbuf[2] = 0xF1;
        wbuf[3] = 0x00;
        serial.write(wbuf, 4);
    }
    else
    {
        ui->consoleTB->setText("Port clossed or flash model not changed");
    }
}


void UART_Prog::on_fWrSregBTN_clicked()
{
    if(ui->fDevCB->currentText() != "" && isOpen)
    {
        wbuf[0] = 0xFE;
        wbuf[1] = 0x01;
        wbuf[2] = 0xF3;
        wbuf[3] = strToByte(ui->hSregTB->text());
        wbuf[4] = strToByte(ui->lSregTB->text());
        serial.write(wbuf, 5);
    }
    else
    {
        ui->consoleTB->setText("Port clossed or flash model not changed");
    }
}


void UART_Prog::on_fLoadBTN_clicked()
{
    openDataFile();
}


void UART_Prog::on_fSaveBTN_clicked()
{
    if(rd_arr != NULL)
    {
        int file_size = fl_size;

        while(rd_arr[file_size - 1] == (char)0xFF) file_size --;

        QString path = QFileDialog :: getSaveFileName (NULL, "Title", ".", "*.bin");
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly))
        {
            ui->consoleTB->setText("Creating file ERROR");
        }
        else
        {
            file.write(rd_arr, file_size);
            file.close();
        }
    }
    else ui->consoleTB->setText("Нечего сохранять");
}


//Microwire

void UART_Prog::on_MW_ModelCB_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:{mw_size = 128; mw_type = 0; break;}//93c46
        case 1:{mw_size = 256; mw_type = 0; break;}//93c56
        case 2:{mw_size = 256; mw_type = 1; break;}//93c57
        case 3:{mw_size = 512; mw_type = 0; break;}//93c66
        case 4:{mw_size = 1024; mw_type = 0; break;}//93c76
        case 5:{mw_size = 2048; mw_type = 0; break;}//93c86
    }
}

//Read
void UART_Prog::on_MW_ReadBTN_clicked()
{
    if(ui->MW_ModelCB->currentText() != "" && isOpen == true)
    {
        ui->mainPB->setMaximum(mw_size);
        ui->mainPB->setValue(0);
        ui->consoleTB->setText("Чтение...");

        data_ofset = 0;
        rd_arr = new char[mw_size];

        wbuf[0] = 0xFE;
        wbuf[1] = 0x03;
        wbuf[2] = 0xB0;
        wbuf[3] = (char)(mw_size >> 8);
        wbuf[4] = (char)(mw_size & 0xFF);
        wbuf[5] = (char)mw_type;
        serial.write(wbuf, 6);
    }
    else
    {
        ui->consoleTB->setText("Не выбрана модель EEPROM\r\nили закрыт COM порт!");
    }
}


void UART_Prog::on_MW_WriteBTN_clicked()
{
    if (ui->MW_ModelCB->currentText() != "" && isOpen == true && wr_arr != NULL)
    {
        int new_size = wrsize;
        ui->consoleTB->setText("Запись...");

        if ((new_size % 32) > 0)
        {
            char *temp_arr;
            new_size = new_size + (32 - (new_size % 32));
            temp_arr = new char[new_size];

            for (int i = 0; i < new_size; i++) temp_arr[i] = 0xFF;           //Заполняем 0xFF
            for (int i = 0; i < wrsize; i++) temp_arr[i] = wr_arr[i]; //Копируем wr_arr в temp_arr

            wr_arr = new char[new_size];
            for (int i = 0; i < new_size; i++) wr_arr[i] = temp_arr[i];      //Переписываем обратно
            wrsize = new_size;
        }
        data_ofset = 0;
        ui->mainPB->setMaximum(wrsize);
        ui->mainPB->setValue(0);

        wbuf[0] = 0xFE;
        wbuf[1] = 0x03;
        wbuf[2] = 0xB1;
        wbuf[3] = (char)(mw_size >> 8);
        wbuf[4] = (char)(mw_size & 0xFF);
        wbuf[5] = (char)mw_type;
        serial.write(wbuf, 6);
    }
    else
    {
        ui->consoleTB->setText("Не выбрана модель EEPROM\r\nили закрыт COM порт!");
    }
}


void UART_Prog::on_MW_VerifyBTN_clicked()
{
    verifyData();
}


void UART_Prog::on_MW_LoadBTN_clicked()
{
    openDataFile();
}


void UART_Prog::on_MW_SaveBTN_clicked()
{
    if(rd_arr != NULL)
    {
        int file_size = mw_size;

        while(rd_arr[file_size - 1] == (char)0xFF) file_size --;

        QString path = QFileDialog :: getSaveFileName (NULL, "Title", ".", "*.bin");
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly))
        {
            ui->consoleTB->setText("Creating file ERROR");
        }
        else
        {
            file.write(rd_arr, file_size);
            file.close();
        }
    }
    else ui->consoleTB->setText("Нечего сохранять");
}


void UART_Prog::on_MW_EraseBTN_clicked()
{
    if(ui->MW_ModelCB->currentText() != "" && isOpen == true)
    {
        ui->mainPB->setMaximum(mw_size);
        ui->mainPB->setValue(0);
        ui->consoleTB->setText("Стирание...");

        wbuf[0] = 0xFE;
        wbuf[1] = 0x03;
        wbuf[2] = 0xBC;
        wbuf[3] = (char)(mw_size >> 8);
        wbuf[4] = (char)(mw_size & 0xFF);
        wbuf[5] = (char)mw_type;
        serial.write(wbuf, 6);
    }
    else
    {
        ui->consoleTB->setText("Не выбрана модель EEPROM\r\nили закрыт COM порт!");
    }
}

