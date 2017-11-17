#ifndef PACKET_H
#define PACKET_H

#include <QObject>

struct PcapHeader
{
    qint32 time1;
    qint32 time2;
    qint32 capLen;
    qint32 dataLen;
};

class Packet
{
public:
    Packet(); //пустой конструктор
    Packet(PcapHeader pH); //конструктор с заданием заголовка
    Packet(qint32 t1, qint32 t2, qint32 cL, qint32 dL); //конструктор с напрямую заданными значениями заголовка
    Packet(const Packet &myPacket); //конструктор копирования
    ~Packet(); //деструктор
    void setPHeader(PcapHeader fH); //задание заголовка
    void setTime1(qint32 t1); //прямое задание значений заголовка
    void setTime2(qint32 t2);
    void setCapLen(qint32 cL);
    void setDataLen(qint32 dL);
    void setDataArr(int n); //выделение памяти под пакет(массив)
    PcapHeader getPHeader(); //получение заголовка
    PcapHeader getPHeader() const;
    qint32 getTime1(); //получение значений напрямую
    qint32 getTime2();
    qint32 getCapLen();
    qint32 getCapLen() const;
    qint32 getDataLen();
    unsigned char* getDataArr(); //получение указателя на пакет(массив)
    unsigned char* getDataArr() const;
    bool operator == (const Packet &myPacket);
    bool operator < (const Packet &myPacket);

private:
    PcapHeader pHeader; //заголовок
    unsigned char *data; //пакет
};

#endif // PACKET_H
