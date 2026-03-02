#include "UserProfileWrapper.h"

UserProfileWrapper::UserProfileWrapper(QObject *parent)
    : QObject(parent)
{
}

void UserProfileWrapper::setProfile(const UserProfile &profile)
{
    m_profile = profile;
    Q_EMIT profileChanged();
}

int UserProfileWrapper::uid() const
{
    return m_profile.uid;
}

QString UserProfileWrapper::name() const
{
    return m_profile.name;
}

QString UserProfileWrapper::avatar() const
{
    return m_profile.avatar;
}

QString UserProfileWrapper::slogan() const
{
    return m_profile.slogan;
}

QString UserProfileWrapper::introduction() const
{
    return m_profile.introduction;
}

QString UserProfileWrapper::badge() const
{
    return m_profile.badge.value_or(QString());
}

QDateTime UserProfileWrapper::registerTime() const
{
    return m_profile.registerTime;
}

bool UserProfileWrapper::isAdmin() const
{
    return m_profile.isAdmin;
}

bool UserProfileWrapper::isBanned() const
{
    return m_profile.isBanned;
}

int UserProfileWrapper::color() const
{
    return static_cast<int>(m_profile.color);
}

QString UserProfileWrapper::rawColor() const
{
    return m_profile.rawColor;
}

int UserProfileWrapper::ccfLevel() const
{
    return m_profile.ccfLevel;
}

int UserProfileWrapper::xcpcLevel() const
{
    return m_profile.xcpcLevel;
}

QString UserProfileWrapper::background() const
{
    return m_profile.background;
}

int UserProfileWrapper::eloValue() const
{
    return m_profile.eloValue.value_or(0);
}

bool UserProfileWrapper::hasEloValue() const
{
    return m_profile.eloValue.has_value();
}

int UserProfileWrapper::followingCount() const
{
    return m_profile.followingCount;
}

int UserProfileWrapper::followerCount() const
{
    return m_profile.followerCount;
}

int UserProfileWrapper::ranking() const
{
    return m_profile.ranking;
}

int UserProfileWrapper::passedProblemCount() const
{
    return m_profile.passedProblemCount;
}

int UserProfileWrapper::submittedProblemCount() const
{
    return m_profile.submittedProblemCount;
}
