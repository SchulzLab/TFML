/****************************************************************************
** Meta object code from reading C++ file 'FileListWidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TFML/src/FileListWidget.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileListWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FileListWidget_t {
    QByteArrayData data[17];
    char stringdata0[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileListWidget_t qt_meta_stringdata_FileListWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FileListWidget"
QT_MOC_LITERAL(1, 15, 11), // "itemClicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 45, 5), // "aItem"
QT_MOC_LITERAL(5, 51, 7), // "aNumber"
QT_MOC_LITERAL(6, 59, 19), // "getFileFullPathName"
QT_MOC_LITERAL(7, 79, 8), // "fileName"
QT_MOC_LITERAL(8, 88, 11), // "getFileName"
QT_MOC_LITERAL(9, 100, 7), // "delFile"
QT_MOC_LITERAL(10, 108, 16), // "delFilePermanent"
QT_MOC_LITERAL(11, 125, 12), // "addDirectory"
QT_MOC_LITERAL(12, 138, 4), // "path"
QT_MOC_LITERAL(13, 143, 12), // "clickedEvent"
QT_MOC_LITERAL(14, 156, 18), // "doubleClickedEvent"
QT_MOC_LITERAL(15, 175, 15), // "showContextMenu"
QT_MOC_LITERAL(16, 191, 3) // "pos"

    },
    "FileListWidget\0itemClicked\0\0"
    "QTreeWidgetItem*\0aItem\0aNumber\0"
    "getFileFullPathName\0fileName\0getFileName\0"
    "delFile\0delFilePermanent\0addDirectory\0"
    "path\0clickedEvent\0doubleClickedEvent\0"
    "showContextMenu\0pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileListWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       6,    1,   64,    2, 0x06 /* Public */,
       8,    1,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   70,    2, 0x0a /* Public */,
      10,    0,   71,    2, 0x0a /* Public */,
      11,    1,   72,    2, 0x0a /* Public */,
      13,    2,   75,    2, 0x0a /* Public */,
      14,    2,   80,    2, 0x0a /* Public */,
      15,    1,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QStringList,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::QPoint,   16,

       0        // eod
};

void FileListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileListWidget *_t = static_cast<FileListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->getFileFullPathName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->getFileName((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->delFile(); break;
        case 4: _t->delFilePermanent(); break;
        case 5: _t->addDirectory((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->clickedEvent((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->doubleClickedEvent((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FileListWidget::*_t)(QTreeWidgetItem * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileListWidget::itemClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FileListWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileListWidget::getFileFullPathName)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FileListWidget::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileListWidget::getFileName)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject FileListWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FileListWidget.data,
      qt_meta_data_FileListWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FileListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FileListWidget.stringdata0))
        return static_cast<void*>(const_cast< FileListWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FileListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void FileListWidget::itemClicked(QTreeWidgetItem * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FileListWidget::getFileFullPathName(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FileListWidget::getFileName(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
