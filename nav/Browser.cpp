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


#include "Browser.h"
#include "helper.h"
#include "urldialog.h"

#ifdef Q_WS_WIN
	typedef struct
	{
		int cxLeftWidth;
		int cxRightWidth;
		int cyTopHeight;
		int cyBottomHeight;
	}
	MARGINS;
		typedef HRESULT (WINAPI *PtrDwmExtendFrameIntoClientArea)(HWND hWnd, const MARGINS *margins);
		static PtrDwmExtendFrameIntoClientArea pDwmExtendFrameIntoClientArea = 0;
		typedef HRESULT (WINAPI *PtrDwmIsCompositionEnabled)(BOOL *pfEnabled);
		static PtrDwmIsCompositionEnabled pDwmIsCompositionEnabled = 0;
#endif



Browser::Browser(int &argc, char **argv)
	: QApplication(argc, argv)
{
	setOrganizationName(QLatin1String("gan_"));
	setApplicationName(QLatin1String("Naveo"));

	quitOnClose = true;

	isTheOnlyBrowser = verifyInstance();

	cout<<"Naveo version : "<<VERSION<<endl<<"Software made by gan_"<<endl<<"Compilated : "<<__DATE__<<" at "<<__TIME__<<endl<<endl;

	if (isTheOnlyBrowser)
	{

		setWindowIcon(QIcon(":/icon.png"));

		settings = new QSettings(applicationDirPath() + "/Options.ini", QSettings::IniFormat);

		verifySettings();

		loadPlugins();

		synchronizer = new Synchronizer;
		networkAccessManager = new NetworkAccessManager;

		fileName = "";
		if (argc >= 2)
		{
			fileName = argv[1];
		}

		setQuitOnLastWindowClosed(false);

		if (settings->value("version").toString() != QString(VERSION))
		{
			settings->setValue("version", VERSION);
			settings->setValue("zoom", 1);
		}

		QWebSettings * const webSettings = QWebSettings::globalSettings();
		webSettings->setIconDatabasePath(applicationDirPath() + "/cache/");
		webSettings->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
		webSettings->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
		webSettings->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, true);
		webSettings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
		webSettings->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
		webSettings->setMaximumPagesInCache(40);
		webSettings->setOfflineStoragePath(applicationDirPath() + "/cache/");

		initWebSettings();

		manager = new downloadManager;
		bookMarkManager = new BookMarkManager;
		historyManager = new HistoryManager;
		jar = new CookieJar(this);
		pass = new PasswordManager;
		networkAccessManager->setCookieJar(jar);

		HttpGet *getter = new HttpGet;
		updateIcon = 0;
		connect(getter, SIGNAL(done(bool)), this, SLOT(updateVersion(bool)));
		if(!getter->getFile(QUrl("http://sd-1.archive-host.com/membres/up/105196114112850749/version.ini"), applicationDirPath() + "/version.ini"))
		{
			//QMessageBox::information(0, tr("Opération impossible"), tr("Impossible de vérifier les mises à jour !"));
		}

		trayIcon = new QSystemTrayIcon(QIcon(":/icon.png"));
		trayIcon->show();
		connect(manager, SIGNAL(closed()), this, SLOT(close()));
		connect(historyManager, SIGNAL(load(QString)), this, SLOT(loadHistory(QString)));
		checkDefaultBrowser();
	}
}

Browser *Browser::instance()
{
	return (static_cast<Browser *>(QCoreApplication::instance()));
}

void Browser::initWebSettings()
{
	QWebSettings *webSettings = QWebSettings::globalSettings();
	webSettings->setAttribute(QWebSettings::AutoLoadImages, settings->value("image").toBool());
	webSettings->setAttribute(QWebSettings::PluginsEnabled, settings->value("flash", true).toBool());
	webSettings->setAttribute(QWebSettings::JavascriptEnabled , settings->value("javascript").toBool());
	webSettings->setAttribute(QWebSettings::JavascriptCanOpenWindows , settings->value("javascript").toBool());
	webSettings->setAttribute(QWebSettings::JavaEnabled, settings->value("javascript").toBool());
	webSettings->setAttribute(QWebSettings::PrivateBrowsingEnabled , settings->value("private").toBool());
	QWebSettings::setWebGraphic(QWebSettings::MissingPluginGraphic, QPixmap(":/plug.png"));
	settings->beginGroup("proxy");
	QNetworkProxy proxy;
	if (settings->value("enabled", false).toBool())
	{
		if (settings->value("type", 0).toInt() == 0)
			proxy.setType(QNetworkProxy::Socks5Proxy);
		else
			proxy.setType(QNetworkProxy::HttpProxy);
		proxy.setHostName(settings->value("hostName").toString());
		proxy.setPort(settings->value("port", 1080).toInt());
		proxy.setUser(settings->value("userName").toString());
		proxy.setPassword(settings->value("password").toString());
	}
	settings->endGroup();
	networkAccessManager->setProxy(proxy);
}

