#ifndef SIMULATIONPRESENTER_H
#define SIMULATIONPRESENTER_H

#include <QObject>
#include "Scheduler.h"
#include "presenter/QueueItem.h"
#include "presenter/QueueModel.h"
#include "Scheduler.h"

class SimulationPresenter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QueueModel* queueList READ queueList NOTIFY queueListChanged)
    Q_PROPERTY(bool simulationInProgress READ simulationInProgress NOTIFY simulationInProgressChanged)

public:
    SimulationPresenter(QObject *parent = 0);
    ~SimulationPresenter();

    QueueModel* queueList() const { return m_ListOfQueuesItems; }
    Q_SIGNAL void queueListChanged();

    bool simulationInProgress() const { return m_IsSimulationInProgress; }
    Q_SIGNAL void simulationInProgressChanged();

    Q_INVOKABLE void addQueue(QVariantList queueArguments);
    Q_INVOKABLE void removeQueue(int index);

    Q_INVOKABLE void startSimulation(int throughput, double duration);

private:
    bool _parseName(QVariant &variant, QString &returnString);
    bool _parseLambda(QVariant &variant, int &returnLambda);
    bool _parseAvgSize(QVariant &variant, int &returnAvgSize);
    bool _parseWeight(QVariant &variant, int &returnWeight);
    bool _parseBufforSize(QVariant &variant, int &returnBufforSize);

    void _changeSimulationState(bool newState);

    QueueModel *m_ListOfQueuesItems;
    QList<QString> m_ErrorsList;
    bool m_IsSimulationInProgress;
};

#endif // SIMULATIONPRESENTER_H
