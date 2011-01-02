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


#include "webview.h"
#include <iostream>
#include "Browser.h"

WebView::WebView()
{
	x = 0;
	y = 0;
	setPage(new Page);
	blockPopup = false;
	cursorIsOnLink = false;
	dark = false;
	pageAction(QWebPage::OpenLinkInNewWindow)->setText(tr("Ouvrir le lien dans un nouvel onglet"));
	connect(page(), SIGNAL(linkHovered(QString, QString, QString)), this, SLOT(linkHovered(QString, QString)));
}

void WebView::setBlockPopup(bool enabled)
{
	blockPopup = enabled;
}

WebView *WebView::createWindow (QWebPage::WebWindowType type)
{
	if (type == QWebPage::WebModalDialog && blockPopup)
	{
		emit popupBlocked();
		emit statusBarMessage(tr("Popup bloqué"));
		return 0;
	}
	WebView *page = new WebView;
	emit addPage(page);
	return page;
}

void WebView::contextMenuEvent(QContextMenuEvent */*event*/)
{
	QMenu *menu = new QMenu;
	if (cursorIsOnLink)
	{
		//menu->addAction(pageAction(QWebPage::OpenLink));
		menu->addAction(pageAction(QWebPage::OpenLinkInNewWindow));
		menu->addSeparator();
	}
	if (!selectedText().isEmpty())
	{
		QAction * searchAction = new QAction(tr("rechercher \"") + selectedText() + tr("\" dans Google"), this);
		connect(searchAction, SIGNAL(triggered()), this, SLOT(shearch()));
		menu->addAction(searchAction);
		menu->addSeparator();
	}
	QAction * action = new QAction(QIcon(":/bookmark.png"), tr("Ajouter aux favoris"), this);
	connect(action, SIGNAL(triggered()), this, SIGNAL(addToBookMarks()));
	menu->addAction(action);
	menu->addSeparator();
	menu->addAction(pageAction(QWebPage::Back));
	menu->addAction(pageAction(QWebPage::Forward));
	menu->addAction(pageAction(QWebPage::Reload));

	menu->addSeparator();
	menu->addAction(pageAction(QWebPage::Copy));
	menu->addAction(pageAction(QWebPage::Cut));
	menu->addAction(pageAction(QWebPage::Paste));
	menu->addSeparator();

	menu->addSeparator();
	menu->addAction(pageAction(QWebPage::InspectElement));

	menu->exec(QCursor::pos());

	delete menu;
	delete action;
}

void WebView::keyPressEvent(QKeyEvent *event)
{
	QWebView::keyPressEvent(event);
}

void WebView::keyReleaseEvent(QKeyEvent *event)
{
	QWebView::keyReleaseEvent(event);
}

void WebView::wheelEvent(QWheelEvent *event)
{
	if(event->modifiers() == Qt::ControlModifier)
	{
		setZoomFactor(zoomFactor() + event->delta());
	}
	else
	{
		QWebView::wheelEvent(event);
	}
}

void WebView::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::RightButton)
	{
		x = event->x();
		y = event->y();
	}
	else
	{
		QWebView::mousePressEvent(event);
	}
}

void WebView::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::RightButton)
	{
		if ((x+200) < event->x() && (x+1000) >  event->x())
		{
			if ((y+25) > event->y() && (y-25) < event->y())
			{
				forward();
				return;
			}
		}
		else if ((x-200) > event->x() && (x-1000) <  event->x())
		{
			if ((y+25) > event->y() && (y-25) < event->y())
			{
				back();
				return;
			}
		}
		else if ((x+25) > event->x() && (x-25) < event->x())
		{
			if ((y+200) < event->y() && (y+1000) >  event->y())
			{
				reload();
				return;
			}
			else if ((y-200) > event->y() && (y-1000) < event->y())
			{
				emit addPage();
				return;
			}
		}
	}
	else if (event->button() == Qt::MidButton && cursorIsOnLink)
	{
		WebView *view = new WebView;
		emit addPage(view);
		view->load(QUrl(lastLink));
		return;
	}
	else if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier && cursorIsOnLink)
	{
		WebView *view = new WebView;
		emit addPage(view);
		view->load(QUrl(lastLink));
		return;
	}


	QWebView::mouseReleaseEvent(event);
}

void WebView::linkHovered(QString url, QString link)
{
	if (url.isEmpty() && link.isEmpty())
	{
		cursorIsOnLink = false;
	}
	else
	{
		cursorIsOnLink = true;
		lastLink = url;
	}
	repaint();
}

void WebView::paintEvent(QPaintEvent *event)
{
	QWebView::paintEvent(event);
	if(cursorIsOnLink)
	{
		QPainter p(this);
		int x = 8 + page()->mainFrame()->scrollBarGeometry(Qt::Horizontal).height();
		if(lastLink.length() > 50)
		{
			p.drawText(QPoint(4, height() - x), lastLink.left(50) + QString("  ..."));
		}
		else
		{
			p.drawText(QPoint(4, height() - x), lastLink);
		}
	}
	if (dark)
	{
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);
		p.setCompositionMode(QPainter::CompositionMode_Difference);
		p.fillRect(event->rect(), Qt::white);
		p.end();
	}
}

void WebView::setDarkMode(bool enabled)
{
	dark = enabled;
	repaint();
}

void WebView::shearch()
{
	load(QUrl("http://www.google.com/search?hl=fr&q=" + selectedText()));
}
