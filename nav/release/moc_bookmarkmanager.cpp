/****************************************************************************
** Meta object code from reading C++ file 'bookmarkmanager.h'
**
** Created: Thu 10. Feb 18:35:10 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bookmarkmanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bookmarkmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BookMarkManager[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   16,   16,   16, 0x0a,
      41,   16,   16,   16, 0x0a,
      56,   16,   16,   16, 0x0a,
      73,   16,   16,   16, 0x0a,
      80,   16,   16,   16, 0x0a,
      89,   16,   16,   16, 0x0a,
      98,   16,   16,   16, 0x0a,
     125,  113,   16,   16, 0x0a,
     165,  160,   16,   16, 0x0a,
     198,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BookMarkManager[] = {
    "BookMarkManager\0\0update()\0saveSettings()\0"
    "exportToHTML()\0importFromHTML()\0move()\0"
    "remove()\0addNew()\0addNewFolder()\0"
    "item,newDir\0moveItem(QTreeWidgetItem*,QString)\0"
    "item\0updateItemData(QTreeWidgetItem*)\0"
    "show()\0"
};

const QMetaObject BookMarkManager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BookMarkManager,
      qt_meta_data_BookMarkManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BookMarkManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BookMarkManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BookMarkManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BookMarkManager))
        return static_cast<void*>(const_cast< BookMarkManager*>(this));
    return QWidget::qt_metacast(_clname);
}

int BookMarkManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: update(); break;
        case 1: saveSettings(); break;
        case 2: exportToHTML(); break;
        case 3: importFromHTML(); break;
        case 4: move(); break;
        case 5: remove(); break;
        case 6: addNew(); break;
        case 7: addNewFolder(); break;
        case 8: moveItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: updateItemData((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 10: show(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void BookMarkManager::update()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
