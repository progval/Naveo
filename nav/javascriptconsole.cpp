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


#include "javascriptconsole.h"
#include "Browser.h"

JavascriptConsole::JavascriptConsole(QWebPage *p, QWidget *parent) :
	QDockWidget(tr("Concole javascript"), parent)
{
	page = p;

	setFocusPolicy(Qt::WheelFocus);

	listWidget = new QListWidget;
	listWidget->setSelectionMode(QAbstractItemView::NoSelection);
	listWidget->setSelectionRectVisible(false);
	listWidget->setMinimumHeight(100);

	line = new QLineEdit;
	line->setFrame(false);

	listWidget->setFocusProxy(this);

	new QListWidgetItem(QIcon(":/arrow.png"), QString(), listWidget);
	listWidget->setItemWidget(listWidget->item(listWidget->count() - 1), line);

	setWidget(listWidget);
	setAutoFillBackground(true);

	connect(line, SIGNAL(returnPressed()), this, SLOT(runJs()));
}

void JavascriptConsole::focusInEvent(QFocusEvent *event)
{
	if(event->gotFocus())
		line->setFocus();
}
void JavascriptConsole::runJs()
{
	listWidget->insertItem(listWidget->count() - 2, new QListWidgetItem(QIcon(":/arrow.png"), line->text()));
	line->clear();
	page->mainFrame()->evaluateJavaScript(line->text());
}

void JavascriptConsole::addText(QString text)
{
	listWidget->insertItem(listWidget->count() - 2, new QListWidgetItem(QIcon(":/error.png"), text));
}

void JavascriptConsole::setText(QString text)
{
	foreach(QString item, text.split("\n"))
	{
		listWidget->insertItem(listWidget->count() - 2, new QListWidgetItem(QIcon(":/error.png"), item));
	}
}

void JavascriptConsole::clear()
{
	setText(QString());
}
