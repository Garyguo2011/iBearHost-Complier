/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Header for apyc runtime support library. */

/* Author: P. N. Hilfinger */

#ifndef RUNTIME_H
#define RUNTIME_H

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <cstdarg>

using namespace std;

class PyObject;
typedef PyObject* PyValue;

class PyStr;
class PyInt;
class PyBool;
class PyRange;
class PyList;
class PyDict;
class PyTuple0;
class PyTuple1;
class PyTuple2;
class PyTuple3;

class PyPair;

extern const PyValue PyNone;
extern const PyValue PyTrue;
extern const PyValue PyFalse;


class PyObject {
protected:
    /** Only callable by children. */
    PyObject () { }
public:
    virtual void print(ostream& os);
    virtual const char* typeName ();

    /** Conversion functions */
    virtual PyStr* asStr ();
    virtual PyInt* asInt ();
    virtual PyBool* asBool ();
    virtual PyRange* asRange ();
    virtual PyList* asList ();
    virtual PyDict* asDict ();
    virtual PyTuple0* asTuple0 ();
    virtual PyTuple1* asTuple1 ();
    virtual PyTuple2* asTuple2 ();
    virtual PyTuple3* asTuple3 ();
    virtual PyPair* asPair ();
}; 

/** Represents the None value. There will only be one None object
 *  defined.  PyNone contains a pointer to this singleton object. */
class PyNoType : public PyObject {
private:
    /** Cannot be called from outside. */
    PyNoType() { }
public:
    const char* typeName ();
    void print(ostream& os);
    static PyNoType NoneObj;
};

class PyStr : public PyObject {
public:
    PyStr (const string& val);
    const char* typeName ();

    void print(ostream& os);
    PyStr* asStr ();

    PyStr* append (PyValue other);
    string getValue();

private:
    string _val;
};

class PyInt : public PyObject {
public:
    PyInt (const int val);
    void print(ostream& os);
    PyInt* asInt ();
    const char* typeName ();
    int getValue();

private:
    int _val;
};

class PyBool : public PyObject {
public:
    PyBool (const int val);
    void print(ostream& os);
    PyBool* asBool ();
    const char* typeName ();
    bool getValue();

private:
    bool _val;
};

class PyRange : public PyObject {
public:
    PyRange (PyInt* from, PyInt* to);
    PyRange* asRange ();
    const char* typeName ();
    void print(ostream& os);
    int getSize();
private:
    vector<PyValue> items;
};

class PyList : public PyObject {
public:
    PyList* asList ();
    const char* typeName ();
    /** Add ELT to the end of this. */
    void append (PyValue elt);
    /** Append list OTHER to the end of this. */
    void extend (PyValue other);
    void print(ostream& os);

private:
    vector<PyValue> items;
};

class PyPair : public PyObject {
public:
    PyPair(PyValue val0, PyValue val1);
    PyPair* asPair ();
    const char* typeName();
    pair<PyValue, PyValue> getValue();

private:
    pair<PyValue, PyValue> _val;
};

class PyDict : public PyObject {
public:
    PyDict* asDict ();
    const char* typeName ();
    void insert (PyValue elt);
    void print (ostream& os);
    PyValue get(PyValue key);

private:
    map<PyValue, PyValue> items;
};

class PyTuple0 : public PyObject {
public:
    PyTuple0* asTuple0 ();
    const char* typeName ();
    void print(ostream& os);
};

class PyTuple1 : public PyObject {
public:
    PyTuple1 (PyValue val);
    PyTuple1* asTuple1 ();
    const char* typeName ();
    void print(ostream& os);
private:
    PyValue _vals[1];
};

class PyTuple2 : public PyObject {
public:
    PyTuple2 (PyValue val0, PyValue val1);
    PyTuple2* asTuple2 ();
    const char* typeName ();
    void print(ostream& os);
private:
    PyValue _vals[2];
};

class PyTuple3 : public PyObject {
public:
    PyTuple3 (PyValue val0, PyValue val1, PyValue val2);
    PyTuple3* asTuple3 ();
    const char* typeName ();
    void print(ostream& os);
private:
    PyValue _vals[3];
};

/***** Headers of native methods. *****/

/* Integers */

extern PyInt* __add__int__ (PyInt* v0, PyInt* v1);
extern PyBool* __eq__int__ (PyInt* v0, PyInt* v1);
extern PyInt* __floordiv__int__ (PyInt* v0, PyInt* v1);
extern PyBool* __ge__int__ (PyInt* v0, PyInt* v1);
extern PyBool* __gt__int__ (PyInt* v0, PyInt* v1);
extern PyBool* __le__int__ (PyInt* v0, PyInt* v1);
extern PyBool* __lt__int__ (PyInt* v0, PyInt* v1);
extern PyInt* __mod__int__ (PyInt* v0, PyInt* v1);
extern PyInt* __mul__int__ (PyInt* v0, PyInt* v1);
extern PyBool* __ne__int__ (PyInt* v0, PyInt* v1);
extern PyInt* __neg__int__ (PyInt* v0);
extern PyInt* __pos__int__ (PyInt* v0);
extern PyInt* __pow__int__ (PyInt* v0, PyInt* v1);
extern PyInt* __sub__int__ (PyInt* v0, PyInt* v1);

