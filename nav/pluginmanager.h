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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QtGui>
#include <iostream>
#include "mainWin.h"
#include "plugindialog.h"
#include "settingsDialog.h"

class settingDialog;

typedef void(*PageFunc)(webPage *);
typedef void(*WinFunc)(MainWin *);
typedef void(*SetFunc)(settingDialog *);
typedef void(*VoidFunc)();

typedef bool(*BoolFunc)();
typedef QString(*NameFunc)();

using namespace std;

struct Plugin
{
	QLibrary *lib;
	QString name;
	bool activated;
	bool removed;
};

class PluginManager : public QObject
{
	Q_OBJECT

	public:
		PluginManager(QObject *parent = 0);
		QList<Plugin> pluginsList();
		bool hasSettings(QString name);
		void execSettings(QString name);
		void remove(QString name);
		void activate(QString name);
		void getPlugins();
		bool activated(QString name);
		void resolve(QString name, QString func);
		Plugin plugin(QString name);


	signals:

	public slots:
		void init();
		void addWindow(MainWin *win);
		void addPage(webPage *page);
		void settingsOpenned(settingDialog *dial);
		void closePage(webPage *page);
		void closeWindow(MainWin *win);
		void updateSettings();
		void quit();

	private slots:
		void install(QString name, QString url);

	private:
		bool getList();
		QList<Plugin> plugins;
		QList<MainWin *> wins;

};

#endif // PLUGINMANAGER_H
