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


#include "settingsDialog.h"
#include "Browser.h"
#include "httpget.h"
#include "ui_pluginWindow.h"

settingDialog::settingDialog(Synchronizer *synchronizer, PluginManager *pm)
{
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	setupUi(this);
	pushButton_2->hide();
	#ifdef Q_WS_WIN
	if (QSysInfo::WindowsVersion >= QSysInfo::WV_VISTA) {
		checkBox_13->setEnabled(true);
	}
	#endif
	QStringList itemList;
	if (itemList.isEmpty())
	{
		QDir dir = QDir(qApp->applicationDirPath());
		dir.cd("themes");
		itemList<<dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
	}
	if (!itemList.isEmpty())
	{
		int i = 0;
		while(i != itemList.count())
		{
			new QListWidgetItem(QIcon(qApp->applicationDirPath() + "/themes/" + itemList[i] + "/tIcon.png"), itemList[i], listWidget, 0);
			i++;
		}
	}
	syn = synchronizer;
	plugs = pm;
	for(int i = 0; i != plugs->pluginsList().count(); i++)
	{
		QIcon icon(":/plug.png");
		if(!plugs->pluginsList()[i].activated)
		{
			icon = QIcon(":/desactivated.png");
		}
		new QListWidgetItem(icon, plugs->pluginsList()[i].name, listWidget_3, 0);
		if(plugs->pluginsList()[i].removed)
		{
			listWidget_3->item(listWidget_3->count() - 1)->setFlags(Qt::NoItemFlags);
		}
	}
	listWidget_4->setCurrentRow(0);
	pushButton_7->setEnabled(false);
	connect(synchronizer, SIGNAL(imported()), this, SLOT(updateAll()));
	connect(synchronizer, SIGNAL(loggedIn()), this, SLOT(updateAll()));
	connect(radioButton_3, SIGNAL(toggled(bool)), this, SLOT(updateCheck()));
	connect(radioButton_5, SIGNAL(toggled(bool)), this, SLOT(updateCheck()));
	connect(radioButton_6, SIGNAL(toggled(bool)), this, SLOT(updateCheck()));
	connect(syn, SIGNAL(statusChanged(bool)), this, SLOT(synStatusChanded(bool)));
	updateAll();
	on_listWidget_3_currentRowChanged(listWidget_3->currentRow());
	updateCheck();
}

