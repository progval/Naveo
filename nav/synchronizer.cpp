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

//#define FROM_FILES

#include "Browser.h"
#include "synchronizer.h"

Synchronizer::Synchronizer()
{
	ftp = new QFtp(this);
	isConnected = false;
	ui = true;
	autoConnectionfailed = false;
	file = 0;
	dlDone = 0;
	progress = new QProgressDialog;
	progress->setWindowTitle(tr("Patientez ..."));
	progress->setWindowIcon(QIcon(QString(":/icon.png")));
	progress->setRange(0,0);
	progress->findChild<QPushButton *>()->hide();
	connect(ftp, SIGNAL(commandFinished(int,bool)), this, SLOT(commandFinished(int,bool)));
	connect(ftp, SIGNAL(listInfo(QUrlInfo)), this, SLOT(addToList(QUrlInfo)));
	//connect(this, SIGNAL(needPass()), this, SLOT(dlPass()));
	serverIndex = 0;
	settings = new QSettings(qApp->applicationDirPath() + "/server.txt", QSettings::IniFormat);
	names<<settings->value("list").toStringList();

	#ifdef USE_GAN_H
		host<<gan_::ftp::serverHost();
		log<<gan_::ftp::serverLog();
		passwords<<gan_::ftp::serverPass();
	#endif

	foreach(QString str, names)
	{
		settings->beginGroup(str);
		host<<settings->value("host").toString();
		log<<settings->value("log").toString();
		passwords<<settings->value("pass").toString();
		settings->endGroup();
	}

	#ifdef FROM_FILES
		cout<<"synchronise on THIS computer only !"<<endl;
	#endif

	#ifdef USE_GAN_H
		names.push_front(tr("Serveur officiel"));
	#endif

	settings = new QSettings(qApp->applicationDirPath() + "/synchro.ini", QSettings::IniFormat);






	//settings->setValue("auto", false);






	if(names.count() != 0)
	{
		if(settings->value("auto").toBool())
		{
			ui = false;
			exec();
		}
	}
}

void Synchronizer::setVisible()
{
	ui = true;
}

bool Synchronizer::connected()
{
	return isConnected;
}

QString Synchronizer::user()
{
	return newName;
}

void Synchronizer::exec()
{
	disconnect();
	cout<<"connecting to host"<<endl;
	ftp->connectToHost(host.at(serverIndex));
	ftp->login(log.at(serverIndex), passwords.at(serverIndex));
	ftp->cd("/synchro/");
	ftp->list();
	if(ui)
	{
		progress->setLabelText(tr("Connexion au serveur ..."));
		progress->open();
	}
}

void Synchronizer::disconnect()
{
	if(ftp->state() != QFtp::Unconnected)
	{
		ftp->abort();
		ftp->close();
		cout<<"closing connection ... "<<endl;
	}
	emit statusChanged(false);
	newName.clear();
	pass.clear();
	isConnected = false;
}

QStringList Synchronizer::serverList()
{
	return names;
}

void Synchronizer::addToList(const QUrlInfo &urlInfo)
{
	if(urlInfo.isDir())
	{
		dir<<urlInfo.name();
	}
	else
	{
		files<<urlInfo.name();
	}
}



bool Synchronizer::checkPass()
{
	QByteArray array;

	#ifndef FROM_FILES
		file->close();
		if(ftp->error())
		{
			cout<<"error : "<<qPrintable(ftp->errorString())<<endl;
			return false;
		}
		if(!file->open(QIODevice::ReadOnly))
		{
			return false;
		}
		array = file->readAll();
		file->close();
		file->remove();
	#else
		if(!file->open(QIODevice::ReadOnly))
		{
			return false;
		}
		array = file->readAll();
		file->close();
	#endif

	if(hash(pass.toAscii()) != array)
	{
		return false;
	}

	return true;
}

QByteArray Synchronizer::hash(QByteArray array)
{
	#ifdef USE_GAN_H
		return gan_::encryption::hash(array);
	#else
		return QCryptographicHash::hash(array, QCryptographicHash::Md5).toHex();
	#endif
}

