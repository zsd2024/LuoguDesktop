#pragma once
#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsEffect>

class RoundedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoundedWidget(QWidget *parent = nullptr, QColor BackgroundColor = QColor(0, 0, 0, 128));

    void setBackgroundColor(const QColor &color);
    void setRadius(int radius);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor m_color;
    int m_radius;
};