/****************************************************************************
** Meta object code from reading C++ file 'mainWin.h'
**
** Created: Thu 10. Feb 18:34:29 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainWin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainWin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWin[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      23,   18,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,    8,    8,    8, 0x0a,
      63,   57,    8,    8, 0x0a,
      84,    8,    8,    8, 0x0a,
      97,    8,    8,    8, 0x0a,
     106,    8,    8,    8, 0x0a,
     124,  120,    8,    8, 0x0a,
     145,  140,    8,    8, 0x0a,
     163,  120,    8,    8, 0x0a,
     191,  187,    8,    8, 0x0a,
     211,    8,    8,    8, 0x0a,
     229,    8,    8,    8, 0x0a,
     243,    8,    8,    8, 0x0a,
     267,    8,    8,    8, 0x0a,
     292,  284,    8,    8, 0x0a,
     321,  312,    8,    8, 0x0a,
     338,  336,    8,    8, 0x0a,
     351,  120,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWin[] = {
    "MainWin\0\0closed()\0file\0loadFirstPage(QString)\0"
    "closeTab()\0title\0setTabTitle(QString)\0"
    "tabChanged()\0newTab()\0showSources()\0"
    "url\0newTab(QString)\0page\0openTab(webPage*)\0"
    "setLoadingIcon(QString)\0pix\0"
    "setTabIcon(QPixmap)\0showTabSettings()\0"
    "changeIndex()\0updateNewTabButtonPos()\0"
    "updateSettings()\0enabled\0setFullScreen(bool)\0"
    "fileName\0setup(QString)\0p\0grab(QPoint)\0"
    "openFtp(QString)\0"
};

const QMetaObject MainWin::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_MainWin,
      qt_meta_data_MainWin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWin))
        return static_cast<void*>(const_cast< MainWin*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int MainWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: closed(); break;
        case 1: loadFirstPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: closeTab(); break;
        case 3: setTabTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: tabChanged(); break;
        case 5: newTab(); break;
        case 6: showSources(); break;
        case 7: newTab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: openTab((*reinterpret_cast< webPage*(*)>(_a[1]))); break;
        case 9: setLoadingIcon((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: setTabIcon((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 11: showTabSettings(); break;
        case 12: changeIndex(); break;
        case 13: updateNewTabButtonPos(); break;
        case 14: updateSettings(); break;
        case 15: setFullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: setup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: grab((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 18: openFtp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MainWin::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWin::loadFirstPage(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_TabBar[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    8,    7,    7, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_TabBar[] = {
    "TabBar\0\0p\0grab(QPoint)\0"
};

const QMetaObject TabBar::staticMetaObject = {
    { &QTabBar::staticMetaObject, qt_meta_stringdata_TabBar,
      qt_meta_data_TabBar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TabBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TabBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TabBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TabBar))
        return static_cast<void*>(const_cast< TabBar*>(this));
    return QTabBar::qt_metacast(_clname);
}

int TabBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: grab((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TabBar::grab(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
