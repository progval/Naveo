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


#include "httpget.h"
#include "Browser.h"

HttpGet::HttpGet()
{
	manager = new QNetworkAccessManager;
	canceled = false;
}

bool HttpGet::getFile(QUrl url, QString toSave)
{
	if (!url.isValid() || url.path().isEmpty())
		return false;

	file.setFileName(toSave);

	if (!file.open(QIODevice::WriteOnly))
		return false;

	reply = manager->get(QNetworkRequest(url));
	reply->setParent(this);

	if (!reply)
		return false;

	connect(reply, SIGNAL(readyRead()), this, SLOT(download()));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(cancel()));
	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(progress(qint64, qint64)));
	connect(reply, SIGNAL(finished()), this, SLOT(httpDone()));

	if (reply->error() != QNetworkReply::NoError)
	{
		return false;
	}
	return true;
}

void HttpGet::download()
{
	if (!canceled)
	{
		if(!file.isOpen())
		{
			if(!file.open(QIODevice::WriteOnly))
			{
				cout<<"unable to open file"<<endl;
				cancel();
			}
		}
		if(file.write(reply->readAll()) == -1)
		{
			cout<<"Reading failed !"<<endl;
			cancel();
		}
	}
}


void HttpGet::cancel()
{
	/*if(static_cast<QNetworkReply *>(sender()) != 0)
	{
		cout<<"error : "<<qPrintable(static_cast<QNetworkReply *>(sender())->errorString())<<endl;
	}*/

	file.close();
	file.remove();
	canceled = true;
	emit done(true);
}

int HttpGet::error()
{
	return reply->error();
}

void HttpGet::httpDone()
{
	if (canceled)
	{
		cout<<"download canceled"<<endl;
		return;
	}
	if (reply->error() != QNetworkReply::NoError)
	{
		cout<<"download failed"<<endl;
		cancel();
		QMessageBox::critical(0, tr("Opération impossible"),tr("Impossible de télécharger le fichier : \nErreur  %1").arg(reply->error()));
	}
	else
	{
		file.close();
		emit done(false);
	}
}

