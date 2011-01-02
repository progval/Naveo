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


#include "bookmarkmanager.h"
#include "Browser.h"
#include "urldialog.h"

BookMarkManager::BookMarkManager(QWidget *parent) :
	QWidget(parent)
{
	setWindowTitle(tr("Naveo - Favoris"));
	setWindowIcon(QIcon(":/bookmark.png"));

	settings = new QSettings(Browser::instance()->iniFile("BookMarks.ini"), QSettings::IniFormat);
	name = settings->value("name").toStringList();
	url = settings->value("url").toStringList();
	dir = settings->value("dir").toStringList();
	menuList = settings->value("menu").toStringList();

	menuList.removeDuplicates();

	int i = 0;
	while(i != name.count())
	{
		id.append(tr("%1").arg(i));
		i++;
	}

	if (menuList.isEmpty())
	{
		menuList.append(dir);
	}

	QAction *removeButton = new QAction(tr("Supprimer"), this);
	QAction *addNewButton = new QAction(tr("Nouveau"), this);
	QAction *addNewFolderButton = new QAction(tr("Nouveau dossier"), this);
	QAction *moveButton = new QAction(tr("Déplacer"), this);
	QAction *exportButton = new QAction(tr("Exporter"), this);
	QAction *importButton = new QAction(tr("Importer"), this);

	connect(moveButton, SIGNAL(triggered()), this, SLOT(move()));
	connect(removeButton, SIGNAL(triggered()), this, SLOT(remove()));
	connect(addNewButton, SIGNAL(triggered()), this, SLOT(addNew()));
	connect(addNewFolderButton, SIGNAL(triggered()), this, SLOT(addNewFolder()));
	connect(exportButton, SIGNAL(triggered()), this, SLOT(exportToHTML()));
	connect(importButton, SIGNAL(triggered()), this, SLOT(importFromHTML()));

	QPushButton *button = new QPushButton(tr("Menu  "));

	menu = new QMenu(tr("Menu"));
	menu->addAction(removeButton);
	menu->addAction(moveButton);
	menu->addAction(addNewButton);
	menu->addAction(addNewFolderButton);
	menu->addSeparator();
	menu->addAction(exportButton);
	menu->addAction(importButton);

	button->setMenu(menu);

	QMenu *contextMenu = new QMenu(tr("Menu"));
	contextMenu->addAction(removeButton);
	contextMenu->addAction(moveButton);

	tree = new BookMarkTree(contextMenu);

	connect(tree, SIGNAL(editingFinished(QTreeWidgetItem *)), this, SLOT(updateItemData(QTreeWidgetItem*)));
	connect(tree, SIGNAL(itemMoved(QTreeWidgetItem *, QString)), this, SLOT(moveItem(QTreeWidgetItem*,QString)));

	QStringList headerLabels;
	headerLabels << tr("Nom") << tr("Url");
	tree->setHeaderLabels(headerLabels);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(tree);
	QHBoxLayout *buttonLayout = new QHBoxLayout;

	buttonLayout->addStretch();
	buttonLayout->addWidget(button);

	layout->addLayout(buttonLayout);
	setLayout(layout);

	resize(QSize(500, 400));

	tree->setColumnWidth(0, 250);
}

void BookMarkManager::exportToHTML()
{
	QFile file(QFileDialog::getSaveFileName(this, tr("Exporter"), QDesktopServices::displayName(QDesktopServices::DesktopLocation) + "/bookmarks.html", "HTML (*.html *.htm *.xhtml)"));
	if(file.fileName().isEmpty())
	{
		return;
	}
	if(file.open(QIODevice::WriteOnly))
	{
		file.write(QString("<!DOCTYPE NETSCAPE-Bookmark-file-1>\n<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=UTF-8\">\n<TITLE>Bookmarks</TITLE>\n<H1>Bookmarks menu</H1>\n\n<DL><p>\n").toAscii());
		int i = 0;
		foreach(QString string, dir)
		{
			if(string == "/")
			{
				QString str = url.at(i);
				if(str.left(7) != "http://")
				{
					str = "http://" + str;
				}
				if(str.right(1) != "/")
				{
					str += "/";
				}
				file.write(QString("\t<DT><A HREF=\"" + str + "\" ADD_DATE=\"0\" LAST_MODIFIED=\"0\">" + name.at(i) + "</A>\n").toAscii());
			}
			i++;
		}
		QStringList done;
		foreach(QString menu, menuList)
		{
			int j = 0;
			QStringList dirs = menu.split("/", QString::SkipEmptyParts);
			QString current = "/";
			foreach(QString s, dirs)
			{
				if(!done.contains(current + s + "/"))
				{
					cout<<"s = "<<qPrintable(s)<<endl<<"current = "<<qPrintable(current)<<endl;
					file.write(QString("\t<DT><H3 ADD_DATE=\"0\" LAST_MODIFIED=\"0\">" + s + "</H3>\n\t\t<DL><p>\n").toAscii());
					int k = 0;
					foreach(QString string, dir)
					{
						if(string == current + s)
						{
							QString str = url.at(k);
							if(str.left(7) != "http://")
							{
								str = "http://" + str;
							}
							if(str.right(1) != "/")
							{
								str += "/";
							}
							file.write(QString("\t\t\t<DT><A HREF=\"" + str + "\" ADD_DATE=\"0\" LAST_MODIFIED=\"0\">" + name.at(k) + "</A>\n").toAscii());
						}
						k++;
					}
					j++;
				}
				done<<current;
				current += s + "/";
			}
			for(; j != 0; j--)
			{
				file.write("\t\t</DL><p>\n");
			}
		}
		file.write("</DL><p>");
		file.close();
	}
	else
	{
		QMessageBox::critical(this, tr("Oppération impossible"), tr("Impossible d'exporter les favoris !"));
	}
}