NetworkAccessManager *Browser::accessManager()
{
	return networkAccessManager;
}

void Browser::showHelp()
{
	Helper *h = new Helper;
	h->show();
}

Synchronizer *Browser::syn()
{
	return synchronizer;
}

SpeedDial *Browser::createDial()
{
	return new SpeedDial;
}

void Browser::newLocalSocketConnection()
{
	QLocalSocket *socket = localServer->nextPendingConnection();
	if (!socket)
		return;
	socket->waitForReadyRead(1000);
	QTextStream stream(socket);
	QString url;
	stream >> url;
	addNew(url);
	delete socket;
}

CookieJar *Browser::cJar()
{
	return jar;
}

HistoryManager *Browser::hManager()
{
	return historyManager;
}

void Browser::loadHistory(QString url)
{
	windows.last()->newTab(url);
}

void Browser::about()
{
	About *dial = new About;
	dial->show();
}

void Browser::checkDefaultBrowser()
{
	if (!isDefaultBrowser())
	{
		trayIcon->showMessage( "Naveo", tr("Naveo n'est pas votre navigateur par défaut, cliquez ici pour définir Naveo comme navigateur par defaut"));
		connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(setDefaultBrowser()));
	}
}

bool Browser::isDefaultBrowser()
{
	#ifdef Q_WS_WIN
		QSettings reg("HKEY_CLASSES_ROOT\\http\\shell\\open\\command", QSettings::NativeFormat);
		return (reg.value("Default").toString() == QDir::toNativeSeparators("\"" + applicationDirPath() + "/Naveo.exe\" \"%1\""));
	#endif
	return true;
}

void Browser::setDefaultBrowser()
{
	#ifdef Q_WS_WIN
		QSettings reg("HKEY_CLASSES_ROOT\\http\\shell\\open\\command", QSettings::NativeFormat);
		reg.setValue("Default", QDir::toNativeSeparators("\"" + applicationDirPath() + "/Naveo.exe\" \"%1\""));
		QSettings reg3("HKEY_CLASSES_ROOT\\http\\shell\\open\\ddeexec\\Application", QSettings::NativeFormat);
		reg3.setValue("Default", "Naveo");
		QSettings reg2("HKEY_CLASSES_ROOT\\https\\shell\\open\\command", QSettings::NativeFormat);
		reg2.setValue("Default", QDir::toNativeSeparators("\"" + applicationDirPath() + "/Naveo.exe\" \"%1\""));
		QSettings reg4("HKEY_CLASSES_ROOT\\https\\shell\\open\\ddeexec\\Application", QSettings::NativeFormat);
		reg4.setValue("Default", "Naveo");
		QSettings reg5("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\Shell\\Associations\\UrlAssociations\\http\\UserChoice", QSettings::NativeFormat);
		reg5.setValue("Progid", "Naveo");

		QMessageBox::information(0, tr("Naveo"), tr("Naveo est maintenant votre navigateur par défaut !"));
	#endif
}

void Browser::verifySettings()
{
	if (!QFile(applicationDirPath() + "/Options.ini").exists())
	{
		settings->setValue("dlInk", false);
		settings->setValue("showHome", true);
		settings->setValue("showStop", false);
		settings->setValue("image", true);
		settings->setValue("javascript", true);
		settings->setValue("changeTab", true);
		settings->setValue("google", true);
		settings->setValue("eraseHistory", false);
		settings->setValue("private", false);
		settings->setValue("falsh", true);
		settings->setValue("perso", true);
		settings->setValue("Noplug-in", true);
		settings->setValue("transparency", true);
		settings->setValue("block", true);
		settings->setValue("speedDial", false);
		settings->setValue("close", true);
		settings->setValue("toolbarTranparency", true);
		settings->setValue("dark", false);
		settings->setValue("noText", false);
		settings->setValue("saveTab", false);
		settings->setValue("openHome", true);
		settings->setValue("openUrl", false);
		settings->setValue("tabOpenHome", true);
		settings->setValue("newUrl", "www.google.fr");
		settings->setValue("tabUrl", "www.google.fr");
		settings->setValue("home", "www.google.fr");
		settings->setValue("askForDir", true);
		settings->setValue("downloadIn", "/");
		settings->setValue("zoom", 1);
		settings->setValue("motor", "Google");
		settings->setValue("posPerso", 0);
		settings->setValue("posNav", 0);
		settings->setValue("saveHistory", 0);
		settings->setValue("saveCookies", 0);
		settings->setValue("pos", QPoint(100, 100));
		settings->setValue("size", QSize(800, 600));
		settings->setValue("theme", "classique");
		settings->setValue("version", VERSION);
		settings->setValue("max", false);
	}
}

