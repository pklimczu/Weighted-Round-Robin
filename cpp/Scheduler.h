#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Queue.h"
#include <map>
#include <queue>

class Scheduler
{
public:
    enum ServerState { IDLE, WORKING };
    enum SimulationEventType { IncomingPacket, ProcessPacket };
    typedef std::map<std::string, Queue*> SimulationMap;

    struct SimulationEventStruct
    {
        double eventTime;
        int queueNumber;
        SimulationEventType simulationEventType;

        bool operator<(const SimulationEventStruct &other) const
        {
            return eventTime < other.eventTime;
        }
    };

    Scheduler();
    Scheduler(int linkMaxThroughput, int endTime);

    bool addQueue(Queue *queue);
    bool removeQueue(Queue &queue);

    void run();

private:
    void _normalizeQueuesWeights();
    void _doZeroIteration();
    void _runSimulation();
    void _processPacketArrival();
    void _processPacketDeparture();
    void _prepareStatistics();

    double _generateTime(double lambda);

    SimulationMap m_QueuesMap;
    std::priority_queue<SimulationEventStruct> m_EventPriorityQueue;
    int m_LinkMaxThroughput;
    int m_EndTime;
    int m_QueuesIterationCounter;

};

#endif // SCHEDULER_H
