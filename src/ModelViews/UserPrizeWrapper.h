#pragma once
#include "../Models/User.h"
#include <QDateTime>
#include <QObject>
#include <optional>

class UserPrizeWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int year READ year NOTIFY prizeChanged)
    Q_PROPERTY(QString contest READ contest NOTIFY prizeChanged)
    Q_PROPERTY(QString event READ event NOTIFY prizeChanged)
    Q_PROPERTY(bool hasEvent READ hasEvent NOTIFY prizeChanged)
    Q_PROPERTY(QString prize READ prize NOTIFY prizeChanged)
    Q_PROPERTY(int score READ score NOTIFY prizeChanged)
    Q_PROPERTY(int rank READ rank NOTIFY prizeChanged)

public:
    explicit UserPrizeWrapper(QObject *parent = nullptr);

    void setPrize(const UserPrize &prize);

    int year() const;
    QString contest() const;
    QString event() const;
    bool hasEvent() const;
    QString prize() const;
    int score() const;
    int rank() const;

Q_SIGNALS:
    void prizeChanged();

private:
    UserPrize m_prize;
};
