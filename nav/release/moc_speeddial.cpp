/****************************************************************************
** Meta object code from reading C++ file 'speeddial.h'
**
** Created: Thu 10. Feb 18:35:36 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../speeddial.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'speeddial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LinkButton[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,
      34,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   11,   11,   11, 0x0a,
      57,   50,   11,   11, 0x0a,
      81,   11,   73,   11, 0x0a,
      94,   91,   11,   11, 0x0a,
     106,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LinkButton[] = {
    "LinkButton\0\0str\0selected(QString)\0"
    "added()\0clear()\0newUrl\0setUrl(QString)\0"
    "QString\0pageUrl()\0ok\0image(bool)\0"
    "createPage()\0"
};

const QMetaObject LinkButton::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LinkButton,
      qt_meta_data_LinkButton, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LinkButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LinkButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LinkButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LinkButton))
        return static_cast<void*>(const_cast< LinkButton*>(this));
    return QWidget::qt_metacast(_clname);
}

int LinkButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: added(); break;
        case 2: clear(); break;
        case 3: setUrl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: { QString _r = pageUrl();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: image((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: createPage(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void LinkButton::selected(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LinkButton::added()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_SpeedDial[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SpeedDial[] = {
    "SpeedDial\0\0enabled\0setFullScreen(bool)\0"
    "save()\0"
};

const QMetaObject SpeedDial::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SpeedDial,
      qt_meta_data_SpeedDial, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SpeedDial::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SpeedDial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SpeedDial::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpeedDial))
        return static_cast<void*>(const_cast< SpeedDial*>(this));
    return QWidget::qt_metacast(_clname);
}

int SpeedDial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setFullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: save(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SpeedDial::setFullScreen(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
