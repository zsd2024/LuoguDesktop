#pragma once
#include <QWidget>
#include <QGraphicsBlurEffect>
#include <QPainter>
#include <QPainterPath>
#include <QBitmap>
#include <QRegion>

class RoundedBlurWidget : public QWidget
{
	Q_OBJECT
public:
	explicit RoundedBlurWidget(QWidget *parent = nullptr, QColor backgroundColor = QColor(255, 255, 255, 200), int radius = 20, int blurRadius = 20);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	int m_radius;
	int m_blurRadius;
	QColor m_backgroundColor;
	void applyBlurEffect();
	void resizeEvent(QResizeEvent *event) override;
};