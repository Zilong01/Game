/****************************************************************************
** Meta object code from reading C++ file 'minessweeperlogic.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../GamesCollection/minessweeperlogic.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'minessweeperlogic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MinesSweeperLogic_t {
    QByteArrayData data[6];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MinesSweeperLogic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MinesSweeperLogic_t qt_meta_stringdata_MinesSweeperLogic = {
    {
QT_MOC_LITERAL(0, 0, 17), // "MinesSweeperLogic"
QT_MOC_LITERAL(1, 18, 8), // "gameOver"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "gameWin"
QT_MOC_LITERAL(4, 36, 16), // "firstClickSignal"
QT_MOC_LITERAL(5, 53, 16) // "flagChangeSignal"

    },
    "MinesSweeperLogic\0gameOver\0\0gameWin\0"
    "firstClickSignal\0flagChangeSignal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MinesSweeperLogic[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MinesSweeperLogic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MinesSweeperLogic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gameOver(); break;
        case 1: _t->gameWin(); break;
        case 2: _t->firstClickSignal(); break;
        case 3: _t->flagChangeSignal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MinesSweeperLogic::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinesSweeperLogic::gameOver)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MinesSweeperLogic::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinesSweeperLogic::gameWin)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MinesSweeperLogic::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinesSweeperLogic::firstClickSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MinesSweeperLogic::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinesSweeperLogic::flagChangeSignal)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MinesSweeperLogic::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MinesSweeperLogic.data,
    qt_meta_data_MinesSweeperLogic,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MinesSweeperLogic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MinesSweeperLogic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MinesSweeperLogic.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MinesSweeperLogic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MinesSweeperLogic::gameOver()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MinesSweeperLogic::gameWin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MinesSweeperLogic::firstClickSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MinesSweeperLogic::flagChangeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
