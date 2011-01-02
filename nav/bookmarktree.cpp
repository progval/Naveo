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


#include "bookmarktree.h"
#include "Browser.h"

ItemDelegate::ItemDelegate(BookMarkTree *tree)
{
	this->tree = tree;
}

bool ItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	return QItemDelegate::editorEvent(event, model, option, index);
}

QWidget *ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QLineEdit *edit = static_cast<QLineEdit *>(QItemDelegate::createEditor(parent, option, index));
	if(edit)
	{
		connect(edit, SIGNAL(returnPressed()), tree, SLOT(closeEditor()));
		return static_cast<QWidget *>(edit);
	}
	return QItemDelegate::createEditor(parent, option, index);
}

BookMarkTree::BookMarkTree(QMenu *menu)
{
	contextMenu = menu;
	currentEditor = 0;

	setItemDelegate(new ItemDelegate(this));

	setDragDropMode(QAbstractItemView::InternalMove);
	setDragEnabled(true);
	setDragDropOverwriteMode(false);

	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));
}

void BookMarkTree::closeEditor()
{
	if(currentEditor)
	{
		closePersistentEditor(currentEditor->item, currentEditor->column);
		emit editingFinished(currentEditor->item);
		currentEditor = 0;
	}
}

void BookMarkTree::dropEvent(QDropEvent *event)
{
	QTreeWidget::dropEvent(event);
	if(dragedItem != 0)
	{
		QString dir = "/";
		if(dragedItem->parent() != 0 && dragedItem->parent()->type() != QTreeWidgetItem::UserType)
		{
			dir = dragedItem->parent()->toolTip(0);
		}
		while(dragedItem->parent() != 0 && dragedItem->parent()->type() == QTreeWidgetItem::UserType)
		{
			if(dragedItem->parent()->parent())
			{
				QTreeWidgetItem *parent = dragedItem->parent()->parent();
				dragedItem->parent()->removeChild(dragedItem);
				parent->addChild(dragedItem);
				dir = parent->toolTip(0);
			}
			else
			{
				dragedItem->parent()->removeChild(dragedItem);
				addTopLevelItem(dragedItem);
			}
		}
		emit itemMoved(dragedItem, dir);
	}
}

void BookMarkTree::mousePressEvent(QMouseEvent *event)
{
	dragedItem = itemAt(event->pos());
	QTreeWidget::mousePressEvent(event);
	if(event->button() == Qt::RightButton && itemAt(event->pos()) != 0)
	{
		contextMenu->exec(mapToGlobal(QPoint(event->pos().x(), event->pos().y() + header()->height())));
	}
}

void BookMarkTree::itemDoubleClicked(QTreeWidgetItem *item, int column)
{
	if(currentEditor != 0)
	{
		closePersistentEditor(currentEditor->item, currentEditor->column);
		emit editingFinished(currentEditor->item);
	}
	currentEditor = new Editor;
	currentEditor->item = item;
	currentEditor->column = column;
	openPersistentEditor(currentEditor->item, currentEditor->column);
}
