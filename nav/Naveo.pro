# #####################################################################
# Automatically generated by qmake (2.01a) jeu. 2. juil. 13:43:40 2009
# #####################################################################


#TEMPLATE = app

TEMPLATE = app
#CONFIG += dll
#TEMPLATE = lib

TARGET =
QT += webkit
QT += network
CONFIG += console

# Input
HEADERS += path.h \
	Browser.h \
	CookieJar.h \
	googlesuggest.h \
	httpget.h \
	mainWin.h \
	settingsDialog.h \
	webPage.h \
	sourcesPage.h \
	version.h \
	download.h \
	downloadWidget.h \
	webview.h \
	bookmarkmanager.h \
	historymanager.h \
	helper.h \
	page.h \
	synchronizer.h \
	bookmarktree.h \
	speeddial.h \
	about.h \
	urldialog.h \
	javascriptconsole.h \
	cleardialog.h \
	pluginmanager.h \
	plugindialog.h \
	dockwidget.h \
	lib.h \
	passwordmanager.h \
	networkaccessmanager.h \
    formwindow.h
FORMS += ui/settings.ui
SOURCES += Browser.cpp \
	CookieJar.cpp \
	googlesuggest.cpp \
	httpget.cpp \
	main.cpp \
	mainWin.cpp \
	settingsDialog.cpp \
	webPage.cpp \
	download.cpp \
	sourcesPage.cpp \
	downloadWidget.cpp \
	webview.cpp \
	bookmarkmanager.cpp \
	historymanager.cpp \
	helper.cpp \
	page.cpp \
	synchronizer.cpp \
	bookmarktree.cpp \
	speeddial.cpp \
	about.cpp \
	urldialog.cpp \
	javascriptconsole.cpp \
	cleardialog.cpp \
	pluginmanager.cpp \
	plugindialog.cpp \
	dockwidget.cpp \
	passwordmanager.cpp \
	networkaccessmanager.cpp \
    formwindow.cpp
RESOURCES += ressources/ressources.qrc
win32:RC_FILE *= ressources/Ress.rc
