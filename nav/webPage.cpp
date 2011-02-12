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

#include "webPage.h"
#include "Browser.h"
#include "version.h"
#include "urldialog.h"

webPage::~webPage()
{
	//dial->save();

	delete page;
	delete dial;
	delete stack;
	delete settingMenu;
	delete gCompleter;

	if(loadinging)
		delete movie;
}

webPage::webPage()
{
	settings = new QSettings(Browser::instance()->iniFile(), QSettings::IniFormat);
	create(new WebView);
	if (settings->value("tabOpenHome").toBool())
	{
		goToHome();
	}
	else
	{
		loadUrl(settings->value("tabUrl").toString());
		if (settings->value("tabUrl").toString() != "speedDial")
		{
			emit pageChanged(page->url().toString(), page->title());
		}
	}
}

webPage::webPage(WebView *view)
{
	settings = new QSettings(Browser::instance()->iniFile(), QSettings::IniFormat);
	create(view);
	emit pageChanged(page->url().toString(), page->title());
}

void webPage::create(WebView *view)
{
	setAutoFillBackground(!settings->value("toolbarTranparency").toBool() || !settings->value("transparency").toBool());
	loadinging = false;
	isADownload = false;
	noError = false;
	downloads = 0;
	page = view;
	page->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
	page->page()->setNetworkAccessManager(Browser::instance()->accessManager());
	page->setDarkMode(settings->value("dark").toBool());
	dial = new SpeedDial;
	//---------------------------------------------------------------------------------------------------------------------
	stack = new QStackedWidget;
	stack->addWidget(page);
	stack->addWidget(dial);
	stack->setCurrentIndex(0);
	//---------------------------------------------------------------------------------------------------------------------
	urlEdit = new UrlLineEdit(page);
	gCompleter = new GSuggestCompletion(urlEdit);
	themeDir = settings->value("theme").toString();
	page->setZoomFactor(settings->value("zoom").toDouble());
	page->setBlockPopup(settings->value("block").toBool());
	backButton = new QToolButton(this);
	backButton->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/back.png"));
	backAction = new QAction(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/back.png"), tr("Précédent"), this);
	forwardAction = new QAction(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/forward.png"), tr("Suivant"), this);
	stopAction = new QAction(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/stop.png"), tr("Stop"), this);
	reloadAction = new QAction(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/reload.png"), tr("Actualiser"), this);
	homeAction = new QAction(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/home.png"), tr("Accueil"), this);
	bookMarkAction = new QAction(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/bookMark.png"), tr("Favoris"), this);
	addBookMarkAction = new QAction(tr("Ajouter aux favoris"), this);
	orgBookMarkAction = new QAction(tr("Organiser les favoris"), this);
	backButton->setShortcut(QKeySequence::Back);
	//backButton->setArrowType(Qt::NoArrow);
	//backButton->setPopupMode(QToolButton::MenuButtonPopup);
	backAction->setShortcut(QKeySequence::Back);
	forwardAction->setShortcut(QKeySequence::Forward);
	reloadAction->setShortcut(QKeySequence::Refresh);
	sourcesAction = new QAction(tr("Afficher la source"), this);
	findAction = new QAction(QIcon(":/search.png"), tr("Rechercher"), this);
	findAction->setShortcut(QKeySequence::Find);
	QAction *printAction = new QAction(tr("Imprimer"), this);
	printAction->setShortcut(QKeySequence::Print);
	defineHomeAction = new QAction(tr("Définir cette page comme page d'accueil"), this);
	advancedSettingAction = new QAction(tr("Options"), this);
	QAction *showAction = new QAction(tr("Afficher l'historique"), this);
	QAction *helpAction = new QAction(tr("Aide"), this);
	QAction *jsAction = new QAction(tr("Console javascript"), this);
	QAction *clearAction = new QAction(tr("Effacer les donnéées de navigation"), this);
	homeAction->setVisible(settings->value("showHome").toBool());
	newTabAction = new QAction(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/new.png"), tr("Nouvel onglet"), this);
	newTabAction->setShortcut(QKeySequence::AddTab);
	QAction *aboutAction = new QAction(tr("A propos"), this);
	dialAction = new QAction(QIcon(":/speedDial.png"), tr("Speed Dial"), this);
	QAction *saveAction = new QAction(tr("Enregister la page"), this);
	QAction *cacheAction = new QAction(tr("En cache avec Google"), this);
	QAction *inspectAction = new QAction(tr("Inspecter la page"), this);
	QAction *zoomInAction = new QAction(tr("Zoom avant"), this);
	QAction *zoomOutAction = new QAction(tr("Zoom arrière"), this);
	QAction *zoomAction = new QAction(tr("Taille réelle"), this);
	zoomInAction->setShortcut(QKeySequence::ZoomIn);
	zoomOutAction->setShortcut(QKeySequence::ZoomOut);
	/*synchroAction = new QAction(QIcon(":/synchro.png"), tr("Synchroniser"), this);
	importAction = new QAction(tr("Importer les paramètres"), this);
	exportAction = new QAction(tr("Exporter les paramètres"), this);*/
	showDownloadAction = new QAction(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/down.png"), tr("Afficher les téléchargements"), this);
	showDownloadButton = new QAction(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/down.png"), tr("Afficher les téléchargements"), this);
	showDownloadButton->setVisible(settings->value("dlInk").toBool());
	dialAction->setVisible(settings->value("speedDial").toBool());
	page->page()->setForwardUnsupportedContent(true);
	statusBar()->hide();
	javascriptConsole = 0;
	toolBar = new QToolBar(tr("Actions"));
	//toolBar->setStyleSheet("QToolBar {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #909090, stop: 1.0 #606060);}");
	//setStyleSheet("QToolBar {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #A6A6A6, stop: 1.0 #8D8D8D);}");
	if (settings->value("posNav").toInt() == 1)
	{
		addToolBar(Qt::BottomToolBarArea, toolBar);
	}
	else
	{
		addToolBar(toolBar);
	}
	toolBar->addWidget(backButton);
	toolBar->addAction(forwardAction);
	toolBar->addAction(reloadAction);
	toolBar->addAction(stopAction);
	toolBar->addWidget(urlEdit);
	toolBar->addAction(homeAction);
	toolBar->addAction(dialAction);
	toolBar->addAction(showDownloadButton);
	toolBar->addAction(bookMarkAction);
	//toolBar->addAction(settingAction);
	toolBar->setIconSize(QSize(22, 22));
	toolBar->setMovable(false);
	//toolBar->setStyleSheet("border : 0px;");
	findBar = new QToolBar(tr("Rechercher"));
	addToolBar(Qt::BottomToolBarArea, findBar);
	findBar->setMovable(false);
	closeButton = new QPushButton("X");
	closeButton->setFixedWidth(30);
	findBar->addWidget(closeButton);
	findEdit = new QLineEdit;
	findBar->addWidget(findEdit);
	findNextButton = new QPushButton("<");
	findNextButton->setFixedWidth(30);
	findBar->addWidget(findNextButton);
	findPreviousButton = new QPushButton(">");
	findPreviousButton->setFixedWidth(30);
	findBar->addWidget(findPreviousButton);
	findBar->close();
	passBar = new QToolBar(tr("Enregister"));
	passBar->setMovable(false);
	QPushButton *saveButton = new QPushButton(tr("Oui"));
	QPushButton *dontSaveButton = new QPushButton(tr("Non"));
	QPushButton *saveOnceButton = new QPushButton(tr("Oui pour cette fois"));
	passBar->widgetForAction(passBar->addWidget(new QLabel(tr("Voulez vous que Naveo se souvienne de votre mot de passe ?"))))->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	passBar->addWidget(saveButton);
	passBar->addWidget(saveOnceButton);
	passBar->addWidget(dontSaveButton);

	setCentralWidget(stack);

	setWindowIcon(page->icon());
	QAction *goToDialAction = new QAction(QIcon(":/speedDial.png"), tr("Speed Dial"), this);
	settingMenu = new QMenu(tr("Naveo"), this);
	settingMenu->setIcon(QIcon(":/icon.png"));
	settingMenu->addAction(newTabAction);
	settingMenu->addSeparator();
	settingMenu->addAction(backAction);
	settingMenu->addAction(forwardAction);
	settingMenu->addAction(reloadAction);
	settingMenu->addAction(stopAction);
	settingMenu->addAction(homeAction);
	settingMenu->addAction(goToDialAction);
	settingMenu->addSeparator();
	bookMarkMenu = new QMenu(tr("Favoris"));
	settingMenu->addMenu(bookMarkMenu);
	settingMenu->addAction(defineHomeAction);
	settingMenu->addAction(saveAction);
	settingMenu->addAction(findAction);
	settingMenu->addAction(printAction);
	QMenu *zoomMenu = new QMenu(tr("Zoom"));
	zoomMenu->addAction(zoomInAction);
	zoomMenu->addAction(zoomAction);
	zoomMenu->addAction(zoomOutAction);
	settingMenu->addMenu(zoomMenu);
	settingMenu->addSeparator();
	settingMenu->addAction(showDownloadAction);
	settingMenu->addAction(showAction);
	toolsMenu = new QMenu(tr("Outils"));
	/*QMenu *synMenu = new QMenu(tr("Synchronisation"));
	synMenu->setIcon(QIcon(":/synchro.png"));
	synMenu->addAction(synchroAction);
	synMenu->addAction(importAction);
	synMenu->addAction(exportAction);
	toolsMenu->addMenu(synMenu);*/
	toolsMenu->addSeparator();
	toolsMenu->addAction(sourcesAction);
	toolsMenu->addSeparator();
	toolsMenu->addAction(jsAction);
	toolsMenu->addSeparator();
	toolsMenu->addAction(clearAction);
	toolsMenu->addSeparator();
	toolsMenu->addAction(cacheAction);
	toolsMenu->addAction(inspectAction);
	settingMenu->addMenu(toolsMenu);
	settingMenu->addSeparator();
	settingMenu->addAction(advancedSettingAction);
	settingMenu->addSeparator();
	settingMenu->addAction(aboutAction);
	settingMenu->addAction(helpAction);
	helpAction->setShortcut(QKeySequence::HelpContents);
	showAction->setShortcut(tr("Ctrl+H"));
	findAction->setShortcut(tr("Ctrl+F"));
	sourcesAction->setShortcut(tr("Ctrl+U"));

	bookmarkBar = new QToolBar(tr("Favoris"));
	switch (settings->value("posPerso").toInt())
	{
		case 1:
			addToolBar(Qt::BottomToolBarArea, bookmarkBar);
		break;
		case 2:
			addToolBar(Qt::LeftToolBarArea, bookmarkBar);
		break;
		case 3:
			addToolBar(Qt::RightToolBarArea, bookmarkBar);
		break;
		default:
			addToolBar(bookmarkBar);
		break;
	}
	insertToolBarBreak(bookmarkBar);
	if (settings->value("perso").toBool())
	{
		bookmarkBar->close();
	}
	addToolBar(Qt::BottomToolBarArea, passBar);
	passBar->close();
	bookmarkBar->setIconSize(QSize(16, 16));
	bookmarkBar->setMovable(false);
	bookmarkBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	setAttribute(Qt::WA_DeleteOnClose);
	updateBookMark();

	//-------------------------------------------------connection---------------------------------------------------


	connect(dialAction, SIGNAL(triggered()), this, SLOT(goToDial()));
	connect(dial, SIGNAL(setFullScreen(bool)), this, SIGNAL(setFullScreen(bool)));
	connect(aboutAction, SIGNAL(triggered()), Browser::instance(), SLOT(about()));
	connect(newTabAction, SIGNAL(triggered()), this, SLOT(createNewPage()));
	connect(page, SIGNAL(addPage(WebView *)), this, SLOT(createNewPage(WebView *)));
	connect(page, SIGNAL(addPage()), this, SLOT(createNewPage()));
	connect(printAction, SIGNAL(triggered()), this, SLOT(print()));
	connect(advancedSettingAction, SIGNAL(triggered()), Browser::instance(), SLOT(execSettings()));
	connect(clearAction, SIGNAL(triggered()), Browser::instance(), SLOT(clearData()));
	connect(showAction, SIGNAL(triggered()), Browser::instance()->hManager(), SLOT(show()));
	connect(defineHomeAction, SIGNAL(triggered()), this, SLOT(defineHome()));
	connect(sourcesAction, SIGNAL(triggered()), this, SLOT(sources()));
	connect(addBookMarkAction, SIGNAL(triggered()), this, SLOT(addToBookMark()));
	connect(page, SIGNAL(addToBookMarks()), this, SLOT(addToBookMark()));
	connect(orgBookMarkAction, SIGNAL(triggered()), Browser::instance()->bmManager(), SLOT(show()));
	connect(forwardAction, SIGNAL(triggered()), this, SLOT(forward()));
	connect(cacheAction, SIGNAL(triggered()), this, SLOT(inCache()));
	connect(reloadAction, SIGNAL(triggered()), page, SLOT(reload()));
	connect(helpAction, SIGNAL(triggered()), Browser::instance(), SLOT(showHelp()));
	connect(backAction, SIGNAL(triggered()), this, SLOT(back()));
	connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
	connect(stopAction, SIGNAL(triggered()), page, SLOT(stop()));
	connect(inspectAction, SIGNAL(triggered()), this, SLOT(inspectPage()));
	connect(homeAction, SIGNAL(triggered()), this, SLOT(goToHome()));
	connect(showDownloadAction, SIGNAL(triggered()), Browser::instance()->dlManager(), SLOT(show()));
	connect(Browser::instance(), SIGNAL(settingsChanged()), this, SLOT(updateOptions()));
	connect(Browser::instance()->bmManager(), SIGNAL(update()), this, SLOT(updateBookMark()));
	connect(jsAction, SIGNAL(triggered()), this, SLOT(showConsole()));
	connect(showDownloadButton, SIGNAL(triggered()), Browser::instance()->dlManager(), SLOT(show()));
	connect(page->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(loadUrl(QUrl)));
	connect(bookMarkAction, SIGNAL(triggered()), this, SLOT(showBookMark()));
	connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));
	connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));
	connect(zoomAction, SIGNAL(triggered()), this, SLOT(restoreZoom()));
	connect(urlEdit, SIGNAL(returnPressed()), this, SLOT(loadUrl()));
	connect(page, SIGNAL(statusBarMessage(QString)), statusBar(), SLOT(showMessage(QString)));
	connect(page, SIGNAL(loadStarted()), this, SLOT(startLoading()));
	connect(page, SIGNAL(loadProgress(int)), this, SLOT(updateIcon()));
	connect(page, SIGNAL(loadFinished(bool)), this, SLOT(finishLoading(bool)));
	connect(page, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
	connect(page, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));
	connect(page->page()->action(QWebPage::InspectElement), SIGNAL(triggered()), this, SLOT(inspectPage()));
	connect(page->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(loadUrl(QUrl)));
	connect(this, SIGNAL(needPrint(QPrinter *)), page, SLOT(print(QPrinter*)));
	connect(Browser::instance()->passManager(), SIGNAL(savePass()), passBar, SLOT(show()));
	connect(saveButton, SIGNAL(clicked()), Browser::instance()->passManager(), SLOT(yes()));
	connect(saveOnceButton, SIGNAL(clicked()), Browser::instance()->passManager(), SLOT(yesOnce()));
	connect(saveButton, SIGNAL(clicked()), passBar, SLOT(close()));
	connect(saveOnceButton, SIGNAL(clicked()), passBar, SLOT(close()));
	connect(dontSaveButton, SIGNAL(clicked()), passBar, SLOT(close()));
	connect(findPreviousButton, SIGNAL(clicked()), this, SLOT(findPrevious()));
	connect(goToDialAction, SIGNAL(triggered()), this, SLOT(goToDial()));
	connect(findNextButton, SIGNAL(clicked()), this, SLOT(findNext()));
	connect(findEdit, SIGNAL(returnPressed()), this, SLOT(findNext()));
	connect(closeButton, SIGNAL(clicked()), findBar, SLOT(close()));
	connect(findAction, SIGNAL(triggered()), this, SLOT(showBar()));
	connect(page->page(), SIGNAL(downloadRequested(const QNetworkRequest&)), this, SLOT(downloadFile(const QNetworkRequest&)));
	connect(page->page(), SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(downloadFile(QNetworkReply*)));
	connect(this, SIGNAL(isLoading(QPixmap)), this, SLOT(updateUrlIcon(QPixmap)));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(savePage()));
}

void webPage::back()
{
	if(stack->currentIndex() == 1)
		showPage();
	else
		page->back();
}

void webPage::forward()
{
	if(stack->currentIndex() == 1)
		showPage();
	else
		page->forward();
}


void webPage::showConsole()
{
	if(!javascriptConsole)
	{
		javascriptConsole = new JavascriptConsole(page->page(), this);
		addDockWidget(Qt::BottomDockWidgetArea, javascriptConsole);
		static_cast<Page *>(page->page())->setConsole(javascriptConsole);
	}
	else
	{
		javascriptConsole->show();
	}

}

void webPage::inspectPage()
{
	QWebInspector *inspector = new QWebInspector;

	inspector->setPage(page->page());
	DockWidget *dock = new DockWidget(inspector);
	addDockWidget(Qt::BottomDockWidgetArea, dock);
}

void webPage::showPage()
{
	if(!stack->currentIndex())
		return;

	stack->setCurrentIndex(0);
	urlEdit->setText(page->url().toString());
	urlEdit->setIcon(icon());
	emit titleChanged(page->title());
	emit loading(page->title());
}

void webPage::inCache()
{
	loadUrl("http://webcache.googleusercontent.com/search?q=cache:" + url());
}

void webPage::showDial()
{
	if(stack->currentIndex())
		return;

	if(loadinging)
		finishLoading(true);

	emit speedDial();
	stack->setCurrentIndex(1);
	emit titleChanged("Speed Dial");
	emit loading("Naveo::dial");
	urlEdit->setIcon(icon());
	urlEdit->setText("Naveo::dial");
	urlEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void webPage::resizeEvent(QResizeEvent *event)
{
	QMainWindow::resizeEvent(event);
}

void webPage::paintEvent(QPaintEvent *event)
{
	QMainWindow::paintEvent(event);
}

void webPage::startLoading()
{
	Browser::instance()->passManager()->getPass();
	gCompleter->setActive(false);
	showPage();
	if (!settings->value("showStop").toBool())
	{
		reloadAction->setVisible(false);
		stopAction->setVisible(true);

	}
	else
	{
		reloadAction->setEnabled(false);
		stopAction->setEnabled(true);
	}
	urlEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
	loadinging = true;
	movie = new QMovie(":/loading.gif");
	movie->start();
}

void webPage::updateIcon()
{
	if (loadinging)
	{
		emit isLoading(movie->currentPixmap());
		QTimer::singleShot(30, this, SLOT(updateIcon()));
	}
}

void webPage::updateUrlIcon(QPixmap pixmap)
{
	urlEdit->setIcon(QIcon(pixmap));
}

void webPage::finishLoading(bool ok)
{
	static_cast<Page* >(page->page())->enableJS();
	if(noError)
	{
		noError = false;
		return;
	}
	#ifdef INTEGRATED_FTP
	addToHistory();
	#endif
	gCompleter->setActive(true);
	if (!settings->value("showStop").toBool())
	{
		reloadAction->setVisible(true);
		stopAction->setVisible(false);
	}
	else
	{
		reloadAction->setEnabled(true);
		stopAction->setEnabled(false);
	}
	backAction->setEnabled(page->page()->history()->canGoBack());
	backButton->setEnabled(page->page()->history()->canGoBack());
	forwardAction->setEnabled(page->page()->history()->canGoForward());
	urlEdit->setIcon(icon());
	if (ok)
	{
		if (!settings->value("private").toBool())
		{
			emit pageChanged(page->url().toString(), title());
		}
		else
		{
			emit pageChanged("private", page->title());
		}
		if (page->url().toString().left(5) == "https")
		{
			urlEdit->setStyleSheet("background-color: rgb(255, 245, 195);");
			urlEdit->setIcon(QIcon(":/https.png"));
		}
		else
		{
			urlEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
		}
	}
	else if (isADownload)
	{
		urlEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
		isADownload = false;
	}
	else
	{
		urlEdit->setStyleSheet("background-color: rgb(255, 155, 140);");
		emit titleChanged(tr("Erreur"));
	}
	Browser::instance()->hManager()->add(url(), page->title());
	loadinging = false;
	movie->stop();
	delete movie;

	Browser::instance()->passManager()->setPage(page->page());

	if(javascriptConsole)
		javascriptConsole->clear();

	emit loading(url());
}

QString webPage::title()
{
	if(stack->currentIndex() == 0)
	{
		return page->title();
	}
	else
	{
		return "Speed Dial";
	}
}

void webPage::changeTitle(QString title)
{
	emit titleChanged(title);
}

void webPage::changeUrl(QUrl url)
{
	urlEdit->setText(url.toString());
}

QString webPage::homePage()
{
	return settings->value("home").toString();
}

void webPage::goToHome()
{
	loadUrl(homePage());
}

void webPage::loadUrl()
{
	loadUrl(urlEdit->text());
}

//--------------------------------------------------Load Url----------------------------------------------------
//---------------------------------------------VeryImportantFunction--------------------------------------------

void webPage::loadUrl(QUrl url)
{
	loadUrl(url.toString());
}

void webPage::loadUrl(QString url)
{
	if(url == "about:blank" || url.isEmpty())
	{
		return;
	}
	noError = loadinging;
	if (url == "Naveo::dial")
	{
		page->stop();
		QTimer::singleShot(50, this, SLOT(showDial()));
		return;
	}
	else
	{
		showPage();
	}
	if(Browser::instance()->bmManager()->nameList().contains(url))
	{
		loadUrl(Browser::instance()->bmManager()->urlList().at(Browser::instance()->bmManager()->nameList().indexOf(url)));
		return;
	}
	else if (url.left(6) == "ftp://")
	{
		QDesktopServices::openUrl(url);
		return;
	}
	else if (url.left(10) == "javascript")
	{
		QUrl jsurl(url);
		QString scriptSource = QUrl::fromPercentEncoding(jsurl.toString(Q_FLAGS(QUrl::TolerantMode | QUrl::RemoveScheme)).toAscii());
		page->page()->mainFrame()->evaluateJavaScript(scriptSource);
		return;
	}
	else if (settings->value("google").toBool() && (!url.contains(".") || url.contains(" ")) && !url.contains("/"))
	{
		url.replace(" ", "+");
		url = urlEdit->shearchMotorUrl(url);
		urlEdit->setText(url);
		page->load(QUrl(url));
	}
	else if (url.left(2).right(1) == ":" && url.left(1).toUpper() == url.left(1))
	{
		url = "file:///" + url;
		urlEdit->setText(url);
		page->load(QUrl(url));
	}
	else
	{
		#ifdef INTEGRATED_FTP
		isFtp = false;
		#endif
		if (url.left(8) != "https://")
				{
					if (url.left(7) != "http://" && url.left(6) != "ftp://" && url.left(8) != "file:///")
					{
						url = "http://" + url;
						urlEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
					}
					else
					{
						urlEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
					}
				}
				else
				{
					urlEdit->setStyleSheet("background-color: rgb(255, 245, 195);");
				}
		urlEdit->setText(url);
		page->load(QUrl(url));
	}
}

void webPage::addToBookMark()
{
	UrlDialog *dial = new UrlDialog(this, false, urlEdit->text(), true, page->title(), true);
	dial->setWindowTitle(tr("Nouveau favoris"));
	QString newUrl = dial->exec();
	QString name = dial->name();
	QString newDir = dial->selectedDir();
	delete dial;
	if (!name.isEmpty() && !newUrl.isEmpty())
	{
		Browser::instance()->bmManager()->add(newUrl,  name, newDir);
	}
}

void webPage::loadBookMark()
{
	QAction *action = qobject_cast<QAction *>(sender());
	loadUrl(action->toolTip());
}

void webPage::showBookMark()
{
	bookMarkMenu->exec(QCursor::pos());
}

void webPage::downloadFile(const QNetworkRequest & info)
{
	QUrl url = info.url();
	if (url.isValid())
	{
		isADownload = Browser::instance()->dlManager()->downloadFile(url);
	}
}

QString webPage::getFileName(QNetworkReply *reply)
{
	QString path;
	if (reply->hasRawHeader("Content-Disposition"))
	{
		QString value = reply->rawHeader("Content-Disposition");
		int pos = value.indexOf("filename=");
		if (pos != -1)
		{
			QString name = value.mid(pos + 9);
			if(name.right(1) == ";")
				name = name.left(name.size() - 1);
			if (name.startsWith(QLatin1Char('"')) && name.endsWith(QLatin1Char('"')))
				name = name.mid(1, name.size() - 2);
			path = name;
		}
	}
	if(path.isEmpty())
	{
		path = reply->url().path();
	}
	QFileInfo info(path);
	QString file = info.completeBaseName();

	if(!file.isEmpty())
	{
		file += "." + info.suffix();
	}
	return file;
}

void webPage::downloadFile(QNetworkReply *reply)
{
	if (!reply || reply->url().isEmpty())
		return;

	QVariant header = reply->header(QNetworkRequest::ContentLengthHeader);
	bool ok;
	int size = header.toInt(&ok);
	if (ok && size == 0)
		return;
	QUrl url = reply->url();
	if (url.isValid())
	{
		isADownload = true;
		Browser::instance()->dlManager()->downloadFile(url, getFileName(reply));
	}
}

void webPage::defineHome()
{
	settings->setValue("home", urlEdit->text());
}

void webPage::sources()
{
	emit showSources(page->url().toString());
}

QString webPage::url()
{
	return page->url().toString();
}

void webPage::updateBookMark()
{
	bookMarkMenu->clear();
	bookmarkBar->clear();
	bookMarkMenu->addAction(addBookMarkAction);
	bookMarkMenu->addAction(orgBookMarkAction);
	bookMarkMenu->addSeparator();
	QStringList name = Browser::instance()->bmManager()->nameList();
	QStringList url = Browser::instance()->bmManager()->urlList();
	QStringList dir = Browser::instance()->bmManager()->dirList();
	int i = 0;
	QStringList folders;
	QList<QMenu *> items;
	foreach(QString str , dir)
	{
		if (str != "/")
		{
			if (!folders.contains(str))
			{
				//std::cout<<"bookmarks updated : \""<<qPrintable(str)<<"\" repertory added"<<std::endl;
				folders.append(str);
				QStringList subDirs = str.split("/");
				subDirs.removeFirst();
				foreach(QString directory, subDirs)
				{
					QString lastFolder;
					foreach(QString folder, subDirs)
					{
						if(subDirs.indexOf(folder) <= subDirs.indexOf(directory))
						{
							lastFolder.append("/" + folder);
						}
					}
					bool hasItem = false;
					foreach(QMenu *item, items)
					{
						if (item->title() == directory && item->toolTip() == lastFolder)
						{
							hasItem = true;
						}
					}
					if (!hasItem)
					{
						if (subDirs.indexOf(directory) == 0)
						{
							QMenu *item = new QMenu(directory);
							bookMarkMenu->addMenu(item);
							item->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon));
							item->setToolTip(lastFolder);
							items.append(item);
						}
						else
						{
							QString list;
							foreach(QString folder, subDirs)
							{
									if(subDirs.indexOf(folder) < subDirs.indexOf(directory))
									{
										list.append("/" + folder);
									}
							}
							foreach(QMenu *item, items)
							{
								if (item->toolTip() == list)
								{
									QMenu *folderItem = new QMenu(directory);
									item->addMenu(folderItem);
									folderItem->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon));
									folderItem->setToolTip(lastFolder);
									items.append(folderItem);
									if (subDirs.first() == tr("barre"))
									{
										QToolButton *button = new QToolButton;
										button->setText(directory);
										button->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon));
										button->setMenu(folderItem);
										button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
										button->setPopupMode(QToolButton::InstantPopup);
										//button->setFlat(true);
										bookmarkBar->addWidget(button);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	foreach(QString str, name)
	{
		if (dir.at(i) != "/")
		{
			foreach(QMenu *parent, items)
			{
				if (parent->toolTip() == dir.at(i))
				{
					//std::cout<<"bookmarks updated : \""<<qPrintable(str)<<"\" action added"<<std::endl;
					QAction * item = new QAction(iconForUrl(url.at(i)), str, this);
					item->setToolTip(url.at(i));
					parent->addAction(item);
					connect(item, SIGNAL(triggered()), this, SLOT(loadBookMark()));
					if (parent->title() == tr("barre"))
					{
						bookmarkBar->addAction(item);
					}
				}
			}
		}
		else
		{
			//std::cout<<"bookmarks updated : \""<<qPrintable(str)<<"\" action added"<<std::endl;
			QAction * item = new QAction(iconForUrl(url.at(i)), str, this);
			item->setToolTip(url.at(i));
			bookMarkMenu->addAction(item);
			connect(item, SIGNAL(triggered()), this, SLOT(loadBookMark()));
		}
		i++;
	}
}

void webPage::updateOptions()
{
	settings = new QSettings(Browser::instance()->iniFile(), QSettings::IniFormat);
	if (settings->value("showStop").toBool())
	{
		stopAction->setVisible(true);
		stopAction->setEnabled(false);
	}
	else
	{
		stopAction->setVisible(false);
		stopAction->setEnabled(true);
	}
	page->setBlockPopup(settings->value("block").toBool());
	page->setDarkMode(settings->value("dark").toBool());
	homeAction->setVisible(settings->value("showHome").toBool());
	themeDir = settings->value("theme").toString();
	backButton->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/back.png"));
	backAction->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/back.png"));
	forwardAction->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/forward.png"));
	stopAction->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/stop.png"));
	reloadAction->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/reload.png"));
	homeAction->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/home.png"));
	newTabAction->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/new.png"));
	showDownloadAction->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/down.png"));
	bookMarkAction->setIcon(QIcon(qApp->applicationDirPath() + "/themes/" + themeDir + "/bookMark.png"));
	dialAction->setVisible(settings->value("speedDial").toBool());
	showDownloadButton->setVisible(settings->value("dlInk").toBool());
	bookmarkBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	urlEdit->load();
	if (settings->value("perso").toBool())
	{
		bookmarkBar->close();
	}
	else
	{
		bookmarkBar->show();
		insertToolBarBreak(bookmarkBar);
		switch (settings->value("posPerso").toInt())
		{
			case 1:
				addToolBar(Qt::BottomToolBarArea, bookmarkBar);
			break;
			case 2:
				addToolBar(Qt::LeftToolBarArea, bookmarkBar);
			break;
			case 3:
				addToolBar(Qt::RightToolBarArea, bookmarkBar);
			break;
			default:
				addToolBar(bookmarkBar);
			break;
		}
	}
	setAutoFillBackground(!settings->value("toolbarTranparency").toBool() || !settings->value("transparency").toBool());
	page->setZoomFactor(settings->value("zoom").toInt());
	if (settings->value("posNav").toInt() == 1)
	{
		if (settings->value("posPerso").toInt() == 1)
		{
			insertToolBar(bookmarkBar, toolBar);
		}
		else
		{
			addToolBar(Qt::BottomToolBarArea, toolBar);
		}
	}
	else
	{
		if (settings->value("posPerso").toInt() == 0)
		{
			insertToolBar(bookmarkBar, toolBar);
		}
		else
		{
			addToolBar(toolBar);
		}
	}
	insertToolBarBreak(bookmarkBar);
}

void webPage::findNext()
{
	QString shearch = findEdit->text();
	if (!shearch.isEmpty())
	{
		if (!page->findText(shearch))
		{
			findEdit->setStyleSheet("background-color: rgb(255, 155, 140);");
		}
		else
		{
			findEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
		}
		page->setFocus();
	}
}

void webPage::findPrevious()
{
	QString shearch = findEdit->text();
	if (!shearch.isEmpty())
	{
		if (!page->findText(shearch, QWebPage::FindBackward))
		{
			findEdit->setStyleSheet("background-color: rgb(255, 155, 140);");
		}
		else
		{
			findEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
		}
		page->setFocus();
	}
}

void webPage::showBar()
{
	if(findBar->isHidden())
	{
		findBar->setFixedHeight(10);
		findBar->show();
	}
	if(findBar->height() < 30)
	{
		findBar->setFixedHeight(findBar->height() + 3);
		QTimer::singleShot(20, this, SLOT(showBar()));
	}
}

void webPage::keyPressEvent(QKeyEvent *event)
{
	if (event == QKeySequence::Find){
		showBar();}
	else if (event == QKeySequence::Print){
		print();}
	else if (event == QKeySequence::Copy){
		copy();}
	else if (event->key() == Qt::Key_F11 && !window()->isFullScreen()){
		#ifdef Q_WS_WIN
		setAutoFillBackground(true);
		#endif
		emit setFullScreen(true);}
	else if (event->key() == Qt::Key_F11 && window()->isFullScreen()){
		#ifdef Q_WS_WIN
		setAutoFillBackground(!settings->value("toolbarTranparency").toBool() || !settings->value("transparency").toBool());
		#endif
		emit setFullScreen(false);}
	else if (event == QKeySequence::AddTab){
		createNewPage();}
	else if (event == QKeySequence::Replace){
		Browser::instance()->hManager()->show();}
	else if (event == QKeySequence::HelpContents){
		Browser::instance()->showHelp();}
	else if (event == QKeySequence::Underline){
		sources();}
	else if (event == QKeySequence::ZoomIn) {
		zoomIn();}
	else if (event == QKeySequence::ZoomOut) {
		zoomOut();
	}
}

void webPage::restoreZoom()
{
	page->setZoomFactor(1);
}

void webPage::zoomIn()
{
	if(page->zoomFactor() < 2)
		page->setZoomFactor(page->zoomFactor() + 0.1);
}

void webPage::zoomOut()
{
	if(page->zoomFactor() > 0.5)
		page->setZoomFactor(page->zoomFactor() - 0.1);
}

void webPage::savePage()
{
	Browser::instance()->dlManager()->downloadFile(page->url());
}

void webPage::print()
{
	/*QPrinter *printer = new QPrinter;
	QPrintDialog printDialog(printer);
	if (printDialog.exec() == QDialog::Accepted)
	{
		emit needPrint(printer);
	}*/
	QPrintPreviewDialog *dialog = new QPrintPreviewDialog(this);
	connect(dialog, SIGNAL(paintRequested(QPrinter *)), this, SIGNAL(needPrint(QPrinter*)));
	dialog->exec();
}

void webPage::createNewPage(WebView *newPage)
{
	emit openTab(new webPage(newPage));
}

void webPage::createNewPage()
{
	emit openTab(new webPage());
}

void webPage::copy()
{
	QClipboard *clip = QApplication::clipboard();
	clip->setText(page->selectedText());
}

void webPage::authentification(QNetworkReply */*reply*/, QAuthenticator */*authenticator*/)
{

}

void webPage::goToDial()
{
	loadUrl("Naveo::dial");
}


WebView *webPage::view()
{
	return page;
}

QToolBar *webPage::bar()
{
	return toolBar;
}

QMenu *webPage::menu()
{
	return settingMenu;
}

QIcon webPage::icon()
{
	if(stack->currentIndex() != 0)
	{
		return QIcon(":/speedDial.png");
	}

	QIcon icon = QWebSettings::iconForUrl(QUrl(page->url()));
	if (!icon.isNull())
	{
		return icon;
	}
	return QIcon(":/default.png");
}

QIcon webPage::iconForUrl(QString url)
{
	QIcon icon = QWebSettings::iconForUrl(QUrl(url));
	if (!icon.isNull())
	{
		return icon;
	}
	return QIcon(":/default.png");
}


void UrlLineEdit::load()
{
	QSettings settings(naveoConfigurationPath + "/Options.ini", QSettings::IniFormat);
	motor = settings.value("motor", motor).toString();
	motorButton->setStyleSheet("QPushButton{background-image: url(':/" + motor + ".png');}"
							  "QPushButton::pressed{border : none; background-image: url(':/" + motor + ".png');}"
							  "QPushButton::hover{background-image: url(':/" + motor + ".png');}");
}


void UrlLineEdit::change()
{
	QSettings settings(naveoConfigurationPath + "/Options.ini", QSettings::IniFormat);
	settings.setValue("motor", motor);
	motorButton->setStyleSheet("QPushButton{background-image: url(':/" + motor + ".png');}"
							  "QPushButton::pressed{border : none; background-image: url(':/" + motor + ".png');}"
							  "QPushButton::hover{background-image: url(':/" + motor + ".png');}");
}
