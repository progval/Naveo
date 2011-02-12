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

#include "plugindialog.h"
#include "Browser.h"

PluginDialog::PluginDialog()
{
	#ifdef Q_WS_WIN
		os = "windows";
	#endif
	#ifdef Q_WS_X11
		os = "X11";
	#endif

	setWindowIcon(QIcon(":/plug.png"));

	listWidget = new QTreeWidget(this);
	listWidget->setIconSize(QSize(24, 24));
	listWidget->header()->hide();

	info = new QPushButton(tr("plus d'info"));
	installButton = new QPushButton(tr("Installer"));
	line = new QLineEdit;

	line->setPlaceholderText(tr("Rechercher"));

	connect(info, SIGNAL(clicked()), this, SLOT(getInfo()));
	connect(installButton, SIGNAL(clicked()), this, SLOT(installPlugin()));
	connect(listWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(indexChanged()));
	connect(line, SIGNAL(textChanged(QString)), this, SLOT(search()));

	QVBoxLayout *lay = new QVBoxLayout;
	QHBoxLayout *hLay = new QHBoxLayout;
	lay->addWidget(listWidget);
	hLay->addStretch();
	hLay->addWidget(info);
	hLay->addWidget(line);
	hLay->addWidget(installButton);
	lay->addLayout(hLay);

	hLay->setStretchFactor(line, 100);

	setLayout(lay);

	QSettings set(naveoConfigurationPath + "/pluginsList.ini", QSettings::IniFormat);
	set.beginGroup(os);
	QStringList items = set.value("list").toStringList();
	set.endGroup();
	fillTree(items);

	indexChanged();
	resize(500, 400);
}

void PluginDialog::installPlugin()
{
	QSettings set(naveoConfigurationPath + "/pluginsList.ini", QSettings::IniFormat);
	set.beginGroup(listWidget->currentItem()->text(0));
	emit install(listWidget->currentItem()->text(0), set.value("url").toString());
	close();
}

void PluginDialog::getInfo()
{
	QSettings set(naveoConfigurationPath + "/pluginsList.ini", QSettings::IniFormat);
	set.beginGroup(listWidget->currentItem()->text(0));
	QMessageBox::about(this, listWidget->currentItem()->text(0), set.value("info").toString());
}

void PluginDialog::indexChanged()
{
	if(!listWidget->currentItem())
		return;


	info->setEnabled(listWidget->currentItem()->childCount() == 0);
	installButton->setEnabled(listWidget->currentItem()->childCount() == 0);
}

void PluginDialog::search()
{
	QSettings set(naveoConfigurationPath + "/pluginsList.ini", QSettings::IniFormat);
	set.beginGroup(os);
	QStringList items = set.value("list").toStringList();
	set.endGroup();
	QString text = line->text();
	if(text.isEmpty())
	{
		fillTree(items);
		return;
	}
	else
	{
		int i = 0;
		while(1)
		{
			if(i >= items.count()) {
				break;
			} else {
				if(!items.at(i).contains(text, Qt::CaseInsensitive)) {
					items.removeAt(i);
				} else {
					i++;
				}
			}
		}
		if(items.isEmpty())
		{
			listWidget->clear();
			info->setEnabled(false);
			installButton->setEnabled(false);
			return;
		}
		fillTree(items, false);
	}
}


void PluginDialog::fillTree(QStringList list, bool tree)
{
	listWidget->clear();
	QSettings set(naveoConfigurationPath + "/pluginsList.ini", QSettings::IniFormat);
	QList<QTreeWidgetItem*> types;
	foreach(QString plug, list)
	{
		set.beginGroup(plug);
		QString type = set.value("type").toString();
		if(type.isEmpty())
		{
			type = tr("Divers");
		}
		type = type.left(1).toUpper() + type.right(type.size() - 1).toLower();
		QTreeWidgetItem *item = 0;
		if(tree)
		{
			QTreeWidgetItem *parent = NULL;
			for(int i = 0; i != types.count(); i++)
			{
				if(types[i]->text(0) == type)
				{
					parent = types[i];
					break;
				}
			}
			if(!parent)
			{
				parent = new QTreeWidgetItem(listWidget, QStringList(type));
				parent->setIcon(0, QApplication::style()->standardIcon(QStyle::SP_DirIcon));
				types.append(parent);
			}
			item = new QTreeWidgetItem(parent, QStringList(plug));
		}
		else
		{
			item = new QTreeWidgetItem(listWidget, QStringList(plug));
		}
		item->setIcon(0, QIcon(":/plug.png"));
		set.endGroup();
	}
	info->setEnabled(false);
	installButton->setEnabled(false);
	listWidget->sortItems(0, Qt::AscendingOrder);
}
