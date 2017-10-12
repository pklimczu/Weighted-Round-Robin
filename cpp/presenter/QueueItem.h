#ifndef QUEUEITEM_H
#define QUEUEITEM_H
#include <QDebug>

class QueueItem
{

public:
    QueueItem();
    QueueItem(QString name, QString lambda, QString avgSize, QString weight, QString bufforSize, QObject *parent = 0);
    QueueItem(QString name, int lambda, int avgSize, int weight, int bufforSize);

    QString name() const { return m_Name; }

    QString lambda() const { return m_Lambda; }
    int lambdaInt() const { return m_LambdaInt; }

    QString avgSize() const { return m_AvgSize; }
    int avgSizeInt() const { return m_AvgSizeInt; }

    QString weight() const { return m_Weight; }
    int weightInt() const { return m_WeightInt; }

    QString bufforSize() const { return m_BufforSize; }
    int bufforSizeInt() const { return m_BufforSizeInt; }

private:
    QString m_Name;
    QString m_Lambda;
    int m_LambdaInt;
    QString m_AvgSize;
    int m_AvgSizeInt;
    QString m_Weight;
    int m_WeightInt;
    QString m_BufforSize;
    int m_BufforSizeInt;

};

#endif // QUEUEITEM_H
