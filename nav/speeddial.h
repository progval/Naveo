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

#ifndef SPEEDDIAL_H
#define SPEEDDIAL_H

#include <QtGui>
#include <QtWebKit>
#include <iostream>
#include "webview.h"

using namespace std;


class LinkButton : public QWidget
{
	Q_OBJECT

	public:
		LinkButton(QWidget *parent = 0);

		//WebView *page();

	signals:
		void selected(QString str);
		void added();

	protected:
		void enterEvent(QEvent *event);
		void leaveEvent(QEvent *event);
		void paintEvent(QPaintEvent *event);
		void resizeEvent(QResizeEvent *event);
		void mousePressEvent(QMouseEvent *event);
		void keyPressEvent(QKeyEvent *event);


	public slots:
		void clear();
		void setUrl(QString newUrl);
		QString pageUrl();
		void image(bool ok);
		void createPage();

	private:
		QPushButton *clearButton;
		QLabel *label;
		QString url;
		WebView *view;
		bool inside;
		QPixmap *pix;

};

class SpeedDial : public QWidget
{
	Q_OBJECT

	public:
		SpeedDial(QWidget *parent = 0);

	protected:
		void resizeEvent(QResizeEvent *event);
		void keyPressEvent(QKeyEvent *event);

	signals:
		void setFullScreen(bool enabled);

	public slots:
		void save();

	private:
		QGridLayout *lay;

};

#endif // SPEEDDIAL_H
