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

#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QtCore>
#include <QtNetwork>
#include <QtWebKit>

class PasswordManager : public QObject
{
	Q_OBJECT
	public:

		struct Form
		{
			QUrl url;
			QString value;
			QString name;
			bool save;
		};

		PasswordManager(QObject *parent = 0);
		void setPage(QWebPage *p);
		void extract();
		void getPass();
		void setPass();

		void save();
		void load();

		void clear() {forms.clear();}

	signals:
		void savePass();

	public slots:
		void yes();
		void yesOnce();

	private:
		bool hasPass;
		QWebPage *page;
		QList<Form> forms;
		QList<Form> list;



};

#endif // PASSWORDMANAGER_H
