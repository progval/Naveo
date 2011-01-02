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


#include "download.h"
#include "Browser.h"


downloadManager::downloadManager()
{
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	themeDir = settings.value("theme").toString();

	setWindowIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/down.png"));
	setWindowTitle(tr("Naveo - Téléchargements"));


	canClose = false;
	downloads = 0;
	oldDownloads = 0;
	currentDownload = 0;
	listWidget = new QListWidget;
	QHBoxLayout *layout = new QHBoxLayout;
	QHBoxLayout *bottomLay = new QHBoxLayout;
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QPushButton *removeDownloadButton = new QPushButton(tr("Vider la liste"));
	QPushButton *dlFileButton = new QPushButton("Télécharger");
	//dlFileButton->setFixedWidth(30);
	line = new QLineEdit(this);
	label = new QLabel(tr("0 téléchargements"));

	resize(650, 400);

	listWidget->setAlternatingRowColors (true);
	listWidget->setIconSize(QSize(32, 32));
	bottomLay->addWidget(line);
	bottomLay->addWidget(dlFileButton);
	layout->addWidget(removeDownloadButton);
	layout->addStretch();
	layout->addWidget(label);
	mainLayout->addLayout(layout);
	mainLayout->addWidget(listWidget);
	mainLayout->addLayout(bottomLay);
	setLayout(mainLayout);

	connect(removeDownloadButton, SIGNAL(clicked()), this, SLOT(clearDownloads()));
	connect(dlFileButton, SIGNAL(clicked()), this, SLOT(downloadFile()));
	connect(line, SIGNAL(returnPressed()), this, SLOT(downloadFile()));

	QSettings dls(Browser::instance()->iniFile("Download.ini"), QSettings::IniFormat);
	urlList = dls.value("Url").toStringList();
	localList = dls.value("Local").toStringList();
	stateList = dls.value("States").toStringList();
	nameList = dls.value("Names").toStringList();
	QStringList urls = urlList;
	urls.removeDuplicates();
	line->setCompleter(new QCompleter(urls));
	if (!urlList.isEmpty())
	{
		int i = 0;
		foreach(QString url, urlList)
		{
			if (stateList.at(i) == "1")
			{
				DownloadWidget *down = new DownloadWidget(url, localList.at(i), "1", nameList.at(i));
				connect(down, SIGNAL(retry()), this, SLOT(retryDownload()));
				dlWidgets.append(down);
				listWidget->setItemWidget(new QListWidgetItem(QIcon(QPixmap(qApp->applicationDirPath() + "/themes/" + themeDir + "/ok.png").scaled(32, 32)), "", listWidget, 0), down);
			}
			else
			{
				DownloadWidget *down = new DownloadWidget(url, localList.at(i), "0", nameList.at(i));
				connect(down, SIGNAL(retry()), this, SLOT(retryDownload()));
				dlWidgets.append(down);
				listWidget->setItemWidget(new QListWidgetItem(QIcon(QPixmap(qApp->applicationDirPath() + "/themes/" + themeDir + "/canceled.png").scaled(32, 32)), "", listWidget, 0), down);
			}
			oldDownloads++;
			i++;
		}
	}
	label->setText(tr("%1 téléchargements").arg(listWidget->count()));
}

void downloadManager::downloadFile()
{
	QString text = line->text();
	if(text.left(7) != "http://" && text.left(6) != "ftp://")
	{
		text = "http://" + text;
	}
	if(downloadFile(QUrl(text)))
	{
		line->clear();
	}
}

