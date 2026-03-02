#include "DailyCountWrapper.h"

DailyCountWrapper::DailyCountWrapper(QObject *parent)
    : QObject(parent)
{
}

void DailyCountWrapper::setDailyCount(const DailyCount &count)
{
    m_count = count;
    Q_EMIT dailyCountChanged();
}

int DailyCountWrapper::count() const
{
    return m_count.count;
}

int DailyCountWrapper::maxDifficulty() const
{
    return m_count.maxDifficulty;
}
