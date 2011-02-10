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

#include "cleardialog.h"
#include "Browser.h"

ClearDialog::ClearDialog(QWidget *parent) :
	QDialog(parent)
{
	mainLabel = new QLabel(tr("Données à effacer : "));
	history = new QCheckBox(tr("Historique de navigation"));
	bookMarks = new QCheckBox(tr("Favoris"));
	cookies = new QCheckBox(tr("Cookies"));
	pass = new QCheckBox(tr("Mots de passe enregistés"));
	downloads = new QCheckBox(tr("Historique des téléchargements"));
	cached = new QCheckBox(tr("Cache web"));
	icons = new QCheckBox(tr("Favicones des pages visitées"));
	clear = new QPushButton(tr("Effacer"));
	cancel = new QPushButton(tr("Annuler"));
	label = new QLabel;

	history->setChecked(true);
	cookies->setChecked(true);
	downloads->setChecked(true);
	cached->setChecked(true);
	icons->setChecked(true);

	QVBoxLayout *mainLay = new QVBoxLayout;
	mainLay->addWidget(mainLabel);
	mainLay->addWidget(history);
	mainLay->addWidget(bookMarks);
	mainLay->addWidget(cookies);
	mainLay->addWidget(pass);
	mainLay->addWidget(downloads);
	mainLay->addWidget(cached);
	mainLay->addWidget(icons);

	QHBoxLayout *hLay = new QHBoxLayout;
	hLay->addWidget(clear);
	hLay->addWidget(cancel);

	label->hide();

	mainLay->addLayout(hLay);
	mainLay->addWidget(label);
	setFixedSize(190, 200);

	connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
	connect(clear, SIGNAL(clicked()), this, SLOT(clearData()));

	setLayout(mainLay);
}

void ClearDialog::clearData()
{
	setFixedSize(190, 225);
	setEnabled(false);

	label->setText(tr("Effacement en cours ..."));
	label->show();

	if(history->isChecked())
		Browser::instance()->hManager()->clear();

	if(bookMarks->isChecked())
		Browser::instance()->bmManager()->clear();

	if(cookies->isChecked())
		Browser::instance()->cJar()->clear();

	if(cookies->isChecked())
		Browser::instance()->passManager()->clear();

	if(downloads->isChecked())
		Browser::instance()->dlManager()->clearDownloads();

	if(cached->isChecked())
		QWebSettings::globalSettings()->clearMemoryCaches();

	if(icons->isChecked())
		QWebSettings::globalSettings()->clearIconDatabase();

	setEnabled(true);
	label->setText(tr("Données effacées !"));
}