bool downloadManager::downloadFile(QUrl url, QString file)
{
	QString path;
	HttpGet *getter = new HttpGet;
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	QString themeDir = settings.value("theme").toString();
	QFileInfo info(path);
	if(file.isEmpty())
	{
		file = info.completeBaseName();
		if(!file.isEmpty())
		{
			file += "." + info.suffix();
		}
	}
	if(file.isEmpty() && url.toString().split("/").last().size() > 5)
	{
		file = url.toString().split("/").last();
	}
	if (QMessageBox::question(this, tr("Télécharger le fichier ?"), tr("<html>Voulez vous télécharger <strong>%1</strong>?</html>").arg(file + url.toString().left(url.toString().size() * (file.isEmpty()))), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		if (settings.value("askForDir").toBool())
		{
			path = QFileDialog::getSaveFileName(this, tr("Télécharger un fichier"), QDir::homePath() + tr("/Desktop/") + file, "All (*.*)");
			if (path.isEmpty())
			{
				return false;
			}
		}
		else
		{
			path = settings.value("downloadIn").toString();
		}
		localList.prepend(path);
	}
	else
	{
		return true;
	}
	//QStringList list = path.split("/");
	QString name = path.split("/").last();
	nameList.prepend(name);
	getterList.prepend(getter);
	urlList.prepend(url.toString());
	stateList.prepend("?");

	QStringList urls = urlList;
	urls.removeDuplicates();
	line->setCompleter(new QCompleter(urls));

	wait(500);

	DownloadWidget *down = new DownloadWidget(urlList.first(), localList.first(), stateList.first(), nameList.first());
	dlWidgets.prepend(down);
	listWidget->insertItem(0, new QListWidgetItem(QIcon(QPixmap(qApp->applicationDirPath() + "/themes/" + themeDir + "/down.png").scaled(32, 32)), ""));
	listWidget->setItemWidget(listWidget->item(0), down);

	connect(getter, SIGNAL(done(bool)), this, SLOT(downloadDone(bool)));
	connect(getter, SIGNAL(done(bool)), down, SLOT(done(bool)));
	connect(getter, SIGNAL(progress(qint64, qint64)), down, SLOT(update(qint64, qint64)));
	connect(down, SIGNAL(canceled()), getter, SLOT(cancel()));
	connect(down, SIGNAL(retry()), this, SLOT(retryDownload()));

	currentDownload++;
	if (isHidden())
	{
		show();
	}
	if (!getter->getFile(url.toString(), path) && getter->error() != 0)
	{
		QMessageBox::critical(this, tr("Opération impossible"), tr("Impossible de télécharger le fichier !\n Erreur %1").arg(getter->error()));
		stateList.replace(0, "0");
		listWidget->item(0)->setIcon(QIcon(QPixmap(qApp->applicationDirPath() + "/themes/" + themeDir + "/canceled.png").scaled(32, 32)));
		return false;
	}
	label->setText(tr("%1 téléchargements").arg(listWidget->count()));
	update();
	return true;
}

void downloadManager::retryDownload()
{
	DownloadWidget *down = qobject_cast<DownloadWidget *>(sender());
	downloadFile(down->fileUrl());
}

void downloadManager::downloadDone(bool error)
{
	int index = getterList.indexOf(qobject_cast<HttpGet *>(sender()));
	if (error)
	{
		stateList.replace(index, "0");
		listWidget->item(index)->setIcon(QIcon(QPixmap(qApp->applicationDirPath() + "/themes/" + themeDir + "/canceled.png").scaled(32, 32)));
	}
	else
	{
		stateList.replace(index, "1");
		listWidget->item(index)->setIcon(QIcon(QPixmap(qApp->applicationDirPath() + "/themes/" + themeDir + "/ok.png").scaled(32, 32)));
	}
	currentDownload--;
	update();
}

void downloadManager::clearDownloads()
{
	if (currentDownload != 0)
	{
		int close = QMessageBox::critical(this, tr("Attention"), tr("Des téléchargements sont en cours, voulez vous les annuler ?"), QMessageBox::Yes | QMessageBox::No);
		if (close == QMessageBox::No)
		{
			return;
		}
	}
	foreach(HttpGet *get, getterList)
	{
		get->cancel();
	}
	nameList.clear();
	urlList.clear();
	localList.clear();
	stateList.clear();
	dlWidgets.clear();
	getterList.clear();
	currentDownload = 0;
	listWidget->clear();
	label->setText(tr("%1 téléchargements").arg(listWidget->count()));
}


void downloadManager::closeEvent(QCloseEvent *event)
{
	if(currentDownload != 0 && canClose)
	{
		int close = QMessageBox::critical(this, tr("Attention"), tr("Des téléchargements sont en cours, voulez vous les annuler ?"), QMessageBox::Yes | QMessageBox::No);
		if (close == QMessageBox::Yes)
		{
			QSettings dls(Browser::instance()->iniFile("Download.ini"), QSettings::IniFormat);
			dls.setValue("Url", urlList);
			dls.setValue("Local", localList);
			dls.setValue("States", stateList);
			dls.setValue("Names", nameList);
			emit closed();
			//QMessageBox::critical(this, tr("Opération impossible"), tr("Impossible de fermer les telechargement (pas encore codé =/)"));
		}
		else
		{
			event->ignore();
		}
	}
	else
	{
		QSettings dls(Browser::instance()->iniFile("Download.ini"), QSettings::IniFormat);
		dls.setValue("Url", urlList);
		dls.setValue("Local", localList);
		dls.setValue("States", stateList);
		dls.setValue("Names", nameList);
		hide();
		if (canClose) {
			emit closed();
		}
	}
}

void downloadManager::setClosable(bool closable)
{
	canClose = closable;
	if (closable && currentDownload != 0)
	{
		show();
	}
}

bool downloadManager::downloading()
{
	return currentDownload != 0 ;
}

void downloadManager::wait(int msec)
{
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
	timer.start(msec);
	loop.exec();
}
