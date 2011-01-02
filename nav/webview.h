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


#ifndef HEADER_WEBVIEW
#define HEADER_WEBVIEW

#include <QtGui>
#include <QtNetwork>
#include <QtWebKit>
#include <iostream>
#include "page.h"

using namespace std;

class WebView : public QWebView
{
	Q_OBJECT

	public:
		WebView();
		void setDarkMode(bool enabled);
		void setBlockPopup(bool enabled);

	public slots:
		void linkHovered(QString url, QString link);
		void shearch();

	signals:
		void addPage(WebView *page);
		void addPage();
		void addToBookMarks();
		void popupBlocked();


	protected:
		void contextMenuEvent(QContextMenuEvent *event);
		WebView *createWindow(QWebPage::WebWindowType type);
		void paintEvent(QPaintEvent * event);
		void mousePressEvent(QMouseEvent * event);
		void mouseReleaseEvent(QMouseEvent * event);
		void keyReleaseEvent(QKeyEvent *event);
		void keyPressEvent(QKeyEvent *event);
		void wheelEvent(QWheelEvent *event);


	private:
		int x;
		int y;
		bool cursorIsOnLink;
		QString lastLink;
		bool blockPopup;
		bool dark;
};
#endif
