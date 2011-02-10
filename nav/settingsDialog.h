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


#ifndef HEADER_SETTING
#define HEADER_SETTING
#include <QtGui>
#include <iostream>
#include "ui_settings.h"
#include "CookieJar.h"
#include "synchronizer.h"
#include "pluginmanager.h"

using namespace std;

class PluginManager;

class settingDialog : public QDialog, private Ui::Dialog
{
	Q_OBJECT

	public:
		//settingDialog();
		settingDialog(Synchronizer *synchronizer, PluginManager *pm);

	public slots:
		void exec();

	private slots:
		void updateCheck();
		void on_pushButton_clicked();
		void on_pushButton_2_clicked();
		void on_pushButton_3_clicked();
		void on_pushButton_4_clicked();
		void on_pushButton_5_clicked();
		void on_pushButton_6_clicked();
		void on_pushButton_7_clicked();
		void on_pushButton_8_clicked();
		void on_pushButton_9_clicked();
		void on_pushButton_10_clicked();
		void on_pushButton_11_clicked();
		void on_pushButton_12_clicked();
		void on_pushButton_13_clicked();
		void on_pushButton_14_clicked();
		void on_pushButton_15_clicked();
		void synStatusChanded(bool connected);
		void on_listWidget_3_currentRowChanged(int row);
		void updateAll();
		//void installPlugin();
		void save();
		void accept();


	signals:
		void finished();
		void clearCookies();
		void clearHistory();
		void restart();

	private:
		Synchronizer *syn;
		PluginManager *plugs;
		QListWidget *pluginListWidget;
};
#endif
