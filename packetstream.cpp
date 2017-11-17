#include "packetstream.h"

PacketStream::PacketStream()
{
    fHeader.magic = 0;
    fHeader.version_major = 0;
    fHeader.version_minor = 0;
    fHeader.thiszone = 0;
    fHeader.sigfigs = 0;
    fHeader.snaplen = 0;
    fHeader.linktype = 0;
}
PacketStream::PacketStream(PcapFHeader fH)
{
    fHeader = fH;
}
PacketStream::PacketStream(qint32 mag, qint16 v_maj, qint16 v_min, qint32 tZ, qint32 sF, qint32 sL, qint32 lT)
{
    fHeader.magic= mag;
    fHeader.version_major = v_maj;
    fHeader.version_minor = v_min;
    fHeader.thiszone = tZ;
    fHeader.sigfigs = sF;
    fHeader.snaplen = sL;
    fHeader.linktype = lT;
}
PacketStream::~PacketStream()
{
    packets.clear();
}
void PacketStream::setFHeader(PcapFHeader fH) {fHeader = fH;}
void PacketStream::setMagic(qint32 mag) {fHeader.magic = mag;}
void PacketStream::setVersion_major(qint16 v_maj) {fHeader.version_major = v_maj;}
void PacketStream::setVersion_minor(qint16 v_min) {fHeader.version_minor = v_min;}
void PacketStream::setThiszone(qint32 tZ) {fHeader.thiszone = tZ;}
void PacketStream::setSigfigs(qint32 sF) {fHeader.sigfigs = sF;}
void PacketStream::setSnaplen(qint32 sL) {fHeader.snaplen = sL;}
void PacketStream::setLinktype(qint32 lT) {fHeader.linktype = lT;}
PcapFHeader PacketStream::getFHeader() {return fHeader;}
qint32 PacketStream::getMagic() {return fHeader.magic;}
qint16 PacketStream::getVersion_major() {return fHeader.version_major;}
qint16 PacketStream::getVersion_minor() {return fHeader.version_minor;}
qint32 PacketStream::getThiszone() {return fHeader.thiszone;}
qint32 PacketStream::getSigfigs() {return fHeader.sigfigs;}
qint32 PacketStream::getSnaplen() {return fHeader.snaplen;}
qint32 PacketStream::getLinktype() {return fHeader.linktype;}
