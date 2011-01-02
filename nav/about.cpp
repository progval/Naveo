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


#include "about.h"
#include "Browser.h"

About::About(QWidget *parent) :
	QDialog(parent)
{
	cout<<qPrintable(qApp->applicationDirPath())<<endl;

	QFile file(":/about_" + QLocale::system().name().left(2) + ".txt");
	if (!file.open(QIODevice::ReadOnly)){
		return;}
	QFile build(":/build.txt");
	if (!build.open(QIODevice::ReadOnly)){
		return;}
	QFile license(":/gpl.txt");
	if (!license.open(QIODevice::ReadOnly)){
		return;}

	QString OS;
	#ifdef Q_WS_WIN
	OS = "Windows";
	#endif
	#ifdef Q_WS_X11
	OS = "X11";
	#endif
	#ifdef Q_WS_MAC
	OS = "Mac OS X";
	#endif
	QVBoxLayout *vLayout = new QVBoxLayout;
	QHBoxLayout *hLayout = new QHBoxLayout;
	QHBoxLayout *topLayout = new QHBoxLayout;
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	QPushButton *button = new QPushButton(tr("Fermer"));
	tab = new QTabWidget;

	QLabel *infoLabel = new QLabel(QString("<strong>Naveo</strong>  %1").arg(VERSION));
	QLabel *icon = new QLabel;
	icon->setPixmap(QPixmap(":/icon.ico").scaled(48, 48));
	icon->setFixedSize(48, 48);

	QPlainTextEdit * edit = new QPlainTextEdit;
	edit->setReadOnly(true);

	edit->setPlainText(QString(license.readAll()));

	QLabel *label = new QLabel(QString(file.readAll()).arg(VERSION).arg(OS).arg(__DATE__).arg(__TIME__).arg(QString(build.readAll())).arg(QT_VERSION_STR));

	connect(label, SIGNAL(linkActivated(QString)), this, SLOT(openLink(QString)));

	QLabel *image = new QLabel;
	image->setPixmap(QPixmap(":/icon.ico"));

	QWidget *first = new QWidget;
	hLayout->addWidget(image);
	hLayout->addWidget(label);

	first->setLayout(hLayout);

	tab->addTab(first, tr("A propos"));
	tab->addTab(edit, tr("License"));

	topLayout->setContentsMargins(15, 0, 0, 0);
	topLayout->addWidget(icon);
	topLayout->addWidget(infoLabel);

	vLayout->addLayout(topLayout);
	vLayout->addWidget(tab);
	//vLayout->addStretch();

	buttonLayout->addStretch();
	buttonLayout->addWidget(button);
	vLayout->addLayout(buttonLayout);

	connect(button, SIGNAL(clicked()), this, SLOT(close()));
	setWindowIcon(QIcon(":/icon.png"));
	setLayout(vLayout);

	resize(600, 600);
}

void About::openLink(QString link)
{
	if(link == "aboutQt")
	{
		Browser::instance()->aboutQt();
	}
	else if (link == "license")
	{
		tab->setCurrentIndex(1);
	}
}