void BookMarkManager::importFromHTML()
{
	QFile file(QFileDialog::getOpenFileName(this, tr("Importer"), QDesktopServices::displayName(QDesktopServices::DesktopLocation), "HTML (*.html *.htm *.xhtml)"));
	if(file.fileName().isEmpty())
	{
		return;
	}
	if(file.open(QIODevice::ReadOnly))
	{
		QString line;
		while(line.left(7) != "<DL><p>" && !file.atEnd())
		{
			line = QString(file.readLine());
		}
		if(file.atEnd())
		{
			return;
		}
		/*name.clear();
		url.clear();
		dir.clear();
		menuList.clear();
		id.clear();
		menuList<<"/";*/
		QString current;
		int i = id.last().toInt();
		while(!file.atEnd())
		{
			line = QString(file.readLine());
			line.replace("\t", "");
			line.replace(" ", "");
			if(line.left(6) == "<DT><A") // item
			{
				QString n;
				QString u;
				bool a = false;
				while(true)
				{
					if(line.at(0) == '\"' && !a)
					{
						a = true;
					}
					else if(line.at(0) == '\"')
					{
						break;
					}
					else if(a)
					{
						u += line.at(0);
					}
					line = line.right(line.size() - 1);
				}
				a = false;
				while(true)
				{
					if(line.at(0) == '>' && !a)
					{
						a = true;
					}
					else if(line.at(0) == '<')
					{
						break;
					}
					else if(a)
					{
						n += line.at(0);
					}
					line = line.right(line.size() - 1);
				}
				if (current.isEmpty())
				{
					dir<<"/";
				}
				else
				{
					dir<<current;
				}
				name<<n;
				url<<u;
				id<<QString("%1").arg(i);
				i++;
			} // item end
			if(line.left(7) == "<DT><H3") // folder
			{
				line = line.right(line.size() - 7);
				bool a = false;
				current += "/";
				while(true)
				{
					if(line.at(0) == '>' && !a)
					{
						a = true;
					}
					else if(line.at(0) == '<')
					{
						break;
					}
					else if(a)
					{
						current += line.at(0);
					}
					line = line.right(line.size() - 1);
				}
				file.readLine();
				menuList<<current;
			} // folder end
			if(line.left(8) == "</DL><p>")
			{
				QStringList list = current.split("/");
				list.removeLast();
				current = list.join("/");
			}
		}
		cout<<name.count()<<" bookmarks imported"<<endl;
	}
	else
	{
		QMessageBox::critical(this, tr("Oppération impossible"), tr("Impossible d'Importer les favoris !"));
	}
	menuList.removeDuplicates();
	saveSettings();
	updateWidget();
	emit update();
}

void BookMarkManager::updateItemData(QTreeWidgetItem *item)
{
	int index = id.indexOf(item->toolTip(1));
	name.replace(index, item->text(0));
	url.replace(index, item->text(1));
	saveSettings();
	updateWidget();
	emit update();
}

void BookMarkManager::updateLists()
{
	settings = new QSettings(Browser::instance()->iniFile("BookMarks.ini"), QSettings::IniFormat);
	name = settings->value("name").toStringList();
	url = settings->value("url").toStringList();
	dir = settings->value("dir").toStringList();
	menuList = settings->value("menu").toStringList();

	menuList.removeDuplicates();

	int i = 0;
	while(i != name.count())
	{
		id.append(tr("%1").arg(i));
		i++;
	}

	if (menuList.isEmpty())
	{
		menuList.append(dir);
	}

	emit update();
}

