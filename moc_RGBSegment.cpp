/****************************************************************************
** Meta object code from reading C++ file 'RGBSegment.h'
**
** Created: Wed 10. Oct 15:03:26 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RGBSegment.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RGBSegment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RGBSegment[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x05,
      46,   39,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      89,   82,   11,   11, 0x08,
     117,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RGBSegment[] = {
    "RGBSegment\0\0color\0colorChanged(QColor)\0"
    "colors\0segment(std::vector<ColorSegment>*)\0"
    "widget\0slotSetLabelColor(QWidget*)\0"
    "sendParameter()\0"
};

void RGBSegment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RGBSegment *_t = static_cast<RGBSegment *>(_o);
        switch (_id) {
        case 0: _t->colorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: _t->segment((*reinterpret_cast< std::vector<ColorSegment>*(*)>(_a[1]))); break;
        case 2: _t->slotSetLabelColor((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->sendParameter(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RGBSegment::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RGBSegment::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RGBSegment,
      qt_meta_data_RGBSegment, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RGBSegment::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RGBSegment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RGBSegment::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RGBSegment))
        return static_cast<void*>(const_cast< RGBSegment*>(this));
    if (!strcmp(_clname, "Ui::RGBSegment"))
        return static_cast< Ui::RGBSegment*>(const_cast< RGBSegment*>(this));
    return QWidget::qt_metacast(_clname);
}

int RGBSegment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void RGBSegment::colorChanged(QColor _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RGBSegment::segment(std::vector<ColorSegment> * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
