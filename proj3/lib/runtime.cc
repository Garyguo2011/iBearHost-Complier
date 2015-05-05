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

int
PyObject::getSize()
{
    return 1;
}

const char*
PyObject::typeName ()
{
    return "?";
}

string
PyObject::strFormat(PyValue val)
{
    std::string temp = val->typeName();
    string result = "";
    if (temp.compare("str") == 0) {
        result += "\'";
    }
    return result;
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

PyStr*
PyStr::get(int index)
{
    return new PyStr(getValue().substr(index, 1));
}

int
PyStr::getSize()
{
    return getValue().size();
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
    _first = from;
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
    str += "xrange(";
    str += first()->toStr();
    str += ", ";
    if (getSize() == 0) {
        str += first()->toStr();
    } else {
        stringstream ss;
        ss << items[getSize()-1]->getValue()+1;
        str +=  ss.str();
    }
    str += ")";
    return str;
}

int
PyRange::getSize()
{
    return (int) items.size();
}

PyInt*
PyRange::get(int index)
{
    return items[index];
}

PyInt*
PyRange::first()
{
    return _first;
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
        str += PyObject::strFormat(items[i]);
        str += items[i]->toStr();
        str += PyObject::strFormat(items[i]);
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

PyValue
PyList::setItem(PyInt* position, PyValue val)
{
    int i = position->getValue();
    if (i < 0) {
        i = getSize() + i;
    }
    items[i] = val;
    return PyNone;
}

vector<PyValue>
PyList::getList()
{
    return items;
}

PyValue
PyList::setSlice(PyInt* a, PyInt* b, PyList* val)
{
    std::vector<PyValue>::iterator first;
    std::vector<PyValue>::iterator last;
    std::vector<PyValue> valList = val->getList();

    if (a->getValue() < items.size()) {
        // remove all element between index a and b
        first = items.begin() + a->getValue();
        if (b->getValue() <= items.size()) {
            last = items.begin() + b->getValue();
        } else {
            last = items.end();
        }
        items.erase (first, last);
        items.insert(first, valList.begin(), valList.end());
    } else {
        // directly push to the end of list
        for (std::vector<PyValue>::iterator it=valList.begin(); it!=valList.end(); ++it) {
            items.push_back(*it);    
        }
    }
}

PyValue
PyList::get(int index)
{
    return items[index];
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
    for (map<PyValue, PyValue>::reverse_iterator it=items.rbegin(); 
        it!=items.rend(); ++it) {
        str += PyObject::strFormat(it->first);
        str += it->first->toStr();
        str += PyObject::strFormat(it->first);
        str += ": ";
        str += PyObject::strFormat(it->second);
        str += it->second->toStr();
        str += PyObject::strFormat(it->second);
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

PyValue
PyDictInt::setItem(PyInt* key, PyValue val)
{
    for (std::map<PyValue, PyValue>::iterator it=items.begin(); it!=items.end(); ++it) {
        if (it->first->toStr().compare(key->toStr()) == 0) {
            items[it->first] = val;
            return val;
        }
    }
    items[(PyValue)key] = val;
    return val;
}

/* PyDictStr */

const char*
PyDictStr::typeName ()
{
    return "dictStr";
}

PyValue
PyDictStr::setItem(PyStr* key, PyValue val)
{
    for (std::map<PyValue, PyValue>::iterator it=items.begin(); it!=items.end(); ++it) {
        if (it->first->toStr().compare(key->toStr()) == 0) {
            items[it->first] = val;
            return val;
        }
    }
    items[(PyValue)key] = val;
    return val;
}

/* PyDictBool */

const char*
PyDictBool::typeName ()
{
    return "dictBool";
}

PyValue
PyDictBool::setItem(PyBool* key, PyValue val)
{
    for (std::map<PyValue, PyValue>::iterator it=items.begin(); it!=items.end(); ++it) {
        if (it->first->toStr().compare(key->toStr()) == 0) {
            items[it->first] = val;
            return val;
        }
    }
    items[(PyValue)key] = val;
    return val;
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
    str += PyObject::strFormat(_vals[0]);
    str += _vals[0]->toStr();
    str += PyObject::strFormat(_vals[0]);
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
    str += PyObject::strFormat(_vals[0]);
    str += _vals[0]->toStr();
    str += PyObject::strFormat(_vals[0]);
    str += ", ";
    str += PyObject::strFormat(_vals[1]);
    str += _vals[1]->toStr();
    str += PyObject::strFormat(_vals[1]);
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
    str += PyObject::strFormat(_vals[0]);
    str += _vals[0]->toStr();
    str += PyObject::strFormat(_vals[0]);
    str += ", ";
    str += PyObject::strFormat(_vals[1]);
    str += _vals[1]->toStr();
    str += PyObject::strFormat(_vals[1]);
    str += ", ";
    str += PyObject::strFormat(_vals[2]);
    str += _vals[2]->toStr();
    str += PyObject::strFormat(_vals[2]);
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
    return new PyStr(v0->getValue().substr(temp1, temp2-temp1));
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
__setitem__dict__ (PyDictInt* v0, PyInt* v1, PyValue v2)
{
    // return NULL;  // REPLACE WITH BODY
    v0->setItem(v1, v2);
    return v2;
}

PyValue
__setitem__dict__ (PyDictBool* v0, PyBool* v1, PyValue v2)
{
    v0->setItem(v1, v2);
    return v2;
}

PyValue
__setitem__dict__ (PyDictStr* v0, PyStr* v1, PyValue v2)
{
    v0->setItem(v1, v2);
    return v2;
}

PyBool*
__notcontains__dict__ (PyValue v0, PyDict* v1)
{
    // return NULL;  // REPLACE WITH BODY
    return v1->contains(v0)->notBool();

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
__setitem__list__ (PyList* v0, PyInt* v1, PyValue v2)
{
    // return NULL;  // REPLACE WITH BODY
    v0->asList()->setItem(v1, v2);
    return v2;
}


PyList*
__setslice__list__ (PyList* v0, PyInt* v1, PyInt* v2, PyList* v3)
{
    v0->setSlice(v1, v2, v3);
    return v3; 
}

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

PyBool*
__not_bool__ (PyValue v0)
{
    int i;
    if (v0->typeName() == "bool"){
        if (v0->toStr() == "True"){
            i = 0;
        } else {
            i = 1;
        }
    } else if (v0->typeName() == "int") {
        if (v0->asInt()->getValue() != 0){
            i = 0;
        } else {
            i = 1;
        }
    } else {
        if (v0->getSize() == 0){
            i = 1;
        } else {
            i = 0;    
        }
        
    }
    return toPyBool(i);
}

PyBool*
__truth__ (PyValue v0)
{
    int i;
    if (v0->typeName() == "bool"){
        if (v0->toStr() == "True"){
            i = 1;
        } else {
            i = 0;
        }
    } else if (v0->typeName() == "int") {
        if (v0->asInt()->getValue() != 0){
            i = 1;
        } else {
            i = 0;
        }
    } else {
        if (v0->getSize() == 0){
            i = 0;
        } else {
            i = 1;    
        }
        
    }
    return toPyBool(i);
}


/* Communication with environment. */

static PyList* commandLine;

PyList*
__argv__ ()
{
    // return NULL;  // REPLACE WITH BODY
    return commandLine;
}

PyStr*
__read__ ()
{
    // return NULL;  // REPLACE WITH BODY
    string input_line;
    while (cin) {
        getline(cin, input_line);
    }
    return new PyStr(input_line);
}

PyStr*
__readline__ ()
{
    // return NULL;  // REPLACE WITH BODY
    string s;
    cin >> s;
    s += "\\n";
    return new PyStr(s);
}


/***** Other support *****/

static bool atStart;

void __printspace__()
{
    if (!atStart) {
        cout << " ";
    }
}
void
__print__ (int count, ...)
{
    // if (!atStart) 
	   // cout << " ";
    // if (count == 0) {
    //     cout << "";
    // }
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i ++) {
        PyValue temp = va_arg(args, PyValue);
        __printspace__();
        temp->print(cout);
        atStart = false;
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

	
    