void Browser::clearData()
{
	ClearDialog *dial = new ClearDialog;
	dial->exec();
	dial->deleteLater();
}

int Browser::exec()
{
	MainWin *main = new MainWin(fileName);

	setStyle(main);
	manager->setClosable(false);
	windows.append(main);

	connect(main, SIGNAL(closed()), this, SLOT(closeWin()));

	if (settings->value("max").toBool())
	{
		main->showMaximized();
	}
	else
	{
		main->show();
	}
	return QApplication::exec();
}

bool Browser::verifyInstance()
{
	QString serverName = applicationName();
	QLocalSocket socket;
	socket.connectToServer(serverName);
	if (socket.waitForConnected(500)) {
		QTextStream stream(&socket);
		QStringList args = QCoreApplication::arguments();
		if (args.count() > 1)
			stream << args.last();
		else
			stream << QString();
		stream.flush();
		socket.waitForBytesWritten();
		cout<<"there already is a Naveo instancce running"<<endl;
		return false;
	}

	localServer = new QLocalServer(this);
	connect(localServer, SIGNAL(newConnection()),
			this, SLOT(newLocalSocketConnection()));
	if (!localServer->listen(serverName)) {
		if (localServer->serverError() == QAbstractSocket::AddressInUseError
			&& QFile::exists(localServer->serverName())) {
			QFile::remove(localServer->serverName());
			localServer->listen(serverName);
		}
	}
	return true;
}

void Browser::addNew(QString url, bool show)
{
	MainWin *main = new MainWin(url);

	setStyle(main);
	manager->setClosable(false);
	windows.append(main);

	connect(main, SIGNAL(closed()), this, SLOT(closeWin()));

	if(show)
	{
		if (settings->value("max").toBool()) {
			main->showMaximized();
		} else {
			main->show();
		}
	}
}

void Browser::close(int exitCode)
{
	localServer->close();
	trayIcon->hide();
	historyManager->hide();
	bookMarkManager->hide();
	manager->hide();

	if(updateIcon)
		updateIcon->hide();

	if (settings->value("eraseHistory").toBool())
	{
		historyManager->clear();
		manager->clearDownloads();
		jar->clear();
		pass->clear();
	}
	saveSettings();

	if(quitOnClose)
	{
		QFile(applicationDirPath() + "/Version.ini").remove();
		QSettings set(applicationDirPath() + "/crash.ini", QSettings::IniFormat);
		set.setValue("crash", false);
		delete jar;
		plugs->quit();
	}

	foreach(MainWin *w, windows)
	{
		w->hide();
		cout<<"hiden"<<endl;
	}

	if(quitOnClose)
	{
		synchronizer->close();
		cout<<"exit("<<exitCode<<");"<<endl;
		exit(exitCode);
	}

}


void Browser::setQuitOnClose(bool c)
{
	quitOnClose = c;
}

void Browser::closeWin()
{
	MainWin * win = qobject_cast<MainWin *>(sender());
	win->hide();
	plugs->closeWindow(win);
	windows.removeOne(win);
	if (windows.isEmpty() && manager->downloading())
	{
		manager->show();
		manager->setClosable(true);
	}
	else if (windows.isEmpty() && manager->isVisible())
	{
		manager->setClosable(true);
	}
	else if (windows.isEmpty())
	{
		close();
	}
}

void Browser::loadPlugins()
{
	plugs = new PluginManager;
	plugs->init();
}

PluginManager *Browser::plugins()
{
	return plugs;
}

