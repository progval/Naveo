/*******************************
Copyright (C) 2009-2010 gr�goire ANGERAND

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

#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include <QtGui>
#include <iostream>

using namespace std;

class PluginDialog : public QDialog
{
	Q_OBJECT

	public:
		PluginDialog();

	public slots:
		void getInfo();
		void installPlugin();
		void indexChanged();
		void search();

	signals:
		void install(QString name, QString url);

	private:
		void fillTree(QStringList list, bool tree = true);

		QTreeWidget *listWidget;
		QPushButton *info;
		QPushButton *installButton;
		QLineEdit *line;

		QString os;

};

#endif // PLUGINDIALOG_H
