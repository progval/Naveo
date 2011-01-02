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



#include <iostream>
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QLibrary>
#include "mainWin.h"
#include "version.h"
#include "Browser.h"

using namespace std;

#include "lib.h"

int main(int argc, char *argv[])
{
	Browser *app = new Browser(argc, argv);
	if(!app->isTheOnlyBrowser)
	{
		return 0;
	}
	QString locale = QLocale::system().name();
	QTranslator translator;
	if(!translator.load(QString(app->applicationDirPath() + "/locale/qt_") + locale))
		cout<<"Unable to load translation for \""<<qPrintable(locale)<<"\""<<endl;
	app->installTranslator(&translator);
	return app->exec();
}
