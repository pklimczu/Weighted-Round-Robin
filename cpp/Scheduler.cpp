#include "Scheduler.h"
#include <limits>
#include <iostream>
#include <cmath>

double globalTime = 0;

Scheduler::Scheduler() { }

Scheduler::Scheduler(int linkMaxThroughput, int endTime)    :
    m_LinkMaxThroughput(linkMaxThroughput),
    m_EndTime(endTime),
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
    _prepareStatistics();
}

void Scheduler::_processPacketArrival(SimulationEventStruct &event)
{
    double timeOfArrivalNextPacket = globalTime + m_QueuesMap[event.queueName]->generateRandomTime();
    auto newEvent = std::make_shared<SimulationEventStruct>(timeOfArrivalNextPacket,
                                                            event.queueName,
                                                            IncomingPacket);
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

}

void Scheduler::_prepareStatistics()
{

}
