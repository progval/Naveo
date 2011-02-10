/****************************************************************************
** Meta object code from reading C++ file 'downloadWidget.h'
**
** Created: Thu 10. Feb 18:34:59 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../downloadWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'downloadWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DownloadWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      27,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   35,   15,   15, 0x0a,
      67,   15,   15,   15, 0x0a,
      80,   74,   15,   15, 0x0a,
      91,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DownloadWidget[] = {
    "DownloadWidget\0\0canceled()\0retry()\0"
    "prog,size\0update(qint64,qint64)\0open()\0"
    "error\0done(bool)\0updateTime()\0"
};

const QMetaObject DownloadWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DownloadWidget,
      qt_meta_data_DownloadWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DownloadWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DownloadWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DownloadWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DownloadWidget))
        return static_cast<void*>(const_cast< DownloadWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int DownloadWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: canceled(); break;
        case 1: retry(); break;
        case 2: update((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: open(); break;
        case 4: done((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: updateTime(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void DownloadWidget::canceled()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DownloadWidget::retry()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