void settingDialog::updateAll()
{
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	lineEdit_2->setText(settings.value("downloadIn").toString());
	lineEdit_3->setText(settings.value("newUrl").toString());
	lineEdit_4->setText(settings.value("tabUrl").toString());
	checkBox->setChecked(settings.value("dlInk").toBool());
	checkBox_2->setChecked(settings.value("showHome").toBool());
	checkBox_3->setChecked(settings.value("showStop").toBool());
	checkBox_4->setChecked(settings.value("image").toBool());
	checkBox_5->setChecked(settings.value("javascript").toBool());
	checkBox_6->setChecked(settings.value("changeTab").toBool());
	checkBox_7->setChecked(settings.value("google").toBool());
	checkBox_8->setChecked(settings.value("eraseHistory").toBool());
	checkBox_9->setChecked(settings.value("private").toBool());
	checkBox_10->setChecked(!settings.value("perso").toBool());
	checkBox_13->setChecked(settings.value("transparency").toBool());
	checkBox_14->setChecked(settings.value("block").toBool());
	checkBox_15->setChecked(settings.value("speedDial").toBool());
	checkBox_16->setChecked(settings.value("close").toBool());
	checkBox_17->setChecked(settings.value("toolbarTranparency").toBool());
	checkBox_18->setChecked(settings.value("dark").toBool());
	checkBox_20->setChecked(settings.value("flash").toBool());
	radioButton->setChecked(settings.value("saveTab").toBool());
	radioButton_2->setChecked(settings.value("openHome").toBool());
	radioButton_3->setChecked(settings.value("openUrl").toBool());
	radioButton_4->setChecked(settings.value("tabOpenHome").toBool());
	radioButton_5->setChecked(!settings.value("tabOpenHome").toBool());
	radioButton_6->setChecked(settings.value("askForDir").toBool());
	radioButton_7->setChecked(!settings.value("askForDir").toBool());
	spinBox->setValue((int)settings.value("zoom").toDouble()*100);
	comboBox_2->setCurrentIndex(settings.value("posPerso").toInt());
	comboBox_3->setCurrentIndex(settings.value("posNav").toInt());
	comboBox_4->setCurrentIndex(settings.value("saveHistory").toInt());
	comboBox_5->setCurrentIndex(settings.value("saveCookies").toInt());
	if (settings.value("Home").toString() != "Naveo::dial") {
	comboBox_6->addItem(settings.value("Home").toString());
	comboBox_6->setCurrentIndex(1);}
	settings.beginGroup("proxy");
	proxySupport->setChecked(settings.value("enabled", false).toBool());
	proxyType->setCurrentIndex(settings.value("type", 0).toInt());
	proxyHostName->setText(settings.value("hostName").toString());
	proxyPort->setValue(settings.value("port", 1080).toInt());
	proxyUserName->setText(settings.value("userName").toString());
	proxyPassword->setText(settings.value("password").toString());
	settings.endGroup();
	if (settings.value("motor").toString() == "Yahoo") {
		comboBox->setCurrentIndex(1);
	} else if (settings.value("motor").toString() == "bing") {
		comboBox->setCurrentIndex(2);
	} else if (settings.value("motor").toString() == "exalead") {
		comboBox->setCurrentIndex(3);
	} else {
		comboBox->setCurrentIndex(0);
	}
	QSettings set(naveoConfigurationPath + "/Options.ini", QSettings::IniFormat);
	QString current = set.value("currentSes").toString();
	if(current.isEmpty()) {
		current = tr("Default");
	}
	QStringList dirs = QDir(qApp->applicationDirPath() + "/session/").entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	dirs.prepend(tr("Default"));
	listWidget_2->clear();
	foreach(QString str, dirs)
	{
		QListWidgetItem *item = new QListWidgetItem(QIcon(":/void.png"), str);
		if(str == current)
		{
			item->setIcon(QIcon(":/arrow.png"));
		}
		listWidget_2->addItem(item);
	}

	if(syn->connected()) {
		label_3->setText(tr("Naveo est synchronisé pour : <strong>%1</strong>").arg(syn->user()));
		pushButton_3->hide();
		pushButton_15->show();
		comboBox_7->setEnabled(false);
		pushButton_9->setEnabled(true);
		pushButton_10->setEnabled(true);
		checkBox_19->setEnabled(true);
	} else {
		label_3->setText(tr("<strong>Naveo n'est pas synchronisé</strong>"));
		pushButton_15->hide();
		pushButton_3->show();
		comboBox_7->setEnabled(true);
		pushButton_9->setEnabled(false);
		pushButton_10->setEnabled(false);
		checkBox_19->setEnabled(false);
	}
	comboBox_7->clear();
	comboBox_7->addItems(syn->serverList());
	if(syn->serverList().isEmpty())
	{
		pushButton_3->setEnabled(false);
		comboBox_7->setEnabled(false);
		checkBox_19->setEnabled(false);
	}
	QString themeDir = settings.value("theme").toString();
	label_2->setText(tr("Le thême actuel est : %1").arg(themeDir));
	QSettings synchro(Browser::instance()->iniFile("synchro.ini"), QSettings::IniFormat);
	checkBox_19->setChecked(synchro.value("auto").toBool() && syn->connected());
	setWindowIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/icon.png"));
	label_8->hide();
	updateCheck();
}

void settingDialog::on_pushButton_11_clicked()
{
	QDir dir(qApp->applicationDirPath() + "/session/");
	QString name = QInputDialog::getText(this, tr("Nouvelle session"), tr("Entrez le nom de la nouvelle session"));
	if(name == tr("Default"))
		return;

	dir.mkdir(name);
	QFile(Browser::instance()->iniFile()).copy(qApp->applicationDirPath() + "/session/" + name + "/Options.ini");
	updateAll();
}

void settingDialog::on_pushButton_12_clicked()
{
	if(!listWidget_2->currentItem())
		return;

	save();

	QSettings set(naveoConfigurationPath + "/Options.ini", QSettings::IniFormat);
	if(listWidget_2->currentItem()->text() == tr("Default"))
	{
		set.setValue("currentSes", "");
	}
	else
	{
		set.setValue("currentSes", listWidget_2->currentItem()->text());
	}
	updateAll();
}

