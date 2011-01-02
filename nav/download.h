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


#ifndef DL_H
#define DL_H
#include "httpget.h"
#include "webPage.h"
#include "downloadWidget.h"
#include <QtGui>
#include <QtNetwork>
#include <iostream>

using namespace std;

class downloadManager : public QWidget
{
	Q_OBJECT

	public:
		downloadManager();
		void setClosable(bool closable);
		bool downloading();

	public slots:
		bool downloadFile(QUrl url, QString file = QString());
		void clearDownloads();

	private slots:
		void downloadDone(bool error);
		void retryDownload();
		void downloadFile();

	protected:
		void closeEvent(QCloseEvent *event);

	signals:
		void closed();

	private:
		void wait(int msec);
		bool canClose;
		int downloads;
		int currentDownload;
		int oldDownloads;
		QList<HttpGet *> getterList;
		QStringList nameList;
		QStringList urlList;
		QStringList stateList;
		QStringList localList;
		QListWidget *listWidget;
		QLabel *label;
		QString themeDir;
		QLineEdit *line;
		QList<DownloadWidget *> dlWidgets;

};

#endif