void Synchronizer::import()
{
	cout<<"import"<<endl;
	if (ui)
	{
		progress->setLabelText(tr("Importation ..."));
		progress->open();
	}

	bool i = false;


	cout<<"settings"<<endl;
	file = new QFile(qApp->applicationDirPath() + "/Options_");
	i = file->open(QIODevice::WriteOnly);
	ftp->get("1_", file);
	while(ftp->currentCommand() == QFtp::Get && i && !ftp->error())
	{
		Browser::instance()->processEvents();
	}
	file->close();
	if(ftp->error())
	{
		cout<<"error : "<<qPrintable(ftp->errorString())<<endl;
	}
	else
	{
		quickWrite("Options.ini", encryptFromFile("Options_"));
	}


	cout<<"cookies"<<endl;
	file = new QFile(qApp->applicationDirPath() + "/cookies_");
	i = file->open(QIODevice::WriteOnly);
	ftp->get("2_", file);
	while(ftp->currentCommand() == QFtp::Get && i && !ftp->error())
	{
		Browser::instance()->processEvents();
	}
	file->close();
	if(ftp->error())
	{
		cout<<"error : "<<qPrintable(ftp->errorString())<<endl;
	}
	else
	{
		quickWrite("cookies.ini", encryptFromFile("cookies_"));
	}



	cout<<"bookmarks"<<endl;
	file = new QFile(qApp->applicationDirPath() + "/BookMarks_");
	i = file->open(QIODevice::WriteOnly);
	ftp->get("3_", file);
	while(ftp->currentCommand() == QFtp::Get && i && !ftp->error())
	{
		Browser::instance()->processEvents();
	}
	file->close();
	if(ftp->error())
	{
		cout<<"error : "<<qPrintable(ftp->errorString())<<endl;
	}
	else
	{
		quickWrite("BookMarks.ini", encryptFromFile("BookMarks_"));
	}

	cout<<"forms"<<endl;
	file = new QFile(qApp->applicationDirPath() + "/forms_");
	i = file->open(QIODevice::WriteOnly);
	ftp->get("4_", file);
	while(ftp->currentCommand() == QFtp::Get && i && !ftp->error())
	{
		Browser::instance()->processEvents();
	}
	file->close();

	if(ftp->error())
	{
		cout<<"error : "<<qPrintable(ftp->errorString())<<endl;
	}
	else
	{
		quickWrite("forms.txt", encryptFromFile("forms_"));
	}


	progress->accept();
	if(ui)
	{
		QMessageBox::information(0, tr("Importation"), tr("Importation reussie !"));
	}

	emit imported();
}

void Synchronizer::exportSettings()
{
	if(isConnected)
	{
		if (ui)
		{
			progress->setLabelText(tr("Exportation ..."));
			progress->open();
		}
		cout<<"export"<<endl;

		file = new QFile(Browser::instance()->iniFile());
		file->open(QIODevice::ReadOnly);

		ftp->put(crypt(file->readAll()), "1_");
		cout<<"hosting settings file"<<endl;
		while(ftp->currentCommand() == QFtp::Put && !ftp->error())
		{
			Browser::instance()->processEvents();
		}
		file->close();


		file = new QFile(Browser::instance()->iniFile("cookies.txt"));
		file->open(QIODevice::ReadOnly);

		#ifdef USE_GAN_H
			ftp->put(crypt(gan_::encryption::uncrypt(file->readAll())), "2_");
		#else
			ftp->put(crypt(file->readAll()), "2_");
		#endif
		cout<<"hosting cookies"<<endl;
		while(ftp->currentCommand() == QFtp::Put && !ftp->error())
		{
			Browser::instance()->processEvents();
		};

		file->close();


		file = new QFile(Browser::instance()->iniFile("BookMarks.ini"));
		file->open(QIODevice::ReadOnly);

		ftp->put(crypt(file->readAll()), "3_");
		cout<<"hosting bookMarks"<<endl;
		while(ftp->currentCommand() == QFtp::Put && !ftp->error())
		{
			Browser::instance()->processEvents();
		}

		file->close();

		file = new QFile(Browser::instance()->iniFile("forms.txt"));
		file->open(QIODevice::ReadOnly);

		#ifdef USE_GAN_H
			ftp->put(crypt(gan_::encryption::uncrypt(file->readAll())), "4_");
		#else
			ftp->put(crypt(file->readAll()), "4_");
		#endif
		cout<<"hosting forms"<<endl;
		while(ftp->currentCommand() == QFtp::Put && !ftp->error())
		{
			Browser::instance()->processEvents();
		}

		file->close();

		cout<<"files hosted"<<endl;

		progress->accept();
		if(ui)
		{
			QMessageBox::information(0, tr("Exportation"), tr("Exportation reussie !"));
		}

	}
}

