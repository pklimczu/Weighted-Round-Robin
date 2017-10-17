#include "ResultItem.h"
#include <iostream>

ResultItem::ResultItem(QObject *parent)
{
}

ResultItem::ResultItem(std::string _name, int _pIB, int _pP, int _rP, int _sWQ, QObject *parent)
    : m_Name(_name.c_str())
    , m_InBuffor(_pIB)
    , m_Processed(_pP)
    , m_Rejected(_rP)
    , m_WithoutInQueue(_sWQ)
{
    /* Removing guarding suffix */
    m_Name.truncate(m_Name.size() - 3);
}

void ResultItem::createFromAnother(const ResultItem &resultItem)
{
    m_Name = resultItem.name();
    m_InBuffor = resultItem.inBuffor();
    m_Processed = resultItem.processed();
    m_Rejected = resultItem.rejected();
    m_WithoutInQueue = resultItem.withoutInQueue();
}
