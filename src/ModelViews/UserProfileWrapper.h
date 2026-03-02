#pragma once
#include "../Models/User.h"
#include <QDateTime>
#include <QObject>
#include <QString>
#include <optional>

class UserProfileWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int uid READ uid NOTIFY profileChanged)
    Q_PROPERTY(QString name READ name NOTIFY profileChanged)
    Q_PROPERTY(QString avatar READ avatar NOTIFY profileChanged)
    Q_PROPERTY(QString slogan READ slogan NOTIFY profileChanged)
    Q_PROPERTY(QString introduction READ introduction NOTIFY profileChanged)
    Q_PROPERTY(QString badge READ badge NOTIFY profileChanged)
    Q_PROPERTY(QDateTime registerTime READ registerTime NOTIFY profileChanged)
    Q_PROPERTY(bool isAdmin READ isAdmin NOTIFY profileChanged)
    Q_PROPERTY(bool isBanned READ isBanned NOTIFY profileChanged)
    Q_PROPERTY(int color READ color NOTIFY profileChanged)
    Q_PROPERTY(QString rawColor READ rawColor NOTIFY profileChanged)
    Q_PROPERTY(int ccfLevel READ ccfLevel NOTIFY profileChanged)
    Q_PROPERTY(int xcpcLevel READ xcpcLevel NOTIFY profileChanged)
    Q_PROPERTY(QString background READ background NOTIFY profileChanged)
    Q_PROPERTY(int eloValue READ eloValue NOTIFY profileChanged)
    Q_PROPERTY(bool hasEloValue READ hasEloValue NOTIFY profileChanged)
    Q_PROPERTY(int followingCount READ followingCount NOTIFY profileChanged)
    Q_PROPERTY(int followerCount READ followerCount NOTIFY profileChanged)
    Q_PROPERTY(int ranking READ ranking NOTIFY profileChanged)
    Q_PROPERTY(int passedProblemCount READ passedProblemCount NOTIFY profileChanged)
    Q_PROPERTY(int submittedProblemCount READ submittedProblemCount NOTIFY profileChanged)

public:
    explicit UserProfileWrapper(QObject *parent = nullptr);

    void setProfile(const UserProfile &profile);

    int uid() const;
    QString name() const;
    QString avatar() const;
    QString slogan() const;
    QString introduction() const;
    QString badge() const;
    QDateTime registerTime() const;
    bool isAdmin() const;
    bool isBanned() const;
    int color() const;
    QString rawColor() const;
    int ccfLevel() const;
    int xcpcLevel() const;
    QString background() const;
    int eloValue() const;
    bool hasEloValue() const;
    int followingCount() const;
    int followerCount() const;
    int ranking() const;
    int passedProblemCount() const;
    int submittedProblemCount() const;

Q_SIGNALS:
    void profileChanged();

private:
    UserProfile m_profile;
};
