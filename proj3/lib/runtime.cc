/* -*-C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Runtime support library for apyc. */

/* Author: P. N. Hilfinger */

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

#include "runtime.h"

static void fatal(const char* msg) __attribute__ ((noreturn));
static PyBool* toPyBool (PyValue v);

static void fatal(const char* msg) 
{
    cerr << "Fatal error: " << msg << endl;
    exit(2);
}

/***** Methods and Constructors *****/

void
PyObject::print(ostream& os)
{
    os << "<" << typeName () << "@" << (void*) this << ">";
}

const char*
PyObject::typeName ()
{
    return "?";
}

PyStr*
PyObject::asStr () {
    fatal ("invalid internal type conversion");
}

PyInt*
PyObject::asInt () {
    fatal ("invalid internal type conversion");
}

PyBool*
PyObject::asBool () {
    fatal ("invalid internal type conversion");
}

PyRange*
PyObject::asRange () {
    fatal ("invalid internal type conversion");
}

PyList*
PyObject::asList () {
    fatal ("invalid internal type conversion");
}

PyDict*
PyObject::asDict () {
    fatal ("invalid internal type conversion");
}

PyTuple0*
PyObject::asTuple0 () {
    fatal ("invalid internal type conversion");
}

PyTuple1*
PyObject::asTuple1 () {
    fatal ("invalid internal type conversion");
}

PyTuple2*
PyObject::asTuple2 () {
    fatal ("invalid internal type conversion");
}

PyTuple3*
PyObject::asTuple3 () {
    fatal ("invalid internal type conversion");
}

/* None */
const char*
PyNoType::typeName ()
{
    return "<None>";
}

void
PyNoType::print (ostream& os)
{
    os << "None";
}

PyNoType
PyNoType::NoneObj;

const PyValue PyNone = &PyNoType::NoneObj;

/* Strings. */

PyStr::PyStr (const string& val) : _val (val) 
{
}

void
PyStr::print (ostream& os)
{
    os << _val;
}

PyStr* 
PyStr::asStr ()
{
    return this;
}

const char*
PyStr::typeName ()
{
    return "str";
}

PyStr*
PyStr::append (PyValue other)
{
    return new PyStr(_val + other->asStr()->_val);
}

string
PyStr::getValue()
{
    return _val;
}

/* Ints */

PyInt::PyInt (const int val) : _val (val)
{
}

void
PyInt::print (ostream& os)
{
    os << _val;
}

PyInt*
PyInt::asInt ()
{
    return this;
}

const char*
PyInt::typeName ()
{
    return "int";
}

int
PyInt::getValue()
{
    return _val;
}

/* Bools */

static PyBool* TrueObj = new PyBool(1);
static PyBool* FalseObj = new PyBool(0);

const PyValue PyTrue = TrueObj;
const PyValue PyFalse = FalseObj;

PyBool::PyBool (const int val) : _val (val)
{
}

void
PyBool::print(ostream& os)
{
    if (_val) {
        os << true;
    } else {
        os << false;
    }
}

PyValue
toPyBool (int v)
{
    return v ? PyTrue : PyFalse;
}

PyBool*
PyBool::asBool ()
{
    return this;
}
    
const char*
PyBool::typeName ()
{
    return "bool";
}

/* Ranges */

PyRange*
PyRange::asRange ()
{
    return this;
}

const char*
PyRange::typeName ()
{
    return "range";
}

/* Lists */

PyList*
PyList::asList ()
{
    return this;
}

const char*
PyList::typeName ()
{
    return "list";
}

void
PyList::append (PyValue elt)
{
    items.push_back (elt);
}

void
PyList::extend (PyValue other)
{
    PyList* otherp = other->asList ();
    vector<PyValue>& otherItems = otherp->items;
    items.insert (items.end (), otherItems.begin (), otherItems.end ());
}

/* Dicts */

PyDict*
PyDict::asDict ()
{
    return this;
}

const char*
PyDict::typeName ()
{
    return "dict";
}

PyTuple0*
PyTuple0::asTuple0 ()
{
    return this;
}

/* Tuples */

const char*
PyTuple0::typeName ()
{
    return "tuple0";
}

PyTuple1*
PyTuple1::asTuple1 ()
{
    return this;
}

const char*
PyTuple1::typeName ()
{
    return "tuple1";
}


PyTuple2*
PyTuple2::asTuple2 ()
{
    return this;
}

const char*
PyTuple2::typeName ()
{
    return "tuple2";
}

PyTuple3*
PyTuple3::asTuple3 ()
{
    return this;
}
 
const char*
PyTuple3::typeName ()
{
    return "tuple3";
}

/* Integers */

PyValue
__add__int__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyInt(v0->asInt()->getValue() + v1->asInt()->getValue());
}

PyValue
__eq__int__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyBool(v0->asInt()->getValue() == v1->asInt()->getValue());
}

PyValue
__floordiv__int__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyInt(v0->asInt()->getValue() / v1->asInt()->getValue());
}

PyValue
__ge__int__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyBool(v0->asInt()->getValue() >= v1->asInt()->getValue());
}

PyValue
__gt__int__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyBool(v0->asInt()->getValue() > v1->asInt()->getValue());
}

PyValue
__le__int__ (PyValue v0, PyValue v1)
{
    return __ge__int__ (v1, v0);
}

PyValue
__lt__int__ (PyValue v0, PyValue v1)
{
    return __gt__int__ (v1, v0);
}

