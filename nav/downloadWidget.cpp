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


#include "downloadWidget.h"
#include "Browser.h"


DownloadWidget::DownloadWidget(QString Url, QString Local, QString State, QString Name)
{
	url = Url;
	name = Name;
	local = Local;
	setFixedHeight(32);
	waiting = true;
	progress = new QProgressBar;
	progress->setStyle(new QCleanlooksStyle);
	QSettings settings(naveoConfigurationPath + "/Options.ini", QSettings::IniFormat);
	QString themeDir = settings.value("theme").toString();
	layout = new QHBoxLayout;
	layout->setContentsMargins(0, 1, 0, 1);
	nameLabel = new QLabel("<strong>" + Name + "</strong><br><sup>" + url + "</sup>");
	timeLabel = new QLabel;
	layout->addWidget(nameLabel);
	layout->addWidget(timeLabel);
	layout->addWidget(progress);
	cancelButton = new QPushButton;
	cancelButton->setFlat(true);
	cancelButton->setFixedSize(32, 32);
	cancelButton->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/stop.png"));
	openButton = new QPushButton;
	openButton->setFlat(true);
	openButton->setFixedSize(32, 32);
	openButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon));
	retryButton = new QPushButton;
	retryButton->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/reload.png"));
	retryButton->setFlat(true);
	retryButton->setFixedSize(32, 32);
	connect(openButton, SIGNAL(clicked()), this, SLOT(open()));
	connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(canceled()));
	connect(retryButton, SIGNAL(clicked()), this, SIGNAL(retry()));
	layout->addWidget(cancelButton);
	layout->addWidget(openButton);
	layout->addWidget(retryButton);
	progress->setRange(0, 0);
	sec = -1;
	timer = new QTimer;
	timer->setInterval(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
	if(State != "0")
	{
		retryButton->hide();
	}
	if (State != "?")
	{
		progress->hide();
		cancelButton->hide();
		timeLabel->hide();
		if (State == "0")
		{
			openButton->hide();
		}
	}
	else
	{
		openButton->hide();
	}
	setLayout(layout);
}

QString DownloadWidget::fileUrl()
{
	return url;
}

void DownloadWidget::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu;
	if(retryButton->isVisible())
	{
		QAction *Action = new QAction(retryButton->icon(), tr("Reessayer"), this);
		connect(Action, SIGNAL(triggered()), this, SIGNAL(retry()));
		menu.addAction(Action);
	}
	else if(openButton->isVisible())
	{
		QAction *Action = new QAction(openButton->icon(), tr("Ouvrir"), this);
		connect(Action, SIGNAL(triggered()), this, SLOT(open()));
		menu.addAction(Action);
	}
	else
	{
		QAction *Action = new QAction(cancelButton->icon(), tr("Stop"), this);
		connect(Action, SIGNAL(triggered()), this, SIGNAL(canceled()));
		menu.addAction(Action);
	}
	menu.exec(mapToGlobal(event->pos()));
}

void DownloadWidget::updateTime()
{
	progress->setValue((int)writed);
	int seconds = (int)ceil(((time.elapsed()/writed)  * total) / 1000);
	if(sec != -1)
	{
		seconds = ((9 * sec) + seconds) / 10;
	}
	else
	{
		seconds += seconds / 10;
	}
	sec = seconds;
	if(sec >= 60)
	{
		timeLabel->setText(tr("%1 min %2 sec restantes").arg(seconds/60).arg(seconds%60));
	}
	else
	{
		timeLabel->setText(tr("%1 secondes restantes").arg(seconds));
	}
}

void DownloadWidget::update(qint64 prog, qint64 size)
{
	if (waiting)
	{
		progress->setRange(0, size);
		total = size;
		timer->start();
		time.start();
		waiting = false;
	}
	writed = prog;
}

void DownloadWidget::open()
{
	QDesktopServices::openUrl(QUrl(local));
}

void DownloadWidget::done(bool error)
{
	progress->hide();
	timeLabel->hide();
	timer->stop();
	layout->insertStretch(2);
	cancelButton->hide();
	if (!error)
	{
		cout<<"done in "<<time.elapsed() / 1000<<" sec"<<endl;
		openButton->show();
	}
	else
	{
		retryButton->show();
	}
}