void Synchronizer::setServer(int index)
{
	serverIndex = index;
}

void Synchronizer::close()
{
	if(!isConnected)
	{
		settings->setValue("auto", false);
	}
	ui = false;
	#ifdef USE_GAN_H
		if(settings->value("auto").toBool())
		{
			exportSettings();
			gan_::ftp::saveConnectionSettings(newName, pass, Browser::instance()->currentSession());
		}
	#endif
	ftp->close();
	ftp->abort();
}


void Synchronizer::commandFinished(int, bool error)
{
	if(ftp->currentCommand() == QFtp::Login)
	{
		cout<<"logged on server"<<endl;
		waitingPass = false;
		#ifdef USE_GAN_H
			if(settings->value("auto").toBool() && !autoConnectionfailed)
			{
				QStringList list = gan_::ftp::autoConnect(Browser::instance()->currentSession());;
				pass = list.at(1);
				newName = list.at(0);
				file = new QFile(qApp->applicationDirPath() + "/pass_");
				file->open(QIODevice::WriteOnly);
				waitingPass = true;
				ftp->cd(newName);
				ftp->get("0_", file);
			}
		#endif
		return;
	}
	if(ftp->currentCommand() == QFtp::List)
	{
		progress->accept();
		if(isConnected)
		{
			return;
		}
		if(error)
		{
			QMessageBox::critical(0, tr("Connexion impossible"), tr("Impossible de se connecter à la BDD, reessayez plus tard."));
			return;
		}
		if(!ui) {
			return;
		}
		QDialog *dial = new QDialog;
		dial->setWindowIcon(QIcon(QString(":/icon.png")));
		dial->setWindowTitle(tr("Naveo - Synchronisation"));
		QVBoxLayout lay;
		QLineEdit *nameEdit = new QLineEdit;
		QLineEdit *passEdit = new QLineEdit;
		passEdit->setEchoMode(QLineEdit::Password);
		QLabel *l1 = new QLabel(tr("Identifiant : "));
		QLabel *l2 = new QLabel(tr("Mot de passe : "));
		lay.addWidget(l1);
		lay.addWidget(nameEdit);
		lay.addWidget(l2);
		lay.addWidget(passEdit);
		QHBoxLayout lay2;
		QPushButton *connectButton = new QPushButton(tr("Connexion !"));
		QPushButton *accountButton = new QPushButton(tr("Créer un compte"));
		connectButton->setCheckable(true);
		accountButton->setCheckable(true);
		connect(connectButton, SIGNAL(clicked()), dial, SLOT(accept()));
		connect(accountButton, SIGNAL(clicked()), dial, SLOT(accept()));
		lay2.addWidget(connectButton);
		lay2.addWidget(accountButton);
		lay.addLayout(&lay2);
		dial->setLayout(&lay);
		dial->exec();
		if(!dial->result())
		{
			return;
		}
		pass = passEdit->text();
		if(connectButton->isChecked())
		{
			newName = nameEdit->text();
			file = new QFile(qApp->applicationDirPath() + "/pass_");
			file->open(QIODevice::WriteOnly);
			waitingPass = true;
			ftp->cd(nameEdit->text());
			ftp->get("0_", file);
		}
		if(accountButton->isChecked())
		{
			bool ok = false;
			QString name = QInputDialog::getText(0, tr("Création d'un compte"), tr("Identifiant :"), QLineEdit::Normal, QString(), &ok);
			if(!ok) {return;}
			while(dir.contains(name))
			{
				QMessageBox::critical(0, tr("Identifiant incorrect"), tr("Cet identifiant est déjà utilisé, choisissez en un autre."));
				name = QInputDialog::getText(0, tr("Création d'un compte"), tr("Identifiant :"), QLineEdit::Normal, QString(), &ok);
				if(!ok) {return;}
			}
			pass = "none";
			newName = name;
			ftp->mkdir(name);
		}
	}
	if(ftp->currentCommand() == QFtp::Mkdir)
	{
		if(error)
		{
			cout<<"not created : "<<qPrintable(ftp->errorString())<<endl;
			return;
		}
		if(pass == "none")
		{
			bool ok = false;
			pass = QInputDialog::getText(0, tr("Création d'un compte"), tr("Mot de passe :"), QLineEdit::Password, QString(), &ok);
			while(pass.length() < 4 || pass.length() > 31)
			{
				pass = QInputDialog::getText(0, tr("Création d'un compte"), tr("Mot de passe :\n/!\\ Votre mot de passe doit faire entre 3 et 32 caractères !"), QLineEdit::Password, QString(), &ok);
				if(!ok) {return;}
			}
			if(!ok) {return;}
			QString secondPass = QInputDialog::getText(0, tr("Création d'un compte"), tr("Mot de passe (confirmez) :"), QLineEdit::Password, QString(), &ok);
			if(!ok) {return;}
			while(pass != secondPass)
			{
				secondPass = QInputDialog::getText(0, tr("Création d'un compte"), tr("Mot de passe (confirmez) :\n/!\\ Vous n'avez pas entré 2 fois la même chose !"), QLineEdit::Password, QString(), &ok);
				if(!ok) {return;}
			}
			progress->setLabelText(tr("Identification ..."));
			progress->open();

			#ifndef FROM_FILES
				ftp->put(hash(pass.toAscii()), QString("%1/0_").arg(newName));
				while(ftp->currentCommand() == QFtp::Put && !ftp->error())
				{
					Browser::instance()->processEvents();
				}
			#else
				file = new QFile(qApp->applicationDirPath() + "/pass_");
				bool i = file->open(QIODevice::WriteOnly);
				file->write(hash(pass.toAscii()));
				file->close();
			#endif

			progress->accept();

			#ifndef FROM_FILES
				if(ftp->error())
			#else
				if(!i)
			#endif
			{
				QMessageBox::critical(0, tr("Création impossible"), tr("Impossible de créer votre compte : %1").arg(ftp->errorString()));
				return;
			}
			QMessageBox::information(0, tr("Création effectuée"), tr("Votre compte a été créé sans problèmes !\nVous devez maintenant vous identifier."));
			dir.clear();
			files.clear();
			ftp->list();
			return;
		}
	}
	if(ftp->currentCommand() == QFtp::Cd)
	{
		if(waitingPass && error)
		{
			QMessageBox::critical(0, tr("Connexion impossible"), tr("Connexion impossible : Verifiez votre identifiant."));
			waitingPass = false;
		}
	}
	if(ftp->currentCommand() == QFtp::Get)
	{
		if(waitingPass)
		{
			if(checkPass())
			{
				isConnected = true;
				cout<<"connected to account"<<endl;
				if(ui)
				{
					QMessageBox::information(0, tr("Connexion effectuée"), tr("Connexion effectuée sans problèmes !"));
				}
				emit loggedIn();
				emit statusChanged(true);
			}
			else
			{
				QMessageBox::critical(0, tr("Connexion impossible"), tr("Connexion impossible : Verifiez votre mot de passe."));
				autoConnectionfailed = true;
			}
			waitingPass = false;
			if(settings->value("auto").toBool())
			{
				ui = true;
			}
		}
	}
}

