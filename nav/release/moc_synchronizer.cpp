/****************************************************************************
** Meta object code from reading C++ file 'synchronizer.h'
**
** Created: Thu 10. Feb 18:35:26 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../synchronizer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'synchronizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Synchronizer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      25,   13,   13,   13, 0x05,
      46,   36,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      73,   66,   13,   13, 0x08,
     107,   99,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Synchronizer[] = {
    "Synchronizer\0\0loggedIn()\0imported()\0"
    "connected\0statusChanged(bool)\0,error\0"
    "commandFinished(int,bool)\0urlInfo\0"
    "addToList(QUrlInfo)\0"
};

const QMetaObject Synchronizer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Synchronizer,
      qt_meta_data_Synchronizer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Synchronizer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Synchronizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Synchronizer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Synchronizer))
        return static_cast<void*>(const_cast< Synchronizer*>(this));
    return QObject::qt_metacast(_clname);
}

int Synchronizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loggedIn(); break;
        case 1: imported(); break;
        case 2: statusChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: commandFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: addToList((*reinterpret_cast< const QUrlInfo(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Synchronizer::loggedIn()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Synchronizer::imported()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Synchronizer::statusChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
