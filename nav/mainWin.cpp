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


#include "mainWin.h"
#include "version.h"
#include "Browser.h"
#include <iostream>

MainWin::MainWin(QString fileName)
{
	quit = false;
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	#ifdef Q_WS_WIN
	if (QSysInfo::WindowsVersion >= QSysInfo::WV_VISTA) {
		if (settings.value("transparency").toBool()) {
			setAttribute(Qt::WA_TranslucentBackground);
		}
	}
	#endif
	setTabBar(new TabBar);
	tabBar()->setDrawBase(false);
	themeDir = settings.value("theme").toString();
	setWindowIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/icon.png"));
	settingsButton = new QPushButton(this);
	tabBar()->setExpanding(false);
	setUsesScrollButtons(false);
	settingsButton->setStyleSheet("QPushButton{image: url(':/naveo.png');border : none;}"
								  "QPushButton::hover{image: url(':/naveo_.png');border : none;}");
	settingsButton->setFixedSize(40, 28);
	settingsButton->move(-4, -3);
	setDocumentMode(true);
	newTabButton = new QPushButton(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/new.png"), tr(""), this);
	newTabButton->setFlat(true);
	newTabButton->setStyleSheet("QPushButton::pressed{border : none;}");
	newTabButton->setFixedSize(QSize(24,24));
	resize(settings.value("size").toSize());
	move(QPoint(settings.value("pos").toPoint().x() + 10, settings.value("pos").toPoint().y() + 10));
	if (settings.value("max").toBool())
	{
		resize(800, 600);
	}
	newTabButton->setShortcut(QKeySequence::AddTab);
	setMovable(true);
	setStyleSheet("QTabWidget::tab-bar {left: 32px; /*bottom: -1px;*/}");
	/*tabBar()->setStyleSheet("QTabBar::tab:!selected {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #DFDFDF, stop: 1.0 #C6C6C6);}"
							"QTabBar::tab:selected {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #BFBFBF, stop: 1.0 #A6A6A6);}");*/
	Browser::instance()->plugins()->addWindow(this);
	setMinimumSize(300, 200);
	connect(this, SIGNAL(loadFirstPage(QString)), this, SLOT(setup(QString)));
	emit loadFirstPage(fileName);
	connect(static_cast<TabBar *>(tabBar()), SIGNAL(grab(QPoint)), this, SLOT(grab(QPoint)));
	connect(newTabButton, SIGNAL(clicked()), this, SLOT(newTab()));
	connect(this, SIGNAL(currentChanged(int)), this, SLOT(tabChanged()));
	connect(settingsButton, SIGNAL(clicked()), this, SLOT(showTabSettings()));
	connect(Browser::instance(), SIGNAL(settingsChanged()), this, SLOT(updateSettings()));
	#ifdef CUSTOM_WINDOW
		QPoint pos = this->pos();
		if(transluent) {
			setWindowFlags(Qt::CustomizeWindowHint);
		} else {
			setWindowFlags(Qt::FramelessWindowHint);
		}
		move(pos);
		show();
	#endif
}

void MainWin::grab(QPoint p)
{
	move(pos() + p);
}
void MainWin::paintEvent(QPaintEvent *event)
{
	QTabWidget::paintEvent(event);
	#ifdef CUSTOM_WINDOW
		if(!transluent)
		{
			QStylePainter stylePainter(this);
			QStyleOptionTitleBar option;
			option.initFrom(this);
			option.rect = QRect(-6, -6, width() + 12, height() + 12);
			stylePainter.drawComplexControl(QStyle::CC_TitleBar, option);
		}
	#endif
}


void MainWin::setup(QString fileName)
{
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	QStringList pagesUrl = settings.value("pagesList").toStringList();
	if (fileName.isEmpty())
	{
		if (settings.value("saveTab").toBool())
		{
			if (pagesUrl.isEmpty())
			{
				newTab();
			}
			else
			{
				int i = 0;
				do
				{
					newTab(pagesUrl.at(i));
					i++;
				}while (i != pagesUrl.count());
			}
		}
		else
		{
			if (settings.value("openUrl").toBool())
			{
				newTab(settings.value("newUrl").toString());
			}
			else
			{
				newTab(settings.value("home").toString());
			}
		}
	}
	else
	{
		newTab(/*"file:///" + */fileName);
		//cout<<qPrintable(/*"file:///" + */fileName)<<endl<<"openned"<<endl;
	}
}

void MainWin::newTab(QString url)
{
	webPage *_page = createPage();
	_page->loadUrl(url);
	int index = addTab(page, _page->title());
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	if (settings.value("changeTab").toBool())
	{
	setCurrentIndex(index);
	}
	if (count() > 1)
	{
		tabBar()->show();
		newTabButton->show();
	}
}

void MainWin::newTab()
{
	int index = addTab(createPage(), tr("(nouvelle page)"));
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	if (settings.value("changeTab").toBool())
	{
		setCurrentIndex(index);
	}
	if (count() > 1)
	{
		tabBar()->show();
		newTabButton->show();
	}
}

void MainWin::setTabTitle(QString title)
{
	int index = indexOf(qobject_cast<QWidget *>(sender()));
	setTabToolTip(index, title);
	//QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	/*if (!settings.value("noText").toBool())
	{*/
		if (title.size() > 32)
		{
			title = title.left(29) + "...";
		}
		setTabText(index, title);
	/*}
	else
	{
		setTabText(index, "");
	}*/
	tabChanged();
	updateNewTabButtonPos();
}

void MainWin::tabChanged()
{
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	QString title = tabToolTip(currentIndex());
	if (settings.value("private").toBool())
	{
		setWindowTitle(title + " - Naveo (privé)");
	}
	else
	{
		setWindowTitle(title + " - Naveo");
	}
	/*if (settings.value("noText").toBool())
	{
		if (tabBar()->tabButton(currentIndex(), QTabBar::RightSide))
		{
			int a = 0;
			while(a != count())
			{
				tabBar()->tabButton(a, QTabBar::RightSide)->hide();
				a++;
			}
			tabBar()->tabButton(currentIndex(), QTabBar::RightSide)->show();
			tabBar()->setStyleSheet("QTabBar::tab:!selected {width:28 px;}"
								"QTabBar::tab:selected {width:50 px;}");
		}
		else
		{
			QTimer::singleShot(50, this, SLOT(tabChanged()));
		}
	}*/
}

void MainWin::closeTab()
{
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	int index = tabBar()->tabAt(qobject_cast<QPushButton *>(sender())->pos());
	if(count() == 1)
	{
		if (settings.value("close").toBool())
		{
			settings.setValue("pagesList", settings.value("home").toString());
			close();
		}
		else
		{
			newTab();
		}
	}
	QWidget *page = widget(index);
	Browser::instance()->plugins()->closePage(static_cast<webPage *>(page));
	removeTab(index);
	pageList.removeAt(index);
	page->deleteLater();
	cout<<"tab closed"<<endl;
	updateNewTabButtonPos();
}

void MainWin::updateSettings()
{
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	if (settings.value("private").toBool())
	{
		setWindowTitle(tabText(currentIndex()) + " - Naveo (privé)");
	}
	else
	{
		setWindowTitle(tabText(currentIndex()) + " - Naveo");
	}
	foreach(webPage *page, pageList)
	{
		page->updateOptions();
	}
	themeDir = settings.value("theme").toString();
	newTabButton->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/new.png"));
	setWindowIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/icon.png"));
	#ifdef Q_WS_WIN
	if (QSysInfo::WindowsVersion >= QSysInfo::WV_VISTA) {
			setAttribute(Qt::WA_NoSystemBackground, settings.value("transparency").toBool());
	}
	#endif
	int a = 0;
	while(a != count())
	{
		tabBar()->tabButton(a, QTabBar::RightSide)->show();
		a++;
	}
	/*if (settings.value("noText").toBool())
	{
		int a = 0;
		while(a != count())
		{
			setTabText(a, "");
			a++;
		}
		tabBar()->setStyleSheet("QTabBar::tab:!selected {width:28 px;}"
								"QTabBar::tab:selected {width:50 px;}");
		int b = 0;
		while(b != count())
		{
			if (b != currentIndex())
			{
				tabBar()->tabButton(b, QTabBar::RightSide)->hide();
			}
			b++;
		}
	}
	else
	{*/
		a = 0;
		while(a != count())
		{
			setTabText(a, tabToolTip(a));
			a++;
		}
		 tabBar()->setStyleSheet("");
	//}
	QString title = tabToolTip(currentIndex());
	if (settings.value("private").toBool())
	{
		setWindowTitle(title + " - Naveo (privé)");
	}
	else
	{
		setWindowTitle(title + " - Naveo");
	}
	updateNewTabButtonPos();
	#ifdef CUSTOM_WINDOW
		QPoint pos = this->pos();
		if(transluent) {
			setWindowFlags(Qt::CustomizeWindowHint);
		} else {
			setWindowFlags(Qt::FramelessWindowHint);
		}
		move(pos);
		show();
	#endif
}

webPage *MainWin::createPage()
{
	QTime t;
	t.start();
	page = new webPage;
	pageList.append(page);
	page->setParent(this);
	connect(page, SIGNAL(titleChanged(QString)), this, SLOT(setTabTitle(QString)));
	connect(page, SIGNAL(showSources(QString)), this, SLOT(showSources()));
	connect(page, SIGNAL(openTab(webPage *)), this, SLOT(openTab(webPage *)));
	connect(page, SIGNAL(loading(QString)), this, SLOT(setLoadingIcon(QString)));
	connect(page, SIGNAL(isLoading(QPixmap)), this, SLOT(setTabIcon(QPixmap)));
	connect(page, SIGNAL(setFullScreen(bool)), this, SLOT(setFullScreen(bool)));
	Browser::instance()->plugins()->addPage(page);
	cout<<t.elapsed()<<" ms to create a web page"<<endl;
	return page;
}

void MainWin::showSources()
{
	sourcesEditor *edit = new sourcesEditor;
	edit->setText(qobject_cast<webPage *>(sender())->view()->page()->mainFrame()->toHtml());
	int i = insertTab(currentIndex() + 1, edit, tr("source de %1").arg(qobject_cast<webPage *>(sender())->url()));
	setCurrentIndex(i);
	QTabWidget::setTabIcon(i, QIcon(":/code.png"));
	updateNewTabButtonPos();
}

void MainWin::closeEvent(QCloseEvent */*event*/)
{
	emit closed();
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	QStringList pagesUrl;
	int i = 0;
	do
	{
		if (indexOf(pageList.at(i)) != (-1))
		{
			pagesUrl.append(pageList.at(i)->url());
		}
		i++;
	}while (i != pageList.count());
	settings.setValue("pagesList", pagesUrl);
	settings.setValue("size", size());
	settings.setValue("max", isMaximized());
	settings.setValue("pos", pos());
}

void MainWin::setFullScreen(bool enabled)
{
	if(enabled)
	{
		settingsButton->hide();
		newTabButton->hide();
		tabBar()->hide();
		setWindowState(Qt::WindowFullScreen);
	}
	else
	{
		settingsButton->show();
		newTabButton->show();
		tabBar()->show();
		setWindowState(Qt::WindowNoState);
	}
}

void MainWin::openTab(webPage * page)
{
	pageList.append(page);
	page->setParent(this);
	connect(page, SIGNAL(titleChanged(QString)), this, SLOT(setTabTitle(QString)));
	connect(page, SIGNAL(showSources(QString)), this, SLOT(showSources()));
	connect(page, SIGNAL(openTab(webPage *)), this, SLOT(openTab(webPage *)));
	connect(page, SIGNAL(loading(QString)), this, SLOT(setLoadingIcon(QString)));
	connect(page, SIGNAL(isLoading(QPixmap)), this, SLOT(setTabIcon(QPixmap)));
	connect(page, SIGNAL(setFullScreen(bool)), this, SLOT(setFullScreen(bool)));
	Browser::instance()->plugins()->addPage(page);
	int index = addTab(page, page->title());
	QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	if (settings.value("changeTab").toBool())
	{
		setCurrentIndex(index);
	}
	cout<<"tab created"<<endl;
}

void MainWin::setLoadingIcon(QString)
{
	webPage *page = qobject_cast<webPage *>(sender());
	int index = indexOf(page);
	QTabWidget::setTabIcon(index, page->icon());
	updateNewTabButtonPos();
}

void MainWin::setTabIcon(QPixmap pix)
{
	int index = indexOf(qobject_cast<QWidget *>(sender()));
	QTabWidget::setTabIcon(index, QIcon(pix));
	updateNewTabButtonPos();
}

void MainWin::showTabSettings()
{
	if(currentPage())
	{
		currentPage()->menu()->exec(mapToGlobal(QPoint(settingsButton->x() + 4, settingsButton->y() + 29)));
	}
	else if(currentEditor())
	{
		currentEditor()->menu()->exec(mapToGlobal(QPoint(settingsButton->x() + 4, settingsButton->y() + 29)));
	}
}

webPage *MainWin::currentPage()
{
	return qobject_cast<webPage *>(currentWidget());
}

sourcesEditor *MainWin::currentEditor()
{
	return qobject_cast<sourcesEditor *>(currentWidget());
}

void MainWin::changeIndex()
{
	QString text = qobject_cast<QAction *>(sender())->text();
	int i = 0;
	do
	{
		if (text == tabText(i))
		{
			break;
		}
		i++;
	}while (i != count());
	setCurrentIndex(i);
}

QList<webPage *>MainWin::pages()
{
	return pageList;
}

QIcon MainWin::iconForUrl(QString url)
{
	if(url == "Naveo::dial")
		return QIcon(":/speedDial.png");
	return QWebSettings::iconForUrl(QUrl(url));
}

int MainWin::addTab(QWidget *tab, QString label)
{
	//QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	int i = 0;
	/*if(settings.value("noText").toString() == "true")
	{
		i = QTabWidget::addTab(tab, "");
	}
	else
	{*/
		i = QTabWidget::addTab(tab, label);
	//}
	setTabToolTip(i, label);
	QTabWidget::setTabIcon(i, QIcon(":/speedDial.png"));
	QPushButton *closeTabButton = new QPushButton("");
	closeTabButton->setFlat(true);
	closeTabButton->setStyleSheet("QPushButton{background-image: url(':/closetab_.png');}"
								  "QPushButton::pressed{border : none; background-image: url(':/closetab_.png');}"
								  "QPushButton::hover{background-image: url(':/closetab.png');}");
	closeTabButton->setFixedSize(QSize(17, 17));
	connect(closeTabButton, SIGNAL(clicked()), this, SLOT(closeTab()));
	tabBar()->setTabButton(i, QTabBar::RightSide, closeTabButton);
	/*if (settings.value("noText").toBool())
	{
		closeTabButton->hide();
	}*/
	return i;
}

int MainWin::insertTab(int index, QWidget *tab, QString label)
{
	//QSettings settings(Browser::instance()->iniFile(), QSettings::IniFormat);
	int i = 0;
	/*if(settings.value("noText").toString() == "true")
	{
		i = QTabWidget::insertTab(index, tab, "");
	}
	else
	{*/
		i = QTabWidget::insertTab(index, tab, label);
	//}
	setTabToolTip(i, label);
	QTabWidget::setTabIcon(i, QIcon(":/speedDial.png"));
	QPushButton *closeTabButton = new QPushButton("");
	closeTabButton->setFlat(true);
	closeTabButton->setStyleSheet("QPushButton{background-image: url(':/closetab_.png');}"
								  "QPushButton::pressed{border : none; background-image: url(':/closetab_.png');}"
								  "QPushButton::hover{background-image: url(':/closetab.png');}");
	closeTabButton->setFixedSize(QSize(17, 17));
	connect(closeTabButton, SIGNAL(clicked()), this, SLOT(closeTab()));
	tabBar()->setTabButton(i, QTabBar::RightSide, closeTabButton);
	/*if (settings.value("noText").toBool())
	{
		closeTabButton->hide();
	}*/
	return i;
}

void MainWin::updateNewTabButtonPos()
{
	int pix = 0;
	while(tabBar()->tabAt(QPoint(pix, 0)) != -1 && pix < width())
	{
		pix++;
	}
	pix += 10 + newTabButton->width();
	newTabButton->move(QPoint(pix, 1));
	//newTabButton->show();
}

void MainWin::tabInserted(int index)
{
	Q_UNUSED(index);
	updateNewTabButtonPos();
}


void MainWin::openFtp(QString url)
{
	Q_UNUSED(url);
}








void TabBar::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu;
	QAction action(tr("Nouvel onglet"), this);
	QAction action2(tr("Nouvelle fenêtre"), this);
	connect(&action, SIGNAL(triggered()), static_cast<MainWin *>(parent()), SLOT(newTab()));
	connect(&action2, SIGNAL(triggered()), Browser::instance(), SLOT(addNew()));
	menu.addAction(&action);
	menu.addAction(&action2);
	menu.exec(mapToGlobal(event->pos()));
}
