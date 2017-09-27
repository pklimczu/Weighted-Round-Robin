#include "Scheduler.h"

double globalTime = 0;

Scheduler::Scheduler()
{

}

Scheduler::Scheduler(int linkMaxThroughput, int endTime)
{

}

bool Scheduler::addQueue(Queue &queue)
{
    m_QueuesVector.push_back(queue);
    return true;
}

bool Scheduler::removeQueue(Queue &queue)
{
//    for (auto &q : m_QueuesVector)
//    {

//    }
}

void Scheduler::_normalizeQueuesWeights()
{

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
