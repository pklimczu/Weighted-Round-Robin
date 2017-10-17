#ifndef SIMULATIONPRESENTER_H
#define SIMULATIONPRESENTER_H

#include <QObject>
#include <QTimer>
#include <memory>
#include "presenter/QueueItem.h"
#include "presenter/QueueModel.h"
#include "presenter/ResultItem.h"

class SimulationPresenter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QueueModel* queueList READ queueList NOTIFY queueListChanged)
    Q_PROPERTY(bool simulationInProgress READ simulationInProgress NOTIFY simulationInProgressChanged)
    Q_PROPERTY(QList<QObject*> resultList READ resultList NOTIFY resultListChanged)
    Q_PROPERTY(bool showErrors READ showErrors WRITE setShowErrors NOTIFY showErrorsChanged)
    Q_PROPERTY(QString listOfErrors READ listOfErrors NOTIFY listOfErrorsChanged)
    Q_PROPERTY(float progressValue READ progressValue NOTIFY progressValueChanged)

public:
    struct ResultStruct
    {
        ResultStruct(std::string _name, int _pIB, int _pP, int _rP, int _sWQ) :
            name(_name), packetsInBuffor(_pIB), proccessedPackets(_pP), rejectedPackets(_rP), servedWithoutQueue(_sWQ) {}
        std::string name;
        int packetsInBuffor;
        int proccessedPackets;
        int rejectedPackets;
        int servedWithoutQueue;
    };

    SimulationPresenter(QObject *parent = 0);
    ~SimulationPresenter();

    QueueModel* queueList() const { return m_ListOfQueuesItems; }
    Q_SIGNAL void queueListChanged();

    bool simulationInProgress() const { return m_IsSimulationInProgress; }
    Q_SIGNAL void simulationInProgressChanged();

    QList<QObject*> resultList() const { return m_ResultsList; }
    Q_SIGNAL void resultListChanged();

    bool showErrors() const { return m_ShowErrors; }
    void setShowErrors(bool newValue);
    Q_SIGNAL void showErrorsChanged();

    QString listOfErrors() const { return m_ErrorsList.join("\n"); }
    Q_SIGNAL void listOfErrorsChanged();

    float progressValue() const { return m_ProgressValue; }
    Q_SIGNAL void progressValueChanged();

    Q_INVOKABLE void addQueue(QVariantList queueArguments);
    Q_INVOKABLE void removeQueue(int index);

    Q_INVOKABLE void startSimulation(int throughput, double duration);

    Q_INVOKABLE void saveToFile();

    Q_SIGNAL void resultsReady();
    void onResultsReady();

private:
    bool _parseName(QVariant &variant, QString &returnString);
    bool _parseLambda(QVariant &variant, int &returnLambda);
    bool _parseAvgSize(QVariant &variant, int &returnAvgSize);
    bool _parseWeight(QVariant &variant, int &returnWeight);
    bool _parseBufforSize(QVariant &variant, int &returnBufforSize);

    void _runSimulation(int throughput, double duration);
    void _changeSimulationState(bool newState);
    void _prepareResults(std::list<std::shared_ptr<ResultStruct>> &listOfResult);
    void _changeProgressValue();

    QueueModel *m_ListOfQueuesItems;
    QList<QString> m_ErrorsList;
    bool m_IsSimulationInProgress;
    QList<QObject*> m_ThreadResultList;
    QList<QObject*> m_ResultsList;
    bool m_ShowErrors;
    float m_ProgressValue;
    QTimer *m_TimerGlobalTime;
    double m_SimulationDuration;
};

#endif // SIMULATIONPRESENTER_H
