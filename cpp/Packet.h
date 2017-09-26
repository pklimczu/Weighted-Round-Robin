#ifndef PACKET_H
#define PACKET_H


class Packet
{
public:
    Packet(int packetSize, float timeOfArrival);

    int getPacketSize() const { return m_PacketSize; }
    void setPacketSize(int packetSize);

    float getTimeOfArrival() const { return m_TimeOfArrival; }
    void setTimeOfArrival(float timeOfArrival);

private:
    int m_PacketSize;
    float m_TimeOfArrival;
};

#endif // PACKET_H