PyValue
__mod__int__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyInt(v0->asInt()->getValue() % v1->asInt()->getValue());
}

PyValue
__mul__int__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyInt(v0->asInt()->getValue() * v1->asInt()->getValue());
}

PyValue
__ne__int__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyBool(v0->asInt()->getValue() != v1->asInt()->getValue());
}

PyValue
__neg__int__ (PyValue v0)
{
    // return NULL;  // REPLACE WITH BODY
    if (v0->asInt()->getValue() > 0) {
        return (PyValue) new PyInt(-1 * v0->asInt()->getValue());
    } else {
        return v0;
    }   
}

PyValue
__pos__int__ (PyValue v0)
{
    if (v0->asInt()->getValue() < 0) {
        return (PyValue) new PyInt(-1 * v0->asInt()->getValue());
    } else {
        return v0;
    }
}

PyValue
__pow__int__ (PyValue v0, PyValue v1)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__sub__int__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyInt(v0->asInt()->getValue() - v1->asInt()->getValue());
}


/* Strings */

PyValue
__add__str__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyStr (v0->asStr()->getValue() + v1->asStr()->getValue());
}

PyValue
__eq__str__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyBool(v0->asStr()->getValue().compare(v1->asStr()->getValue()) == 0);
}

PyValue
__ne__str__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyBool(v0->asStr()->getValue().compare(v1->asStr()->getValue()) != 0);
}

PyValue
__ge__str__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyBool(v0->asStr()->getValue().compare(v1->asStr()->getValue()) >= 0);
}

PyValue
__getitem__str__ (PyValue v0, PyValue v1)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__getslice__str__ (PyValue v0, PyValue v1, PyValue v2)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__gt__str__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyBool(v0->asStr()->getValue().compare(v1->asStr()->getValue()) > 0);
}

PyValue
__le__str__ (PyValue v0, PyValue v1)
{
    return __le__str__ (v1, v0);
}

PyValue
__len__str__ (PyValue v0)
{
    // return NULL;  // REPLACE WITH BODY
    return (PyValue) new PyInt(v0->asStr()->getValue().length());
}

PyValue
__lmul__str__ (PyValue v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    // v0 is str
    // v1 is int
    string tmp = "";
    string input_str = v0->asStr()->getValue();
    int times = v1->asInt()->getValue();
    for (int i = 0; i < times; ++i)
    {
        tmp += input_str;
    }
    return (PyValue) new PyStr(tmp);
}

PyValue
__lt__str__ (PyValue v0, PyValue v1)
{
    return __gt__str__ (v1, v0);
}

PyValue
__rmul__str__ (PyValue v0, PyValue v1)
{
    return __lmul__str__ (v1, v0);
}

PyValue
__toint__str__ (PyValue v0)
{
    // v0 is str
    // return int
    // return NULL;  // REPLACE WITH BODY
    // return (PyValue) new PyInt(std::stoi(v0->asStr()->getValue()));
}

PyValue
__tostr__ (PyValue v0)
{
    // v0 can be anytype
    return NULL;  // REPLACE WITH BODY
}


/* Dictionaries */

PyValue
__contains__dict__ (PyValue v0, PyValue v1)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__getitem__dict__ (PyValue v0, PyValue v1)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__len__dict__ (PyValue v0)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__setitem__dict__ (PyValue v0, PyValue v1, PyValue v2)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__notcontains__dict__ (PyValue v0, PyValue v1)
{
    return NULL;  // REPLACE WITH BODY
}


/* Lists */

PyValue
__getitem__list__ (PyValue v0, PyValue v1)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__getslice__list__ (PyValue v0, PyValue v1, PyValue v2)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__len__list__ (PyValue v0)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__setitem__list__ (PyValue v0, PyValue v1, PyValue v2)
{
    return NULL;  // REPLACE WITH BODY
}

extern PyValue __setslice__list__ (PyValue v0, PyValue v1, PyValue v2,
                                   PyValue v3);

/* Ranges */

PyValue
__len__range__ (PyValue v0)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__xrange__ (PyValue v0, PyValue v1)
{
    return NULL;  // REPLACE WITH BODY
}
 

/* General values */

PyValue
__is__ (PyValue v0, PyValue v1)
{
    return toPyBool (v0 == v1);
}

PyValue
__isnot__ (PyValue v0, PyValue v1)
{
    return toPyBool (v0 != v1);
}

PyValue
__not__ (PyValue v0)
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__truth__ (PyValue v0)
{
    return NULL;  // REPLACE WITH BODY
}


/* Communication with environment. */

static PyList* commandLine;

PyValue
__argv__ ()
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__read__ ()
{
    return NULL;  // REPLACE WITH BODY
}

PyValue
__readline__ ()
{
    return NULL;  // REPLACE WITH BODY
}


/***** Other support *****/

static bool atStart;

void
__print__ (PyValue v)
{
    if (!atStart) 
	cout << " ";
    atStart = false;
    v->print (cout);
}


void
__newline__ ()
{
    cout << endl;
    atStart = true;
}

/***** THe main routine *****/

extern void __main__ ();

int
main (int argc, char* argv[])
{
    atStart = true;
    commandLine = new PyList();
    for (int i = 0; i < argc; i += 1) {
	commandLine->asList()->append(__cons_str__ (argv[i]));
    }
    __main__ ();
}

	
    
