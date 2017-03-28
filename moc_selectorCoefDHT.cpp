/****************************************************************************
** Meta object code from reading C++ file 'selectorCoefDHT.h'
**
** Created: Mon 22. Oct 14:41:36 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "selectorCoefDHT.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectorCoefDHT.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SelectorCoefDHT[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   42,   16,   16, 0x08,
      67,   42,   16,   16, 0x08,
      85,   42,   16,   16, 0x08,
     103,   42,   16,   16, 0x08,
     121,   42,   16,   16, 0x08,
     140,   42,   16,   16, 0x08,
     158,   42,   16,   16, 0x08,
     176,   42,   16,   16, 0x08,
     194,   42,   16,   16, 0x08,
     212,   42,   16,   16, 0x08,
     230,   42,   16,   16, 0x08,
     251,  248,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SelectorCoefDHT[] = {
    "SelectorCoefDHT\0\0coef\0sendOption(QString)\0"
    "toggle\0loadCoef000(bool)\0loadCoef010(bool)\0"
    "loadCoef100(bool)\0loadCoef001(bool)\0"
    "loadGradient(bool)\0loadCoef110(bool)\0"
    "loadCoef101(bool)\0loadCoef011(bool)\0"
    "loadCoef200(bool)\0loadCoef020(bool)\0"
    "loadCoef002(bool)\0on\0restartVolume(bool)\0"
};

void SelectorCoefDHT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SelectorCoefDHT *_t = static_cast<SelectorCoefDHT *>(_o);
        switch (_id) {
        case 0: _t->sendOption((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->loadCoef000((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->loadCoef010((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->loadCoef100((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->loadCoef001((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->loadGradient((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->loadCoef110((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->loadCoef101((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->loadCoef011((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->loadCoef200((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->loadCoef020((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->loadCoef002((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->restartVolume((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SelectorCoefDHT::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SelectorCoefDHT::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SelectorCoefDHT,
      qt_meta_data_SelectorCoefDHT, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SelectorCoefDHT::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SelectorCoefDHT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SelectorCoefDHT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SelectorCoefDHT))
        return static_cast<void*>(const_cast< SelectorCoefDHT*>(this));
    if (!strcmp(_clname, "Ui::selectorCoefDHT"))
        return static_cast< Ui::selectorCoefDHT*>(const_cast< SelectorCoefDHT*>(this));
    return QWidget::qt_metacast(_clname);
}

int SelectorCoefDHT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void SelectorCoefDHT::sendOption(const QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