void BookMarkManager::remove()
{
	if (tree->currentItem() == 0)
	{
		return;
	}
	int a = QMessageBox::question(this, tr("êtes vous sur ?"), tr("êtes vous sur de vouloir suprimmer <strong>%1</strong> ?").arg(tree->currentItem()->text(0)), QMessageBox::No | QMessageBox::Yes);
	if (a == QMessageBox::No)
	{
		return;
	}
	if (tree->currentItem()->text(1).isEmpty())
	{
		QString text = tree->currentItem()->toolTip(0);
		int i = 0;
		QStringList directories = dir;
		QStringList urls = url;
		QStringList names = name;
		dir.clear();
		name.clear();
		url.clear();
		foreach(QString str, directories)
		{
			if(str.left(text.size()) != text)
			{
				dir.append(str);
				name.append(names.at(i));
				url.append(urls.at(i));
			}
			i++;
		}
		QStringList list;
		list << dir << menuList;
		menuList.clear();
		foreach(QString str, list)
		{
			if(str.left(text.size()) != text)
			{
				menuList.append(str);
			}
		}
	}
	else
	{
		QString bookMarkId = tree->currentItem()->toolTip(1);
		int index = id.indexOf(bookMarkId);
		name.removeAt(index);
		url.removeAt(index);
		dir.removeAt(index);
		id.removeAt(index);
	}
	saveSettings();
	updateWidget();
	emit update();
}

void BookMarkManager::move()
{
	if (tree->currentItem() == 0)
	{
		return;
	}
	if (!tree->currentItem()->text(1).isEmpty())
	{
		QString newDir = selectFolder(tr("Où voulez vous placer le favoris ?"));
		if (!newDir.isEmpty())
		{
			QString bookMarkId = tree->currentItem()->toolTip(1);
			int index = id.indexOf(bookMarkId);
			QStringList dirList;
			dirList << dir;
			dir.clear();
			int i = 0;
			foreach(QString str, dirList)
			{
				if (i != index)
				{
					dir.append(str);
				}
				else
				{
					dir.append(newDir.replace("racine", "/"));
				}
				i++;
			}
		}
	}
	else
	{
		QString newDir = selectFolder(tr("Où voulez vous placer le dossier ?"));
		if (!newDir.isEmpty())
		{
			//QMessageBox::critical(this, tr("Erreur"), tr("Vous devez selectionner un dossier !"));
			QStringList dirList;
			dirList << dir;
			dir.clear();
			foreach(QString str, dirList)
			{
				if (str.left(tree->currentItem()->toolTip(0).size()) != tree->currentItem()->toolTip(0))
				{
					dir.append(str);
				}
				else
				{
					str.replace(tree->currentItem()->toolTip(0), newDir.replace("racine", "") + "/" + tree->currentItem()->text(0));
					dir.append(str);
				}
			}
			QStringList menus;
			menus << dir << menuList;
			menuList.clear();
			foreach(QString str, menus)
			{
				if (str.left(tree->currentItem()->toolTip(0).size()) != tree->currentItem()->toolTip(0))
				{
					menuList.append(str);
				}
				else
				{
					str.replace(tree->currentItem()->toolTip(0), newDir.replace("racine", "") + "/" + tree->currentItem()->text(0));
					menuList.append(str);
				}
			}
		}
	}
	saveSettings();
	updateWidget();
	emit update();
}

void BookMarkManager::addNew()
{
	UrlDialog *dial = new UrlDialog(this, false, "http://", true, QString(), true);
	dial->setWindowTitle(tr("Nouveau"));
	QString newUrl = dial->exec();
	QString newName = dial->name();
	QString newDir = dial->selectedDir();
	delete dial;
	if (!newUrl.isEmpty() && !newName.isEmpty())
	{
			dir.append(newDir);
			name.append(newName);
			url.append(newUrl);
			id.append(tr("%1").arg(name.count()));
			saveSettings();
			updateWidget();
	}
}

QStringList BookMarkManager::menus()
{
	return menuList;
}

