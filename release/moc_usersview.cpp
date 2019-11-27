/****************************************************************************
** Meta object code from reading C++ file 'usersview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../usersview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usersview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_User_t {
    QByteArrayData data[14];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_User_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_User_t qt_meta_stringdata_User = {
    {
QT_MOC_LITERAL(0, 0, 4), // "User"
QT_MOC_LITERAL(1, 5, 14), // "photo50Changed"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "photoidChanged"
QT_MOC_LITERAL(4, 36, 17), // "first_nameChanged"
QT_MOC_LITERAL(5, 54, 12), // "likedChanged"
QT_MOC_LITERAL(6, 67, 15), // "photo100Changed"
QT_MOC_LITERAL(7, 83, 9), // "idChanged"
QT_MOC_LITERAL(8, 93, 7), // "photo50"
QT_MOC_LITERAL(9, 101, 7), // "photoid"
QT_MOC_LITERAL(10, 109, 10), // "first_name"
QT_MOC_LITERAL(11, 120, 5), // "liked"
QT_MOC_LITERAL(12, 126, 8), // "photo100"
QT_MOC_LITERAL(13, 135, 2) // "id"

    },
    "User\0photo50Changed\0\0photoidChanged\0"
    "first_nameChanged\0likedChanged\0"
    "photo100Changed\0idChanged\0photo50\0"
    "photoid\0first_name\0liked\0photo100\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_User[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       6,   50, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,
       6,    0,   48,    2, 0x06 /* Public */,
       7,    0,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::QString, 0x00495103,
       9, QMetaType::QString, 0x00495103,
      10, QMetaType::QString, 0x00495103,
      11, QMetaType::QString, 0x00495103,
      12, QMetaType::QString, 0x00495103,
      13, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

void User::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        User *_t = static_cast<User *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->photo50Changed(); break;
        case 1: _t->photoidChanged(); break;
        case 2: _t->first_nameChanged(); break;
        case 3: _t->likedChanged(); break;
        case 4: _t->photo100Changed(); break;
        case 5: _t->idChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (User::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&User::photo50Changed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (User::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&User::photoidChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (User::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&User::first_nameChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (User::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&User::likedChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (User::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&User::photo100Changed)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (User::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&User::idChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        User *_t = static_cast<User *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->photo50(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->photoid(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->first_name(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->liked(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->photo100(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->id(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        User *_t = static_cast<User *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPhoto50(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setPhotoid(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setFirst_name(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setLiked(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setPhoto100(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setId(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

const QMetaObject User::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_User.data,
      qt_meta_data_User,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *User::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *User::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_User.stringdata0))
        return static_cast<void*>(const_cast< User*>(this));
    return QObject::qt_metacast(_clname);
}

int User::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void User::photo50Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void User::photoidChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void User::first_nameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void User::likedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void User::photo100Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void User::idChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
struct qt_meta_stringdata_usersView_t {
    QByteArrayData data[12];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_usersView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_usersView_t qt_meta_stringdata_usersView = {
    {
QT_MOC_LITERAL(0, 0, 9), // "usersView"
QT_MOC_LITERAL(1, 10, 7), // "addUser"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "photo50"
QT_MOC_LITERAL(4, 27, 7), // "photoid"
QT_MOC_LITERAL(5, 35, 10), // "first_name"
QT_MOC_LITERAL(6, 46, 8), // "photo100"
QT_MOC_LITERAL(7, 55, 2), // "id"
QT_MOC_LITERAL(8, 58, 5), // "clear"
QT_MOC_LITERAL(9, 64, 7), // "refresh"
QT_MOC_LITERAL(10, 72, 8), // "setToken"
QT_MOC_LITERAL(11, 81, 5) // "token"

    },
    "usersView\0addUser\0\0photo50\0photoid\0"
    "first_name\0photo100\0id\0clear\0refresh\0"
    "setToken\0token"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_usersView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    5,   34,    2, 0x0a /* Public */,
       8,    0,   45,    2, 0x0a /* Public */,
       9,    0,   46,    2, 0x0a /* Public */,
      10,    1,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void usersView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        usersView *_t = static_cast<usersView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 1: _t->clear(); break;
        case 2: _t->refresh(); break;
        case 3: _t->setToken((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject usersView::staticMetaObject = {
    { &QQuickWidget::staticMetaObject, qt_meta_stringdata_usersView.data,
      qt_meta_data_usersView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *usersView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *usersView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_usersView.stringdata0))
        return static_cast<void*>(const_cast< usersView*>(this));
    return QQuickWidget::qt_metacast(_clname);
}

int usersView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
