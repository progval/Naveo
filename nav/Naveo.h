#include <QtCore>

#define VERSION "0.9"



void wait(int msec)
{
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
	timer.start(msec);
	loop.exec();
}