void Browser::updateVersion(bool error)
{
	if (error)
	{
		cout<<"Unable to get update file"<<endl;
		return;
	}
	QSettings versionSettings(applicationDirPath() + "/version.ini", QSettings::IniFormat);
	#ifdef Q_WS_WIN
		versionSettings.beginGroup("win");
	#else
		versionSettings.beginGroup("X11");
	#endif
	QString v = versionSettings.value("version", 0).toString();
	v.replace(".", "");
	v.replace(QRegExp("[a-z]"), "");
	int lastVersion = v.toInt();
	v = QString(VERSION).replace(".", "");
	v.replace(QRegExp("[a-z]"), "");
	int actualVersion = v.toInt();
	if(actualVersion < lastVersion)
	{
		updateIcon = new QSystemTrayIcon(QIcon(":/maj.png"));
		QMenu menu;
		QAction *action = new QAction(tr("Mettre Naveo à jour"), this);
		QAction *hideIconAction = new QAction(tr("Ignorer"), this);
		QAction *newsAction = new QAction(tr("Quoi de plus dans Naveo %1 ?").arg(versionSettings.value("version", 0).toString()), this);
		menu.addAction(action);
		menu.addAction(newsAction);
		menu.addAction(hideIconAction);
		connect(hideIconAction, SIGNAL(triggered()), updateIcon, SLOT(hide()));
		connect(newsAction, SIGNAL(triggered()), this, SLOT(news()));
		updateIcon->setContextMenu(&menu);
		updateIcon->show();
		updateIcon->showMessage( "Naveo", tr("Une mise à jour est disponible !\n(version %1)\nCliquez ici pour l'installer !").arg(versionSettings.value("version", 0).toString()));
		connect(action, SIGNAL(triggered()), this, SLOT(closeAndUpdate()));
		connect(updateIcon, SIGNAL(messageClicked()), this, SLOT(closeAndUpdate()));
	}
	versionSettings.endGroup();
}

void Browser::closeAndUpdate()
{
	close(-2);
}

void Browser::news()
{
	QSettings versionSettings(applicationDirPath() + "/version.ini", QSettings::IniFormat);
	QString version = versionSettings.value("nav").toString();
	QMessageBox::about(0, tr("Quoi de plus dans Naveo %1").arg(version), versionSettings.value("news").toString());
}


void Browser::setStyle(QWidget* wid)
{
	#ifdef Q_WS_WIN
		QLibrary dwmapi("dwmapi");
		if (QSysInfo::WindowsVersion >= QSysInfo::WV_VISTA)
		{
			pDwmIsCompositionEnabled = (PtrDwmIsCompositionEnabled)dwmapi.resolve("DwmIsCompositionEnabled");
			BOOL enabled = FALSE;
			pDwmIsCompositionEnabled(&enabled);
			if (enabled)
			{
				pDwmExtendFrameIntoClientArea = (PtrDwmExtendFrameIntoClientArea)dwmapi.resolve("DwmExtendFrameIntoClientArea");
				MARGINS margins = {-1};
				pDwmExtendFrameIntoClientArea(wid->winId(), &margins);
			}
		}
		dwmapi.unload();
	#else
		Q_UNUSED(wid);
	#endif
}


downloadManager *Browser::dlManager()
{
	return manager;
}

BookMarkManager *Browser::bmManager()
{
	return bookMarkManager;
}

void Browser::saveSettings()
{
	pass->save();
	bmManager()->saveSettings();
	hManager()->save();
}

settingDialog *Browser::settingsManager()
{
	return new settingDialog(synchronizer, plugs);
}

PasswordManager *Browser::passManager()
{
	return pass;
}

void Browser::execSettings()
{
	saveSettings();
	settingDialog *settingDial = settingsManager();
	connect(settingDial, SIGNAL(clearHistory()), historyManager, SLOT(clear()));
	connect(settingDial, SIGNAL(clearCookies()), jar, SLOT(clear()));
	connect(settingDial, SIGNAL(restart()), this, SLOT(restart()));
	plugs->settingsOpenned(settingDial);
	pass->load();
	settingDial->exec();
	plugs->updateSettings();
	update();
	delete settingDial;
	emit settingsChanged();
	foreach(MainWin *win, windows)
	{
		setStyle(win);
	}
	saveSettings();
}


void Browser::restart()
{
	close(-1);
}


void Browser::update()
{
	jar = new CookieJar(this);
	bookMarkManager->updateLists();
	foreach(MainWin *win, windows)
	{
		win->updateSettings();
	}
	initWebSettings();
	saveSettings();
}

QList<MainWin *> Browser::activeWindows()
{
	return windows;
}

QString Browser::iniFile(QString file)
{
	QString name = getSessionName();
	if(name.isEmpty())
		return QString(applicationDirPath() + "/" + file);
	return QString(applicationDirPath() + "/session/" + name + "/" + file);
}

QString Browser::getUrl(QWidget *parent, QString title, QString text)
{
	UrlDialog *dial = new UrlDialog(parent, true, text);
	dial->setWindowTitle(title);
	QString s = dial->exec();
	delete dial;
	return s;
}

QString Browser::currentSession()
{
	return getSessionName();
}

QString Browser::getSessionName()
{
	return settings->value("currentSes", "").toString();
}
