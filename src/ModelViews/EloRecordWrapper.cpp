#include "EloRecordWrapper.h"

EloRecordWrapper::EloRecordWrapper(QObject *parent)
    : QObject(parent)
{
}

void EloRecordWrapper::setEloRecord(const EloRecord &record)
{
    m_record = record;
    Q_EMIT eloRecordChanged();
}

int EloRecordWrapper::rating() const
{
    return m_record.rating;
}

QDateTime EloRecordWrapper::time() const
{
    return m_record.time;
}

int EloRecordWrapper::contestId() const
{
    return m_record.contestId;
}

QDateTime EloRecordWrapper::contestStart() const
{
    return m_record.contestStart;
}

QDateTime EloRecordWrapper::contestEnd() const
{
    return m_record.contestEnd;
}

QString EloRecordWrapper::contestName() const
{
    return m_record.contestName;
}

int EloRecordWrapper::userCount() const
{
    return m_record.userCount;
}

int EloRecordWrapper::prevDiff() const
{
    return m_record.prevDiff.value_or(0);
}

bool EloRecordWrapper::hasPrevDiff() const
{
    return m_record.prevDiff.has_value();
}