QByteArray Synchronizer::crypt(QByteArray array)
{
	QByteArray byteArray;
	QByteArray hash = QCryptographicHash::hash(pass.toAscii(), QCryptographicHash::Md5);
	QByteArray newHash;
	for (int i = 0; i != hash.count(); i++)
	{
		newHash.push_back(hash[i] ^ pass.toAscii().at(i % (pass.count() - 1)));
	}
	for (int i = 0; i != array.count(); i++)
	{
		byteArray.push_back(array[i] ^ pass.toAscii().at(i % (pass.count() - 1)));
	}
	return byteArray;
}

void Synchronizer::cryptInFile(QByteArray array, QString fileName)
{
	QFile f(Browser::instance()->iniFile(fileName));
	f.open(QIODevice::WriteOnly);
	f.write(crypt(array));
	f.close();
}

QByteArray Synchronizer::encryptFromFile(QString fileName)
{
	QByteArray array;
	QFile f(Browser::instance()->iniFile(fileName));
	if(!f.open(QIODevice::ReadOnly))
	{
		cout<<"error : "<<qPrintable(f.errorString())<<endl;
	}
	array = crypt(f.readAll());
	f.close();
	return array;
}

void Synchronizer::quickWrite(QString fileName, QByteArray array)
{
	QFile f(Browser::instance()->iniFile(fileName));
	cout<<qPrintable(Browser::instance()->iniFile(fileName))<<endl;
	f.open(QIODevice::WriteOnly);
	f.write(array);
	f.close();
}




