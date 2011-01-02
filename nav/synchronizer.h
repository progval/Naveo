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


#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include <QtGui>
#include <QtNetwork>
#include <iostream>
#include <qcryptographichash.h>
#include "version.h"

using namespace std;

class Synchronizer : public QObject
{
	Q_OBJECT

	public:
		Synchronizer();

		void exec();
		bool connected();
		QString user();
		void disconnect();
		void close();
		void import();
		void exportSettings();
		void setVisible();
		QByteArray crypt(QByteArray array);
		void cryptInFile(QByteArray array, QString fileName);
		QByteArray encryptFromFile(QString fileName);
		void quickWrite(QString fileName, QByteArray array);

		QStringList serverList();
		void setServer(int index);
		bool checkPass();

	signals:
		void loggedIn();
		void imported();
		void statusChanged(bool connected);

	private slots:
		void commandFinished(int, bool error);
		void addToList(const QUrlInfo &urlInfo);

	private:
		bool autoConnectionfailed;
		QByteArray hash(QByteArray array);
		QProgressDialog *progress;
		QFile *file;
		int dlDone;
		bool isConnected;
		bool ui;
		QFtp *ftp;
		QSettings *settings;
		QString pass;
		QString newName;
		QStringList dir;
		QStringList files;
		bool waitingPass;

		int serverIndex;

		QStringList host;
		QStringList log;
		QStringList passwords;
		QStringList names;

};

#endif // SYNCHRONIZER_H
