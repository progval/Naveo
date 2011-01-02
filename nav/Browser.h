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


#ifndef HEADER_BROWSER
#define HEADER_BROWSER

#include <QtGui>
#include <QtWebKit>
#include <iostream>
#include "settingsDialog.h"
#include "version.h"
#include "download.h"
#include "httpget.h"
#include "cookiejar.h"
#include "mainWin.h"
#include "bookmarkmanager.h"
#include "historymanager.h"
#include "synchronizer.h"
#include "speeddial.h"
#include "about.h"
#include "cleardialog.h"
#include "pluginmanager.h"

#ifdef Q_WS_WIN
	#include <windows.h>
#endif

class webPage;
class MainWin;

using namespace std;

#ifdef qApp
	#undef qApp
#endif
#define qApp Browser::instance()

class Browser : public QApplication
{
	Q_OBJECT

	public:


		Browser(int &argc, char **argv);

		int exec();
		void setStyle(QWidget* wid);
		void loadPlugins();
		bool verifyInstance();
		QList<MainWin *> activeWindows();
		downloadManager *dlManager();
		BookMarkManager *bmManager();
		HistoryManager *hManager();
		settingDialog *settingsManager();
		CookieJar *cJar();
		static Browser *instance();
		void verifySettings();
		bool isDefaultBrowser();
		void checkDefaultBrowser();
		bool isTheOnlyBrowser;
		SpeedDial *createDial();
		Synchronizer *syn();
		void initWebSettings();
		PluginManager *plugins();
		QString iniFile(QString file = QString("Options.ini"));
		QString currentSession();
		void setQuitOnClose(bool c);

		static QString getUrl(QWidget *parent, QString title, QString text = QString());

	public slots:
		void addNew(QString url = QString(), bool show = true);
		void updateVersion(bool error);
		void saveSettings();
		void showHelp();
		void closeWin();
		void close(int exitCode = 0);
		void news();
		void closeAndUpdate();
		void setDefaultBrowser();
		void loadHistory(QString url);
		void newLocalSocketConnection();
		void execSettings();
		void update();
		void about();
		void clearData();
		void restart();

	signals:
		void settingsChanged();

	private:
		QString getSessionName();

		BookMarkManager* bookMarkManager;
		HistoryManager * historyManager;
		QList<MainWin *> windows;
		QString fileName;
		QSettings *settings;
		downloadManager *manager;
		PluginManager *plugs;
		QSystemTrayIcon *trayIcon;
		DownloadWidget *down;
		CookieJar *jar;
		QLocalServer *localServer;
		Synchronizer *synchronizer;
		bool quitOnClose;
		QSystemTrayIcon *updateIcon;

};

#endif
