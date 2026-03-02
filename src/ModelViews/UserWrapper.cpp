#include "UserWrapper.h"

UserWrapper::UserWrapper(QObject *parent)
    : QObject(parent), m_profileWrapper(new UserProfileWrapper(this)), m_guWrapper(new GuWrapper(this)), m_isEmpty(true)
{
}

UserWrapper::~UserWrapper()
{
    clearWrappers();
}

void UserWrapper::clearWrappers()
{
    qDeleteAll(m_prizes);
    m_prizes.clear();
    qDeleteAll(m_eloHistory);
    m_eloHistory.clear();
    qDeleteAll(m_dailyCounts);
    m_dailyCounts.clear();
}

void UserWrapper::setUser(const User &user)
{
    clearWrappers();

    m_profileWrapper->setProfile(user.profile);
    m_guWrapper->setGu(user.gu);

    for (const auto &prize : user.prizes)
    {
        auto *wrapper = new UserPrizeWrapper(this);
        wrapper->setPrize(prize);
        m_prizes.append(wrapper);
    }

    for (const auto &elo : user.eloHistory)
    {
        auto *wrapper = new EloRecordWrapper(this);
        wrapper->setEloRecord(elo);
        m_eloHistory.append(wrapper);
    }

    for (auto it = user.dailyCounts.constBegin(); it != user.dailyCounts.constEnd(); ++it)
    {
        auto *wrapper = new DailyCountWrapper(this);
        wrapper->setDailyCount(it.value());
        m_dailyCounts.insert(it.key(), wrapper);
    }

    m_isEmpty = false;
    Q_EMIT userChanged();
}

UserProfileWrapper *UserWrapper::profile() const
{
    return m_profileWrapper;
}

GuWrapper *UserWrapper::gu() const
{
    return m_guWrapper;
}

QList<QObject *> UserWrapper::prizes() const
{
    return m_prizes;
}

QList<QObject *> UserWrapper::eloHistory() const
{
    return m_eloHistory;
}

QList<QDate> UserWrapper::dailyCountDates() const
{
    return m_dailyCounts.keys();
}

DailyCountWrapper *UserWrapper::dailyCount(const QDate &date) const
{
    return m_dailyCounts.value(date, nullptr);
}

QObject *UserWrapper::prizeAt(int index) const
{
    if (index >= 0 && index < m_prizes.size())
    {
        return m_prizes.at(index);
    }
    return nullptr;
}

QObject *UserWrapper::eloAt(int index) const
{
    if (index >= 0 && index < m_eloHistory.size())
    {
        return m_eloHistory.at(index);
    }
    return nullptr;
}

bool UserWrapper::isEmpty() const
{
    return m_isEmpty;
}