/* Strings */

extern PyValue __add__str__ (PyValue v0, PyValue v1);
extern PyBool* __eq__str__ (PyValue v0, PyValue v1);
extern PyBool* __ge__str__ (PyValue v0, PyValue v1);
extern PyValue __getitem__str__ (PyValue v0, PyValue v1);
extern PyValue __getslice__str__ (PyValue v0, PyValue v1, PyValue v2);
extern PyBool* __gt__str__ (PyValue v0, PyValue v1);
extern PyBool* __le__str__ (PyValue v0, PyValue v1);
extern PyValue __len__str__ (PyValue v0);
extern PyValue __lmul__str__ (PyValue v0, PyValue v1);
extern PyBool* __ne__str__ (PyStr* v0, PyStr* v1);
extern PyBool* __lt__str__ (PyValue v0, PyValue v1);
extern PyValue __rmul__str__ (PyValue v0, PyValue v1);
extern PyValue __toint__str__ (PyValue v0);
extern PyValue __tostr__ (PyValue v0);

/* Dictionaries */

extern PyValue __contains__dict__ (PyValue v0, PyValue v1);
extern PyValue __getitem__dict__ (PyValue v0, PyValue v1);
extern PyValue __len__dict__ (PyValue v0);
extern PyValue __setitem__dict__ (PyValue v0, PyValue v1, PyValue v2);
extern PyValue __notcontains__dict__ (PyValue v0, PyValue v1);

/* Lists */

extern PyValue __getitem__list__ (PyValue v0, PyValue v1);
extern PyValue __getslice__list__ (PyValue v0, PyValue v1, PyValue v2);
extern PyValue __len__list__ (PyValue v0);
extern PyValue __setitem__list__ (PyValue v0, PyValue v1, PyValue v2);
extern PyValue __setslice__list__ (PyValue v0, PyValue v1, PyValue v2,
                                   PyValue v3);

/* Ranges */

extern PyInt* __len__range__ (PyRange* v0);
extern PyRange* __xrange__ (PyInt* v0, PyInt* v1); 

/* General values */

extern PyValue __is__ (PyValue v0, PyValue v1);
extern PyValue __isnot__ (PyValue v0, PyValue v1);
extern PyValue __not__ (PyValue v0);
extern PyValue __truth__ (PyValue v0);

/* Communication with environment. */

extern PyValue __argv__ ();
extern PyValue __read__ ();
extern PyValue __readline__ ();


/***** Other runtime support. *****/

/** Print V on cout. */
extern void __print__(PyValue v);
/** Print a newline on cout. */
extern void __newline__();

/** Convert VAL into a Python string. */
static inline PyStr*
__cons_str__ (const char* val)
{
    return new PyStr (val);
}

static inline PyInt*
__cons_int__ (const int val)
{
    return new PyInt (val);
}

static inline PyBool*
__cons_bool__ (const int val)
{
    return new PyBool(val);
}

static inline PyRange*
__cons_range__ (PyInt* from, PyInt* to)
{
    return new PyRange(from, to);
}

static inline PyList*
__cons_list__ (int count, ...)
{
    va_list args;
    va_start(args, count);
    PyList* list = new PyList();
    for (int i = 0; i < count; i++) {
        PyValue temp = va_arg(args, PyValue);
        list->asList()->append(temp);
    }
    va_end(args);
    return list;
}

static inline PyTuple0*
__cons_tuple0__()
{
    return new PyTuple0();
}

static inline PyTuple1*
__cons_tuple1__(PyValue val)
{
    return new PyTuple1(val);
}

static inline PyTuple2*
__cons_tuple2__(PyValue val0, PyValue val1)
{
    return new PyTuple2(val0, val1);
}

static inline PyTuple3*
__cons_tuple3__(PyValue val0, PyValue val1, PyValue val2)
{
    return new PyTuple3(val0, val1, val2);
}

static inline PyPair*
__cons_pair__(PyValue val0, PyValue val1) 
{
    return new PyPair(val0, val1);
}

static inline PyDict*
__cons_dict__ (int count, ...)
{
    va_list args;
    va_start(args, count);
    PyDict* dict = new PyDict();
    for (int i = 0; i < count; i ++) {
        PyValue temp = va_arg(args, PyValue);
        dict->asDict()->insert(temp);
    }
    va_end(args);
    return dict;
}

#endif
