#include "dial.h"

Dial::Dial(QWidget *parent) :
	QGraphicsView(parent)
{
	scene = new QGraphicsScene;
	add = new QPushButton(tr("Ajouter"));
	add->setFixedSize(512, 512);

	QGraphicsProxyWidget *proxy = scene->addWidget(add);
	proxy->setTransform(setPosition(50, 50, 0.6));
	proxies.append(proxy);


	setScene(scene);

	connect(add, SIGNAL(clicked()), this, SLOT(addPage()));
}

QTransform Dial::setPosition(qreal x, qreal y, qreal z)
{
	QTransform matrix;// = new QTransform;
	matrix.translate(x, y);
	matrix.scale(z, z);
	return matrix;
}

void Dial::addPage()
{
	QString url = QInputDialog::getText(this, tr("Ajouter"), tr("Entrez l'adresse web :"));
	WebView *view = new WebView;
	view->setBlockPopup(true);
	connect(view, SIGNAL(loadFinished(bool)), this, SLOT(loadingFinished(bool)));
	view->load(QUrl(url));
}

void Dial::loadingFinished(bool ok)
{
	QPixmap pix(512, 512);
	if(!ok)
		pix.load(":/icon.png");
	else
		static_cast<WebView *>(sender())->render(&pix);

	delete sender();

	QLabel *label = new QLabel;
	label->setPixmap(pix);
	pages.append(label);


	proxies.append(scene->addWidget(label));


	double angle = 360 / (proxies.count());

	for(double i = 0; i != proxies.count(); i++)
	{
		double x = cos(angle * i * 0.017453292519943295769236907684886);
		double y = fabs(x);

		cout<<y<<endl;

		proxies[(int)floor(i)]->setTransform(setPosition(x * 100, height() / 2 - 256, y));
	}

}
