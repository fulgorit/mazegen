/****************************************************************************
** Meta object code from reading C++ file 'scriptwidget.h'
**
** Created: Wed Jun 19 10:41:55 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scriptwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scriptwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x0a,
      42,   13,   13,   13, 0x08,
      64,   57,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ScriptWidget[] = {
    "ScriptWidget\0\0value\0display(QScriptValue)\0"
    "updateSource()\0preset\0setPreset(int)\0"
};

void ScriptWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScriptWidget *_t = static_cast<ScriptWidget *>(_o);
        switch (_id) {
        case 0: _t->display((*reinterpret_cast< QScriptValue(*)>(_a[1]))); break;
        case 1: _t->updateSource(); break;
        case 2: _t->setPreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ScriptWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScriptWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScriptWidget,
      qt_meta_data_ScriptWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptWidget))
        return static_cast<void*>(const_cast< ScriptWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScriptWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
