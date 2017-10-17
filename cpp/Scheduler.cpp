#include "Scheduler.h"
#include <limits>
#include <iostream>
#include <cmath>
#include <sstream>

double globalTime = 0;

Scheduler::Scheduler() { }

Scheduler::Scheduler(int linkMaxThroughput, double endTime)    :
    m_LinkMaxThroughput(linkMaxThroughput*1000),                    // to make kilobits per second
    m_EndTime(endTime),
    m_QueueServedPacketsCounter(0),
    m_QueuesIterationCounter(0),
    m_ServerState(IDLE)
{
    m_QueuesMap.clear();
}

bool Scheduler::addQueue(Queue *queue)
{
    m_QueuesMap[queue->getName()] = queue;
    return true;
}

bool Scheduler::removeQueue(Queue &queue)
{
    SimulationMap::const_iterator it = m_QueuesMap.find(queue.getName());
    m_QueuesMap.erase(it);
    return true;
}

void Scheduler::run()
{
    _normalizeQueuesWeights();
    _doZeroIteration();
    _runSimulation();
    _prepareStatistics();
}

void Scheduler::run(ListResultStruct &resultList)
{
    _normalizeQueuesWeights();
    _doZeroIteration();
    _runSimulation();
    _getStatistics(resultList);
    m_QueuesMap.clear();
}

void Scheduler::_normalizeQueuesWeights()
{
    if (m_QueuesMap.size() > 0)
    {
        float smallestRatio = std::numeric_limits<float>::max();
        std::map<std::string,double> queueRatioMap;

        for (const auto &q : m_QueuesMap)
        {
            queueRatioMap[q.first] = q.second->getRatio();
            if (smallestRatio > q.second->getRatio())
            {
                smallestRatio = q.second->getRatio();
            }
        }

        smallestRatio = pow(smallestRatio, -1.0);
        for (auto &q : queueRatioMap)
        {
            q.second = round(smallestRatio * q.second);
        }

        for (const auto &q : m_QueuesMap)
        {
            q.second->setNumberOfPacketsPerIteration(static_cast<int>(queueRatioMap[q.first]));
        }
    }
}

void Scheduler::_doZeroIteration()
{
    for (const auto &q : m_QueuesMap)
    {
        auto newEvent = std::make_shared<SimulationEventStruct>(q.second->generateRandomTime(),
                                                                q.second->getName(),
                                                                IncomingPacket);
        m_EventPriorityQueue.push(newEvent);
    }
}

void Scheduler::_runSimulation()
{
    while (globalTime < m_EndTime)
    {
        if (m_EventPriorityQueue.empty())
            break;
        auto event = m_EventPriorityQueue.top();
        m_EventPriorityQueue.pop();
        globalTime = event.get()->eventTime;

        switch (event.get()->simulationEventType)
        {
            case IncomingPacket:
                _processPacketArrival(*event.get());
                break;
            case ProcessPacket:
                _processPacketDeparture(*event.get());
                break;
            default:
                break;
        }
    }
    globalTime = 0;
}

void Scheduler::_processPacketArrival(SimulationEventStruct &event)
{
    double timeOfArrivalNextPacket = globalTime + m_QueuesMap[event.queueName]->generateRandomTime();
    auto newEvent = std::make_shared<SimulationEventStruct>(timeOfArrivalNextPacket,
                                                            event.queueName,
                                                            IncomingPacket);
    m_EventPriorityQueue.push(newEvent);

    if (m_ServerState == IDLE)
    {
        _processPacketDeparture(event);
        m_QueuesMap[event.queueName]->addPacketProcessedWithoutBeingInQueue();
        m_ActiveQueueName = event.queueName;
    }
    else    // m_ServerState == WORKING
    {
        Packet *packet = new Packet(event.eventTime);
        m_QueuesMap[event.queueName]->getPacket(packet);
    }
}

void Scheduler::_processPacketDeparture(SimulationEventStruct &event)
{
    Packet packet;

    if (m_ServerState == IDLE)
    {
        m_ServerState = WORKING;
        packet.setPacketSize(m_QueuesMap[event.queueName]->getAvgPacketSize());
        packet.setTimeOfArrival(event.eventTime);
        _calculatePacketSendingEndTime(packet, event.queueName);
        m_QueueServedPacketsCounter++;
        m_ActiveQueueName = event.queueName;
    }
    else if (m_QueueServedPacketsCounter < m_QueuesMap[m_ActiveQueueName]->getPacketsPerIteration() &&
             m_QueuesMap[m_ActiveQueueName]->returnPacket(packet))
    {
        m_QueuesIterationCounter = 0;
        _calculatePacketSendingEndTime(packet, event.queueName);
        m_QueueServedPacketsCounter++;
    }
    else if (!m_QueuesMap[m_ActiveQueueName]->returnPacket(packet) ||
             m_QueueServedPacketsCounter >= m_QueuesMap[m_ActiveQueueName]->getPacketsPerIteration())
    {
        m_QueuesIterationCounter++;
        if (m_QueuesIterationCounter == (m_QueuesMap.size() + 1))
        {
            m_QueuesIterationCounter = 0;
            m_ServerState = IDLE;
        }
        else
        {
            m_QueueServedPacketsCounter = 0;
            auto itr = m_QueuesMap.find(m_ActiveQueueName);
            itr++;
            if (itr == m_QueuesMap.end())
            {
                itr = m_QueuesMap.begin();
            }
            m_ActiveQueueName = (*itr).second->getName();
            _processPacketDeparture(event);
        }
    }
}

void Scheduler::_calculatePacketSendingEndTime(Packet &packet, std::string queueName)
{
    double processingEndTime = globalTime + static_cast<double>(packet.getPacketSize()) / m_LinkMaxThroughput;
    auto newEvent = std::make_shared<SimulationEventStruct>(processingEndTime,
                                                            queueName,
                                                            ProcessPacket);
    m_EventPriorityQueue.push(newEvent);
}

void Scheduler::_prepareStatistics()
{
    for (const auto &q : m_QueuesMap)
    {
        std::cout << "#######################################\n";
        std::cout << "NAME: \t" << q.second->getName() << "\n";
        std::cout << "Number of packets in buffor: \t\t\t" << q.second->getNumberOfPacketsInBuffor() << "\n";
        std::cout << "Number of processed packets: \t\t\t" << q.second->getNumberOfProcessedPackets() << "\n";
        std::cout << "Number of rejected packets: \t\t\t" << q.second->getNumberOfRejectedPackets() << "\n";
        std::cout << "Number of packets served without being in queue: \t" << q.second->getNumberOfPacketsServedWithoutBeingInQueue() << "\n";
    }
}

void Scheduler::_getStatistics(ListResultStruct &resultList)
{
    typedef SimulationPresenter::ResultStruct resultStruct;
    resultList.clear();
    for (const auto &q : m_QueuesMap)
    {
        resultList.push_back(std::shared_ptr<resultStruct>(new resultStruct(q.second->getName(),
                                                                         q.second->getNumberOfPacketsInBuffor(),
                                                                         q.second->getNumberOfProcessedPackets(),
                                                                         q.second->getNumberOfRejectedPackets(),
                                                                         q.second->getNumberOfPacketsServedWithoutBeingInQueue())));
    }
}
