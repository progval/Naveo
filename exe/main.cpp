
/*******************************
Copyright (C) 2009-2010 grégoire ANGERAND

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful
but WITHOUT ANY WARRANTY; without even the implied warranty of
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************/


#include <QLibrary>
#include <QFile>
#include <iostream>
#include <QApplication>
#include <QMessageBox>
#include <stdio.h>
#include <stdlib.h>

#ifdef Q_WS_WIN
	#define LIB "dll"
#else
	#define LIB "so"
#endif

using namespace std;

bool ok(QString path)
{
	return QFile(path + "/Naveo." + LIB).exists() &&
	   QFile(path + "/phonon4." + LIB).exists() &&
	   QFile(path + "/QtWebKit4." + LIB).exists() &&
	   QFile(path + "/QtXmlPatterns4." + LIB).exists() &&
	   QFile(path + "/QtXml4." + LIB).exists() &&
	   QFile(path + "/libssl32." + LIB).exists() &&
	   QFile(path + "/libeay32." + LIB).exists();
}

void update(QString path)
{
	if(QFile(path + "/Naveo_." + LIB).exists())
		QFile(path + "/Naveo_." + LIB).rename(QString(path + "/Naveo." + LIB));
}


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	typedef int (*MainFunction)(int, char**);
	int r = 1;
	update(app.applicationDirPath());
	do
	{
		if(!ok(app.applicationDirPath()) || r == -2)
		{
			MainFunction main = (MainFunction)QLibrary::resolve(QString("maj.") + LIB, "main");
			int i = r;
			if (main)
				r = main(argc, argv);
			else
				return 1;

			if(i == -2)
				return QMessageBox::information(0, QObject::tr("Mise à jour"), QObject::tr("La mise à jour sera finalisé au prochain redémarrage de Naveo")) * 0;
		}

		if(ok(app.applicationDirPath()) && r)
		{
			MainFunction main = (MainFunction)QLibrary::resolve(QString("Naveo.") + LIB, "main");
			if (main)
			{
				do {
					r = main(argc, argv);
				} while(r == -1);
				if(!r)
					return 0;
			}
		}
		else
		{
			return 2;
		}
	} while(r == -2);

	return 1;
}
