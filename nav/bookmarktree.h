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

#ifndef BOOKMARKTREE_H
#define BOOKMARKTREE_H

#include <QtGui>
#include <iostream>

using namespace std;

struct Editor
{
	int column;
	QTreeWidgetItem *item;
};

class ItemDelegate;

class BookMarkTree : public QTreeWidget
{
	Q_OBJECT

	public:
		BookMarkTree(QMenu *menu);

	public slots:
		void closeEditor();

	protected:
		void mousePressEvent(QMouseEvent *event);
		//void keyPressEvent(QKeyEvent *event);

	private slots:
		void itemDoubleClicked(QTreeWidgetItem *item, int column);
		void dropEvent(QDropEvent *event);

	signals:
		void editingFinished(QTreeWidgetItem *item);
		void itemMoved(QTreeWidgetItem *item, QString dir);

	private:
		QMenu *contextMenu;
		QTreeWidgetItem *dragedItem;
		Editor *currentEditor;
};

class ItemDelegate : public QItemDelegate
{
	Q_OBJECT

	public:
		ItemDelegate(BookMarkTree *tree);
		QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
		bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

	private:
		BookMarkTree *tree;
};

#endif // BOOKMARKTREE_H
