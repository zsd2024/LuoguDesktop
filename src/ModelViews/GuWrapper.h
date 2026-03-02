#pragma once
#include "../Models/User.h"
#include <QDateTime>
#include <QObject>

class GuWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int rating READ rating NOTIFY guChanged)
    Q_PROPERTY(QDateTime time READ time NOTIFY guChanged)
    Q_PROPERTY(int social READ social NOTIFY guChanged)
    Q_PROPERTY(int basic READ basic NOTIFY guChanged)
    Q_PROPERTY(int contest READ contest NOTIFY guChanged)
    Q_PROPERTY(int practice READ practice NOTIFY guChanged)
    Q_PROPERTY(int prize READ prize NOTIFY guChanged)

public:
    explicit GuWrapper(QObject *parent = nullptr);

    void setGu(const Gu &gu);

    int rating() const;
    QDateTime time() const;
    int social() const;
    int basic() const;
    int contest() const;
    int practice() const;
    int prize() const;

Q_SIGNALS:
    void guChanged();

private:
    Gu m_gu;
};
