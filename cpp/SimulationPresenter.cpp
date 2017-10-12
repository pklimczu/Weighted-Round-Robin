#include "SimulationPresenter.h"

SimulationPresenter::SimulationPresenter(QObject *parent)   :
    m_IsSimulationInProgress(false)
{
    m_ListOfQueuesItems = new QueueModel(this);
}

SimulationPresenter::~SimulationPresenter()
{
    delete m_ListOfQueuesItems;
}

void SimulationPresenter::addQueue(QVariantList queueArguments)
{
    m_ErrorsList.clear();
    QString name;
    int lambda, avgSize, weight, bufforSize;
    bool canBeParse = _parseName(queueArguments[0], name) &&
                      _parseLambda(queueArguments[1], lambda) &&
                      _parseAvgSize(queueArguments[2], avgSize) &&
                      _parseWeight(queueArguments[3], weight) &&
                      _parseBufforSize(queueArguments[4], bufforSize);
    if (canBeParse)
    {
        QueueItem *queueItem = new QueueItem(name, lambda, avgSize, weight, bufforSize);
        m_ListOfQueuesItems->addQueueItem(queueItem);
    }
    else
    {
        // TODO: ADD DISPLAYING INFO ABOUT ERRORS
        qDebug() << m_ErrorsList;
    }
}

void SimulationPresenter::removeQueue(int index)
{
    m_ListOfQueuesItems->removeQueueItem(index);
}

void SimulationPresenter::startSimulation(int throughput, double duration)
{
    _changeSimulationState(true);
    Scheduler *scheduler = new Scheduler(throughput, duration);
    for (const QueueItem *q : m_ListOfQueuesItems->getListOfItems())
    {
        scheduler->addQueue(new Queue(q->name().toStdString(),
                                      q->lambdaInt(),
                                      q->avgSizeInt(),
                                      q->weightInt(),
                                      q->bufforSizeInt()));
    }
    scheduler->run();
    _changeSimulationState(false);
}

bool SimulationPresenter::_parseName(QVariant &variant, QString &returnString)
{
    bool isString = true;
    returnString = variant.toString();
    if (!returnString.size())
    {
        m_ErrorsList.append("Empty queue name!");
        isString = false;
    }
    return isString;
}

bool SimulationPresenter::_parseLambda(QVariant &variant, int &returnLambda)
{
    bool isLambda = false;
    if (variant.canConvert<int>())
    {
        returnLambda = variant.toInt();
        if (returnLambda > 0.0)
        {
            isLambda = true;
        }
        else
        {
            m_ErrorsList.append("Lambda value must be greater than zero!");
        }
    }
    else
    {
        m_ErrorsList.append("Given lambda value cannot be converted to integer value!");
    }
    return isLambda;
}

bool SimulationPresenter::_parseAvgSize(QVariant &variant, int &returnAvgSize)
{
    bool isAvgSize = false;
    if (variant.canConvert<int>())
    {
        returnAvgSize = variant.toInt();
        if (returnAvgSize > 0.0)
        {
            isAvgSize = true;
        }
        else
        {
            m_ErrorsList.append("Average size value must be greater than zero!");
        }
    }
    else
    {
        m_ErrorsList.append("Given average size value cannot be converted to integer value!");
    }
    return isAvgSize;
}

bool SimulationPresenter::_parseWeight(QVariant &variant, int &returnWeight)
{
    bool isWeight = false;
    if (variant.canConvert<int>())
    {
        returnWeight = variant.toInt();
        isWeight = true;
    }
    else
    {
        m_ErrorsList.append("Given weight value cannot be converted to integer value!");
    }
    return isWeight;
}

bool SimulationPresenter::_parseBufforSize(QVariant &variant, int &returnBufforSize)
{
    bool isBufforSize = false;
    if (variant.canConvert<int>())
    {
        returnBufforSize = variant.toInt();
        isBufforSize = true;
    }
    else
    {
        m_ErrorsList.append("Given buffor size value cannot be converted to integer value!");
    }
    return isBufforSize;
}

void SimulationPresenter::_changeSimulationState(bool newState)
{
    m_IsSimulationInProgress = newState;
    Q_EMIT simulationInProgressChanged();
}


