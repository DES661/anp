#ifndef PACKETSTREAM_H
#define PACKETSTREAM_H
#include "packet.h"
#include <QList>

struct PcapFHeader
{
    qint32 magic;
    qint16 version_major;
    qint16 version_minor;
    qint32 thiszone;
    qint32 sigfigs;
    qint32 snaplen;
    qint32 linktype;
};

class PacketStream
{
public:
    QList <Packet> packets; //вектор пакетов
    PacketStream(); //пустой конструктор
    PacketStream(PcapFHeader fH);//конструктор с заданием заголовка
    PacketStream(qint32 mag, qint16 v_maj, qint16 v_min,
                     qint32 tZ, qint32 sF, qint32 sL, qint32 lT); //конструктор с напрямую заданными значениями заголовка
    ~PacketStream(); //деструктор
    void setFHeader(PcapFHeader fH); //задание заголовка
    void setMagic(qint32 mag);           //прямое задание значений заголовка
    void setVersion_major(qint16 v_maj);
    void setVersion_minor(qint16 v_min);
    void setThiszone(qint32 tZ);
    void setSigfigs(qint32 sF);
    void setSnaplen(qint32 sL);
    void setLinktype(qint32 lT);
    PcapFHeader getFHeader(); //получение заголовка
    qint32 getMagic();         //получение значений напрямую
    qint16 getVersion_major();
    qint16 getVersion_minor();
    qint32 getThiszone();
    qint32 getSigfigs();
    qint32 getSnaplen();
    qint32 getLinktype();

private:
    PcapFHeader fHeader; //заголовок файла
};

#endif // PACKETSTREAM_H
