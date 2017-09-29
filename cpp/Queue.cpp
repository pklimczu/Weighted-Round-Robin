#include "Queue.h"
#include "Scheduler.h"
#include <iostream>

extern double globalTime;
static const int SCALING_FACTOR = 100;

Queue::Queue()
{

}

Queue::Queue(std::string name, int lambda, int avgPacketSize, int weight, int bufforSize) :
    m_Lambda(lambda),
    m_AvgPacketSize(avgPacketSize),
    m_Weight(weight),
    m_Ratio(0.0),
    m_BufforSize(bufforSize),
    m_Name(name),
    m_NumberOfPacketsPerIteration(0),
    m_NumberOfPacketsInBuffor(0),
    m_NumberOfProcessedPackets(0),
    m_NumberOfRejectedPackets(0),
    m_NumberOfPacketsServedWithoutBeingInQueue(0),
    m_Generator(std::random_device{}()),
    m_Distribution(SCALING_FACTOR * lambda)
{
    m_Ratio = static_cast<float>(m_Weight)/static_cast<float>(m_AvgPacketSize);
}

bool Queue::returnPacket(Packet &packet)
{
    if (m_Queue.size() > 0)
    {
        packet = m_Queue.front();
        m_Queue.pop_front();
        m_Intervals.push_back(globalTime - packet.getTimeOfArrival());
        m_NumberOfPacketsInBuffor--;
        m_NumberOfProcessedPackets++;
        return true;
    }
    return false;
}

bool Queue::getPacket(Packet &packet)
{
    if (static_cast<int>(m_Queue.size()) < m_BufforSize)
    {
        m_Queue.push_back(packet);
        m_NumberOfPacketsInBuffor++;
        return true;

    }
    else
    {
        m_NumberOfRejectedPackets++;
        return false;
    }
}

void Queue::setNumberOfPacketsPerIteration(int packetsNumber)
{
    std::cout << "Queue " << m_Name << ": " << packetsNumber << " per iteration." << std::endl;
    if (m_NumberOfPacketsPerIteration != packetsNumber)
    {
        m_NumberOfPacketsPerIteration = packetsNumber;
    }
}

double Queue::generateRandomTime()
{
    auto comp = [](int a, int b) { return a < b; };
    float makeRoundProperly = 1000;
    return round(1.0 * SCALING_FACTOR * makeRoundProperly / static_cast<double>(m_Distribution(m_Generator))) / makeRoundProperly;
}
