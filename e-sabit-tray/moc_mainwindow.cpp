/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[244];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "listToFile"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "list"
QT_MOC_LITERAL(4, 28, 8), // "filename"
QT_MOC_LITERAL(5, 37, 10), // "fileToList"
QT_MOC_LITERAL(6, 48, 11), // "listGetLine"
QT_MOC_LITERAL(7, 60, 4), // "data"
QT_MOC_LITERAL(8, 65, 10), // "listRemove"
QT_MOC_LITERAL(9, 76, 11), // "listReplace"
QT_MOC_LITERAL(10, 88, 7), // "oldData"
QT_MOC_LITERAL(11, 96, 7), // "newData"
QT_MOC_LITERAL(12, 104, 5), // "index"
QT_MOC_LITERAL(13, 110, 9), // "listMerge"
QT_MOC_LITERAL(14, 120, 5), // "list1"
QT_MOC_LITERAL(15, 126, 5), // "list2"
QT_MOC_LITERAL(16, 132, 9), // "dataIndex"
QT_MOC_LITERAL(17, 142, 11), // "listGetList"
QT_MOC_LITERAL(18, 154, 13), // "iconActivated"
QT_MOC_LITERAL(19, 168, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(20, 202, 5), // "gizle"
QT_MOC_LITERAL(21, 208, 12), // "WidgetClosed"
QT_MOC_LITERAL(22, 221, 10), // "widgetShow"
QT_MOC_LITERAL(23, 232, 11) // "resetStatus"

    },
    "MainWindow\0listToFile\0\0list\0filename\0"
    "fileToList\0listGetLine\0data\0listRemove\0"
    "listReplace\0oldData\0newData\0index\0"
    "listMerge\0list1\0list2\0dataIndex\0"
    "listGetList\0iconActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "gizle\0WidgetClosed\0widgetShow\0resetStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x0a /* Public */,
       5,    1,   79,    2, 0x0a /* Public */,
       6,    2,   82,    2, 0x0a /* Public */,
       8,    2,   87,    2, 0x0a /* Public */,
       9,    4,   92,    2, 0x0a /* Public */,
      13,    3,  101,    2, 0x0a /* Public */,
      17,    3,  108,    2, 0x0a /* Public */,
      18,    1,  115,    2, 0x0a /* Public */,
      20,    0,  118,    2, 0x0a /* Public */,
      21,    0,  119,    2, 0x0a /* Public */,
      22,    0,  120,    2, 0x0a /* Public */,
      23,    0,  121,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList, QMetaType::QString,    3,    4,
    QMetaType::QStringList, QMetaType::QString,    4,
    QMetaType::QString, QMetaType::QStringList, QMetaType::QString,    3,    7,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QString,    3,    7,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QString, QMetaType::QString, QMetaType::Int,    3,   10,   11,   12,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList, QMetaType::Int,   14,   15,   16,
    QMetaType::QStringList, QMetaType::QStringList, QMetaType::QString, QMetaType::Int,    3,    7,   12,
    QMetaType::Void, 0x80000000 | 19,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->listToFile((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: { QStringList _r = _t->fileToList((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 2: { QString _r = _t->listGetLine((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { QStringList _r = _t->listRemove((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 4: { QStringList _r = _t->listReplace((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 5: { QStringList _r = _t->listMerge((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 6: { QStringList _r = _t->listGetList((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 8: _t->gizle(); break;
        case 9: _t->WidgetClosed(); break;
        case 10: _t->widgetShow(); break;
        case 11: _t->resetStatus(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
