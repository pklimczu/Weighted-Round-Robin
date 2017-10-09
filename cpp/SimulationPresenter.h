#ifndef SIMULATIONPRESENTER_H
#define SIMULATIONPRESENTER_H

#include <QObject>
#include "Scheduler.h"
#include "presenter/QueueItem.h"

class SimulationPresenter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> queueList READ queueList NOTIFY queueListChanged)

public:
    SimulationPresenter(QObject *parent = 0);

    QList<QObject*> queueList() const { return m_ListOfQueuesItems; }
    Q_SIGNAL void queueListChanged();

private:
    QList<QObject*> m_ListOfQueuesItems;
};

#endif // SIMULATIONPRESENTER_H
