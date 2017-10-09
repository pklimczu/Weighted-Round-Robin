#include "QueueItem.h"

QueueItem::QueueItem(QObject *parent)
{

}

QueueItem::QueueItem(QString name, QString lambda, QString avgSize, QString weight, QString bufforSize, QObject *parent) :
    m_Name(name),
    m_Lambda(lambda),
    m_AvgSize(avgSize),
    m_Weight(weight),
    m_BufforSize(bufforSize)
{

}
