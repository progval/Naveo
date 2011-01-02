/*******************************
Copyright (C) 2009-2010 grégoire ANGERAND

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************/


#ifndef HTTPGET_H
#define HTTPGET_H

#include <QtNetwork>
#include <QtGui>
#include <iostream>

using namespace std;


class HttpGet : public QObject
{
	Q_OBJECT

public:
	HttpGet();

	bool getFile(QUrl file, QString toSave);
	QString name;
	int error();

public slots:
	void cancel();

private slots:
	void httpDone();
	void download();

signals:
	void done(bool error);
	void progress(qint64 prog, qint64 size);

private:
	QFile file;
	QNetworkAccessManager *manager;
	QNetworkReply *reply;
	bool canceled;
};

#endif // HTTPGET_H
