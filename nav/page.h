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


#ifndef PAGE_H
#define PAGE_H

#include <QtGui>
#include <QtWebKit>
#include <version.h>
#include <iostream>
#include "javascriptconsole.h"

using namespace std;


class Page : public QWebPage
{

	public:
		Page();
		void setConsole(JavascriptConsole *c);
		void enableJS();

		void triggerAction(WebAction action, bool checked = false);

	protected:
		QString userAgentForUrl(QUrl url);

		void javaScriptConsoleMessage(const QString &message, int lineNumber, const QString &sourceID);
		void javaScriptAlert(QWebFrame *frame, const QString &msg);
		bool javaScriptConfirm(QWebFrame *frame, const QString &msg);
		bool javaScriptPrompt(QWebFrame *frame, const QString &msg, const QString &defaultValue, QString *result);

	private:
		void info(QString title, QString msg);
		bool question(QString title, QString msg);
		bool input(QString title, QString msg, QString defaultValue, QString *result);
		QString js;
		bool jsDisabled;
		JavascriptConsole *console;

};

#endif // PAGE_H
