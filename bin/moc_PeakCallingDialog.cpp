/****************************************************************************
** Meta object code from reading C++ file 'PeakCallingDialog.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TFML/src/PeakCallingDialog.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PeakCallingDialog.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PeakCallingDialog_t {
    QByteArrayData data[5];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PeakCallingDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PeakCallingDialog_t qt_meta_stringdata_PeakCallingDialog = {
    {
QT_MOC_LITERAL(0, 0, 17), // "PeakCallingDialog"
QT_MOC_LITERAL(1, 18, 15), // "selectDirectory"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 10), // "selectFile"
QT_MOC_LITERAL(4, 46, 13) // "handleClickOk"

    },
    "PeakCallingDialog\0selectDirectory\0\0"
    "selectFile\0handleClickOk"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PeakCallingDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PeakCallingDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PeakCallingDialog *_t = static_cast<PeakCallingDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectDirectory(); break;
        case 1: _t->selectFile(); break;
        case 2: _t->handleClickOk(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PeakCallingDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PeakCallingDialog.data,
      qt_meta_data_PeakCallingDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PeakCallingDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PeakCallingDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PeakCallingDialog.stringdata0))
        return static_cast<void*>(const_cast< PeakCallingDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PeakCallingDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
