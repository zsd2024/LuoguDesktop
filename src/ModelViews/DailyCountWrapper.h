#pragma once
#include "../Models/User.h"
#include <QObject>

class DailyCountWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY dailyCountChanged)
    Q_PROPERTY(int maxDifficulty READ maxDifficulty NOTIFY dailyCountChanged)

public:
    explicit DailyCountWrapper(QObject *parent = nullptr);

    void setDailyCount(const DailyCount &count);

    int count() const;
    int maxDifficulty() const;

Q_SIGNALS:
    void dailyCountChanged();

private:
    DailyCount m_count;
};
