/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed 24. Oct 15:01:30 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Mainwindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   11,   11,   11, 0x0a,
      59,   11,   11,   11, 0x0a,
      76,   71,   11,   11, 0x0a,
      99,   11,   11,   11, 0x0a,
     125,  117,   11,   11, 0x0a,
     144,   11,   11,   11, 0x0a,
     182,  157,   11,   11, 0x0a,
     218,  211,   11,   11, 0x0a,
     264,   11,   11,   11, 0x0a,
     287,   11,   11,   11, 0x0a,
     313,  308,   11,   11, 0x0a,
     346,  338,   11,   11, 0x0a,
     424,  374,   11,   11, 0x0a,
     540,  486,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Mainwindow[] = {
    "Mainwindow\0\0color\0backgroundChanged(QColor)\0"
    "slotDataLoad()\0slotAbout()\0file\0"
    "slotFileReady(QString)\0slotLoadProject()\0"
    "checked\0setSliceCube(bool)\0slotFusion()\0"
    "opacityMean,opacityRange\0"
    "slotSetGrayInterval(int,int)\0colors\0"
    "slotSetRGBSegment(std::vector<ColorSegment>*)\0"
    "slotChangeBackground()\0slotShowRGBSegment()\0"
    "coef\0slotLoadCoefDHT(QString)\0name,op\0"
    "LoadVolume(std::string,int)\0"
    "name,spaceX,spaceY,spaceZ,imaX,imaY,first,last,op\0"
    "LoadVolume(std::string,float,float,float,int,int,int,int,int)\0"
    "dir,file,pfx,ptr,xBegin,xEnd,yBegin,yEnd,imgB,imgE,op\0"
    "LoadVolume(std::string,std::string,std::string,std::string,int,int,int"
    ",int,int,int,int)\0"
};

void Mainwindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Mainwindow *_t = static_cast<Mainwindow *>(_o);
        switch (_id) {
        case 0: _t->backgroundChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: _t->slotDataLoad(); break;
        case 2: _t->slotAbout(); break;
        case 3: _t->slotFileReady((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slotLoadProject(); break;
        case 5: _t->setSliceCube((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->slotFusion(); break;
        case 7: _t->slotSetGrayInterval((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->slotSetRGBSegment((*reinterpret_cast< std::vector<ColorSegment>*(*)>(_a[1]))); break;
        case 9: _t->slotChangeBackground(); break;
        case 10: _t->slotShowRGBSegment(); break;
        case 11: _t->slotLoadCoefDHT((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->LoadVolume((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->LoadVolume((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9]))); break;
        case 14: _t->LoadVolume((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3])),(*reinterpret_cast< std::string(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9])),(*reinterpret_cast< int(*)>(_a[10])),(*reinterpret_cast< int(*)>(_a[11]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Mainwindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Mainwindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Mainwindow,
      qt_meta_data_Mainwindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Mainwindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Mainwindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Mainwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Mainwindow))
        return static_cast<void*>(const_cast< Mainwindow*>(this));
    if (!strcmp(_clname, "Ui::MainWindow"))
        return static_cast< Ui::MainWindow*>(const_cast< Mainwindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Mainwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Mainwindow::backgroundChanged(QColor _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
