#ifndef QUEUEMODEL_H
#define QUEUEMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include "QueueItem.h"

class QueueModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum QueueItemRoles {
        NameRole = Qt::UserRole + 1,
        LambdaRole, AvgSizeRole, WeightRole, BufforSizeRole
    };

    QueueModel(QObject *parent = 0);

    void addQueueItem(QueueItem *queueItem);
    void removeQueueItem(int index);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QueueItem*> m_QueueItems;
};

#endif // QUEUEMODEL_H
