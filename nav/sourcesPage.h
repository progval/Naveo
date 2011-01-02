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


#ifndef HEADER_SOURCESPAGE
#define HEADER_SOURCESPAGE

#include <QtGui>
#include <iostream>

using namespace std;


class Highlighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	Highlighter(QTextDocument *parent = 0);

protected:
	void highlightBlock(const QString &text);

private:
	struct HighlightingRule
	{
			QRegExp pattern;
			QTextCharFormat format;
	};
	QVector<HighlightingRule> highlightingRules;
	QTextCharFormat tagFormat;
	QTextCharFormat valueFormat;
	QTextCharFormat numberFormat;
	QRegExp commentEndExpression;
	QRegExp commentStartExpression;
	QTextCharFormat attributFormat;
	QTextCharFormat multiLineCommentFormat;

};



class sourcesPage : public QPlainTextEdit
{
	Q_OBJECT

	public:
		sourcesPage();
		void setText(QString text);

		void lineNumberAreaPaintEvent(QPaintEvent *event);
		int lineNumberAreaWidth();

	protected:
		void resizeEvent(QResizeEvent *event);
		void contextMenuEvent(QContextMenuEvent *event);

	private slots:
		void updateLineNumberAreaWidth(int newBlockCount);
		void highlightCurrentLine();
		void updateLineNumberArea(const QRect &, int);

	private:
		Highlighter *highlighter;
		QWidget *lineNumberArea;
};


class LineNumberArea : public QWidget
{
public:
	LineNumberArea(sourcesPage *editor) : QWidget(editor) {
		edit = editor;
	}

	QSize sizeHint() const {
		return QSize(edit->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent *event) {
		edit->lineNumberAreaPaintEvent(event);
	}

private:
	sourcesPage *edit;

};

class sourcesEditor : public QMainWindow
{
	Q_OBJECT

	public:
		sourcesEditor();
		sourcesEditor(QString text);
		void setText(QString text);
		QMenu *menu();

	public slots:
		void save();
		void findNext();
		void findPrevious();
		void showBar();

	private:
		void create();
		sourcesPage *edit;
		QToolBar *findBar;
		QLineEdit *findEdit;
		QMenu *editMenu;
		QAction *saveAction;
		QAction *searchAction;
		QAction *cutAction;
		QAction *copyAction;
		QAction *pasteAction;

};


#endif

