#pragma once

#include <QObject>

class WebTransport : public QObject
{
	Q_OBJECT

	WebTransport(QObject *parent = nullptr);
	~WebTransport();

public:
	// 获取实例
	static WebTransport *instance();
signals:
	// 将从js接收的数据发送出去
	void receviedJsMsg(const QString &msg);
public slots:
	// js调用此函数，接收js传入的数据
	void getLatex(const QString &msg);
};

#ifndef WEB_TRSPT
#define WEB_TRSPT WebTransport::instance()
#endif // !WEB_TRSPT
