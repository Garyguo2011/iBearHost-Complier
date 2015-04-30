/* -*-C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Runtime support library for apyc. */

/* Author: P. N. Hilfinger */

#include <cstdlib>
#include <iostream>
#include <string>
#include "math.h"
#include <sstream>

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
    os << toStr();
}

string
PyObject::toStr()
{
    string str = "";
    str.append("undefined toStr()"); 
    return str;
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

PyPair*
PyObject::asPair () {
    fatal ("invalid internal type conversion");
}

/* None */
const char*
PyNoType::typeName ()
{
    return "<None>";
}

string
PyNoType::toStr ()
{
    return "None";
}

PyNoType
PyNoType::NoneObj;

const PyValue PyNone = &PyNoType::NoneObj;

/* Strings. */

PyStr::PyStr (const string& val) : _val (val) 
{
}

string
PyStr::toStr ()
{
    return _val;
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

string
PyInt::toStr ()
{
    stringstream ss;
    ss << _val;
    string str = ss.str();
    return str;
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

string
PyBool::toStr()
{
    if (_val) {
        return "True";
    } else {
        return "False";
    }
}

PyBool*
PyBool::notBool()
{
    if (_val) {
        return new PyBool(0);
    } else {
        return new PyBool(1);
    }
}

PyBool*
toPyBool (int v)
{
    return v ? new PyBool(1) : new PyBool(0);
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
int
PyBool::getValue() {
    return _val;
}

/* Ranges */

PyRange::PyRange (PyInt* from , PyInt* to)
{
    for (int i = from->getValue(); i < to->getValue(); i++) {
        items.push_back(new PyInt(i));
    }
}

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

string
PyRange::toStr()
{
    string str = "";
    str += "[";
    for (int i = 0 ; i < items.size(); i++) {
        str += items[i]->toStr();
        if (i < items.size()-1) {
            str += ", ";
        }
    }
    str += "]";
    return str;
}

int
PyRange::getSize()
{
    return (int) items.size();
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
string
PyList::toStr ()
{
    string str = "";
    str += "[";
    for (int i = 0 ; i < items.size(); i++) {
        str += items[i]->toStr();
        if (i < items.size()-1) {
            str += ", ";
        }
    }
    str += "]";
    return str;
}
int
PyList::getSize()
{
    return (int) items.size();
}

PyValue
PyList::getItem(PyInt* val)
{
    return items[val->getValue()];
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
void
PyDict::insert(PyValue elt)
{
    items.insert(elt->asPair()->getValue());
}

PyValue
PyDict::get(PyValue key)
{
    for (std::map<PyValue, PyValue>::iterator it=items.begin(); it!=items.end(); ++it) {
        if (it->first->toStr().compare(key->toStr()) == 0) {
            return it->second;
        }
        
    }
    return PyNone;
}

PyBool*
PyDict::contains(PyValue key)
{
    if (get(key)->toStr() != "None")
    {
        return new PyBool(1);
    } else {
        return new PyBool(0);
    }
}

int
PyDict::getSize()
{
    return items.size();
}

string
PyDict::toStr ()
{
    string str = "";
    int i = 0;
    str += "{";
    for (map<PyValue, PyValue>::iterator it=items.begin(); 
        it!=items.end(); ++it) {
        str += it->first->toStr();
        str += ": ";
        str += it->second->toStr();
        if (i != items.size() - 1) {
            str += ", ";
        }
        i++;
    }
    str += "}";
    return str;
}

/* PyDictInt */

const char*
PyDictInt::typeName ()
{
    return "dictInt";
}

/* PyDictStr */

const char*
PyDictStr::typeName ()
{
    return "dictStr";
}

/* PyDictBool */

const char*
PyDictBool::typeName ()
{
    return "dictBool";
}

/* Pair */
PyPair::PyPair(PyValue val0, PyValue val1) {
    _val = make_pair (val0, val1);
}

PyPair*
PyPair::asPair ()
{
    return this;
}

const char*
PyPair::typeName()
{
    return "pair";
}

pair<PyValue, PyValue> 
PyPair::getValue()
{
    return _val;
}

/* Tuples */

PyTuple0*
PyTuple0::asTuple0 ()
{
    return this;
}

const char*
PyTuple0::typeName ()
{
    return "tuple0";
}

string
PyTuple0::toStr()
{
    string str = "";
    str += "()";
    return str;
}

PyTuple1::PyTuple1 (PyValue val)
{
    _vals[0] = val;
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

string
PyTuple1::toStr()
{
    string str = "";
    str += "(";
    str += _vals[0]->toStr();
    str += ",";
    str +=")";
    return str;
}

PyTuple2::PyTuple2 (PyValue val0, PyValue val1)
{
    _vals[0] = val0;
    _vals[1] = val1;
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

string
PyTuple2::toStr()
{
    string str = "";
    str += "(";
    str += _vals[0]->toStr();
    str += ", ";
    str += _vals[1]->toStr();
    str +=")";
    return str;
}

PyTuple3::PyTuple3 (PyValue val0, PyValue val1, PyValue val2)
{
    _vals[0] = val0;
    _vals[1] = val1;
    _vals[2] = val2;
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

string
PyTuple3::toStr()
{
    string str = "";
    str += "(";
    str += _vals[0]->toStr();
    str += ", ";
    str += _vals[1]->toStr();
    str += ", ";
    str += _vals[2]->toStr();
    str +=")";
    return str;
}

/* Integers */

PyInt*
__add__int__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(v0->asInt()->getValue() + v1->asInt()->getValue());
}

PyBool*
__eq__int__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyBool(v0->asInt()->getValue() == v1->asInt()->getValue());
}

PyInt*
__floordiv__int__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(v0->asInt()->getValue() / v1->asInt()->getValue());
}

PyBool*
__ge__int__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyBool(v0->asInt()->getValue() >= v1->asInt()->getValue());
}

PyBool*
__gt__int__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyBool(v0->asInt()->getValue() > v1->asInt()->getValue());
}

PyBool*
__le__int__ (PyInt* v0, PyInt* v1)
{
    return __ge__int__ (v1, v0);
}

PyBool*
__lt__int__ (PyInt* v0, PyInt* v1)
{
    return __gt__int__ (v1, v0);
}

PyInt*
__mod__int__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(v0->asInt()->getValue() % v1->asInt()->getValue());
}

PyInt*
__mul__int__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(v0->asInt()->getValue() * v1->asInt()->getValue());
}

PyBool*
__ne__int__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyBool(v0->asInt()->getValue() != v1->asInt()->getValue());
}

PyInt*
__neg__int__ (PyInt* v0)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(-1 * v0->asInt()->getValue()); 
}

