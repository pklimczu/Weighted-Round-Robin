#include "Packet.h"

Packet::Packet(float timeOfArrival) :
    m_PacketSize(0),
    m_TimeOfArrival(timeOfArrival)
{ }

Packet::Packet(int packetSize, float timeOfArrival)  :
    m_PacketSize(packetSize),
    m_TimeOfArrival(timeOfArrival)
{ }

void Packet::setPacketSize(int packetSize)
{
    // Default and common MTU is 1500 bytes
    if (m_PacketSize != packetSize)
        m_PacketSize = packetSize;
}

void Packet::setTimeOfArrival(float timeOfArrival)
{
    if (m_TimeOfArrival != timeOfArrival)
        m_TimeOfArrival = timeOfArrival;
}

