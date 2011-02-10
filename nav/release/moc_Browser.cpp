/****************************************************************************
** Meta object code from reading C++ file 'Browser.h'
**
** Created: Thu 10. Feb 18:34:05 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Browser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Browser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Browser[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   27,    8,    8, 0x0a,
      61,   57,    8,    8, 0x2a,
      77,    8,    8,    8, 0x2a,
      92,   86,    8,    8, 0x0a,
     112,    8,    8,    8, 0x0a,
     127,    8,    8,    8, 0x0a,
     138,    8,    8,    8, 0x0a,
     158,  149,    8,    8, 0x0a,
     169,    8,    8,    8, 0x2a,
     177,    8,    8,    8, 0x0a,
     184,    8,    8,    8, 0x0a,
     201,    8,    8,    8, 0x0a,
     221,   57,    8,    8, 0x0a,
     242,    8,    8,    8, 0x0a,
     269,    8,    8,    8, 0x0a,
     284,    8,    8,    8, 0x0a,
     293,    8,    8,    8, 0x0a,
     301,    8,    8,    8, 0x0a,
     313,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Browser[] = {
    "Browser\0\0settingsChanged()\0url,show\0"
    "addNew(QString,bool)\0url\0addNew(QString)\0"
    "addNew()\0error\0updateVersion(bool)\0"
    "saveSettings()\0showHelp()\0closeWin()\0"
    "exitCode\0close(int)\0close()\0news()\0"
    "closeAndUpdate()\0setDefaultBrowser()\0"
    "loadHistory(QString)\0newLocalSocketConnection()\0"
    "execSettings()\0update()\0about()\0"
    "clearData()\0restart()\0"
};

const QMetaObject Browser::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_Browser,
      qt_meta_data_Browser, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Browser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Browser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Browser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Browser))
        return static_cast<void*>(const_cast< Browser*>(this));
    return QApplication::qt_metacast(_clname);
}

int Browser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: settingsChanged(); break;
        case 1: addNew((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: addNew((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: addNew(); break;
        case 4: updateVersion((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: saveSettings(); break;
        case 6: showHelp(); break;
        case 7: closeWin(); break;
        case 8: close((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: close(); break;
        case 10: news(); break;
        case 11: closeAndUpdate(); break;
        case 12: setDefaultBrowser(); break;
        case 13: loadHistory((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: newLocalSocketConnection(); break;
        case 15: execSettings(); break;
        case 16: update(); break;
        case 17: about(); break;
        case 18: clearData(); break;
        case 19: restart(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void Browser::settingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
