#ifndef QUEUEITEM_H
#define QUEUEITEM_H

#include <QObject>

class QueueItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY itemChanged)
    Q_PROPERTY(QString lambda READ lambda NOTIFY itemChanged)
    Q_PROPERTY(QString avgSize READ avgSize NOTIFY itemChanged)
    Q_PROPERTY(QString weight READ weight NOTIFY itemChanged)
    Q_PROPERTY(QString bufforSize READ bufforSize NOTIFY itemChanged)

public:
    QueueItem(QObject *parent = 0);
    QueueItem(QString name, QString lambda, QString avgSize, QString weight, QString bufforSize, QObject *parent = 0);

    QString name() const { return m_Name; }
//    void setName(QString newName);
    Q_SIGNAL void nameChanged();

    QString lambda() const { return m_Lambda; }
//    void setLambda(QString newLambda);
    Q_SIGNAL void lambdaChanged();

    QString avgSize() const { return m_AvgSize; }
//    void setAvgSize(QString newAvgSize);
    Q_SIGNAL void avgSizeChanged();

    QString weight() const { return m_Weight; }
//    void setWeight(QString newWeight);
    Q_SIGNAL void weightChanged();

    QString bufforSize() const { return m_BufforSize; }
//    void setBufforSize(QString newBufforSize);
    Q_SIGNAL void bufforSizeChanged();

    Q_SIGNAL void itemChanged();

private:
    QString m_Name;
    QString m_Lambda;
    QString m_AvgSize;
    QString m_Weight;
    QString m_BufforSize;

};

#endif // QUEUEITEM_H