PyInt*
__pos__int__ (PyInt* v0)
{
    return v0;    
}

PyInt*
__pow__int__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(pow(v0->asInt()->getValue(), v1->asInt()->getValue()));
}

PyInt*
__sub__int__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(v0->asInt()->getValue() - v1->asInt()->getValue());
}


/* Strings */

PyStr*
__add__str__ (PyStr* v0, PyStr* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyStr (v0->asStr()->getValue() + v1->asStr()->getValue());
}

PyBool*
__eq__str__ (PyStr* v0, PyStr* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyBool(v0->asStr()->getValue().compare(v1->asStr()->getValue()) == 0);
}

PyBool*
__ne__str__ (PyStr* v0, PyStr* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyBool(v0->asStr()->getValue().compare(v1->asStr()->getValue()) != 0);
}

PyBool*
__ge__str__ (PyStr* v0, PyStr* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyBool(v0->asStr()->getValue().compare(v1->asStr()->getValue()) >= 0);
}

PyStr*
__getitem__str__ (PyStr* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    int temp = 0;
    if (v1->getValue() < 0) {
        temp = __len__str__(v0)->getValue() + v1->getValue();
    } else {
        temp = v1->getValue();
    }
    if (temp >= __len__str__(v0)->getValue()) {
        fatal("can't get item with index out of range!");
    }
    const char c = v0->getValue().at(temp);
    stringstream ss;
    string s;
    ss << c;
    ss >> s;
    return new PyStr(s);
}

PyStr*
__getslice__str__ (PyStr* v0, PyInt* v1, PyInt* v2)
{
    // return NULL;  // REPLACE WITH BODY
    // char* s = v0->getValue().substr(v1->getValue(), v2->getValue());
    // fprintf(stderr, "lala: %s\n", s);
    int temp1 = 0;
    int temp2 = 0;
    int size = __len__str__(v0)->getValue();
    if (v1->getValue() < 0) {
        temp1 = size + v1->getValue();
    } else {
        temp1 = v1->getValue();
    }
    if (v2->getValue() < 0) {
        temp2 = size + v2->getValue();
    } else {
        temp2 = v2->getValue();
    }
    if (temp1 > temp2) {
        return new PyStr("");
    }
    if (temp1 > size) {
        temp1 = size;
    }
    if (temp2 > size) {
        temp2 = size;
    }
    return new PyStr(v0->getValue().substr(temp1, temp2));
}

PyBool*
__gt__str__ (PyStr* v0, PyStr* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyBool(v0->asStr()->getValue().compare(v1->asStr()->getValue()) > 0);
}

PyBool*
__le__str__ (PyStr* v0, PyStr* v1)
{
    return __ge__str__ (v1, v0);
}

