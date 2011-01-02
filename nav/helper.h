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


#ifndef HELPER_H
#define HELPER_H

#include <QtGui>
#include <iostream>

class Helper : public QWidget
{
	Q_OBJECT

	public:
		Helper(QWidget *parent = 0);

	signals:
		void closed();

	public slots:
		void updateView();
		void itemActivated(QTreeWidgetItem *item);

	protected:
		void closeEvent(QCloseEvent *event);

	private:
		QTreeWidget *tree;
		QTextBrowser *browser;

};

#endif // HELPER_H
