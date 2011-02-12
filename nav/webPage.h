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


#ifndef HEADER_WEBPAGE
#define HEADER_WEBPAGE

#include <QtGui>
#include <QtNetwork>
#include <QtWebKit>
#include "path.h"
#include "httpget.h"
#include "webview.h"
#include "speeddial.h"
#include "googlesuggest.h"
#include "CookieJar.h"
#include "javascriptconsole.h"
#include "passwordmanager.h"
#include "dockwidget.h"

#include <iostream>

class MainWin;
class UrlLineEdit;

using namespace std;

class webPage : public QMainWindow
{
	Q_OBJECT

	public:
		webPage();
		webPage(WebView *view);

		~webPage();

		QString title();
		QString url();
		WebView *view();
		QToolBar *bar();
		QMenu *menu();
		QIcon icon();
		QIcon iconForUrl(QString url);

	public slots:
		void startLoading();
		void finishLoading(bool ok);
		void changeTitle(QString title);
		void changeUrl(QUrl url);
		void goToHome();
		void loadUrl();
		void loadUrl(QUrl url);
		void loadUrl(QString url);
		void addToBookMark();
		void downloadFile(const QNetworkRequest &);
		void downloadFile(QNetworkReply *reply);
		void loadBookMark();
		void showBookMark();
		void sources();
		void defineHome();
		void findNext();
		void findPrevious();
		void print();
		void createNewPage(WebView *page);
		void createNewPage();
		void updateIcon();
		void copy();
		void authentification(QNetworkReply *reply, QAuthenticator *authenticator);
		void inspectPage();
		void goToDial();
		void updateUrlIcon(QPixmap pixmap);
		void updateBookMark();
		void updateOptions();
		void showBar();
		void showPage();
		void showDial();
		void inCache();
		void showConsole();
		void zoomIn();
		void zoomOut();
		void restoreZoom();
		void savePage();
		void back();
		void forward();

	signals:
		void loading(QString url);
		void isLoading(QPixmap pix);
		void titleChanged(QString title);
		void pageChanged(QString url, QString title);
		void showSources(QString url);
		void speedDial();
		void needPrint(QPrinter *printer);
		void openTab(webPage *page);
		void setFullScreen(bool enabled);

	protected:
		void keyPressEvent(QKeyEvent *event);
		void resizeEvent(QResizeEvent *event);
		void paintEvent(QPaintEvent *event);
		//void closeEvent (QCloseEvent *event);
		//void mouseMoveEvent(QMouseEvent *event);

	private:
		void create(WebView *view);
		QString getFileName(QNetworkReply *reply);
		QMenu *toolsMenu;
		bool isADownload;
		bool noError;
		QMenu *settingMenu;
		QMenu *bookMarkMenu;
		QToolBar *toolBar;
		QToolBar *findBar;
		QSettings *settings;
		QString homePage();
		QAction *findAction;
		QLineEdit *findEdit;
		UrlLineEdit *urlEdit;
		WebView *page;
		QAction *advancedSettingAction;
		QToolButton *backButton;
		QAction *backAction;
		QAction *forwardAction;
		QAction *stopAction;
		QAction *reloadAction;
		QAction *homeAction;
		QAction *sourcesAction;
		QAction *defineHomeAction;
		QAction *bookMarkAction;
		QPushButton *findPreviousButton;
		QPushButton *findNextButton;
		QPushButton *closeButton;
		QString themeDir;
		bool loadinging;
		QMovie *movie;
		QToolBar *bookmarkBar;
		int downloads;
		GSuggestCompletion *gCompleter;
		QAction *newTabAction;
		QAction *dialAction;
		QAction *showDownloadAction;
		QAction *showDownloadButton;
		QAction *addBookMarkAction;
		QAction *orgBookMarkAction;
		QStackedWidget *stack;
		SpeedDial *dial;
		JavascriptConsole *javascriptConsole;
		QToolBar *passBar;
		QAction *synchroAction;
		QAction *importAction;
		QAction *exportAction;
};

class UrlLineEdit : public QLineEdit
{

Q_OBJECT


public:

