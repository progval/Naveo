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


#include "helper.h"
#include "Browser.h"

Helper::Helper(QWidget *parent) :
	QWidget(parent)
{
	setWindowIcon(QIcon(":/icon.png"));
	setWindowTitle(tr("Aide - Naveo"));
	tree = new QTreeWidget;
	tree->header()->hide();
	tree->setFixedWidth(200);
	connect(tree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(itemActivated(QTreeWidgetItem*)));
	browser = new QTextBrowser;
	browser->setSearchPaths(QStringList(qApp->applicationDirPath() + "/help/" + QLocale::system().name().left(2) + "/"));
	QHBoxLayout *lay = new QHBoxLayout;
	lay->addWidget(tree);
	lay->addWidget(browser);
	lay->setStretchFactor(browser, 1);
	setLayout(lay);
	resize(800, 600);
	updateView();
}

void Helper::closeEvent(QCloseEvent */*event*/)
{
	emit closed();
}

void Helper::updateView()
{
	QSettings settings(qApp->applicationDirPath() + "/help/help_" + QLocale::system().name().left(2) +".ini", QSettings::IniFormat);
	QStringList name = settings.value("name").toStringList();
	QStringList url = settings.value("url").toStringList();
	QStringList dir = settings.value("dir").toStringList();
	QStringList menuList = settings.value("menu").toStringList();
	QStringList id;
	QString first = settings.value("first").toString();
	menuList.removeDuplicates();

	int a = 0;
	while(a != name.count())
	{
		id.append(tr("%1").arg(a));
		a++;
	}

	if (menuList.isEmpty())
	{
		menuList.append(dir);
	}
	tree->clear();
	int i = 0;
	QStringList folders;
	QList<QTreeWidgetItem *> items;
	QStringList menus;
	menus << dir << menuList;
	foreach(QString str , menus)
	{
		if (str != "/")
		{
			if (!folders.contains(str))
			{
				folders.append(str);
				QStringList subDirs = str.split("/");
				subDirs.removeFirst();
				foreach(QString directory, subDirs)
				{
					QString lastFolder;
					foreach(QString folder, subDirs)
					{
						if(subDirs.indexOf(folder) <= subDirs.indexOf(directory))
						{
							lastFolder.append("/" + folder);
						}
					}
					bool hasItem = false;
					foreach(QTreeWidgetItem *item, items)
					{
						if (item->text(0) == directory && item->toolTip(0) == lastFolder)
						{
							hasItem = true;
						}
					}
					if (!hasItem)
					{
						if (subDirs.indexOf(directory) == 0)
						{
							QTreeWidgetItem *item = new QTreeWidgetItem(tree, QStringList(directory));
							item->setIcon(0, QIcon(":/folder.png"));
							item->setToolTip(0, lastFolder);
							items.append(item);
						}
						else
						{
							QString list;
							foreach(QString folder, subDirs)
							{
									if(subDirs.indexOf(folder) < subDirs.indexOf(directory))
									{
										list.append("/" + folder);
									}
							}
							foreach(QTreeWidgetItem *item, items)
							{
								if (item->toolTip(0) == list)
								{
									QTreeWidgetItem *folderItem = new QTreeWidgetItem(item, QStringList(directory));
									folderItem->setIcon(0, QIcon(":/folder.png"));
									folderItem->setToolTip(0, lastFolder);
									items.append(folderItem);
								}
							}
						}
					}
				}
			}
		}
	}
		foreach(QString str, name)
	{
		if (dir.at(i) != "/")
		{
			foreach(QTreeWidgetItem *parent, items)
			{
				if (parent->toolTip(0) == dir.at(i))
				{
					QStringList labelsList;
					labelsList << str << url.at(i);
					QTreeWidgetItem * item = new QTreeWidgetItem(parent, labelsList);
					item->setToolTip(1, id.at(i));
					item->setIcon(0, QIcon(":/code.png"));
				}
			}
		}
		else
		{
			QStringList labelsList;
			labelsList << str << url.at(i);
			QTreeWidgetItem * item = new QTreeWidgetItem(/*tree, */labelsList);
			item->setToolTip(1, id.at(i));
			item->setIcon(0, QIcon(":/code.png"));
			tree->insertTopLevelItem(0, item);
			if(str == first)
			{
				itemActivated(item);
			}
		}
		i++;
	}
	//tree->expandAll();
}

void Helper::itemActivated(QTreeWidgetItem *item)
{
	QFile page(qApp->applicationDirPath() + "/help/" + item->text(1));
	if(page.open(QIODevice::ReadOnly))
	{
		browser->setHtml(page.readAll());
		page.close();
	}
	else
	{
		std::cout<<"Unable to read "<<qPrintable(item->text(1))<<std::endl<<"reason : "<<qPrintable(page.errorString())<<std::endl;
	}
}
