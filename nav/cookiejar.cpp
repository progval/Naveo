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

#include "cookiejar.h"
#include "Browser.h"


CookieJar::CookieJar(QObject *parent)
	:QNetworkCookieJar(parent)
{
	QFile cookieFile(Browser::instance()->iniFile("cookies.txt"));
	if (cookieFile.open(QIODevice::ReadOnly) )
	{
		QList<QNetworkCookie> list;
		QByteArray text = cookieFile.readAll();
		#ifdef USE_GAN_H
			text = gan_::encryption::uncrypt(text);
		#endif
		if(!text.isEmpty())
		{
			foreach(QByteArray line, text.split('\n'))
			{
				int i = list.count();
				list.append(QNetworkCookie::parseCookies(line));
				if(list.count() == i)
					cout<<"Cookies parse error for \""<<line.constData()<<"\""<<endl;
			}
			setAllCookies(list);
		}
	}
	cleared = false;
}

CookieJar::~CookieJar()
{
	purgeOldCookies();
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	if (settings.value("saveCookies").toInt() == 0 && !cleared)
	{
		QFile cookieFile(Browser::instance()->iniFile("cookies.txt"));
		if(cookieFile.open(QIODevice::WriteOnly))
		{
			QTextStream out(&cookieFile);
			QByteArray array;
			foreach(const QNetworkCookie & cookie, allCookies())
			{
				array.append(cookie.toRawForm() + "\n");
			}

			#ifdef USE_GAN_H
				array = gan_::encryption::encrypt(array);
			#endif
			out<<array<<endl;
		}
	}
	else
	{
		QFile(Browser::instance()->iniFile("cookies.txt")).remove();
	}
}

QList<QNetworkCookie> CookieJar::cookiesForUrl ( const QUrl & url ) const
{
	return QNetworkCookieJar::cookiesForUrl(url);
}

bool CookieJar::setCookiesFromUrl ( const QList<QNetworkCookie> & cookieList, const QUrl & url )
{
	return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}

void CookieJar::purgeOldCookies()
{
	QList<QNetworkCookie> cookies = allCookies();
	if (cookies.isEmpty())
		return;
	int oldCount = cookies.count();
	QDateTime now = QDateTime::currentDateTime();
	for (int i = cookies.count() - 1; i >= 0; --i) {
		if (!cookies.at(i).isSessionCookie() && cookies.at(i).expirationDate() < now)
			cookies.removeAt(i);
	}
	if (oldCount == cookies.count())
		return;
	setAllCookies(cookies);
}

void CookieJar::clear()
{
	cleared = true;
}
