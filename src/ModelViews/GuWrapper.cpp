#include "GuWrapper.h"

GuWrapper::GuWrapper(QObject *parent)
    : QObject(parent)
{
}

void GuWrapper::setGu(const Gu &gu)
{
    m_gu = gu;
    Q_EMIT guChanged();
}

int GuWrapper::rating() const
{
    return m_gu.rating;
}

QDateTime GuWrapper::time() const
{
    return m_gu.time;
}

int GuWrapper::social() const
{
    return m_gu.social;
}

int GuWrapper::basic() const
{
    return m_gu.basic;
}

int GuWrapper::contest() const
{
    return m_gu.contest;
}

int GuWrapper::practice() const
{
    return m_gu.practice;
}

int GuWrapper::prize() const
{
    return m_gu.prize;
}
