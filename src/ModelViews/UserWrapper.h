#pragma once
#include "../Models/User.h"
#include "DailyCountWrapper.h"
#include "EloRecordWrapper.h"
#include "GuWrapper.h"
#include "UserPrizeWrapper.h"
#include "UserProfileWrapper.h"
#include <QDate>
#include <QObject>
#include <QQmlListProperty>
#include <QVector>

class UserWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(UserProfileWrapper *profile READ profile NOTIFY userChanged)
    Q_PROPERTY(GuWrapper *gu READ gu NOTIFY userChanged)
    Q_PROPERTY(QList<QObject *> prizes READ prizes NOTIFY userChanged)
    Q_PROPERTY(QList<QObject *> eloHistory READ eloHistory NOTIFY userChanged)
    Q_PROPERTY(QList<QDate> dailyCountDates READ dailyCountDates NOTIFY userChanged)

public:
    explicit UserWrapper(QObject *parent = nullptr);
    ~UserWrapper();

    void setUser(const User &user);

    UserProfileWrapper *profile() const;
    GuWrapper *gu() const;
    QList<QObject *> prizes() const;
    QList<QObject *> eloHistory() const;
    QList<QDate> dailyCountDates() const;
    Q_INVOKABLE DailyCountWrapper *dailyCount(const QDate &date) const;
    Q_INVOKABLE QObject *prizeAt(int index) const;
    Q_INVOKABLE QObject *eloAt(int index) const;

    bool isEmpty() const;

Q_SIGNALS:
    void userChanged();

private:
    void clearWrappers();

    UserProfileWrapper *m_profileWrapper;
    GuWrapper *m_guWrapper;
    QList<QObject *> m_prizes;
    QList<QObject *> m_eloHistory;
    QMap<QDate, DailyCountWrapper *> m_dailyCounts;
    bool m_isEmpty;
};
