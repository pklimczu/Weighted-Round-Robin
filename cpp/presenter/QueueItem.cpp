#include "QueueItem.h"

QueueItem::QueueItem()
{

}

QueueItem::QueueItem(QString name, QString lambda, QString avgSize, QString weight, QString bufforSize, QObject *parent) :
    m_Name(name),
    m_Lambda(lambda),
    m_LambdaInt(lambda.toInt()),
    m_AvgSize(avgSize),
    m_AvgSizeInt(avgSize.toInt()),
    m_Weight(weight),
    m_WeightInt(weight.toInt()),
    m_BufforSize(bufforSize),
    m_BufforSizeInt(bufforSize.toInt())
{

}

QueueItem::QueueItem(QString name, int lambda, int avgSize, int weight, int bufforSize) :
    m_Name(name),
    m_Lambda(QString::number(lambda)),
    m_LambdaInt(lambda),
    m_AvgSize(QString::number(avgSize)),
    m_AvgSizeInt(avgSize),
    m_Weight(QString::number(weight)),
    m_WeightInt(weight),
    m_BufforSize(QString::number(bufforSize)),
    m_BufforSizeInt(bufforSize)
{

}
