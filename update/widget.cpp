/*******************************
Copyright (C) 2009-2010 grï¿½goire ANGERAND

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

#include "widget.h"

#ifdef Q_WS_WIN
	#define SYSTEM "win"
	#define LIB "dll"
#else
	#define SYSTEM "x11"
	#define LIB "so"
#endif

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle(tr("Naveo - mise à jour"));
	setWindowIcon(QIcon(":/down.png"));

	settingsGetter = new HttpGet;
	connect(settingsGetter, SIGNAL(done(bool)), this, SLOT(done(bool)));

	QDir dir(qApp->applicationDirPath());
	dir.mkdir("update");
	dir.mkdir("session");

	list = new QListWidget;
	dlButton = new QPushButton(tr("Télécharger"));
	startButton = new QPushButton(tr("Lancer Naveo"));
	reloadButton = new QPushButton(QIcon(":/reload.png"), QString());
	prog = new QProgressBar;
	label = new QLabel;

	prog->setRange(0, 0);
	list->setIconSize(QSize(32, 32));
	prog->setStyle(new QCleanlooksStyle);

	connect(dlButton, SIGNAL(clicked()), this, SLOT(start()));
	connect(reloadButton, SIGNAL(clicked()), this, SLOT(getList()));
	connect(startButton, SIGNAL(clicked()), this, SLOT(exit()));

	QVBoxLayout *mainLay = new QVBoxLayout;
	QHBoxLayout *buttonLay = new QHBoxLayout;

	mainLay->addWidget(list);
	buttonLay->addWidget(label, 99);
	buttonLay->addWidget(prog, 99);
	buttonLay->addWidget(dlButton);
	buttonLay->addWidget(startButton);
	buttonLay->addWidget(reloadButton);
	mainLay->addLayout(buttonLay);

	setLayout(mainLay);

	resize(500, 350);

	getList();
}

void Widget::getList()
{
	#ifdef Q_WS_WIN
		system("cls");
	#else
		system("clear");
	#endif
	setDownloaded = false;
	dlButton->setEnabled(false);
	startButton->hide();
	prog->show();
	if(!settingsGetter->getFile(QUrl("http://sd-1.archive-host.com/membres/up/105196114112850749/update/" + QString(SYSTEM) + "update.txt"), qApp->applicationDirPath() + "/update/list.ini"))
	{
		QMessageBox::critical(this, tr("Oppération impossible"), tr("Impossible de télécharger la mise à jour !\nImpossible de récupérer le fichier source."));
		QTimer::singleShot(500, qApp, SLOT(quit()));
	}
	QTimer::singleShot(2000, this, SLOT(done()));
}

void Widget::done(bool error)
{
	if(setDownloaded)
		return;

	setDownloaded = true;
	downloads.clear();
	files.clear();
	list->clear();

	if(error || !QFile(qApp->applicationDirPath() + "/update/list.ini").exists())
	{
		QMessageBox::critical(this, tr("Oppération impossible"), tr("Impossible de télécharger la mise à jour !\nImpossible d' ouvrir le fichier source."));
		qApp->quit();
	}
	else
	{
		cout<<"file downloaded : "<<qPrintable(qApp->applicationDirPath() + "/update/list.ini")<<endl<<endl;
	}

	QStringList urls;

	QSettings set(qApp->applicationDirPath() + "/update/list.ini", QSettings::IniFormat);

	set.beginGroup("always");
	urls.append(set.value("files", QStringList()).toStringList());
	set.endGroup();
	set.beginGroup("needed");
	for(int i = 0; i != set.value("files", QStringList()).toStringList().count(); i++)
	{
		cout<<qPrintable(set.value("files", QStringList()).toStringList().at(i))<<endl;
		QFile file(qApp->applicationDirPath() + "/" + set.value("files", QStringList()).toStringList().at(i));
		if(!file.exists())
		{
			urls.append(set.value("files", QStringList()).toStringList().at(i));
		}
		else if(set.value("sizes", QStringList()).toStringList().count() > i && (file.size() < set.value("sizes", QStringList()).toStringList().at(i).toInt() && !set.value("sizes", QStringList()).toStringList().at(i).isEmpty()))
		{
			urls.append(set.value("files", QStringList()).toStringList().at(i));
		}
	}
	set.endGroup();
	set.beginGroup("md5");
	for(int i = 0; i != set.value("files", QStringList()).toStringList().count(); i++)
	{
		QFile file(qApp->applicationDirPath() + "/" + set.value("files", QStringList()).toStringList().at(i));
		if(!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::critical(this, tr("Oppération impossible"), tr("Impossible d'ouvrir les fichiers"));
			qApp->quit();
		}
		if(QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex() != set.value("hash", QStringList()).toStringList().at(i).toAscii())
		{
			urls.append(set.value("files", QStringList()).toStringList().at(i));
		}
	}
	set.endGroup();


	if(urls.isEmpty() && set.allKeys().count())
	{
		QMessageBox::information(this, tr("Naveo est dejà à jour"), tr("Naveo est dejà à jour"));
		exit();
	}
	else if(!set.allKeys().count())
	{
		QMessageBox::information(this, tr("Arrgh !"), tr("Une erreur de nature, d'origine, de nom et conséquences inconnues s'est produite !"));
		exit();
	}

	foreach(QString file, urls)
	{
		file.replace(" ", "");
		QStringList url = file.split("/");
		if(url.count() > 1)
		{
			QDir dir(qApp->applicationDirPath());
			QStringList sub = url;
			sub.removeLast();
			foreach(QString subDir, sub)
			{
				dir.mkdir(subDir);
				dir.cd(subDir);
			}
		}
		QString name = url.last();
		QString local = qApp->applicationDirPath() + "/" + file;
		cout<<qPrintable(local)<<endl;
		HttpGet *getter = new HttpGet;
		downloads.append(getter);
		getter->name = file;
		files.append(local);
		DownloadWidget *down = new DownloadWidget(file, local, "?", name);
		connect(getter, SIGNAL(done(bool)), this, SLOT(downloadDone(bool)));
		connect(getter, SIGNAL(done(bool)), down, SLOT(done(bool)));
		connect(getter, SIGNAL(progress(qint64, qint64)), down, SLOT(update(qint64, qint64)));
		list->setItemWidget(new QListWidgetItem(QIcon(":/down.png"), QString(), list, 0), down);
	}

	label->setText(tr("%1 téléchargements").arg(downloads.count()));

	dlButton->setEnabled(true);
	prog->hide();
	dlButton->show();
}

void Widget::start()
{
	dlButton->setEnabled(false);
	reloadButton->setEnabled(false);
	if(!downloads.first()->getFile("http://sd-1.archive-host.com/membres/up/105196114112850749/update/" + downloads.first()->name, files.first()))
	{
		QMessageBox::critical(this, tr("Oppération impossible"), tr("Impossible de télécharger le fichier !"));
		qApp->quit();
	}
}

void Widget::downloadDone(bool error)
{
	if(error)
	{
		cout<<qPrintable(QString("Impossible de télécharger %1 : Erreur %2").arg(static_cast<HttpGet *>(sender())->name).arg(static_cast<HttpGet *>(sender())->error()))<<endl;
	}
	list->takeItem(0);
	downloads.removeFirst();
	files.removeFirst();
	label->setText(tr("%1 téléchargements").arg(downloads.count()));
	if(downloads.isEmpty())
	{
		if(QFile(qApp->applicationDirPath() + "/Naveo_." + LIB).exists() && !QFile(qApp->applicationDirPath() + "/Naveo_." + LIB).rename(QString(qApp->applicationDirPath() + "/Naveo." + LIB)))
			startButton->setText(tr("Terminer"));


		startButton->show();
		dlButton->hide();
		label->setText(QString());
		reloadButton->setEnabled(true);

		new QListWidgetItem(QIcon(":/ok.png"), tr("mise à jour effectuée !"), list);
	}
	else
		start();
}

Widget::~Widget()
{

}

void Widget::exit()
{
	qApp->exit(-1);
}
