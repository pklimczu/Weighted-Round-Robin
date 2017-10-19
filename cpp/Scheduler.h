#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Queue.h"
#include "SimulationPresenter.h"
#include <map>
#include <queue>
#include <memory>
#include <functional>
#include <QStringList>

class SimulationPresenter;

class Scheduler
{
public:
    enum ServerState { IDLE, WORKING };
    enum SimulationEventType { IncomingPacket, ProcessPacket };

    struct SimulationEventStruct
    {
        SimulationEventStruct(double eT, std::string qN, SimulationEventType sET) :
            eventTime(eT), queueName(qN), simulationEventType(sET) {}
        double eventTime;
        std::string queueName;
        SimulationEventType simulationEventType;

        bool operator<(const SimulationEventStruct &other) const
        {
            return eventTime < other.eventTime;
        }
    };
    typedef std::map<std::string, Queue*> SimulationMap;
    typedef std::shared_ptr<SimulationEventStruct> pSimulationEventStruct;
    typedef std::list<std::shared_ptr<SimulationPresenter::ResultStruct>> ListResultStruct;

    struct Comparator
    {
        bool operator() (pSimulationEventStruct &a, pSimulationEventStruct &b)
        {
            return a.get()->eventTime > b.get()->eventTime;
        }
    };

    Scheduler();
    Scheduler(int linkMaxThroughput, double endTime);

    bool addQueue(Queue *queue);
    bool removeQueue(Queue &queue);

    void run();
    void run(ListResultStruct &resultList);

private:
    void _normalizeQueuesWeights();
    void _doZeroIteration();
    void _runSimulation();
    void _processPacketArrival(SimulationEventStruct &event);
    void _processPacketDeparture(SimulationEventStruct *event = nullptr);
    void _calculatePacketSendingEndTime(Packet &packet, std::string queueName);
    void _prepareStatistics();
    void _getStatistics(ListResultStruct &resultList);

    double _generateTime(double lambda);

    SimulationMap m_QueuesMap;

    std::priority_queue<pSimulationEventStruct,
                        std::vector<pSimulationEventStruct>,
                        Comparator> m_EventPriorityQueue;
    int m_LinkMaxThroughput;
    double m_EndTime;
    int m_QueueServedPacketsCounter;
    int m_QueuesIterationCounter;
    ServerState m_ServerState;
    std::string m_ActiveQueueName;

};

#endif // SCHEDULER_H