PyInt*
__len__str__ (PyStr* v0)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(v0->asStr()->getValue().length());
}

PyStr*
__lmul__str__ (PyStr* v0, PyInt* v1)
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
    return new PyStr(tmp);
}

PyBool*
__lt__str__ (PyStr* v0, PyStr* v1)
{
    return __gt__str__ (v1, v0);
}

PyStr*
__rmul__str__ (PyInt* v0, PyStr* v1)
{
    return __lmul__str__ (v1, v0);
}

PyInt*
__toint__str__ (PyStr* v0)
{
    // v0 is str
    // return int
    // return NULL;  // REPLACE WITH BODY
    std::stringstream sstr(v0->getValue());
    int val;
    sstr >> val;
    // TO BE IMPLEMENTED: Should throw an error if it is not an "int string"
    // e.g. "hello world" should throw a runtime error.
    return new PyInt(val);
}

PyStr*
__tostr__ (PyValue v0)
{
    // v0 can be anytype
    // return NULL;  // REPLACE WITH BODY
    return new PyStr(v0->toStr());
}


/* Dictionaries */

PyBool*
__contains__dict__ (PyValue v0, PyDict* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return v1->contains(v0);
}

PyValue
__getitem__dict__ (PyDict* v0, PyValue v1)
{
    // return NULL;  // REPLACE WITH BODY
    return v0->get(v1);
}

PyInt*
__len__dict__ (PyDict* v0)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(v0->getSize());
}

PyValue
__setitem__dict__ (PyValue v0, PyValue v1, PyValue v2)
{
    return NULL;  // REPLACE WITH BODY
}

PyBool*
__notcontains__dict__ (PyValue v0, PyDict* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return __notcontains__dict__(v0, v1)->notBool();

}


/* Lists */

PyValue
__getitem__list__ (PyList* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    int temp = 0;
    if (v1->getValue() < 0) {
        temp = __len__list__(v0)->getValue() + v1->getValue();
    } else {
        temp = v1->getValue();
    }
    if (temp >= __len__list__(v0)->getValue()) {
        fatal("can't get item with index out of range!");
    }
    return v0->getItem(new PyInt(temp));
}

PyList*
__getslice__list__ (PyList* v0, PyInt* v1, PyInt* v2)
{
    // return NULL;  // REPLACE WITH BODY
    int temp1 = 0;
    int temp2 = 0;
    int size = __len__list__(v0)->getValue();
    if (v1->getValue() < 0) {
        temp1 = size + v1->getValue();
    } else {
        temp1 = v1->getValue();
    }
    if (v2->getValue() < 0) {
        temp2 = size + v2->getValue();
    } else {
        temp2 = v2->getValue();
    }
    if (temp1 > size) {
        temp1 = size;
    }
    if (temp2 > size) {
        temp2 = size;
    }
    if (temp1 > temp2 ) {
        return new PyList();
    }
    PyList* list = new PyList();
    for (int i = temp1; i < temp2; i++) {
        list->asList()->append(__getitem__list__(v0, new PyInt(i)));
    }
    return list;
}

PyInt*
__len__list__ (PyList* v0)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(v0->getSize());
}

PyValue
__setitem__list__ (PyValue v0, PyValue v1, PyValue v2)
{
    return NULL;  // REPLACE WITH BODY
}

extern PyValue __setslice__list__ (PyValue v0, PyValue v1, PyValue v2,
                                   PyValue v3);

/* Ranges */

PyInt*
__len__range__ (PyRange* v0)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyInt(v0->getSize());
}

PyRange*
__xrange__ (PyInt* v0, PyInt* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return new PyRange(v0, v1);
}
 

/* General values */

PyBool*
__is_bool__ (PyValue v0, PyValue v1)
{
    int i;
    if (v0->typeName() == v1->typeName()){
        if (v0->toStr() == v1->toStr())
            i = 1;
        else
            i = 0;
    } else {
        i = 0;
    }
    return toPyBool (i);
}

PyBool*
__isnot_bool__ (PyValue v0, PyValue v1)
{
    int i;
    if (v0->typeName() != v1->typeName()){
        i = 1;
    } else if (v0->toStr() != v1->toStr()){
        i = 1;
    } else {
        i = 0;
    }
    return toPyBool (i);
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
__print__ (int count, ...)
{
 //    if (!atStart) 
	// cout << " ";
    // if (count == 0) {
    //     cout << "";
    // }
    va_list args;
    va_start(args, count);
    // atStart = false;
    for (int i = 0; i < count; i ++) {
        PyValue temp = va_arg(args, PyValue);
        temp->print(cout);   
        if (i < count-1) {
            cout << " ";
        }
    }
    va_end(args);
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

	
    
