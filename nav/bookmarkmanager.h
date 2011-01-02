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


#ifndef BOOKMARKMANAGER_H
#define BOOKMARKMANAGER_H

#include <QtGui>
#include <QtNetWork>
#include <QtWebKit>
#include <iostream>
#include "bookmarktree.h"

using namespace std;

class BookMarkManager : public QWidget
{
	Q_OBJECT

	public:
		BookMarkManager(QWidget *parent = 0);
		QStringList nameList();
		QStringList urlList();
		QStringList dirList();
		QStringList menus();
		void add(QString newUrl, QString newName, QString newDir = QString("/"));
		void updateWidget();
		QIcon iconForUrl(QString url);
		void updateLists();
		void clear();

	signals:
		void update();

	public slots:
		void saveSettings();
		void exportToHTML();
		void importFromHTML();
		void move();
		void remove();
		void addNew();
		void addNewFolder();
		void moveItem(QTreeWidgetItem *item, QString newDir);
		void updateItemData(QTreeWidgetItem *item);

		void show();

	protected:
		void closeEvent(QCloseEvent *event);

	private:
		QString selectFolder(QString label);
		QSettings *settings;
		QTreeWidget *tree;
		QMenu *menu;
		QStringList name;
		QStringList url;
		QStringList dir;
		QStringList menuList;
		QStringList id;

};

#endif // BOOKMARKMANAGER_H
