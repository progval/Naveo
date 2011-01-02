#ifndef DIAL_H
#define DIAL_H

#include <QtGui>
#include <QtWebKit>
#include <iostream>
#include "webview.h"


using namespace std;

class Dial : public QGraphicsView
{
	Q_OBJECT

	public:
		Dial(QWidget *parent = 0);

	signals:

	public slots:
		void addPage();

	private slots:
		void loadingFinished(bool ok);

	private:
		QTransform setPosition(qreal x, qreal y, qreal z);


		QGraphicsScene *scene;
		QPushButton *add;
		QList<QLabel*> pages;
		QList<QGraphicsProxyWidget *> proxies;
};

#endif // DIAL_H
