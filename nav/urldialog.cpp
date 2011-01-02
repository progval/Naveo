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

#include "urldialog.h"
#include "Browser.h"

UrlDialog::UrlDialog(QWidget *parent, bool showSavedUrl, QString text, bool nameEdit, QString name, bool selectDir, bool url) :
	QDialog(parent)
{
	returnUrl = url;

	line = new QLineEdit;
	edit = new QLineEdit;
	tree = new QTreeWidget;
	cancel = new QPushButton(tr("Annuler"));
	ok = new QPushButton(tr("OK"));
	treeWidget = new QTreeWidget;

	QVBoxLayout *mainLay = new QVBoxLayout;
	QHBoxLayout *lineLay = new QHBoxLayout;
	QHBoxLayout *editLay = new QHBoxLayout;
	QHBoxLayout *buttonLay = new QHBoxLayout;


	QStringList labels;
	labels<<tr("Nom")<<tr("Url");
	tree->setHeaderLabels(labels);
	tree->setColumnWidth(0, 200);
	treeWidget->header()->hide();

	line->setText(text);
	edit->setText(name);

	buttonLay->addStretch();
	buttonLay->addWidget(ok);
	buttonLay->addWidget(cancel);

	editLay->addWidget(new QLabel(tr("Nom : ")));
	editLay->addWidget(edit);

	lineLay->addWidget(new QLabel(tr("Url : ")));
	lineLay->addWidget(line);

	if(showSavedUrl)
		mainLay->addWidget(tree);
	if(selectDir)
	{
		if(url)
			mainLay->addWidget(new QLabel(tr("Ou voulez vous placer le nouveau favoris ?")));
		else
			mainLay->addWidget(new QLabel(tr("Ou voulez vous placer le nouveau dossier ?")));
		mainLay->addWidget(treeWidget);
	}
	if(nameEdit)
		mainLay->addLayout(editLay);
	if(url)
		mainLay->addLayout(lineLay);
	mainLay->addLayout(buttonLay);

	setLayout(mainLay);

	connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
	connect(tree, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(setData(QTreeWidgetItem*)));
	connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

	QWebSettings::setIconDatabasePath(qApp->applicationDirPath() + "/cache/");

	addHistory();
	addBookMarks();
	fillDirTree();

	/*tree->resize(400, 200);
	treeWidget->resize(400, 200);*/
	resize(450, 350);
}

QString UrlDialog::selectedDir()
{
	return treeWidget->currentItem()->toolTip(0);
}

void UrlDialog::fillDirTree()
{
	QStringList folders;
	QList<QTreeWidgetItem *> items;
	QStringList menus;
	menus << Browser::instance()->bmManager()->dirList() << Browser::instance()->bmManager()->menus();
	QTreeWidgetItem *Origin = new QTreeWidgetItem(treeWidget, QStringList("/"));
	Origin->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DirIcon));
	Origin->setToolTip(0, "/");
	foreach(QString str , menus)
	{
		//cout<<"<";
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
							QTreeWidgetItem *item = new QTreeWidgetItem(Origin, QStringList(directory));
							item->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DirIcon));
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
									folderItem->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DirIcon));
									folderItem->setToolTip(0, lastFolder);
									items.append(folderItem);
								}
							}
						}
					}
				}
			}
		}
		//cout<<">"<<endl;
	}
	treeWidget->setCurrentItem(Origin);
	treeWidget->expandAll();
}

QString UrlDialog::url()
{
	return line->text();
}

QString UrlDialog::name()
{
	return edit->text();
}

void UrlDialog::addHistory()
{
	QTreeWidgetItem *historyItem = new QTreeWidgetItem(tree);
	historyItem->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_DirIcon));
	historyItem->setText(0, tr("Historique"));

	QTreeWidgetItem *oftenItem = new QTreeWidgetItem(tree);
	oftenItem->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_DirIcon));
	oftenItem->setText(0, tr("Pages les plus visitées"));


	QStringList *urls = new QStringList;
	QStringList *names = new QStringList;
	Browser::instance()->hManager()->history(urls, names);

	QStringList u;
	QStringList often;

	for(int i = 0; i != urls->count(); i++)
	{
		if(!u.contains(urls->at(i)))
		{
			QStringList l;
			l<<names->at(i)<<urls->at(i);
			QTreeWidgetItem *item = new QTreeWidgetItem(l);
			item->setIcon(0, QWebSettings::iconForUrl(urls->at(i)));
			historyItem->addChild(item);
			u.append(urls->at(i));
		}
	}

	for(int i = 0; i != urls->count(); i++)
	{
		if(!often.contains(urls->at(i)))
		{
			QStringList lst(*urls);
			int total = lst.removeAll(urls->at(i));
			if(total > 30 || (total > 5 && total > urls->count() / 10))
			{
				QStringList l;
				l<<names->at(i)<<urls->at(i);
				QTreeWidgetItem *item = new QTreeWidgetItem(l);
				item->setIcon(0, QWebSettings::iconForUrl(urls->at(i)));
				oftenItem->addChild(item);
			}
			often.append(urls->at(i));
		}
	}

	oftenItem->setExpanded(true);
}

void UrlDialog::addBookMarks()
{
	QStringList urls = Browser::instance()->bmManager()->urlList();
	QStringList names = Browser::instance()->bmManager()->nameList();

	QTreeWidgetItem *bmItem = new QTreeWidgetItem(tree);
	bmItem->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_DirIcon));
	bmItem->setText(0, tr("Favoris"));

	for(int i = 0; i != urls.count(); i++)
	{
		QStringList l;
		l<<names.at(i)<<urls.at(i);
		QTreeWidgetItem *item = new QTreeWidgetItem(l);
		item->setIcon(0, QWebSettings::iconForUrl(urls.at(i)));
		bmItem->addChild(item);
	}
}

void UrlDialog::setData(QTreeWidgetItem *item)
{
	if(item)
	{
		edit->setText(item->text(0));
		line->setText(item->text(1));
	}
}


QString UrlDialog::exec()
{
	if(!QDialog::exec())
		return QString();

	if(returnUrl)
		return line->text();

	return edit->text();
}
