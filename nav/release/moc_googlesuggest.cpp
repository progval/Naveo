/****************************************************************************
** Meta object code from reading C++ file 'googlesuggest.h'
**
** Created: Thu 10. Feb 18:34:18 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../googlesuggest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'googlesuggest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GSuggestCompletion[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      47,   34,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GSuggestCompletion[] = {
    "GSuggestCompletion\0\0autoSuggest()\0"
    "networkReply\0handleNetworkData(QNetworkReply*)\0"
};

const QMetaObject GSuggestCompletion::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GSuggestCompletion,
      qt_meta_data_GSuggestCompletion, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GSuggestCompletion::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GSuggestCompletion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GSuggestCompletion::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GSuggestCompletion))
        return static_cast<void*>(const_cast< GSuggestCompletion*>(this));
    return QObject::qt_metacast(_clname);
}

int GSuggestCompletion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: autoSuggest(); break;
        case 1: handleNetworkData((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
