#pragma once
#include "../Models/User.h"
#include <QDateTime>
#include <QObject>
#include <optional>

class EloRecordWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int rating READ rating NOTIFY eloRecordChanged)
    Q_PROPERTY(QDateTime time READ time NOTIFY eloRecordChanged)
    Q_PROPERTY(int contestId READ contestId NOTIFY eloRecordChanged)
    Q_PROPERTY(QDateTime contestStart READ contestStart NOTIFY eloRecordChanged)
    Q_PROPERTY(QDateTime contestEnd READ contestEnd NOTIFY eloRecordChanged)
    Q_PROPERTY(QString contestName READ contestName NOTIFY eloRecordChanged)
    Q_PROPERTY(int userCount READ userCount NOTIFY eloRecordChanged)
    Q_PROPERTY(int prevDiff READ prevDiff NOTIFY eloRecordChanged)
    Q_PROPERTY(bool hasPrevDiff READ hasPrevDiff NOTIFY eloRecordChanged)

public:
    explicit EloRecordWrapper(QObject *parent = nullptr);

    void setEloRecord(const EloRecord &record);

    int rating() const;
    QDateTime time() const;
    int contestId() const;
    QDateTime contestStart() const;
    QDateTime contestEnd() const;
    QString contestName() const;
    int userCount() const;
    int prevDiff() const;
    bool hasPrevDiff() const;

Q_SIGNALS:
    void eloRecordChanged();

private:
    EloRecord m_record;
};
