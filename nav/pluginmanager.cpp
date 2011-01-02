/*******************************
Copyright (C) 2009-2010 grï¿½goire ANGERAND

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY {} without even the implied warranty of
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************/

#include "pluginmanager.h"
#include "Browser.h"

PluginManager::PluginManager(QObject *parent) :
	QObject(parent)
{

}


void PluginManager::PluginManager::init()
{
	QDir dir(qApp->applicationDirPath());
	if(!dir.cd("plugins"))
		dir.mkdir("plugins");

	QSettings set(qApp->applicationDirPath() + "/Options.ini", QSettings::IniFormat);
	QStringList removed = set.value("toRemove", QStringList()).toStringList();
	QStringList activated = set.value("activated", QStringList()).toStringList();
	foreach(QString path, dir.entryList(QDir::Files))
	{
		QLibrary *lib = new QLibrary(dir.path() + "/" + path);
		if(!lib->load())
		{
			cout<<"Unable to load "<<qPrintable(dir.path() + "/" + path)<<" for "<<qPrintable(lib->errorString())<<endl;
		}
		VoidFunc initFunc = (VoidFunc)lib->resolve("init");
		NameFunc nameFunc = (NameFunc)lib->resolve("name");
		if(initFunc && nameFunc)
		{
			Plugin plug;

			plug.lib = lib;
			plug.name = nameFunc();
			plug.activated = activated.contains(plug.name.replace(" ", ""));


			if(!removed.contains(plug.name))
			{
				plug.removed = false;
				plugins.append(plug);
				if(plug.activated)
					initFunc();
			}
			else
			{
				lib->unload();
				QFile(dir.path() + "/" + path).remove();
			}
		}
		else
		{
			cout<<qPrintable(lib->errorString())<<endl;
			lib->unload();
		}
	}
	set.setValue("toRemove", QStringList());
}

void PluginManager::resolve(QString name, QString func)
{
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].name == name)
		{
			if(plugins[i].activated)
			{
				VoidFunc f = (VoidFunc)plugins[i].lib->resolve(qPrintable(func));
				if(f)
				{
					f();
				}
			}
		}
	}
}

Plugin PluginManager::plugin(QString name)
{
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].name == name)
		{
			return plugins[i];
		}
	}
	return Plugin();
}

void PluginManager::addWindow(MainWin *win)
{
	wins.append(win);
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].activated)
		{
			WinFunc f = (WinFunc)plugins[i].lib->resolve("addWindow");
			if(f)
			{
				f(win);
			}
		}
	}
}

void PluginManager::addPage(webPage *page)
{
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].activated)
		{
			PageFunc f = (PageFunc)plugins[i].lib->resolve("addPage");
			if(f)
			{
				f(page);
			}
		}
	}
}

void PluginManager::closePage(webPage *page)
{
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].activated)
		{
			PageFunc f = (PageFunc)plugins[i].lib->resolve("closePage");
			if(f)
			{
				f(page);
			}
		}
	}
}

void PluginManager::closeWindow(MainWin *win)
{
	wins.removeOne(win);
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].activated)
		{
			WinFunc f = (WinFunc)plugins[i].lib->resolve("closeWindow");
			if(f)
			{
				f(win);
			}
		}
	}
}

void PluginManager::quit()
{
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].activated)
		{
			VoidFunc f = (VoidFunc)plugins[i].lib->resolve("quit");
			if(f)
			{
				f();
			}
			plugins[i].lib->unload();
		}
	}
	QSettings set(qApp->applicationDirPath() + "/Options.ini", QSettings::IniFormat);
	QStringList a = set.value("activated", QStringList()).toStringList();
	a.removeDuplicates();
	set.setValue("activated", a);
}

QList<Plugin> PluginManager::pluginsList()
{
	return plugins;
}

bool PluginManager::hasSettings(QString name)
{
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].name == name)
		{
			BoolFunc boolFunc = (BoolFunc)plugins[i].lib->resolve("hasSettings");
			if(boolFunc)
			{
				return (boolFunc() && plugins[i].activated);
			}
		}
	}
	return false;
}

bool PluginManager::activated(QString name)
{
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].name == name)
		{
			return plugins[i].activated;
		}
	}
	return false;
}

void PluginManager::settingsOpenned(settingDialog *dial)
{
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].activated)
		{
			SetFunc f = (SetFunc)plugins[i].lib->resolve("settingsOpenned");
			if(f)
			{
				f(dial);
			}
		}
	}
}

void PluginManager::updateSettings()
{
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].activated)
		{
			VoidFunc f = (VoidFunc)plugins[i].lib->resolve("updateSettings");
			if(f)
			{
				f();
			}
		}
	}
}

void PluginManager::execSettings(QString name)
{
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].name == name)
		{
			if(plugins[i].activated)
			{
				VoidFunc f = (VoidFunc)plugins[i].lib->resolve("execSettings");
				if(f)
				{
					f();
				}
			}
			break;
		}
	}
}

