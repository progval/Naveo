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


#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QtGui>
#include <iostream>
#include <QtWebKit>

using namespace std;

class HistoryManager : public QWidget
{
	Q_OBJECT

	public:
		HistoryManager();
		void save();
		void add(QString url, QString title);
		void updateList();
		void history(QStringList *url, QStringList *name);

	public slots:
		void clear();
		void itemClicked(QTreeWidgetItem *item);
		void show();
		void remove();

	signals:
		void load(QString url);

	private:
		QStringList urls;
		QStringList titles;
		QStringList dates;

		QTreeWidget *view;
		QPushButton *clearButton;
};

#endif // HISTORYMANAGER_H
