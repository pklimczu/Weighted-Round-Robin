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

    QString avgSize() const { return m_AvgSize; }

    QString weight() const { return m_Weight; }

    QString bufforSize() const { return m_BufforSize; }

private:
    QString m_Name;
    QString m_Lambda;
    QString m_AvgSize;
    QString m_Weight;
    QString m_BufforSize;

};

#endif // QUEUEITEM_H
