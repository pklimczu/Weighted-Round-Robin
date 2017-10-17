#ifndef RESULTITEM_H
#define RESULTITEM_H

#include <QObject>

class ResultItem : public QObject
{
    Q_OBJECT
public:
    explicit ResultItem(QObject* parent = 0);
    ResultItem(std::string _name, int _pIB, int _pP, int _rP, int _sWQ, QObject* parent = 0);

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int inBuffor READ inBuffor NOTIFY inBufforChanged)
    Q_PROPERTY(int processed READ processed NOTIFY processedChanged)
    Q_PROPERTY(int rejected READ rejected NOTIFY rejectedChanged)
    Q_PROPERTY(int withoutInQueue READ withoutInQueue NOTIFY withoutInQueueChanged)

    QString name() const { return m_Name; }
    Q_SIGNAL void nameChanged();

    int inBuffor() const { return m_InBuffor; }
    Q_SIGNAL void inBufforChanged();

    int processed() const { return m_Processed + m_WithoutInQueue; }
    Q_SIGNAL void processedChanged();

    int rejected() const { return m_Rejected; }
    Q_SIGNAL void rejectedChanged();

    int withoutInQueue() const { return m_WithoutInQueue; }
    Q_SIGNAL void withoutInQueueChanged();

    void createFromAnother(const ResultItem &resultItem);
private:
    QString m_Name;
    int m_InBuffor;
    int m_Processed;
    int m_Rejected;
    int m_WithoutInQueue;
};

#endif // RESULTITEM_H
