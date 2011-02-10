/****************************************************************************
** Meta object code from reading C++ file 'webview.h'
**
** Created: Thu 10. Feb 18:35:04 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../webview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'webview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WebView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,    9,    8,    8, 0x05,
      32,    8,    8,    8, 0x05,
      42,    8,    8,    8, 0x05,
      59,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      83,   74,    8,    8, 0x0a,
     112,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WebView[] = {
    "WebView\0\0page\0addPage(WebView*)\0"
    "addPage()\0addToBookMarks()\0popupBlocked()\0"
    "url,link\0linkHovered(QString,QString)\0"
    "shearch()\0"
};

const QMetaObject WebView::staticMetaObject = {
    { &QWebView::staticMetaObject, qt_meta_stringdata_WebView,
      qt_meta_data_WebView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WebView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WebView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WebView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WebView))
        return static_cast<void*>(const_cast< WebView*>(this));
    return QWebView::qt_metacast(_clname);
}

int WebView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addPage((*reinterpret_cast< WebView*(*)>(_a[1]))); break;
        case 1: addPage(); break;
        case 2: addToBookMarks(); break;
        case 3: popupBlocked(); break;
        case 4: linkHovered((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: shearch(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WebView::addPage(WebView * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WebView::addPage()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void WebView::addToBookMarks()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void WebView::popupBlocked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