	UrlLineEdit(QWebView *webView)
	{
		view = webView;
		focus = false;
		connect(view, SIGNAL(loadProgress(int)), this, SLOT(loading(int)));
		setTextMargins(20, 0, 40, 0);
		progress = 0;
		clearButton = new QPushButton(tr(""), this);
		clearButton->setStyleSheet("QPushButton{background-image: url(':/closetab_.png');}"
								  "QPushButton::pressed{border : none; background-image: url(':/closetab.png');}"
								  "QPushButton::hover{background-image: url(':/closetab.png');}");
		clearButton->setFlat(true);
		QSettings settings(naveoConfigurationPath + "/Options.ini", QSettings::IniFormat);
		motor = settings.value("motor").toString();
		if (motor.isEmpty())
		{
			motor = "Google";
		}
		motorButton = new QPushButton(tr(""), this);
		motorButton->setStyleSheet("QPushButton{background-image: url(':/" + motor + ".png');}"
								  "QPushButton::pressed{border : none; background-image: url(':/" + motor + ".png');}"
								  "QPushButton::hover{background-image: url(':/" + motor + ".png');}");
		motorButton->setFlat(true);
		connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
		connect(motorButton, SIGNAL(clicked()), this, SLOT(changeMotor()));
	}

	void setText(QString text)
	{
		if(text != "about:blank")
			QLineEdit::setText(text);
	}


	void setIcon(QIcon newIcon)
	{
		icon = newIcon;
		//repaint();
	}

	QString shearchMotorUrl(QString url)
	{
		if (motor == "Yahoo")
		{
			return "http://fr.search.yahoo.com/search?rd=r1&p=" + url + "&toggle=1&cop=mss&ei=UTF-8&fr=yfp-t-703";
		}
		else if (motor == "bing")
		{
			return "http://www.bing.com/search?q=" + url + "&go=&form=QBLH&filt=all";
		}
		else if (motor == "exalead")
		{
			return "http://www.exalead.com/search/web/results/?q=" + url;
		}
		else
		{
			return "http://www.google.com/search?hl=fr&q=" + url;
		}
	}


protected:
	void paintEvent(QPaintEvent * event)
	{
		QLineEdit::paintEvent(event);
		QPainter painter(this);
		if (progress != 0)
		{
			int chunk = width();
			if (chunk <= 0)
			{
				chunk = 1;
			}
			chunk = chunk / 100;
			chunk = chunk * progress;
			QPen pen(QColor(81, 119, 189, 120));
			pen.setWidth(height());
			painter.setPen(pen);
			painter.drawLine(0, height() / 2, chunk, height() / 2);
		}

		/*QLinearGradient linearGrad(QPointF(0, height() / 2), QPointF(width(), height() / 2));
		linearGrad.setColorAt(0, Qt::darkGray);
		linearGrad.setColorAt(1, Qt::lightGray);
		QPen pen(QBrush(linearGrad), height());
		painter.setPen(pen);
		painter.drawLine(0, height() / 2, width(), height() / 2);*/


		icon.paint(&painter, (height()-16)/2, (height()-16)/2, 16, 16);
		clearButton->setGeometry(width() - 40, 1, 17, 17);
		motorButton->setGeometry(width() - 20, 1, 17, 17);
	}

	void focusInEvent(QFocusEvent *event)
	{
		QLineEdit::focusInEvent(event);
		if(!focus)
		{
			QTimer::singleShot(0, this, SLOT(selectAll()));
		}
		focus = true;
	}

	void focusOutEvent(QFocusEvent *event)
	{
		QLineEdit::focusOutEvent(event);
		if(text() != view->url().toString() && !view->url().toString().isEmpty())
		{
			setText(view->url().toString());
		}
		focus = false;
	}

public slots :

	void loading(int i)
	{
		progress = i;
		if (progress == 100)
		{
			progress = 0;
		}
	}

	void clear()
	{
		QLineEdit::clear();
		setFocus();
	}

	void changeMotor()
	{
		QMenu menu;
		QAction *G = new QAction(QIcon(":/Google.png"), tr("Google"), this);
		QAction *Y = new QAction(QIcon(":/Yahoo.png"), tr("Yahoo"), this);
		QAction *B = new QAction(QIcon(":/bing.png"), tr("bing"), this);
		QAction *E = new QAction(QIcon(":/exalead.png"), tr("exalead"), this);
		menu.addAction(G);
		menu.addAction(Y);
		menu.addAction(B);
		menu.addAction(E);
		connect(G, SIGNAL(triggered()), this, SLOT(changeG()));
		connect(Y, SIGNAL(triggered()), this, SLOT(changeY()));
		connect(B, SIGNAL(triggered()), this, SLOT(changeB()));
		connect(E, SIGNAL(triggered()), this, SLOT(changeE()));
		menu.exec(QCursor::pos());
	}

	void changeG()
	{
		motor = "Google";
		change();
	}

	void changeY()
	{
		motor = "Yahoo";
		change();
	}

	void changeB()
	{
		motor = "bing";
		change();
	}

	void changeE()
	{
		motor = "exalead";
		change();
	}

	void load();

	void change();

private:
	bool focus;
	QIcon icon;
	QWebView *view;
	int progress;
	QPushButton *clearButton;
	QPushButton *motorButton;
	QString motor;
};
#endif