void settingDialog::on_pushButton_13_clicked()
{
	if(!listWidget_2->currentItem() || listWidget_2->currentItem()->text() == tr("Default"))
		return;

	QDir dir(qApp->applicationDirPath() + "/session/" + listWidget_2->currentItem()->text());
	foreach(QString file, dir.entryList(QDir::Files))
	{
		QFile(dir.absolutePath() + "/" + file).remove();
	}
	dir.cdUp();
	if(!dir.rmdir(listWidget_2->currentItem()->text()))
	{
		cout<<"Unable to remove \""<<qPrintable(dir.absolutePath() + "/" + listWidget_2->currentItem()->text())<<"\""<<endl;
	}
	QSettings set(naveoConfigurationPath + "/Options.ini", QSettings::IniFormat);
	if(set.value("currentSes").toString() == listWidget_2->currentItem()->text())
	{
		set.setValue("currentSes", "");
	}
	updateAll();

}

void settingDialog::updateCheck()
{
	lineEdit_3->setEnabled(radioButton_3->isChecked());
	lineEdit_4->setEnabled(radioButton_5->isChecked());
	lineEdit_2->setEnabled(radioButton_7->isChecked());
}

void settingDialog::on_pushButton_clicked()
{
	label_2->setText(tr("Le thême actuel est : %1").arg(listWidget->item(listWidget->currentRow())->text()));
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	settings.setValue("theme", listWidget->item(listWidget->currentRow())->text());
}

void settingDialog::on_pushButton_2_clicked()
{
	save();
	emit restart();
}

void settingDialog::on_pushButton_3_clicked()
{
	if(!syn->connected())
	{
		save();
		syn->setVisible();
		syn->setServer(comboBox_7->currentIndex());
		syn->exec();
		label_8->setVisible(comboBox_7->currentIndex());
		checkBox_19->setChecked(checkBox_19->isChecked() && comboBox_7->currentIndex() == 0);
	}
	else
	{
		syn->close();
	}
}

void settingDialog::synStatusChanded(bool connected)
{
	pushButton_3->setVisible(!connected);
	pushButton_15->setVisible(connected);
	pushButton_9->setEnabled(connected);
	pushButton_10->setEnabled(connected);
}

void settingDialog::on_pushButton_15_clicked()
{
	if(syn->connected())
	{
		label_3->setText(tr("<strong>Naveo n'est pas synchronisé</strong>"));
		syn->disconnect();
		label_8->setVisible(comboBox_7->currentIndex());
		checkBox_19->setChecked(false);
		checkBox_19->setEnabled(false);
	}
}

void settingDialog::on_pushButton_10_clicked()
{
	syn->exportSettings();
}

void settingDialog::on_pushButton_9_clicked()
{
	syn->import();
}

void settingDialog::on_pushButton_4_clicked()
{
	emit clearHistory();
}

void settingDialog::on_pushButton_5_clicked()
{
	emit clearCookies();
}

void settingDialog::on_pushButton_14_clicked()
{
	if (listWidget_3->currentItem())
	{
		plugs->activate(listWidget_3->currentItem()->text());
		if(plugs->activated(listWidget_3->currentItem()->text()))
		{
			SetFunc f = (SetFunc)plugs->plugin(listWidget_3->currentItem()->text()).lib->resolve("settingsOpenned");
			if(f)
			{
				f(this);
			}
		}
		listWidget_3->clear();
		for(int i = 0; i != plugs->pluginsList().count(); i++)
		{
			QIcon icon(":/plug.png");
			if(!plugs->pluginsList()[i].activated)
			{
				icon = QIcon(":/desactivated.png");
			}
			new QListWidgetItem(icon, plugs->pluginsList()[i].name, listWidget_3, 0);
			if(plugs->pluginsList()[i].removed)
			{
				listWidget_3->item(listWidget_3->count() - 1)->setFlags(Qt::NoItemFlags);
			}
		}
	}
}

void settingDialog::on_pushButton_6_clicked()
{
	if (listWidget_3->currentItem())
	{
		if(plugs->activated(listWidget_3->currentItem()->text()))
		{
			plugs->activate(listWidget_3->currentItem()->text());
		}
		plugs->remove(listWidget_3->currentItem()->text());
		listWidget_3->clear();
		for(int i = 0; i != plugs->pluginsList().count(); i++)
		{
			QIcon icon(":/plug.png");
			if(!plugs->pluginsList()[i].activated)
			{
				icon = QIcon(":/desactivated.png");
			}
			new QListWidgetItem(icon, plugs->pluginsList()[i].name, listWidget_3, 0);
			if(plugs->pluginsList()[i].removed)
			{
				listWidget_3->item(listWidget_3->count() - 1)->setFlags(Qt::NoItemFlags);
			}
		}
		on_listWidget_3_currentRowChanged(listWidget_3->currentRow());
	}
	pushButton_2->show();
}

