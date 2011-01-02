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

#include "speeddial.h"
#include "Browser.h"

SpeedDial::SpeedDial(QWidget *parent) :
	QWidget(parent)
{
	QSettings set(Browser::instance()->iniFile(), QSettings::IniFormat);
	set.beginGroup("dial");
	QStringList pages = set.value("url", QStringList()).toStringList();
	set.endGroup();
	lay = new QGridLayout;
	for(int i = 0; i != 3; i++)
	{
		for(int j = 0; j != 3; j++)
		{
			LinkButton *b = new LinkButton(this);
			connect(b, SIGNAL(added()), this, SLOT(save()));
			b->setUrl(pages.at(j + (3 * i)));
			lay->addWidget(b, i, j);
		}
	}
	setLayout(lay);
	resize(600, 600);
}

void SpeedDial::save()
{
	QStringList list;
	QSettings set(Browser::instance()->iniFile(), QSettings::IniFormat);
	set.beginGroup("dial");
	for(int i = 0; i != 3; i++)
	{
		for(int j = 0; j != 3; j++)
		{
			list<<static_cast<LinkButton *>(lay->itemAtPosition(i, j)->widget())->pageUrl();
		}
	}
	set.setValue("url", list);
	set.endGroup();
}

void SpeedDial::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	int k = height() - (x() - lay->itemAtPosition(0, 0)->widget()->x());
	if(k > width())
	{
		k = width();
	}
	for(int i = 0; i != 3; i++)
	{
		for(int j = 0; j != 3; j++)
		{
			lay->itemAtPosition(i, j)->widget()->resize((k - 30) / 3, (k - 30) / 3);
		}
	}
}

void SpeedDial::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_F11 && !window()->isFullScreen()){
		emit setFullScreen(true);}
	else if (event->key() == Qt::Key_F11 && window()->isFullScreen()){
		emit setFullScreen(false);}
	else if (event == QKeySequence::Replace){
		Browser::instance()->hManager()->show();}
	else if (event == QKeySequence::HelpContents){
		Browser::instance()->showHelp();}
}



LinkButton::LinkButton(QWidget *parent) :
	QWidget(parent)
{
	setMinimumSize(100, 100);
	clearButton = new QPushButton(QIcon(":/closetab.png"), "", this);
	clearButton->move(5, 5);
	clearButton->setFixedSize(20, 20);
	clearButton->setFlat(true);
	clearButton->hide();

	pix = 0;

	inside = false;

	label = new QLabel(this);
	label->move(30, 8);
	label->hide();

	if(!url.isEmpty())
	{
		if(url.left(7) != "http://")
		{
			url = "http://" + url;
		}
		createPage();
	}

	connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
}

void LinkButton::image(bool ok)
{
	if (ok)
	{
		pix = new QPixmap(640, 480);
		view->render(pix);
		label->setText(view->title());

		//cout<<"loading finished for "<<qPrintable(url)<<endl;

		// add pixmap to cache
		QSettings set(qApp->applicationDirPath() + "/cache/speedDial/cache.ini", QSettings::IniFormat);
		QString fileName = "0";
		for(int i = 1; QFile(QString(qApp->applicationDirPath() + "/cache/speedDial/%1.png").arg(i)).exists(); i++)
		{
			fileName = QString("%1").arg(i);
		}
		if(pix->save(qApp->applicationDirPath() + "/cache/speedDial/" + fileName + ".png"))
		{
			QStringList cache = set.value("cache", QStringList()).toStringList();
			cache<<url;
			set.setValue("cache", cache);
			QStringList names = set.value("names", QStringList()).toStringList();
			names<<label->text();
			set.setValue("names", names);
			QStringList pixmaps = set.value("pix", QStringList()).toStringList();
			pixmaps<<fileName;
			set.setValue("pix", pixmaps);
		}

		view->deleteLater();
		repaint();

	}
	else
	{
		label->setText(url);
		pix = new QPixmap(QIcon(":/void.png").pixmap(QSize(128, 128)));
		view->deleteLater();
		repaint();
	}
}

