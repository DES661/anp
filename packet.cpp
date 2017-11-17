#include "packet.h"

Packet::Packet()
{
    pHeader.time1 = 0;
    pHeader.time2 = 0;
    pHeader.capLen = 0;
    pHeader.dataLen = 0;
}
Packet::Packet(PcapHeader pH)
{
    pHeader = pH;
}
Packet::Packet(qint32 t1, qint32 t2, qint32 cL, qint32 dL)
{
    pHeader.time1 = t1;
    pHeader.time2 = t2;
    pHeader.capLen = cL;
    pHeader.dataLen = dL;
}
Packet::Packet(const Packet &myPacket)
{
    pHeader = myPacket.getPHeader();
    data = new unsigned char [pHeader.capLen];
    memcpy(data, myPacket.getDataArr(), pHeader.capLen);
}
Packet::~Packet() {delete[] data;}
void Packet::setPHeader(PcapHeader pH) {pHeader = pH;}
void Packet::setTime1(qint32 t1) {pHeader.time1 = t1;}
void Packet::setTime2(qint32 t2) {pHeader.time2 = t2;}
void Packet::setCapLen(qint32 cL) {pHeader.capLen = cL;}
void Packet::setDataLen(qint32 dL) {pHeader.dataLen = dL;}
void Packet::setDataArr(qint32 n) {data = new unsigned char[n];}
PcapHeader Packet::getPHeader() {return pHeader;}
PcapHeader Packet::getPHeader() const {return pHeader;}
qint32 Packet::getTime1() {return pHeader.time1;}
qint32 Packet::getTime2() {return pHeader.time2;}
qint32 Packet::getCapLen() {return pHeader.capLen;}
qint32 Packet::getCapLen() const {return pHeader.capLen;}
qint32 Packet::getDataLen() {return pHeader.dataLen;}
unsigned char* Packet::getDataArr() {return data;}
unsigned char* Packet::getDataArr() const {return data;}
bool Packet::operator == (const Packet &myPacket)
{
    if(pHeader.capLen == myPacket.getCapLen()) return true;
    else return false;
}
bool Packet::operator < (const Packet &myPacket)
{
    if(pHeader.capLen < myPacket.getCapLen()) return true;
    else return false;
}
