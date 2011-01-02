#ifndef GOOGLESUGGEST_H
#define GOOGLESUGGEST_H

#include <QtGui>
#include <QtNetwork>
#include <iostream>

using namespace std;

QT_BEGIN_NAMESPACE
class QLineEdit;
class QNetworkReply;
QT_END_NAMESPACE

class GSuggestCompletion : public QObject
{
	Q_OBJECT

	public:
		GSuggestCompletion(QLineEdit *parent = 0);
		void showCompletion(const QStringList &choices);
		void setActive(bool a);

	public slots:
		void autoSuggest();
		void handleNetworkData(QNetworkReply *networkReply);

	private:
		QString GSUGGEST_URL;
		bool active;
		QLineEdit *editor;
		QStringList pagesList;
		QStringList bookMarkList;
		QNetworkAccessManager networkManager;
};

#endif // GOOGLESUGGEST_H

