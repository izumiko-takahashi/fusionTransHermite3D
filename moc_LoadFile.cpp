/****************************************************************************
** Meta object code from reading C++ file 'LoadFile.h'
**
** Created: Wed 29. Aug 18:13:14 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "LoadFile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LoadFile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoadFile[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      60,   10,    9,    9, 0x05,
     127,  119,    9,    9, 0x05,
     162,  154,    9,    9, 0x05,
     191,  182,    9,    9, 0x05,
     272,  212,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     362,  357,    9,    9, 0x0a,
     382,  357,    9,    9, 0x0a,
     403,  357,    9,    9, 0x0a,
     422,  357,    9,    9, 0x0a,
     444,  442,    9,    9, 0x0a,
     464,  462,    9,    9, 0x0a,
     484,  482,    9,    9, 0x0a,
     504,  502,    9,    9, 0x0a,
     519,  517,    9,    9, 0x0a,
     534,  532,    9,    9, 0x0a,
     550,  547,    9,    9, 0x0a,
     566,  564,    9,    9, 0x0a,
     587,  585,    9,    9, 0x0a,
     605,    9,    9,    9, 0x0a,
     619,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoadFile[] = {
    "LoadFile\0\0name,spaceX,spaceY,spaceZ,imaX,imaY,first,last,op\0"
    "fileRAW(std::string,float,float,float,int,int,int,int,int)\0"
    "name,op\0fileDICOM(std::string,int)\0"
    "dirName\0strDirName(QString)\0fileName\0"
    "strFileName(QString)\0"
    "dir,fileNam,prefix,pattern,xbeg,xend,ybeg,yend,imgb,imge,op\0"
    "fileBMP(std::string,std::string,std::string,std::string,int,int,int,in"
    "t,int,int,int)\0"
    "name\0setDirName(QString)\0setFileName(QString)\0"
    "setPrefix(QString)\0setPattern(QString)\0"
    "x\0setSpaceX(double)\0y\0setSpaceY(double)\0"
    "z\0setSpaceZ(double)\0u\0setDimU(int)\0v\0"
    "setDimV(int)\0w\0setDimW(int)\0vw\0"
    "setDimVW(int)\0f\0setFirstIndex(int)\0g\0"
    "setLastIndex(int)\0getFileName()\0"
    "getDirName()\0"
};

void LoadFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoadFile *_t = static_cast<LoadFile *>(_o);
        switch (_id) {
        case 0: _t->fileRAW((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9]))); break;
        case 1: _t->fileDICOM((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->strDirName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->strFileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->fileBMP((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3])),(*reinterpret_cast< std::string(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9])),(*reinterpret_cast< int(*)>(_a[10])),(*reinterpret_cast< int(*)>(_a[11]))); break;
        case 5: _t->setDirName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->setFileName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setPrefix((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->setPattern((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->setSpaceX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setSpaceY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->setSpaceZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->setDimU((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->setDimV((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->setDimW((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->setDimVW((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->setFirstIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->setLastIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->getFileName(); break;
        case 19: _t->getDirName(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LoadFile::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoadFile::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LoadFile,
      qt_meta_data_LoadFile, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoadFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoadFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoadFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoadFile))
        return static_cast<void*>(const_cast< LoadFile*>(this));
    return QWidget::qt_metacast(_clname);
}

int LoadFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void LoadFile::fileRAW(std::string _t1, float _t2, float _t3, float _t4, int _t5, int _t6, int _t7, int _t8, int _t9)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LoadFile::fileDICOM(std::string _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LoadFile::strDirName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LoadFile::strFileName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LoadFile::fileBMP(std::string _t1, std::string _t2, std::string _t3, std::string _t4, int _t5, int _t6, int _t7, int _t8, int _t9, int _t10, int _t11)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)), const_cast<void*>(reinterpret_cast<const void*>(&_t10)), const_cast<void*>(reinterpret_cast<const void*>(&_t11)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
