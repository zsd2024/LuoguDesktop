#include "RoundedBlurWidget.h"

RoundedBlurWidget::RoundedBlurWidget(QWidget *parent, QColor backgroundColor, int radius, int blurRadius)
	: QWidget(parent), m_radius(radius), m_blurRadius(blurRadius), m_backgroundColor(backgroundColor)
{
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint);

	// 设置圆角蒙版，擦除外部
	QRegion maskRegion = QRegion(rect(), QRegion::Rectangle);
	maskRegion = QRegion(rect(), QRegion::Ellipse); // 先用椭圆，后面用圆角矩形
	QRegion roundMask(rect(), QRegion::Rectangle);
	roundMask = QRegion(rect(), QRegion::Rectangle);
	roundMask = QRegion(rect(), QRegion::Rectangle);
	roundMask = QRegion(rect(), QRegion::Rectangle);
	QPainterPath path;
	path.addRoundedRect(rect(), m_radius, m_radius);
	QRegion region = QRegion(path.toFillPolygon().toPolygon());
	setMask(region);

	applyBlurEffect();
}

void RoundedBlurWidget::applyBlurEffect()
{
	auto *blur = new QGraphicsBlurEffect(this);
	blur->setBlurRadius(m_blurRadius);
	setGraphicsEffect(blur);
}

void RoundedBlurWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	// 每次大小变化都要重设蒙版
	QPainterPath path;
	path.addRoundedRect(rect(), m_radius, m_radius);
	setMask(QRegion(path.toFillPolygon().toPolygon()));
}

void RoundedBlurWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	const qreal borderWidth = 1.2; // 更细的边框
	QRectF drawRect = QRectF(borderWidth / 2, borderWidth / 2,
							 width() - borderWidth, height() - borderWidth);

	// 半透明背景
	painter.setBrush(m_backgroundColor);
	painter.setPen(Qt::NoPen);
	painter.drawRoundedRect(drawRect, m_radius - borderWidth / 2, m_radius - borderWidth / 2);

	// 明确边框
	QPen pen(m_backgroundColor, borderWidth);
	pen.setCosmetic(true); // 保证边框宽度不随缩放变化
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);
	painter.drawRoundedRect(drawRect, m_radius - borderWidth / 2, m_radius - borderWidth / 2);
}