void LinkButton::setUrl(QString newUrl)
{
	url = newUrl;
	createPage();
}

QString LinkButton::pageUrl()
{
	return url;
}

void LinkButton::keyPressEvent(QKeyEvent *event)
{
	//cout<<"-"<<endl;
	/*if (event->key() == Qt::Key_F11 && !window()->isFullScreen()){
		emit setFullScreen(true);}
	else if (event->key() == Qt::Key_F11 && window()->isFullScreen()){
		emit setFullScreen(false);}
	else if (event == QKeySequence::Replace){
		Browser::instance()->hManager()->show();}
	else if (event == QKeySequence::HelpContents){
		Browser::instance()->showHelp();}+*/
}



void LinkButton::clear()
{
	url.clear();
	clearButton->hide();
	delete pix;
	pix = 0;
	label->hide();
	repaint();
	emit added();
}

void LinkButton::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing);

	/*QPen pen(QColor(150, 150, 150));
	pen.setWidth(1);

	painter->setPen(pen);
	painter->drawRoundedRect(rect().x() + 2, rect().y() + 2, rect().width() - 2, rect().height() - 2, 10, 10, Qt::AbsoluteSize);*/

	if(pix != 0 && !url.isEmpty())
	{
		QPixmap p = pix->scaled(width() - 20, height() - 20);
		if(inside)
		{
			painter->drawPixmap(QRect(10, 30, width() - 20, height() - 40), p);
		}
		else
		{
			painter->drawPixmap(QRect(10, 10, width() - 20, height() - 20), p);
		}
	}


	painter->setPen(/*QColor(250, 250, 250)*/QColor(5,5,5));
	painter->drawRoundedRect(rect().x() + 1, rect().y() + 1, rect().width() - 3, rect().height() - 3, 10, 10, Qt::AbsoluteSize);

	if(url.isEmpty())
	{
		painter->drawText(QPoint((mapFromParent(pos()).x() + (height() / 2) - 10), mapFromParent(pos()).y() + (width() / 2)), tr("Vide"));
	}

	painter->end();
}

void LinkButton::createPage()
{
	QSettings set(qApp->applicationDirPath() + "/cache/speedDial/cache.ini", QSettings::IniFormat);
	if(set.value("cache", QStringList()).toStringList().contains(url))
	{
		pix = new QPixmap(qApp->applicationDirPath() + "/cache/speedDial/" + set.value("pix", QStringList()).toStringList().at(set.value("cache", QStringList()).toStringList().indexOf(url)) + ".png");
		label->setText(set.value("names", QStringList()).toStringList().at(set.value("cache", QStringList()).toStringList().indexOf(url)));
	}
	else
	{
		label->setText("Chargement ...");
		view = new WebView;
		view->setFixedSize(640, 480);
		view->setZoomFactor(0.7);
		view->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
		view->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
		connect(view, SIGNAL(loadFinished(bool)), this, SLOT(image(bool)));
		view->setBlockPopup(true);
		view->load(QUrl(url));
	}
}

void LinkButton::mousePressEvent(QMouseEvent * event)
{
	if(event->button() == Qt::LeftButton)
	{
		if(url.isEmpty())
		{
			url = Browser::getUrl(qobject_cast<QWidget *>(parent()), tr("Ajouter"));
			if(!url.isEmpty())
			{
				if(url.left(7) != "http://")
				{
					url = "http://" + url;
				}
				createPage();
			}
			emit added();
			leaveEvent(event);
		}
		else
		{
			emit selected(url);
			QMessageBox::critical(this, "fghj", "fghj");
		}
	}
}

void LinkButton::enterEvent(QEvent *event)
{
	QWidget::enterEvent(event);
	if(!url.isEmpty())
	{
		clearButton->show();
		label->show();
	}
	inside = true;
	repaint();
}

void LinkButton::leaveEvent(QEvent *event)
{
	QWidget::leaveEvent(event);
	clearButton->hide();
	label->hide();
	inside = false;
	repaint();
}

void LinkButton::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	label->setFixedWidth(event->size().width() - 40);
}
