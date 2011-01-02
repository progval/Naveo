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


#ifndef URLDIALOG_H
#define URLDIALOG_H

#include <QtGui>
#include <iostream>

using namespace std;

class UrlDialog : public QDialog
{
	Q_OBJECT

	public:
		UrlDialog(QWidget *parent = 0, bool showSavedUrl = false, QString text = QString(), bool nameEdit = false, QString name = QString(), bool selectDir = false, bool url = true);

		QString url();
		QString name();
		QString selectedDir();

	public slots:
		QString exec();
		void setData(QTreeWidgetItem *item);

	private:
		void addHistory();
		void addBookMarks();
		void fillDirTree();

		bool returnUrl;

		QLineEdit *line;
		QLineEdit *edit;
		QTreeWidget *tree;
		QTreeWidget *treeWidget;
		QPushButton *cancel;
		QPushButton *ok;


};

#endif // URLDIALOG_H
