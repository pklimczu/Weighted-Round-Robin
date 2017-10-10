#include "QueueModel.h"

QueueModel::QueueModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void QueueModel::addQueueItem(const QueueItem &queueItem)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_QueueItems << queueItem;
    endInsertRows();
}

int QueueModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_QueueItems.size();
}

QVariant QueueModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_QueueItems.count())
        return QVariant();

    const QueueItem &queueItem = m_QueueItems[index.row()];
    if (role == NameRole)
        return queueItem.name();
    else if (role == LambdaRole)
        return queueItem.lambda();
    else if (role == AvgSizeRole)
        return queueItem.avgSize();
    else if (role == WeightRole)
        return queueItem.weight();
    else if (role == BufforSizeRole)
        return queueItem.bufforSize();

    return QVariant();
}

QHash<int, QByteArray> QueueModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole]       = "name";
    roles[LambdaRole]     = "lambda";
    roles[AvgSizeRole]    = "avgSize";
    roles[WeightRole]     = "weight";
    roles[BufforSizeRole] = "bufforSize";
    return roles;
}
