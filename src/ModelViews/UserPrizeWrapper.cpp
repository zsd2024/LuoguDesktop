#include "UserPrizeWrapper.h"

UserPrizeWrapper::UserPrizeWrapper(QObject *parent)
    : QObject(parent)
{
}

void UserPrizeWrapper::setPrize(const UserPrize &prize)
{
    m_prize = prize;
    Q_EMIT prizeChanged();
}

int UserPrizeWrapper::year() const
{
    return m_prize.year;
}

QString UserPrizeWrapper::contest() const
{
    return m_prize.contest;
}

QString UserPrizeWrapper::event() const
{
    return m_prize.event.value_or(QString());
}

bool UserPrizeWrapper::hasEvent() const
{
    return m_prize.event.has_value();
}

QString UserPrizeWrapper::prize() const
{
    return m_prize.prize;
}

int UserPrizeWrapper::score() const
{
    return m_prize.score;
}

int UserPrizeWrapper::rank() const
{
    return m_prize.rank;
}
