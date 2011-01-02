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


#ifndef DLW_H
#define DLW_H


#include <QProgressBar>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QCleanLooksStyle>
#include <QSettings>
#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <math.h>
#include "httpget.h"

using namespace std;

class DownloadWidget : public QWidget
{
	Q_OBJECT

	public:
		DownloadWidget(QString Url, QString Local, QString State, QString Name);
		QString fileUrl();

	public slots:
		void update(qint64 prog, qint64 size);
		void open();
		void done(bool error);
		void updateTime();

	signals:
		void canceled();
		void retry();

	protected:
		void contextMenuEvent(QContextMenuEvent *event);

	private:
		QTime time;
		QTimer *timer;
		QProgressBar *progress;
		QLabel *nameLabel;
		QLabel *timeLabel;
		int sec;
		QString local;
		double total;
		double writed;
		QString name;
		QString url;
		bool waiting;
		QHBoxLayout *layout;
};

#endif
