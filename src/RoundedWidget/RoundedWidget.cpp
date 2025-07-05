#include "RoundedWidget.h"
#include <QPainter>
#include <QPainterPath>

RoundedWidget::RoundedWidget(QWidget *parent, QColor BackgroundColor)
    : QWidget(parent), m_color(BackgroundColor), m_radius(15) // 默认半透明黑色
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAutoFillBackground(false);
}

void RoundedWidget::setBackgroundColor(const QColor &color)
{
    m_color = color;
    update();
}

void RoundedWidget::setRadius(int radius)
{
    m_radius = radius;
    update();
}

void RoundedWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPainterPath path;
    path.addRoundedRect(rect(), m_radius, m_radius);

    painter.fillPath(path, m_color);
}