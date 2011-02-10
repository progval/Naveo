/****************************************************************************
** Meta object code from reading C++ file 'webPage.h'
**
** Created: Thu 10. Feb 18:34:42 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../webPage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'webPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_webPage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      48,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,    9,    8,    8, 0x05,
      34,   30,    8,    8, 0x05,
      59,   53,    8,    8, 0x05,
      91,   81,    8,    8, 0x05,
     120,    9,    8,    8, 0x05,
     141,    8,    8,    8, 0x05,
     161,  153,    8,    8, 0x05,
     187,  182,    8,    8, 0x05,
     213,  205,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     233,    8,    8,    8, 0x0a,
     251,  248,    8,    8, 0x0a,
     271,   53,    8,    8, 0x0a,
     292,    9,    8,    8, 0x0a,
     308,    8,    8,    8, 0x0a,
     319,    8,    8,    8, 0x0a,
     329,    9,    8,    8, 0x0a,
     343,    9,    8,    8, 0x0a,
     360,    8,    8,    8, 0x0a,
     376,    8,    8,    8, 0x0a,
     412,  406,    8,    8, 0x0a,
     441,    8,    8,    8, 0x0a,
     456,    8,    8,    8, 0x0a,
     471,    8,    8,    8, 0x0a,
     481,    8,    8,    8, 0x0a,
     494,    8,    8,    8, 0x0a,
     505,    8,    8,    8, 0x0a,
     520,    8,    8,    8, 0x0a,
     528,  182,    8,    8, 0x0a,
     552,    8,    8,    8, 0x0a,
     568,    8,    8,    8, 0x0a,
     581,    8,    8,    8, 0x0a,
     608,  588,    8,    8, 0x0a,
     657,    8,    8,    8, 0x0a,
     671,    8,    8,    8, 0x0a,
     689,  682,    8,    8, 0x0a,
     712,    8,    8,    8, 0x0a,
     729,    8,    8,    8, 0x0a,
     745,    8,    8,    8, 0x0a,
     755,    8,    8,    8, 0x0a,
     766,    8,    8,    8, 0x0a,
     777,    8,    8,    8, 0x0a,
     787,    8,    8,    8, 0x0a,
     801,    8,    8,    8, 0x0a,
     810,    8,    8,    8, 0x0a,
     820,    8,    8,    8, 0x0a,
     834,    8,    8,    8, 0x0a,
     845,    8,    8,    8, 0x0a,
     852,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_webPage[] = {
    "webPage\0\0url\0loading(QString)\0pix\0"
    "isLoading(QPixmap)\0title\0titleChanged(QString)\0"
    "url,title\0pageChanged(QString,QString)\0"
    "showSources(QString)\0speedDial()\0"
    "printer\0needPrint(QPrinter*)\0page\0"
    "openTab(webPage*)\0enabled\0setFullScreen(bool)\0"
    "startLoading()\0ok\0finishLoading(bool)\0"
    "changeTitle(QString)\0changeUrl(QUrl)\0"
    "goToHome()\0loadUrl()\0loadUrl(QUrl)\0"
    "loadUrl(QString)\0addToBookMark()\0"
    "downloadFile(QNetworkRequest)\0reply\0"
    "downloadFile(QNetworkReply*)\0"
    "loadBookMark()\0showBookMark()\0sources()\0"
    "defineHome()\0findNext()\0findPrevious()\0"
    "print()\0createNewPage(WebView*)\0"
    "createNewPage()\0updateIcon()\0copy()\0"
    "reply,authenticator\0"
    "authentification(QNetworkReply*,QAuthenticator*)\0"
    "inspectPage()\0goToDial()\0pixmap\0"
    "updateUrlIcon(QPixmap)\0updateBookMark()\0"
    "updateOptions()\0showBar()\0showPage()\0"
    "showDial()\0inCache()\0showConsole()\0"
    "zoomIn()\0zoomOut()\0restoreZoom()\0"
    "savePage()\0back()\0forward()\0"
};

const QMetaObject webPage::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_webPage,
      qt_meta_data_webPage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &webPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *webPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *webPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_webPage))
        return static_cast<void*>(const_cast< webPage*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int webPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loading((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: isLoading((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 2: titleChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: pageChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: showSources((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: speedDial(); break;
        case 6: needPrint((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 7: openTab((*reinterpret_cast< webPage*(*)>(_a[1]))); break;
        case 8: setFullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: startLoading(); break;
        case 10: finishLoading((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: changeTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: changeUrl((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 13: goToHome(); break;
        case 14: loadUrl(); break;
        case 15: loadUrl((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 16: loadUrl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: addToBookMark(); break;
        case 18: downloadFile((*reinterpret_cast< const QNetworkRequest(*)>(_a[1]))); break;
        case 19: downloadFile((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 20: loadBookMark(); break;
        case 21: showBookMark(); break;
        case 22: sources(); break;
        case 23: defineHome(); break;
        case 24: findNext(); break;
        case 25: findPrevious(); break;
        case 26: print(); break;
        case 27: createNewPage((*reinterpret_cast< WebView*(*)>(_a[1]))); break;
        case 28: createNewPage(); break;
        case 29: updateIcon(); break;
        case 30: copy(); break;
        case 31: authentification((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 32: inspectPage(); break;
        case 33: goToDial(); break;
        case 34: updateUrlIcon((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 35: updateBookMark(); break;
        case 36: updateOptions(); break;
        case 37: showBar(); break;
        case 38: showPage(); break;
        case 39: showDial(); break;
        case 40: inCache(); break;
        case 41: showConsole(); break;
        case 42: zoomIn(); break;
        case 43: zoomOut(); break;
        case 44: restoreZoom(); break;
        case 45: savePage(); break;
        case 46: back(); break;
        case 47: forward(); break;
        default: ;
        }
        _id -= 48;
    }
    return _id;
}

// SIGNAL 0
void webPage::loading(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void webPage::isLoading(QPixmap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void webPage::titleChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void webPage::pageChanged(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void webPage::showSources(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void webPage::speedDial()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void webPage::needPrint(QPrinter * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void webPage::openTab(webPage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void webPage::setFullScreen(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
static const uint qt_meta_data_UrlLineEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x0a,
      28,   12,   12,   12, 0x0a,
      36,   12,   12,   12, 0x0a,
      50,   12,   12,   12, 0x0a,
      60,   12,   12,   12, 0x0a,
      70,   12,   12,   12, 0x0a,
      80,   12,   12,   12, 0x0a,
      90,   12,   12,   12, 0x0a,
      97,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UrlLineEdit[] = {
    "UrlLineEdit\0\0i\0loading(int)\0clear()\0"
    "changeMotor()\0changeG()\0changeY()\0"
    "changeB()\0changeE()\0load()\0change()\0"
};

const QMetaObject UrlLineEdit::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_UrlLineEdit,
      qt_meta_data_UrlLineEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UrlLineEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UrlLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UrlLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UrlLineEdit))
        return static_cast<void*>(const_cast< UrlLineEdit*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int UrlLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loading((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: clear(); break;
        case 2: changeMotor(); break;
        case 3: changeG(); break;
        case 4: changeY(); break;
        case 5: changeB(); break;
        case 6: changeE(); break;
        case 7: load(); break;
        case 8: change(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