void PluginManager::activate(QString name)
{
	QSettings set(qApp->applicationDirPath() + "/Options.ini", QSettings::IniFormat);
	QStringList a = set.value("activated", QStringList()).toStringList();
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].name == name)
		{
			if(!plugins[i].activated)
			{
				if(!plugins[i].lib->load())
				{
					cout<<"Unable to load "<<qPrintable(plugins[i].lib->fileName())<<" for "<<qPrintable(plugins[i].lib->errorString())<<endl;
				}
				else
				{
					plugins[i].activated = true;
					a.append(plugins[i].name);
				}
				VoidFunc initFunc = (VoidFunc)plugins[i].lib->resolve("init");
				if(initFunc) { initFunc(); }
				for(int j = 0; j != wins.count(); j++)
				{
					WinFunc f = (WinFunc)plugins[i].lib->resolve("addWindow");
					if(f) { f(wins[j]); }
					for(int k = 0; k != wins[j]->pages().count(); k++)
					{
						PageFunc fu = (PageFunc)plugins[i].lib->resolve("addPage");
						if(fu) { fu(wins[j]->pages()[k]); }
					}
				}

			}
			else
			{
				plugins[i].activated = false;
				a.removeOne(plugins[i].name);
				for(int j = 0; j != wins.count(); j++)
				{
					for(int k = 0; k != wins[j]->pages().count(); k++)
					{
						PageFunc fu = (PageFunc)plugins[i].lib->resolve("closePage");
						if(fu) { fu(wins[j]->pages()[k]); }
					}
					WinFunc f = (WinFunc)plugins[i].lib->resolve("closeWindow");
					if(f) { f(wins[j]); }
				}
				VoidFunc f = (VoidFunc)plugins[i].lib->resolve("quit");
				if(f) { f(); }
				plugins[i].lib->unload();
			}
			break;
		}
	}
	set.setValue("activated", a);
}

void PluginManager::remove(QString name)
{
	QSettings set(qApp->applicationDirPath() + "/Options.ini", QSettings::IniFormat);
	QStringList r = set.value("toRemove", QStringList()).toStringList();
	for(int i = 0; i != plugins.count(); i++)
	{
		if(plugins[i].name == name && !plugins[i].removed)
		{
			plugins[i].removed = true;
			r.append(name);
			break;
		}
	}
	set.setValue("toRemove", r);
}


void PluginManager::getPlugins()
{
	if(!getList())
	{
		return;
	}
	PluginDialog *dial = new PluginDialog;
	connect(dial, SIGNAL(install(QString, QString)), this, SLOT(install(QString, QString)));
	dial->exec();
}

void PluginManager::install(QString name, QString url)
{
	int answer = QMessageBox::question(0, tr("Voulez vous installer ce plug-in ?"), tr("<html>Voulez vous installer <strong>%1</strong> ?</html>").arg(name), QMessageBox::Yes | QMessageBox::No);
	if (answer == QMessageBox::No)
	{
		return;
	}
	HttpGet *getter = new HttpGet;
	QString str(qApp->applicationDirPath() + "/plugins/" + name);
	#ifdef Q_WS_WIN
		str += ".dll";
		url += ".dll";
	#endif
	#ifdef Q_WS_X11
		str += ".so";
		url += ".so";
	#endif
	if (!getter->getFile(QUrl(url), str))
	{
		if (QFile(str).exists())
		{
			QMessageBox::critical(0, tr("Opération impossible"), tr("Vous possédez déjà ce plug-in,\nsupprimez le avant de le réinstaller !"));
			return;
		}
		else
		{
		QMessageBox::critical(0, tr("Opération impossible"), tr("Impossible de télécharger le plug-in !"));
		return;
		}
	}
	QProgressDialog *dial = new QProgressDialog(tr("Téléchargement du plug-in ..."), tr("Annuler"), 0, 0);
	dial->findChild<QPushButton *>()->hide();
	dial->setValue(0);
	dial->setModal(true);
	dial->show();
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	connect(getter, SIGNAL(done(bool)), &loop, SLOT(quit()));
	connect(dial, SIGNAL(canceled()), &loop, SLOT(quit()));
	connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
	timer.start(10000);
	loop.exec();
	dial->cancel();
	if (!timer.isActive() || getter->error())
	{
		QMessageBox::critical(0, tr("Opération impossible"), tr("Impossible d'obtenir le plug-in !"));
		getter->cancel();
		return;
	}
	QSettings set(qApp->applicationDirPath() + "/Options.ini", QSettings::IniFormat);
	QStringList a = set.value("activated", QStringList()).toStringList();
	a.append(name);
	set.setValue("activated", a);
	QMessageBox::about(0, tr("Opération effectuée"), tr("Plug-in téléchargé !\nIl sera installé au prochain démarrage."));
}


bool PluginManager::getList()
{
	QProgressDialog *dial = new QProgressDialog(tr("Recherche des plug-in disponibles ..."), tr("Annuler"), 0, 0);
	dial->setValue(0);
	dial->setModal(true);
	dial->findChild<QPushButton *>()->hide();
	dial->show();
	HttpGet *getter = new HttpGet;
	if (!getter->getFile(QUrl("http://sd-1.archive-host.com/membres/up/105196114112850749/plugins/pluginsList.ini"), qApp->applicationDirPath() + "/pluginsList.ini"))
	{
		QMessageBox::critical(0, tr("Opération impossible"), tr("Impossible de trouver la liste des plug-in !"));
		dial->cancel();
		return false;
	}
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	connect(getter, SIGNAL(done(bool)), &loop, SLOT(quit()));
	connect(dial, SIGNAL(canceled()), &loop, SLOT(quit()));
	connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
	timer.start(5000);
	loop.exec();
	dial->cancel();
	if (!timer.isActive())
	{
		QMessageBox::critical(0, tr("Opération impossible"), tr("Impossible d'obtenir la liste des plug-in !"));
		getter->cancel();
		return false;
	}
	QFile file(qApp->applicationDirPath() + "/pluginsList.ini");
	if (!file.exists())
	{
		QMessageBox::critical(0, tr("Opération impossible"), tr("Impossible d'obtenir la liste des plug-in !"));
		return false;
	}
	return true;
}