void settingDialog::on_pushButton_7_clicked()
{
	if(listWidget_3->currentItem())
	{
		if(plugs->hasSettings(listWidget_3->currentItem()->text()))
		{
			plugs->execSettings(listWidget_3->currentItem()->text());
		}
	}
}

void settingDialog::on_pushButton_8_clicked()
{
	plugs->getPlugins();
	pushButton_2->show();
}

void settingDialog::on_listWidget_3_currentRowChanged(int row)
{
	if(row != -1)
	{
		pushButton_7->setEnabled(plugs->hasSettings(listWidget_3->item(row)->text()));
		pushButton_14->setEnabled(true);
		pushButton_6->setEnabled(true);
		if(plugs->activated(listWidget_3->currentItem()->text()))
		{
			pushButton_14->setText(tr("Déactiver"));
		}
		else
		{
			pushButton_14->setText(tr("Activer"));
		}
	}
	else
	{
		pushButton_14->setEnabled(false);
		pushButton_7->setEnabled(false);
		pushButton_6->setEnabled(false);
	}
}



void settingDialog::exec()
{
	updateAll();
	QDialog::exec();
}



void settingDialog::save()
{
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	settings.setValue("dlInk", checkBox->isChecked());
	settings.setValue("showHome", checkBox_2->isChecked());
	settings.setValue("showStop", checkBox_3->isChecked());
	settings.setValue("image", checkBox_4->isChecked());
	settings.setValue("javascript", checkBox_5->isChecked());
	settings.setValue("changeTab", checkBox_6->isChecked());
	settings.setValue("google", checkBox_7->isChecked());
	settings.setValue("eraseHistory", checkBox_8->isChecked());
	settings.setValue("private", checkBox_9->isChecked());
	settings.setValue("perso", !checkBox_10->isChecked());
	settings.setValue("transparency", checkBox_13->isChecked());
	settings.setValue("block", checkBox_14->isChecked());
	settings.setValue("speedDial", checkBox_15->isChecked());
	settings.setValue("close", checkBox_16->isChecked());
	settings.setValue("toolbarTranparency", checkBox_17->isChecked());
	settings.setValue("dark", checkBox_18->isChecked());
	settings.setValue("flash", checkBox_20->isChecked());
	//settings.setValue("noText", groupBox_2->isChecked());
	settings.setValue("saveTab", radioButton->isChecked());
	settings.setValue("openHome", radioButton_2->isChecked());
	settings.setValue("openUrl", radioButton_3->isChecked());
	settings.setValue("tabOpenHome", radioButton_4->isChecked());
	settings.setValue("newUrl", lineEdit_3->text());
	settings.setValue("tabUrl", lineEdit_4->text());
	settings.setValue("askForDir", radioButton_6->isChecked());
	settings.setValue("downloadIn", lineEdit_2->text());
	settings.setValue("zoom", spinBox->value()/100);
	settings.setValue("motor", comboBox->itemText(comboBox->currentIndex()));
	settings.setValue("posPerso", comboBox_2->currentIndex());
	settings.setValue("posNav", comboBox_3->currentIndex());
	settings.setValue("saveHistory", comboBox_4->currentIndex());
	settings.setValue("saveCookies", comboBox_5->currentIndex());
	settings.setValue("Home", comboBox_6->currentText());
	settings.beginGroup("proxy");
	settings.setValue("enabled", proxySupport->isChecked());
	settings.setValue("type", proxyType->currentIndex());
	settings.setValue("hostName", proxyHostName->text());
	settings.setValue("port", proxyPort->text());
	settings.setValue("userName", proxyUserName->text());
	settings.setValue("password", proxyPassword->text());
	settings.endGroup();
	QSettings synchro(Browser::instance()->iniFile("synchro.ini"), QSettings::IniFormat);
	synchro.setValue("auto", checkBox_19->isChecked());
}

void settingDialog::accept()
{
	save();
	emit finished();
	QDialog::accept();
}
