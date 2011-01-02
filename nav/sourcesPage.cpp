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


#include "sourcesPage.h"
#include "Browser.h"

sourcesEditor::sourcesEditor(QString text)
{
	create();
	edit->setText(text);
}

sourcesEditor::sourcesEditor()
{
	create();
}

void sourcesEditor::create()
{
	QSettings settings(qApp->applicationDirPath() + "/Options.ini", QSettings::IniFormat);
	setAutoFillBackground(!settings.value("toolbarTranparency").toBool());

	edit = new sourcesPage;

	editMenu = new QMenu;

	QToolBar *toolBar = new QToolBar(tr("Editer"));
	findBar = new QToolBar(tr("Rechercher"));

	findBar->setMovable(false);
	toolBar->setMovable(false);

	saveAction = new QAction(QIcon(":/save.png"), tr("Enregistrer"), this);
	searchAction = new QAction(QIcon(":/search.png"), tr("Rechercher"), this);
	cutAction = new QAction(QIcon(":/cut.png"), tr("Couper"), this);
	copyAction = new QAction(QIcon(":/copy.png"), tr("Copier"), this);
	pasteAction = new QAction(QIcon(":/paste.png"), tr("Coller"), this);

	searchAction->setShortcut(QKeySequence(QKeySequence::Find));

	QPushButton *closeButton = new QPushButton("X");
	QPushButton *findNextButton = new QPushButton("<");
	QPushButton *findPreviousButton = new QPushButton(">");

	closeButton->setFixedWidth(30);
	findPreviousButton->setFixedWidth(30);
	findNextButton->setFixedWidth(30);

	findEdit = new QLineEdit;

	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	connect(cutAction, SIGNAL(triggered()), edit, SLOT(cut()));
	connect(copyAction, SIGNAL(triggered()), edit, SLOT(copy()));
	connect(pasteAction, SIGNAL(triggered()), edit, SLOT(paste()));
	connect(searchAction, SIGNAL(triggered()), this, SLOT(showBar()));

	connect(findPreviousButton, SIGNAL(clicked()), this, SLOT(findPrevious()));
	connect(findNextButton, SIGNAL(clicked()), this, SLOT(findNext()));
	connect(findEdit, SIGNAL(returnPressed()), this, SLOT(findNext()));
	connect(closeButton, SIGNAL(clicked()), findBar, SLOT(close()));

	toolBar->addAction(saveAction);
	toolBar->addSeparator();
	toolBar->addAction(searchAction);
	toolBar->addSeparator();
	toolBar->addAction(cutAction);
	toolBar->addAction(copyAction);
	toolBar->addAction(pasteAction);

	editMenu->addAction(saveAction);
	editMenu->addSeparator();
	editMenu->addAction(searchAction);
	editMenu->addSeparator();
	editMenu->addAction(cutAction);
	editMenu->addAction(copyAction);
	editMenu->addAction(pasteAction);

	findBar->addWidget(closeButton);
	findBar->addWidget(findEdit);
	findBar->addWidget(findNextButton);
	findBar->addWidget(findPreviousButton);

	addToolBar(toolBar);
	addToolBar(Qt::BottomToolBarArea, findBar);

	setCentralWidget(edit);

	findBar->close();
}

void sourcesEditor::showBar()
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

void sourcesEditor::findNext()
{
	QString shearch = findEdit->text();
	if (!shearch.isEmpty())
	{
		if (!edit->find(shearch))
		{
			edit->moveCursor(QTextCursor::Start);
			if (!edit->find(shearch))
			{
				findEdit->setStyleSheet("background-color: rgb(255, 155, 140);");
			}
		}
		else
		{
			findEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
		}
		edit->setFocus();
	}
}

void sourcesEditor::findPrevious()
{
	QString shearch = findEdit->text();
	if (!shearch.isEmpty())
	{
		if (!edit->find(shearch, QTextDocument::FindBackward))
		{
			edit->moveCursor(QTextCursor::End);
			if (!edit->find(shearch, QTextDocument::FindBackward))
			{
				findEdit->setStyleSheet("background-color: rgb(255, 155, 140);");
			}
		}
		else
		{
			findEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
		}
		edit->setFocus();
	}
}
void sourcesEditor::setText(QString text)
{
	edit->setText(text);
}

