/*******************************
Copyright (C) 2009-2010 gr�goire ANGERAND

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

#include "passwordmanager.h"
#include "Browser.h"
#include "version.h"


PasswordManager::PasswordManager(QObject *parent) :
	QObject(parent)
{
	page = 0;
	load();
}

void PasswordManager::setPage(QWebPage *p)
{
	page = p;
	extract();
	setPass();
}

void PasswordManager::setPass()
{
	if(!page) {
		cout<<"Unable to complete forms !"<<endl;
		return;
	}

	for(int i = 0; i != forms.count(); i++)
	{
		if(forms[i].url == page->mainFrame()->url() && !forms[i].value.isEmpty())
		{
			QWebElement element = page->mainFrame()->findFirstElement("#" + forms[i].name);
			if(!element.isNull()) {
				element.setAttribute("value", forms[i].value);
			} else
				cout<<"Error : can not use a null element !"<<endl;
		}
	}
}

void PasswordManager::getPass()
{
	if(!page) {
		return;
	}

	for(int i = 0; i != list.count(); i++)
	{
		if(list[i].url == page->mainFrame()->url() && list[i].value.isEmpty())
		{
			QWebElement element = page->mainFrame()->findFirstElement("#" + list[i].name);
			if(!element.isNull()) {
				list[i].value = element.evaluateJavaScript("this.value").toString();
			} else
				cout<<"Error : can not use a null element !"<<endl;
		}
	}
	if(hasPass)
		emit savePass();

	hasPass = false;
}

void PasswordManager::extract()
{
	if(!page)
		return;

	list.clear();

	QWebElementCollection elements = page->mainFrame()->findAllElements("input[type=text]");
	int i = elements.count();
	elements.append(page->mainFrame()->findAllElements("input[type=password]"));
	for(int i = 0; i != elements.count(); i++)
	{
		if(!elements[i].isNull() && elements[i].attribute("autocomplete") != "off")
		{
			Form f;
			f.url = page->mainFrame()->url();
			f.name = elements[i].attribute("id");
			f.save = false;
			if(!f.name.isEmpty())
			{
				bool found = false;
				for(int j = 0; j != forms.count(); j++)
				{
					if(forms[j].name == f.name && forms[j].url == f.url)
					{
						found = true;
						break;
					}
				}
				if(!found)
					list.append(f);
			}
		}
	}

	hasPass = (i != elements.count() && list.count());
}

void PasswordManager::yesOnce()
{
	forms.append(list);
}

void PasswordManager::yes()
{
	for(int i = 0; i != list.count(); i++)
	{
		list[i].save = true;
	}
	yesOnce();
}



void PasswordManager::save()
{
	{
		QSettings set(Browser::instance()->iniFile("forms.txt"), QSettings::IniFormat);
		QStringList names;
		QStringList urls;
		QStringList values;
		foreach(Form f, forms)
		{
			if(f.save && !f.value.isEmpty())
			{
				names.append(f.name);
				values.append(f.value);
				urls.append(f.url.toString());
			}
		}
		set.setValue("values", values);
		set.setValue("names", names);
		set.setValue("urls", urls);
	}
	#ifdef USE_GAN_H
		QFile file(Browser::instance()->iniFile("forms.txt"));
		if(file.open(QIODevice::ReadWrite))
		{
			file.write(gan_::encryption::encrypt(file.peek(file.size() + 1)));
			file.close();
		}
	#endif
}

void PasswordManager::load()
{
	#ifdef USE_GAN_H
		QFile file(Browser::instance()->iniFile("forms.txt"));
		if(file.open(QIODevice::ReadWrite))
		{
			file.write(gan_::encryption::uncrypt(file.peek(file.size() + 1)));
			file.close();
		}
	#endif
	QSettings set(Browser::instance()->iniFile("forms.txt"), QSettings::IniFormat);
	QStringList names = set.value("names", QStringList()).toStringList();
	QStringList urls = set.value("urls", QStringList()).toStringList();
	QStringList values = set.value("values", QStringList()).toStringList();
	cout<<names.count()<<" forms to load"<<endl;
	for(int i = 0; i != names.count(); i++)
	{
		Form f;
		f.save = true;
		f.name = names[i];
		f.value = values[i];
		f.url = QUrl(urls[i]);
		forms.append(f);
	}
}
