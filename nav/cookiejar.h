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


#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QtNetwork>
#include <QtGui>
#include <QtWebKit>
#include <iostream>


class CookieJar : public QNetworkCookieJar
{
	Q_OBJECT

	public:
		CookieJar(QObject *parent);
		~CookieJar();
		QList<QNetworkCookie> cookiesForUrl(const QUrl & url) const;
		bool setCookiesFromUrl(const QList<QNetworkCookie> & cookieList, const QUrl & url);
		void purgeOldCookies();

	public slots:
		void clear();

	private:
		bool cleared;
};

#endif

