/****************************************************************************
** Meta object code from reading C++ file 'settingsDialog.h'
**
** Created: Thu 10. Feb 18:34:35 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../settingsDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_settingDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      26,   14,   14,   14, 0x05,
      41,   14,   14,   14, 0x05,
      56,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   14,   14,   14, 0x0a,
      73,   14,   14,   14, 0x08,
      87,   14,   14,   14, 0x08,
     111,   14,   14,   14, 0x08,
     137,   14,   14,   14, 0x08,
     163,   14,   14,   14, 0x08,
     189,   14,   14,   14, 0x08,
     215,   14,   14,   14, 0x08,
     241,   14,   14,   14, 0x08,
     267,   14,   14,   14, 0x08,
     293,   14,   14,   14, 0x08,
     319,   14,   14,   14, 0x08,
     346,   14,   14,   14, 0x08,
     373,   14,   14,   14, 0x08,
     400,   14,   14,   14, 0x08,
     427,   14,   14,   14, 0x08,
     454,   14,   14,   14, 0x08,
     491,  481,   14,   14, 0x08,
     518,  514,   14,   14, 0x08,
     557,   14,   14,   14, 0x08,
     569,   14,   14,   14, 0x08,
     576,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_settingDialog[] = {
    "settingDialog\0\0finished()\0clearCookies()\0"
    "clearHistory()\0restart()\0exec()\0"
    "updateCheck()\0on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_7_clicked()\0"
    "on_pushButton_8_clicked()\0"
    "on_pushButton_9_clicked()\0"
    "on_pushButton_10_clicked()\0"
    "on_pushButton_11_clicked()\0"
    "on_pushButton_12_clicked()\0"
    "on_pushButton_13_clicked()\0"
    "on_pushButton_14_clicked()\0"
    "on_pushButton_15_clicked()\0connected\0"
    "synStatusChanded(bool)\0row\0"
    "on_listWidget_3_currentRowChanged(int)\0"
    "updateAll()\0save()\0accept()\0"
};

const QMetaObject settingDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_settingDialog,
      qt_meta_data_settingDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &settingDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *settingDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *settingDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_settingDialog))
        return static_cast<void*>(const_cast< settingDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int settingDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finished(); break;
        case 1: clearCookies(); break;
        case 2: clearHistory(); break;
        case 3: restart(); break;
        case 4: exec(); break;
        case 5: updateCheck(); break;
        case 6: on_pushButton_clicked(); break;
        case 7: on_pushButton_2_clicked(); break;
        case 8: on_pushButton_3_clicked(); break;
        case 9: on_pushButton_4_clicked(); break;
        case 10: on_pushButton_5_clicked(); break;
        case 11: on_pushButton_6_clicked(); break;
        case 12: on_pushButton_7_clicked(); break;
        case 13: on_pushButton_8_clicked(); break;
        case 14: on_pushButton_9_clicked(); break;
        case 15: on_pushButton_10_clicked(); break;
        case 16: on_pushButton_11_clicked(); break;
        case 17: on_pushButton_12_clicked(); break;
        case 18: on_pushButton_13_clicked(); break;
        case 19: on_pushButton_14_clicked(); break;
        case 20: on_pushButton_15_clicked(); break;
        case 21: synStatusChanded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: on_listWidget_3_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: updateAll(); break;
        case 24: save(); break;
        case 25: accept(); break;
        default: ;
        }
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void settingDialog::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void settingDialog::clearCookies()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void settingDialog::clearHistory()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void settingDialog::restart()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
