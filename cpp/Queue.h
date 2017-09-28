#ifndef QUEUE_H
#define QUEUE_H
#include <string>
#include <deque>
#include <vector>
#include "Packet.h"

class Queue
{
public:
    Queue();
    Queue(std::string name, int lambda, int avgPacketSize, int weight, int bufforSize);

    /**
     * @brief returnPacket - returns packet from queue by reference
     * @param packet - packet to be returned
     * @return - true if there is packet to be returned; otherwise false
     */
    bool returnPacket(Packet &packet);

    /**
     * @brief getPacket - takes new packet to queue
     * @param packet - packet to be taken
     * @return - true if there is a place for a packet in queue; otherwise false
     */
    bool getPacket(Packet &packet);

    float getRatio() const { return m_Ratio; }
    std::string getName() const { return m_Name; }
    int getPacketsPerIteration() const { return m_NumberOfPacketsPerIteration; }
    void setNumberOfPacketsPerIteration(int packetsNumber);

    int getNumberOfPacketsInBuffor() const { return m_NumberOfPacketsInBuffor; }
    int getNumberOfProcessedPackets() const { return m_NumberOfProcessedPackets; }
    int getNumberOfRejectedPackets() const { return m_NumberOfRejectedPackets; }
    int getNumberOfPacketsServedWithoutBeingInQueue() const { return m_NumberOfPacketsServedWithoutBeingInQueue; }

    void addPacketProcessedWithoutBeingInQueue() { m_NumberOfPacketsServedWithoutBeingInQueue++; }

private:
    int m_Lambda;               // Determines frequency of incoming next packets due to Poisson distribution
    int m_AvgPacketSize;        // Average packet size [in bits]
    int m_Weight;               // Importance of this queue
    float m_Ratio;              // Ratio weight to average size of queue
    int m_BufforSize;           // Buffor size [in bits]
    std::string m_Name;         // Name of queue
    int m_NumberOfPacketsPerIteration;

    int m_NumberOfPacketsInBuffor;
    int m_NumberOfProcessedPackets;
    int m_NumberOfRejectedPackets;
    int m_NumberOfPacketsServedWithoutBeingInQueue;

    std::deque<Packet> m_Queue;

//    std::vector<int> m_TimesOfArrivals;         // Times of arrival every single packet
    std::vector<float> m_Intervals;               // Differences between times of arrival following packets
    std::vector<int> m_NumberOfPacketsInQueue;    // Number of packets in queue awaiting to be processed at the moment of arrival new packet
};

#endif // QUEUE_H
