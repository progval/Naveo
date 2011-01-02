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

#ifndef CLEARDIALOG_H
#define CLEARDIALOG_H

#include <QtGui>
#include <iostream>
#include "Browser.h"

using namespace std;

class ClearDialog : public QDialog
{
	Q_OBJECT

	public:
		ClearDialog(QWidget *parent = 0);

	public slots:
		void clearData();

	private:
		QLabel *mainLabel;
		QCheckBox *history;
		QCheckBox *bookMarks;
		QCheckBox *cookies;
		QCheckBox *downloads;
		QCheckBox *cached;
		QCheckBox *icons;
		QPushButton *clear;
		QPushButton *cancel;
		QLabel *picture;
		QLabel *label;

};

#endif // CLEARDIALOG_H
