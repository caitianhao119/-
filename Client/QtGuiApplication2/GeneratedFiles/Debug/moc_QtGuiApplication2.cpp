/****************************************************************************
** Meta object code from reading C++ file 'QtGuiApplication2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtGuiApplication2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtGuiApplication2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Kline_t {
    QByteArrayData data[3];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Kline_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Kline_t qt_meta_stringdata_Kline = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Kline"
QT_MOC_LITERAL(1, 6, 8), // "IsReturn"
QT_MOC_LITERAL(2, 15, 0) // ""

    },
    "Kline\0IsReturn\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Kline[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Kline::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Kline *_t = static_cast<Kline *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->IsReturn(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Kline::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Kline.data,
      qt_meta_data_Kline,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Kline::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Kline::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Kline.stringdata0))
        return static_cast<void*>(const_cast< Kline*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Kline::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_ConditionMenu_t {
    QByteArrayData data[5];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConditionMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConditionMenu_t qt_meta_stringdata_ConditionMenu = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ConditionMenu"
QT_MOC_LITERAL(1, 14, 8), // "IsReturn"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "IsK"
QT_MOC_LITERAL(4, 28, 10) // "SlotReshow"

    },
    "ConditionMenu\0IsReturn\0\0IsK\0SlotReshow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConditionMenu[] = {

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
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ConditionMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConditionMenu *_t = static_cast<ConditionMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->IsReturn(); break;
        case 1: _t->IsK(); break;
        case 2: _t->SlotReshow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ConditionMenu::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ConditionMenu.data,
      qt_meta_data_ConditionMenu,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConditionMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConditionMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConditionMenu.stringdata0))
        return static_cast<void*>(const_cast< ConditionMenu*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ConditionMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_MainMenu_t {
    QByteArrayData data[4];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainMenu_t qt_meta_stringdata_MainMenu = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MainMenu"
QT_MOC_LITERAL(1, 9, 12), // "SlotSpecific"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10) // "SlotReshow"

    },
    "MainMenu\0SlotSpecific\0\0SlotReshow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainMenu *_t = static_cast<MainMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotSpecific(); break;
        case 1: _t->SlotReshow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainMenu::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainMenu.data,
      qt_meta_data_MainMenu,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainMenu.stringdata0))
        return static_cast<void*>(const_cast< MainMenu*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_LoginMainWindow_t {
    QByteArrayData data[4];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoginMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoginMainWindow_t qt_meta_stringdata_LoginMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "LoginMainWindow"
QT_MOC_LITERAL(1, 16, 7), // "IsLogin"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10) // "IsRegister"

    },
    "LoginMainWindow\0IsLogin\0\0IsRegister"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LoginMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoginMainWindow *_t = static_cast<LoginMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->IsLogin(); break;
        case 1: _t->IsRegister(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject LoginMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LoginMainWindow.data,
      qt_meta_data_LoginMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LoginMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LoginMainWindow.stringdata0))
        return static_cast<void*>(const_cast< LoginMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LoginMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_MyQCPFinancial_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyQCPFinancial_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyQCPFinancial_t qt_meta_stringdata_MyQCPFinancial = {
    {
QT_MOC_LITERAL(0, 0, 14) // "MyQCPFinancial"

    },
    "MyQCPFinancial"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyQCPFinancial[] = {

 // content:
       7,       // revision
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

void MyQCPFinancial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject MyQCPFinancial::staticMetaObject = {
    { &QCPFinancial::staticMetaObject, qt_meta_stringdata_MyQCPFinancial.data,
      qt_meta_data_MyQCPFinancial,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyQCPFinancial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyQCPFinancial::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyQCPFinancial.stringdata0))
        return static_cast<void*>(const_cast< MyQCPFinancial*>(this));
    return QCPFinancial::qt_metacast(_clname);
}

int MyQCPFinancial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPFinancial::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_Mybtn_t {
    QByteArrayData data[3];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mybtn_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mybtn_t qt_meta_stringdata_Mybtn = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Mybtn"
QT_MOC_LITERAL(1, 6, 13), // "doubleClicked"
QT_MOC_LITERAL(2, 20, 0) // ""

    },
    "Mybtn\0doubleClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mybtn[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void Mybtn::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Mybtn *_t = static_cast<Mybtn *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doubleClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Mybtn::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mybtn::doubleClicked)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Mybtn::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_Mybtn.data,
      qt_meta_data_Mybtn,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Mybtn::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mybtn::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Mybtn.stringdata0))
        return static_cast<void*>(const_cast< Mybtn*>(this));
    return QPushButton::qt_metacast(_clname);
}

int Mybtn::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Mybtn::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
