/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Header for apyc runtime support library. */

/* Author: P. N. Hilfinger */

#ifndef RUNTIME_H
#define RUNTIME_H

#include <iostream>
#include <vector>

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

private:
    string _val;
};

class PyInt : public PyObject {
public:
    PyInt (const int val);
    PyInt* asInt ();
    const char* typeName ();
private:
    int _val;
};

class PyBool : public PyObject {
public:
    PyBool* asBool ();
    const char* typeName ();    
};

class PyRange : public PyObject {
public:
    PyRange* asRange ();
    const char* typeName ();
};

class PyList : public PyObject {
public:
    PyList* asList ();
    const char* typeName ();
    /** Add ELT to the end of this. */
    void append (PyValue elt);
    /** Append list OTHER to the end of this. */
    void extend (PyValue other);

private:
    vector<PyValue> items;
};

class PyDict : public PyObject {
public:
    PyDict* asDict ();
    const char* typeName ();
};

class PyTuple0 : public PyObject {
public:
    PyTuple0* asTuple0 ();
    const char* typeName ();
};

class PyTuple1 : public PyObject {
public:
    PyTuple1* asTuple1 ();
    const char* typeName ();
};

class PyTuple2 : public PyObject {
public:
    PyTuple2* asTuple2 ();
    const char* typeName ();
};

class PyTuple3 : public PyObject {
public:
    PyTuple3* asTuple3 ();
    const char* typeName (); 
};

/***** Headers of native methods. *****/

/* Integers */

extern PyValue __add__int__ (PyValue v0, PyValue v1);
extern PyValue __eq__int__ (PyValue v0, PyValue v1);
extern PyValue __floordiv__int__ (PyValue v0, PyValue v1);
extern PyValue __ge__int__ (PyValue v0, PyValue v1);
extern PyValue __gt__int__ (PyValue v0, PyValue v1);
extern PyValue __le__int__ (PyValue v0, PyValue v1);
extern PyValue __lt__int__ (PyValue v0, PyValue v1);
extern PyValue __mod__int__ (PyValue v0, PyValue v1);
extern PyValue __mul__int__ (PyValue v0, PyValue v1);
extern PyValue __ne__int__ (PyValue v0, PyValue v1);
extern PyValue __ne__str__ (PyValue v0, PyValue v1);
extern PyValue __neg__int__ (PyValue v0);
extern PyValue __pos__int__ (PyValue v0);
extern PyValue __pow__int__ (PyValue v0, PyValue v1);
extern PyValue __sub__int__ (PyValue v0, PyValue v1);

/* Strings */

extern PyValue __add__str__ (PyValue v0, PyValue v1);
extern PyValue __eq__str__ (PyValue v0, PyValue v1);
extern PyValue __ge__str__ (PyValue v0, PyValue v1);
extern PyValue __getitem__str__ (PyValue v0, PyValue v1);
extern PyValue __getslice__str__ (PyValue v0, PyValue v1, PyValue v2);
extern PyValue __gt__str__ (PyValue v0, PyValue v1);
extern PyValue __le__str__ (PyValue v0, PyValue v1);
extern PyValue __len__str__ (PyValue v0);
extern PyValue __lmul__str__ (PyValue v0, PyValue v1);
extern PyValue __lt__str__ (PyValue v0, PyValue v1);
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

extern PyValue __len__range__ (PyValue v0);
extern PyValue __xrange__ (PyValue v0, PyValue v1); 

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
__cons_int__ (const int* val)
{
    return new PyInt (val);
}

#endif