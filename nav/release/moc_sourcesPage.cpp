/****************************************************************************
** Meta object code from reading C++ file 'sourcesPage.h'
**
** Created: Thu 10. Feb 18:34:48 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sourcesPage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sourcesPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Highlighter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_Highlighter[] = {
    "Highlighter\0"
};

const QMetaObject Highlighter::staticMetaObject = {
    { &QSyntaxHighlighter::staticMetaObject, qt_meta_stringdata_Highlighter,
      qt_meta_data_Highlighter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Highlighter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Highlighter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Highlighter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Highlighter))
        return static_cast<void*>(const_cast< Highlighter*>(this));
    return QSyntaxHighlighter::qt_metacast(_clname);
}

int Highlighter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSyntaxHighlighter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_sourcesPage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   13,   12,   12, 0x08,
      58,   12,   12,   12, 0x08,
      83,   81,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_sourcesPage[] = {
    "sourcesPage\0\0newBlockCount\0"
    "updateLineNumberAreaWidth(int)\0"
    "highlightCurrentLine()\0,\0"
    "updateLineNumberArea(QRect,int)\0"
};

const QMetaObject sourcesPage::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_sourcesPage,
      qt_meta_data_sourcesPage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &sourcesPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *sourcesPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *sourcesPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sourcesPage))
        return static_cast<void*>(const_cast< sourcesPage*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int sourcesPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: highlightCurrentLine(); break;
        case 2: updateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_sourcesEditor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      22,   14,   14,   14, 0x0a,
      33,   14,   14,   14, 0x0a,
      48,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_sourcesEditor[] = {
    "sourcesEditor\0\0save()\0findNext()\0"
    "findPrevious()\0showBar()\0"
};

const QMetaObject sourcesEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_sourcesEditor,
      qt_meta_data_sourcesEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &sourcesEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *sourcesEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *sourcesEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sourcesEditor))
        return static_cast<void*>(const_cast< sourcesEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int sourcesEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: save(); break;
        case 1: findNext(); break;
        case 2: findPrevious(); break;
        case 3: showBar(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