QMenu *sourcesEditor::menu()
{
	return editMenu;
}


void sourcesEditor::save()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer"), QString(), "Page web (*.htm *.html)");;
	QFile file(fileName);
	if(file.open(QIODevice::WriteOnly))
	{
		file.write(edit->toPlainText().toLocal8Bit());
		file.close();
	}
	else
	{
		QMessageBox::critical(this, tr("Oppération impossible"), tr("Impossible d'ouvrir le fichier !"));
	}
}











sourcesPage::sourcesPage()
{
	highlighter = new Highlighter(document());

	lineNumberArea = new LineNumberArea(this);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(const QRect &, int)), this, SLOT(updateLineNumberArea(const QRect &, int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
}

void sourcesPage::setText(QString text)
{
	setPlainText(text);
}

int sourcesPage::lineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space;
}

void sourcesPage::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void sourcesPage::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	if (lineNumberArea->isHidden())
	{
	   QAction *hideLineAction = new QAction(tr("Afficher les numéros de ligne"), this);
	   connect(hideLineAction, SIGNAL(triggered()),lineNumberArea, SLOT(show()));
	   menu.addAction(hideLineAction);
	}
	else
	{
	   QAction *hideLineAction = new QAction(tr("Cacher les numéros de ligne"), this);
	   connect(hideLineAction, SIGNAL(triggered()),lineNumberArea, SLOT(hide()));
	   menu.addAction(hideLineAction);
	}
	menu.exec(QCursor::pos());
}


void sourcesPage::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
		lineNumberArea->scroll(0, dy);
	else
		lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}



void sourcesPage::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}



void sourcesPage::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly()) {
		QTextEdit::ExtraSelection selection;

		QColor lineColor = QColor(Qt::yellow).lighter(160);

		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}

	setExtraSelections(extraSelections);
}



void sourcesPage::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	QPainter painter(lineNumberArea);
	painter.fillRect(event->rect(), Qt::lightGray);


	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);
			painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
							 Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		++blockNumber;
	}
}




Highlighter::Highlighter(QTextDocument *parent)
: QSyntaxHighlighter(parent)
{
	HighlightingRule rule;


	//Num
	numberFormat.setForeground(Qt::magenta);
	rule.pattern = QRegExp("\\b[0-9]+\\b");
	rule.format = numberFormat;
	highlightingRules.append(rule);

	//HTML tag
	tagFormat.setForeground(Qt::darkMagenta);
	rule.pattern = QRegExp("<[A-Za-z\\!]{1,}[a-zA-Z0-9=\\s-]*([^>]*)>");
	rule.format = tagFormat;
	highlightingRules.append(rule);

	rule.pattern = QRegExp("</[A-Za-z0-9]{1,}>");
	rule.format = tagFormat;
	highlightingRules.append(rule);

	//Value
	valueFormat.setForeground(Qt::blue);
	rule.pattern = QRegExp("\"[^\"]+\"");
	rule.format = valueFormat;
	highlightingRules.append(rule);

	rule.pattern = QRegExp("'([^\']*)'");
	rule.format = valueFormat;
	highlightingRules.append(rule);


	//Attribut
	attributFormat.setForeground(Qt::darkYellow);
	rule.pattern = QRegExp(" [A-Za-z-]{1,}=");
	rule.format = attributFormat;
	highlightingRules.append(rule);


	//comment
	multiLineCommentFormat.setForeground(Qt::darkGreen);
	commentStartExpression = QRegExp("<!--");
	commentEndExpression = QRegExp("-->");


}



void Highlighter::highlightBlock(const QString &text)
{
	foreach (const HighlightingRule &rule, highlightingRules) {
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0) {
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}
	setCurrentBlockState(0);
	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = commentStartExpression.indexIn(text);
	while (startIndex >= 0) {
		int endIndex = commentEndExpression.indexIn(text, startIndex);
		int commentLength;
		if (endIndex == -1) {
			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		} else {
			commentLength = endIndex - startIndex
			+ commentEndExpression.matchedLength();
		}
		setFormat(startIndex, commentLength, multiLineCommentFormat);
		startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
	}
}
