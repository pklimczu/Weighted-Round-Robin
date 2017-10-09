#include "SimulationPresenter.h"

SimulationPresenter::SimulationPresenter(QObject *parent)
{
    m_ListOfQueuesItems.append(new QueueItem("Some queue", "100", "500", "20", "1000"));
    m_ListOfQueuesItems.append(new QueueItem("Another queue", "100", "1500", "20", "1000"));
    m_ListOfQueuesItems.append(new QueueItem("Still another one queue", "100", "500", "20", "1000"));
    m_ListOfQueuesItems.append(new QueueItem("This is probably also a queue", "100", "5000", "20", "1000"));
}
