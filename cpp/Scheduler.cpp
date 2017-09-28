#include "Scheduler.h"
#include <limits>
#include <iostream>
#include <cmath>

double globalTime = 0;

Scheduler::Scheduler()
{

}

Scheduler::Scheduler(int linkMaxThroughput, int endTime)    :
    m_LinkMaxThroughput(linkMaxThroughput),
    m_EndTime(endTime),
    m_QueuesIterationCounter(0)
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

}

void Scheduler::_runSimulation()
{

}

void Scheduler::_processPacketArrival()
{

}

void Scheduler::_processPacketDeparture()
{

}

void Scheduler::_prepareStatistics()
{

}

double Scheduler::_generateTime(double lambda)
{

}
