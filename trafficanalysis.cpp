#include "trafficanalysis.h"
#include "ui_trafficanalysis.h"
#include "packet.h"
#include "packetstream.h"

PacketStream pStream;

TrafficAnalysis::TrafficAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrafficAnalysis)
{
    ui->setupUi(this);
    connect(ui->pushButton_open,SIGNAL(released()),this,SLOT(pushButton_open_pressed()));
    connect(ui->pushButton_find,SIGNAL(released()),this,SLOT(pushButton_find_pressed()));
    connect(ui->pushButton_clear,SIGNAL(released()),this,SLOT(pushButton_clear_pressed()));
}
TrafficAnalysis::~TrafficAnalysis()
{
    delete ui;
}

void readPackets(QFile &file)
{
    PcapFHeader tempFHeader;
    PcapHeader tempPHeader;
    unsigned char *tempDataArr;
    file.read((char *)&tempFHeader,24);
    pStream.setFHeader(tempFHeader);
    while (file.pos() < file.size())
    {
        file.read((char *)&tempPHeader,16);
        Packet myPacket(tempPHeader);

        myPacket.setDataArr(myPacket.getCapLen());
        tempDataArr = myPacket.getDataArr();
        file.read((char *)tempDataArr, myPacket.getCapLen());

        pStream.packets.push_back(myPacket);
    }
}

void TrafficAnalysis::pushButton_find_pressed()
{
    QString data = "";
    QString jStr = ui->LineEdit_search->text();
    int j = jStr.toInt() - 1;
    if(pStream.packets.length() == 0)
    {
        QMessageBox::critical(this, tr("Error"), tr("Open .pcap file!"));
        return;
    }
    if(j < 0 || j > pStream.packets.length())
    {
        QMessageBox::critical(this, tr("Error"), tr("Incorrect packet's number"));
        return;
    }
    ui->textEdit_packetView->append("################# Packet № " + jStr + " #################");
    ui->textEdit_packetView->append("------------------------------------pcap header------------------------------------");

    data = QDateTime::fromTime_t(pStream.packets[j].getTime1()).toString();
    data += " : " + QString::number(pStream.packets[j].getTime2());
    ui->textEdit_packetView->append("time:    " + data);

    data = QString::number(pStream.packets[j].getCapLen());
    ui->textEdit_packetView->append("caplen:   " + data);

    data = QString::number(pStream.packets[j].getDataLen());
    ui->textEdit_packetView->append("datalen:  " + data);

    ui->textEdit_packetView->append("---------------------------------------Packet---------------------------------------");
    int modulo = pStream.packets[j].getCapLen() % 16;
    for(int i = 0; i < pStream.packets[j].getCapLen() - modulo; i+=16)
    {
        data = "";
        for(int k = 0; k < 8; k++)
        {
            if(QString::number(pStream.packets[j].getDataArr()[i+k], 16).length() == 2) data += QString::number(pStream.packets[j].getDataArr()[i+k], 16) + " ";
            else data += "0" + QString::number(pStream.packets[j].getDataArr()[i+k], 16) + " ";
        }
        data += "\t";
        for(int k = 9; k < 18; k++)
        {
            if(QString::number(pStream.packets[j].getDataArr()[i+k], 16).length() == 2) data += QString::number(pStream.packets[j].getDataArr()[i+k], 16) + " ";
            else data += "0" + QString::number(pStream.packets[j].getDataArr()[i+k], 16) + " ";
        }
        ui->textEdit_packetView->append(data);
    }
    for(int i = modulo; i < pStream.packets[j].getCapLen(); i++)
    {
        data = "";
        if(QString::number(pStream.packets[j].getDataArr()[i], 16).length() == 2) data += QString::number(pStream.packets[j].getDataArr()[i], 16) + " ";
        else data += "0" + QString::number(pStream.packets[j].getDataArr()[i], 16) + " ";
    }
    ui->textEdit_packetView->append("");
}

void TrafficAnalysis::pushButton_clear_pressed()
{
    QString data = "";
    ui->textEdit_packetView->setText(data);
    ui->LineEdit_search->setText(data);
}

void TrafficAnalysis::pushButton_open_pressed()
{
    pStream.packets.clear();
    QString fName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath(), tr("PCAP files (*.cap)"));
    if(fName == "")
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not read file's name"));
        return;
    }
    QFile file(fName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    readPackets(file);
    file.close();
    QString data = "";
    ui->lineEdit_number->setText(data);
    ui->lineEdit_maxLength->setText(data);
    ui->lineEdit_minLength->setText(data);
    ui->lineEdit_averageLength->setText(data);
    data = QString::number(pStream.packets.length());
    ui->lineEdit_number->setText(data);

    qint32 maxTemp, minTemp, averTemp;
    maxTemp = minTemp = averTemp = pStream.packets[0].getCapLen();
    for(int i = 1; i < pStream.packets.length(); i++)
    {
        if(pStream.packets[i].getCapLen() > maxTemp) maxTemp = pStream.packets[i].getCapLen();
        if(pStream.packets[i].getCapLen() < minTemp) minTemp = pStream.packets[i].getCapLen();
        averTemp += pStream.packets[i].getCapLen();
    }
    averTemp /= pStream.packets.length();
    data = QString::number(maxTemp);
    ui->lineEdit_maxLength->setText(data);
    data = QString::number(minTemp);
    ui->lineEdit_minLength->setText(data);
    data = QString::number(averTemp);
    ui->lineEdit_averageLength->setText(data);
}
