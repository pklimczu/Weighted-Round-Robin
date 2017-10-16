#include "SimulationPresenter.h"
#include <memory>
#include <iostream>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include "Scheduler.h"

SimulationPresenter::SimulationPresenter(QObject *parent)   :
    m_IsSimulationInProgress(false)
  , m_ShowErrors(false)
{
    m_ListOfQueuesItems = new QueueModel(this);
}

SimulationPresenter::~SimulationPresenter()
{
    delete m_ListOfQueuesItems;
}

void SimulationPresenter::setShowErrors(bool newValue)
{
    if (newValue != m_ShowErrors)
    {
        m_ShowErrors = newValue;
        Q_EMIT showErrorsChanged();
        Q_EMIT listOfErrorsChanged();
        if (m_ShowErrors == false)
        {
            m_ErrorsList.clear();
        }
    }
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
        setShowErrors(false);
    }
    else
    {
        m_ErrorsList.push_front("Oops, something went wrong - queue cannot be added!");
        setShowErrors(true);
    }
}

void SimulationPresenter::removeQueue(int index)
{
    m_ListOfQueuesItems->removeQueueItem(index);
}

void SimulationPresenter::startSimulation(int throughput, double duration)
{
    std::list<std::unique_ptr<ResultStruct>> stdListOfResults;
    _changeSimulationState(true);
    Scheduler *scheduler = new Scheduler(throughput, duration);
    for (const QueueItem *q : m_ListOfQueuesItems->getListOfItems())
    {
        /* In order to eliminate problem with queues named the same */
        std::string suffix = std::to_string(rand()%1000);
        scheduler->addQueue(new Queue(q->name().toStdString() + suffix,
                                      q->lambdaInt(),
                                      q->avgSizeInt(),
                                      q->weightInt(),
                                      q->bufforSizeInt()));
    }
    scheduler->run(stdListOfResults);
    _changeSimulationState(false);

    _prepareResults(stdListOfResults);
}

void SimulationPresenter::saveToFile()
{
    QDateTime time(QDateTime::currentDateTime());
    QString fileName = "savedResult" + time.toString("yy-mm-dd_hh-mm-ss-zzz") + ".txt";
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        m_ErrorsList.append("File not saved correctly!");
        setShowErrors(true);
    }

    QTextStream out(&file);
    ResultItem *tempResultItem;

    for (auto *q : m_ResultsList)
    {
        tempResultItem = dynamic_cast<ResultItem*>(q);
        out << "########################################\n";
        out << "Queue name: " << tempResultItem->name() << "\n";
        out << "Remains in buffor: " << tempResultItem->inBuffor() << "\n";
        out << "Processed: " << tempResultItem->processed() << "\n";
        out << "Rejected: " << tempResultItem->rejected() << "\n";
        out << "Without in queue: " << tempResultItem->withoutInQueue() << "\n";
    }
    out << "########################################\n";
    file.close();
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

void SimulationPresenter::_prepareResults(std::list<std::unique_ptr<ResultStruct> > &listOfResult)
{
    for (auto *rl : m_ResultsList)
    {
        delete rl;
    }

    m_ResultsList.clear();
    for (const auto &q : listOfResult)
    {
        ResultItem *resultItem = new ResultItem(q.get()->name,
                                                q.get()->packetsInBuffor,
                                                q.get()->proccessedPackets,
                                                q.get()->rejectedPackets,
                                                q.get()->servedWithoutQueue);
        m_ResultsList.append(resultItem);
    }
    Q_EMIT resultListChanged();
}
