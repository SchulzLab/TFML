/****************************************************************************
** Meta object code from reading C++ file 'AnalysisManager.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TFML/src/AnalysisManager.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnalysisManager.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AnalysisManager_t {
    QByteArrayData data[14];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnalysisManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnalysisManager_t qt_meta_stringdata_AnalysisManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "AnalysisManager"
QT_MOC_LITERAL(1, 16, 18), // "mProcessOutputDone"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "aPath"
QT_MOC_LITERAL(4, 42, 10), // "mUpdateLog"
QT_MOC_LITERAL(5, 53, 4), // "aLog"
QT_MOC_LITERAL(6, 58, 15), // "mProcessRunning"
QT_MOC_LITERAL(7, 74, 4), // "aMsg"
QT_MOC_LITERAL(8, 79, 10), // "updateText"
QT_MOC_LITERAL(9, 90, 15), // "receiveFinished"
QT_MOC_LITERAL(10, 106, 5), // "aCode"
QT_MOC_LITERAL(11, 112, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(12, 133, 7), // "aStatus"
QT_MOC_LITERAL(13, 141, 11) // "killProcess"

    },
    "AnalysisManager\0mProcessOutputDone\0\0"
    "aPath\0mUpdateLog\0aLog\0mProcessRunning\0"
    "aMsg\0updateText\0receiveFinished\0aCode\0"
    "QProcess::ExitStatus\0aStatus\0killProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnalysisManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   53,    2, 0x0a /* Public */,
       9,    2,   54,    2, 0x0a /* Public */,
      13,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   10,   12,
    QMetaType::Void,

       0        // eod
};

void AnalysisManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AnalysisManager *_t = static_cast<AnalysisManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mProcessOutputDone((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->mUpdateLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->mProcessRunning((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->updateText(); break;
        case 4: _t->receiveFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 5: _t->killProcess(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AnalysisManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnalysisManager::mProcessOutputDone)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AnalysisManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnalysisManager::mUpdateLog)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AnalysisManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnalysisManager::mProcessRunning)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject AnalysisManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AnalysisManager.data,
      qt_meta_data_AnalysisManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AnalysisManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnalysisManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AnalysisManager.stringdata0))
        return static_cast<void*>(const_cast< AnalysisManager*>(this));
    return QObject::qt_metacast(_clname);
}

int AnalysisManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void AnalysisManager::mProcessOutputDone(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AnalysisManager::mUpdateLog(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AnalysisManager::mProcessRunning(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
