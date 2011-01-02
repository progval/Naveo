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


#include "historymanager.h"
#include "Browser.h"
#include <iostream>

HistoryManager::HistoryManager()
{

	QSettings set(Browser::instance()->iniFile("History.ini"), QSettings::IniFormat);
	urls = set.value("urls").toStringList();
	titles = set.value("titles").toStringList();
	dates = set.value("dates").toStringList();

	QWebSettings::setIconDatabasePath(qApp->applicationDirPath() + "/cache/");

	setWindowIcon(QIcon(":/history.png"));
	setWindowTitle(tr("Naveo - Historique"));

	view = new QTreeWidget;
	clearButton = new QPushButton(tr("Vider"));

	QPushButton *delButton = new QPushButton(tr("Supprimer"));

	QVBoxLayout *vLayout = new QVBoxLayout;
	QHBoxLayout *hLayout = new QHBoxLayout;

	vLayout->addWidget(view);

	hLayout->addStretch();
	hLayout->addWidget(delButton);
	hLayout->addWidget(clearButton);

	vLayout->addLayout(hLayout);

	setLayout(vLayout);

	connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
	connect(delButton, SIGNAL(clicked()), this, SLOT(remove()));
	connect(view, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemClicked(QTreeWidgetItem*)));

	QStringList list;
	list<<tr("Titre")<<tr("Url")<<tr("Date");
	view->setHeaderLabels(list);

	view->setColumnWidth(0, 150);
	view->setColumnWidth(1, 200);
	view->setColumnWidth(2, 150);
}

void HistoryManager::history(QStringList *url, QStringList *name)
{
	url->append(urls);
	name->append(titles);
}

void HistoryManager::itemClicked(QTreeWidgetItem *item)
{
	if(view->currentItem() != 0)
	{
		if(view->currentItem()->childCount() == 0 && !view->currentItem()->text(1).isEmpty())
		{
			emit load(item->text(1));
		}
	}
}

void HistoryManager::remove()
{
	if(view->currentItem() != 0)
	{
		if(view->currentItem()->childCount() == 0)
		{
			int index = dates.indexOf(view->currentItem()->text(2));
			urls.removeAt(index);
			titles.removeAt(index);
			dates.removeAt(index);
		}
	}
	if(!isHidden())
	{
		updateList();
	}
}

void HistoryManager::save()
{
	QSettings set(Browser::instance()->iniFile("History.ini"), QSettings::IniFormat);;
	set.setValue("urls", urls);
	set.setValue("titles", titles);
	set.setValue("dates", dates);
}

void HistoryManager::clear()
{
	urls.clear();
	titles.clear();
	dates.clear();
	if(!isHidden())
	{ updateList(); }
}

void HistoryManager::add(QString url, QString title)
{
	QSettings browserSettings(Browser::instance()->iniFile(), QSettings::IniFormat);
	if (browserSettings.value("saveHistory").toInt() == 0)
	{
		if (!url.isEmpty() && !title.isEmpty())
		{
			urls<<url;
			titles<<title;
			dates<<QDateTime::currentDateTime().toString("yyyy/MM/dd - hh:mm:ss");
		}
	}
	if(!isHidden())
	{ updateList(); }
}

void HistoryManager::updateList()
{
	view->clear();


	QTreeWidgetItem *today = new QTreeWidgetItem(view, QStringList(tr("Aujourd'hui")));
	QTreeWidgetItem *lastWeek = new QTreeWidgetItem(view, QStringList(tr("Cette semaine")));
	QTreeWidgetItem *older = new QTreeWidgetItem(view, QStringList(tr("Ancien")));

	today->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DirIcon));
	lastWeek->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DirIcon));
	older->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DirIcon));

	int i = 0;
	QString date = QDate::currentDate().toString("yyyy/MM/dd");
	foreach(QString title, titles)
	{
		QStringList list;
		list<<title<<urls.at(i)<<dates.at(i);
		QString day = dates.at(i).left(10);
		QTreeWidgetItem * item;
		if(day == date)
		{
			item = new QTreeWidgetItem(today, list);
		}
		else if (day.left(8) == date.left(8) && day.right(2).toInt() + 8 > date.right(2).toInt())
		{
			item = new QTreeWidgetItem(lastWeek, list);
		}
		else
		{
			item = new QTreeWidgetItem(older, list);
		}
		item->setIcon(0, QWebSettings::iconForUrl(urls.at(i)));
		i++;
	}
	view->sortItems(2, Qt::DescendingOrder);
}

void HistoryManager::show()
{
	updateList();
	QWidget::show();
	resize(600, 480);
}
