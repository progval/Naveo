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


#include "page.h"
#include "Browser.h"

Page::Page()
{
	console = 0;
	jsDisabled = false;
}

void Page::setConsole(JavascriptConsole *c)
{
	console = c;
}

void Page::enableJS()
{
	jsDisabled = false;
}

void Page::triggerAction(WebAction action, bool checked)
{
	if(action == QWebPage::InspectElement)
	{
		return;
	}
	QWebPage::triggerAction(action, checked);
}

QString Page::userAgentForUrl(QUrl url)
{
	return QString("Naveo " + QString(VERSION) + " for " + url.toString() + " powered by QtWebKit");
}

void Page::javaScriptConsoleMessage(const QString &message, int lineNumber, const QString &sourceID)
{
	if(!console)
		return;

	cout<<"javascript message : "<<qPrintable(message)<<endl;
	console->addText(QString(/*"<img src=\":/error.png\" alt=\">\"/ >*/" %1 \t(at line %2 of \"%3\")").arg(message).arg(lineNumber).arg(sourceID));
}

void Page::javaScriptAlert(QWebFrame *frame, const QString &msg)
{
	info(frame->title(), msg);
}

bool Page::javaScriptConfirm(QWebFrame *frame, const QString &msg)
{
	return question(frame->title(), msg);
}

bool Page::javaScriptPrompt(QWebFrame *frame, const QString &msg, const QString &defaultValue, QString *result)
{
	return input(frame->title(), msg, defaultValue, result);;
}


void Page::info(QString title, QString msg)
{
	if(jsDisabled)
		return ;

	QDialog *dial = new QDialog(this->view());
	dial->setWindowTitle(title);
	QHBoxLayout *lay = new QHBoxLayout;
	QVBoxLayout *mainLay = new QVBoxLayout;
	QHBoxLayout *buttonLay = new QHBoxLayout;
	QLabel *icon = new QLabel(dial);
	QPushButton *ok = new QPushButton(tr("Ok"), dial);
	QCheckBox *box = new QCheckBox(tr("Empêcher cette page d'ouvrir plus de boites de dialogue"));
	buttonLay->addStretch();
	buttonLay->addWidget(ok);
	connect(ok, SIGNAL(clicked()), dial, SLOT(accept()));
	icon->setPixmap(Browser::instance()->style()->standardIcon(QStyle::SP_MessageBoxInformation).pixmap(QSize(64, 64)));
	lay->addWidget(icon);
	lay->addWidget(new QLabel(msg));
	mainLay->addLayout(lay);
	mainLay->addWidget(box);
	mainLay->addLayout(buttonLay);
	dial->setLayout(mainLay);
	dial->exec();
	jsDisabled = box->isChecked();
	delete dial;
}

bool Page::question(QString title, QString msg)
{
	if(jsDisabled)
		return false;


	QDialog *dial = new QDialog(this->view());
	dial->setWindowTitle(title);
	QHBoxLayout *lay = new QHBoxLayout;
	QVBoxLayout *mainLay = new QVBoxLayout;
	QHBoxLayout *buttonLay = new QHBoxLayout;
	QPushButton *yes = new QPushButton(tr("Oui"), dial);
	QPushButton *no = new QPushButton(tr("Non"), dial);
	QCheckBox *box = new QCheckBox(tr("Empêcher cette page d'ouvrir plus de boites de dialogue"));
	buttonLay->addStretch();
	buttonLay->addWidget(yes);
	buttonLay->addWidget(no);
	QLabel *icon = new QLabel(dial);
	connect(yes, SIGNAL(clicked()), dial, SLOT(accept()));
	connect(no, SIGNAL(clicked()), dial, SLOT(reject()));
	icon->setPixmap(Browser::instance()->style()->standardIcon(QStyle::SP_MessageBoxQuestion).pixmap(QSize(64, 64)));
	lay->addWidget(icon);
	lay->addWidget(new QLabel(msg));
	mainLay->addLayout(lay);
	mainLay->addWidget(box);
	mainLay->addLayout(buttonLay);
	dial->setLayout(mainLay);
	int i = dial->exec();
	jsDisabled = box->isChecked();
	delete dial;
	return (i == 1);
}

bool Page::input(QString title, QString msg, QString defaultValue, QString *result)
{
	if(jsDisabled)
		return false;

	QDialog *dial = new QDialog(this->view());
	dial->setWindowTitle(title);
	QVBoxLayout *mainLay = new QVBoxLayout;
	QHBoxLayout *buttonLay = new QHBoxLayout;
	QPushButton *ok = new QPushButton(tr("Ok"), dial);
	QLineEdit *line = new QLineEdit;
	QCheckBox *box = new QCheckBox(tr("Empêcher cette page d'ouvrir plus de boites de dialogue"));
	line->setText(defaultValue);
	buttonLay->addStretch();
	buttonLay->addWidget(ok);
	connect(ok, SIGNAL(clicked()), dial, SLOT(accept()));
	mainLay->addWidget(new QLabel(msg));
	mainLay->addWidget(line);
	mainLay->addWidget(box);
	mainLay->addLayout(buttonLay);
	dial->setLayout(mainLay);
	int i = dial->exec();
	jsDisabled = box->isChecked();
	*result = line->text();
	delete dial;
	return ((i == 1) && !(result->isEmpty()));
}
