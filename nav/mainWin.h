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


#ifndef HEADER_MAINWIN
#define HEADER_MAINWIN

#include <QtGui>
#include <QtWebKit>
#include "webPage.h"
#include "httpget.h"
#include "sourcesPage.h"

class TabBar;

class MainWin : public QTabWidget
{
	Q_OBJECT

	public:
		MainWin(QString fileName);
		QList<webPage *>pages();
		QIcon iconForUrl(QString url);
		int insertTab(int index, QWidget *tab, QString label);
		int addTab(QWidget *tab, QString label);
		webPage *currentPage();
		sourcesEditor *currentEditor();

	public slots:
		void closeTab();
		void setTabTitle(QString title);
		void tabChanged();
		void newTab();
		void showSources();
		void newTab(QString url);
		void openTab(webPage * page);
		void setLoadingIcon(QString url);
		void setTabIcon(QPixmap pix);
		void showTabSettings();
		void changeIndex();
		void updateNewTabButtonPos();
		void updateSettings();
		void setFullScreen(bool enabled);
		void setup(QString fileName);
		void grab(QPoint p);
		void openFtp(QString url);


	signals:
		void closed();
		void loadFirstPage(QString file);


	protected:
		void paintEvent(QPaintEvent *event);
		void closeEvent(QCloseEvent *event);
		virtual void tabInserted(int index);

	private:
		QList<webPage *> pageList;
		webPage *page;
		webPage *createPage();
		QString themeDir;
		QPushButton *settingsButton;
		bool quit;
		QPushButton *newTabButton;
};


class TabBar : public QTabBar
{

	Q_OBJECT

	public:
		TabBar(QWidget *parent = 0) : QTabBar(parent)
		{
			grabing = false;
			setElideMode(Qt::ElideRight);
		}

	signals:
		void grab(QPoint p);

	protected:
		QSize tabSizeHint(int index) const;

		void mousePressEvent(QMouseEvent *event)
		{
			if(tabAt(event->pos()) == -1)
			{
				grabing = true;
				base = event->pos();
			}
			QTabBar::mousePressEvent(event);
		}

		void mouseMoveEvent(QMouseEvent *event)
		{
			if(grabing)
			{
				emit grab(event->pos() - base);
			}
			QTabBar::mouseMoveEvent(event);
		}

		void mouseReleaseEvent(QMouseEvent *event)
		{
			grabing = false;
			QTabBar::mouseReleaseEvent(event);
		}

		void contextMenuEvent(QContextMenuEvent *event);

	private:
		bool grabing;
		QPoint base;

};

#endif
