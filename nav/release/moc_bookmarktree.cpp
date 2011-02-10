/****************************************************************************
** Meta object code from reading C++ file 'bookmarktree.h'
**
** Created: Thu 10. Feb 18:35:31 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bookmarktree.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bookmarktree.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BookMarkTree[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   14,   13,   13, 0x05,
      62,   53,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      98,   13,   13,   13, 0x0a,
     124,  112,   13,   13, 0x08,
     170,  164,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BookMarkTree[] = {
    "BookMarkTree\0\0item\0editingFinished(QTreeWidgetItem*)\0"
    "item,dir\0itemMoved(QTreeWidgetItem*,QString)\0"
    "closeEditor()\0item,column\0"
    "itemDoubleClicked(QTreeWidgetItem*,int)\0"
    "event\0dropEvent(QDropEvent*)\0"
};

const QMetaObject BookMarkTree::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_BookMarkTree,
      qt_meta_data_BookMarkTree, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BookMarkTree::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BookMarkTree::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BookMarkTree::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BookMarkTree))
        return static_cast<void*>(const_cast< BookMarkTree*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int BookMarkTree::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: editingFinished((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 1: itemMoved((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: closeEditor(); break;
        case 3: itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: dropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void BookMarkTree::editingFinished(QTreeWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BookMarkTree::itemMoved(QTreeWidgetItem * _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_ItemDelegate[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_ItemDelegate[] = {
    "ItemDelegate\0"
};

const QMetaObject ItemDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_ItemDelegate,
      qt_meta_data_ItemDelegate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ItemDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ItemDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ItemDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ItemDelegate))
        return static_cast<void*>(const_cast< ItemDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int ItemDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