QString BookMarkManager::selectFolder(QString label)
{
	QDialog *wid = new QDialog(this);
	QTreeWidget *treeWidget = new QTreeWidget;
	treeWidget->header()->hide();
	wid->setWindowTitle(tr("Choisissez un dossier"));
	QVBoxLayout *layout = new QVBoxLayout;
	QLabel *lab = new QLabel(label);
	layout->addWidget(lab);
	layout->addWidget(treeWidget);


	QPushButton *ok = new QPushButton("Ok");
	QPushButton *cancel = new QPushButton(tr("Annuler"));
	connect(ok, SIGNAL(clicked()), wid, SLOT(accept()));
	connect(cancel, SIGNAL(clicked()), wid, SLOT(reject()));

	QHBoxLayout *lay = new QHBoxLayout;
	lay->addStretch();
	lay->addWidget(ok);
	lay->addWidget(cancel);

	layout->addLayout(lay);


	wid->setLayout(layout);

	QStringList folders;
	QList<QTreeWidgetItem *> items;
	QStringList menus;
	menus << dir << menuList;
	QTreeWidgetItem *Origin = new QTreeWidgetItem(treeWidget, QStringList("/"));
	Origin->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DirIcon));
	Origin->setToolTip(0, "/");
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
	}
	treeWidget->expandAll();
	if (wid->exec() == 0)
	{
		return "";
	}
	else if (treeWidget->currentItem() == 0)
	{
		QMessageBox::critical(this, tr("Erreur"), tr("Vous devez selectionner un dossier !"));
		return selectFolder(label);
	}
	if (treeWidget->currentItem()->toolTip(0) == "/")
	{
		return "racine";
	}
	return treeWidget->currentItem()->toolTip(0).right(treeWidget->currentItem()->toolTip(0).size());
}

void BookMarkManager::addNewFolder()
{
	UrlDialog *dial = new UrlDialog(this, false, QString(), true, QString(), true, false);
	dial->setWindowTitle(tr("Nouveau"));
	dial->exec();
	QString newName = dial->name();
	QString newDir = dial->selectedDir();
	delete dial;
	if(!newName.isEmpty() && !newDir.isEmpty())
	{
		newName = newDir + "/" + newName;
		newName.replace("//", "/");
		menuList.append(newName);
		saveSettings();
		updateWidget();
	}
}

void BookMarkManager::updateWidget()
{
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
					QTreeWidgetItem * item = new QTreeWidgetItem(parent, labelsList, QTreeWidgetItem::UserType);
					item->setToolTip(1, id.at(i));
					item->setIcon(0, iconForUrl(url.at(i)));
				}
			}
		}
		else
		{
			QStringList labelsList;
			labelsList << str << url.at(i);
			QTreeWidgetItem * item = new QTreeWidgetItem(tree, labelsList, QTreeWidgetItem::UserType);
			item->setToolTip(1, id.at(i));
			item->setIcon(0, iconForUrl(url.at(i)));
		}
		i++;
	}
	tree->expandAll();
	emit update();
}

void BookMarkManager::moveItem(QTreeWidgetItem *item, QString newDir)
{
	if(item->type() == QTreeWidgetItem::UserType)
	{
		int index = id.indexOf(item->toolTip(1));
		dir.replace(index, newDir);
	}
	else
	{
		int index = menuList.indexOf(item->toolTip(0));
		menuList.replace(index, newDir + "/" + item->text(0));
		QStringList dirs;
		dirs<<dir;
		dir.clear();
		foreach(QString str, dirs)
		{
			if(str == item->toolTip(0))
			{
				dir<<newDir + "/" + item->text(0);
			}
			else
			{
				dir<<str;
			}
		}
	}
	saveSettings();
	updateWidget();
	emit update();
}

void BookMarkManager::show()
{
	updateWidget();
	QWidget::show();
}

void BookMarkManager::clear()
{
	name.clear();
	url.clear();
	dir.clear();
	menuList.clear();
}

QIcon BookMarkManager::iconForUrl(QString url)
{
	QWebSettings::setIconDatabasePath(qApp->applicationDirPath() + "/cache/");
	if (!QWebSettings::iconForUrl(QUrl(url)).isNull())
	{
		return QWebSettings::iconForUrl(QUrl(url));
	}
	return QIcon(":/default.png");

}

void BookMarkManager::add(QString newUrl, QString newName, QString newDir)
{
	url.append(newUrl);
	name.append(newName);
	dir.append(newDir);
	id.append(tr("%1").arg(name.count()));
	saveSettings();
	emit update();
	updateWidget();
}

QStringList BookMarkManager::nameList()
{
	return name;
}

QStringList BookMarkManager::urlList()
{
	return url;
}

QStringList BookMarkManager::dirList()
{
	return dir;
}

void BookMarkManager::saveSettings()
{
	settings->setValue("name", name);
	settings->setValue("url", url);
	settings->setValue("dir", dir);
	settings->setValue("menu", menuList);
	menuList.removeDuplicates();
}

void BookMarkManager::closeEvent(QCloseEvent *)
{
	saveSettings();
	emit update();
}
