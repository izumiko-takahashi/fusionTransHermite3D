/****************************************************************************
** Meta object code from reading C++ file 'licensewizard.h'
**
** Created: Fri 31. Aug 19:00:51 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "licensewizard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'licensewizard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LicenseWizard[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LicenseWizard[] = {
    "LicenseWizard\0\0showHelp()\0"
};

void LicenseWizard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LicenseWizard *_t = static_cast<LicenseWizard *>(_o);
        switch (_id) {
        case 0: _t->showHelp(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LicenseWizard::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LicenseWizard::staticMetaObject = {
    { &QWizard::staticMetaObject, qt_meta_stringdata_LicenseWizard,
      qt_meta_data_LicenseWizard, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LicenseWizard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LicenseWizard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LicenseWizard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LicenseWizard))
        return static_cast<void*>(const_cast< LicenseWizard*>(this));
    return QWizard::qt_metacast(_clname);
}

int LicenseWizard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizard::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_IntroPage[] = {

 // content:
       6,       // revision
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

static const char qt_meta_stringdata_IntroPage[] = {
    "IntroPage\0"
};

void IntroPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData IntroPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IntroPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_IntroPage,
      qt_meta_data_IntroPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IntroPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IntroPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IntroPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IntroPage))
        return static_cast<void*>(const_cast< IntroPage*>(this));
    return QWizardPage::qt_metacast(_clname);
}

int IntroPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_LoadDICOMPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoadDICOMPage[] = {
    "LoadDICOMPage\0\0dirName\0strDirName(QString)\0"
    "getDirName()\0"
};

void LoadDICOMPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoadDICOMPage *_t = static_cast<LoadDICOMPage *>(_o);
        switch (_id) {
        case 0: _t->strDirName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->getDirName(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LoadDICOMPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoadDICOMPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_LoadDICOMPage,
      qt_meta_data_LoadDICOMPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoadDICOMPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoadDICOMPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoadDICOMPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoadDICOMPage))
        return static_cast<void*>(const_cast< LoadDICOMPage*>(this));
    return QWizardPage::qt_metacast(_clname);
}

int LoadDICOMPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LoadDICOMPage::strDirName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_LoadRAWPage[] = {

 // content:
       6,       // revision
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

static const char qt_meta_stringdata_LoadRAWPage[] = {
    "LoadRAWPage\0"
};

void LoadRAWPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LoadRAWPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoadRAWPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_LoadRAWPage,
      qt_meta_data_LoadRAWPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoadRAWPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoadRAWPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoadRAWPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoadRAWPage))
        return static_cast<void*>(const_cast< LoadRAWPage*>(this));
    return QWizardPage::qt_metacast(_clname);
}

int LoadRAWPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_LoadBMPPage[] = {

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
      21,   13,   12,   12, 0x05,
      50,   41,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      71,   12,   12,   12, 0x0a,
      85,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoadBMPPage[] = {
    "LoadBMPPage\0\0dirName\0strDirName(QString)\0"
    "fileName\0strFileName(QString)\0"
    "getFileName()\0getDirName()\0"
};

void LoadBMPPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoadBMPPage *_t = static_cast<LoadBMPPage *>(_o);
        switch (_id) {
        case 0: _t->strDirName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->strFileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->getFileName(); break;
        case 3: _t->getDirName(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LoadBMPPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoadBMPPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_LoadBMPPage,
      qt_meta_data_LoadBMPPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoadBMPPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoadBMPPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoadBMPPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoadBMPPage))
        return static_cast<void*>(const_cast< LoadBMPPage*>(this));
    return QWizardPage::qt_metacast(_clname);
}

int LoadBMPPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
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
void LoadBMPPage::strDirName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LoadBMPPage::strFileName(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_ConclusionPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ConclusionPage[] = {
    "ConclusionPage\0\0printButtonClicked()\0"
};

void ConclusionPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConclusionPage *_t = static_cast<ConclusionPage *>(_o);
        switch (_id) {
        case 0: _t->printButtonClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ConclusionPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConclusionPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_ConclusionPage,
      qt_meta_data_ConclusionPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConclusionPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConclusionPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConclusionPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConclusionPage))
        return static_cast<void*>(const_cast< ConclusionPage*>(this));
    return QWizardPage::qt_metacast(_clname);
}

int ConclusionPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
