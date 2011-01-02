/*******************************
Copyright (C) 2009-2010 gr�goire ANGERAND

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

#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include "httpget.h"
#include "downloadWidget.h"


class Widget : public QWidget
{
	Q_OBJECT

	public:

		Widget(QWidget *parent = 0);
		~Widget();


	public slots:
		void done(bool error = false);
		void start();
		void downloadDone(bool error);
		void getList();
		void exit();

	private:
		bool setDownloaded;
		QList<HttpGet *> downloads;
		QLabel *label;
		QProgressBar *prog;
		QPushButton *reloadButton;
		QStringList files;
		QListWidget *list;
		QPushButton *dlButton;
		QPushButton *startButton;
		HttpGet *settingsGetter;
};

#endif // WIDGET_H
