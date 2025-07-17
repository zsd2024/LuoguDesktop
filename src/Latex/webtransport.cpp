#include <QMutex>
#include <QMutexLocker>

#include "webtransport.h"

WebTransport::WebTransport(QObject *parent)
	: QObject(parent)
{
}

WebTransport::~WebTransport()
{
}

WebTransport* WebTransport::instance()
{
	static WebTransport* self = nullptr;
	static QMutex lock;
	if (!self)
	{
		QMutexLocker<QMutex> locker(&lock);
		if (!self)
		{
			self = new WebTransport;
		}
	}
	return self;
}

void WebTransport::getLatex(const QString& msg)
{
	emit receviedJsMsg(msg);
}
