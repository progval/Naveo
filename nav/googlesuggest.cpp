#include <QtCore>
#include <QtGui>
#include <QtNetwork>

#include "googlesuggest.h"
#include "Browser.h"

GSuggestCompletion::GSuggestCompletion(QLineEdit *parent): QObject(parent), editor(parent)
{
	GSUGGEST_URL = QString("http://google." + QLocale::system().name().left(2) + "/complete/search?output=toolbar&q=%1");
	connect(editor, SIGNAL(textEdited(QString)), this, SLOT(autoSuggest()));

	connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(handleNetworkData(QNetworkReply*)));
	editor->setFocus();
	active = false;
}


void GSuggestCompletion::showCompletion(const QStringList &choices)
{
	editor->setCompleter(new QCompleter(choices));
	editor->completer()->popup()->move(editor->mapToGlobal(QPoint(22, editor->height())));
	editor->completer()->popup()->resize(QSize(editor->width() - 66, choices.count() * 17));
	editor->completer()->popup()->show();
}

void GSuggestCompletion::setActive(bool a)
{
	active = a;
}

void GSuggestCompletion::autoSuggest()
{
	QString str = editor->text();
	QString url = QString(GSUGGEST_URL).arg(str);
	networkManager.get(QNetworkRequest(QString(url)));
}

void GSuggestCompletion::handleNetworkData(QNetworkReply *networkReply)
{
	//QUrl url = networkReply->url();
	if (!networkReply->error()) {
		QStringList choices;
		QStringList hits;

		QString response(networkReply->readAll());
		QXmlStreamReader xml(response);
		while (!xml.atEnd()) {
			xml.readNext();
			if (xml.tokenType() == QXmlStreamReader::StartElement)
				if (xml.name() == "suggestion") {
					QStringRef str = xml.attributes().value("data");
					choices<<str.toString();
				}
			if (xml.tokenType() == QXmlStreamReader::StartElement)
				if (xml.name() == "num_queries") {
					QStringRef str = xml.attributes().value("int");
					hits<<str.toString();
				}
		}
		if(active)
			showCompletion(choices);
	}

	networkReply->deleteLater();
}
