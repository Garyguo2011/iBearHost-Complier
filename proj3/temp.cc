#include "runtime.h"
PyRange* xrange(PyInt* low, PyInt* high)
{
return __xrange__(low , high );
}
PyInt* len(PyRange* r)
{
return __len__range__(r );
}
PyInt* __add__(PyInt* x, PyInt* y)
{
return __add__int__(x , y );
}
PyInt* __sub__(PyInt* x, PyInt* y)
{
return __sub__int__(x , y );
}
PyInt* __mul__(PyInt* x, PyInt* y)
{
return __mul__int__(x , y );
}
PyInt* __floordiv__(PyInt* x, PyInt* y)
{
return __floordiv__int__(x , y );
}
PyInt* __mod__(PyInt* x, PyInt* y)
{
return __mod__int__(x , y );
}
PyInt* __pow__(PyInt* x, PyInt* y)
{
return __pow__int__(x , y );
}
PyInt* __neg__(PyInt* x)
{
return __neg__int__(x );
}
PyInt* __pos__(PyInt* x)
{
return __pos__int__(x );
}
PyBool* __lt__(PyInt* x, PyInt* y)
{
return __lt__int__(x , y );
}
PyBool* __gt__(PyInt* x, PyInt* y)
{
return __gt__int__(x , y );
}
PyBool* __le__(PyInt* x, PyInt* y)
{
return __le__int__(x , y );
}
PyBool* __ge__(PyInt* x, PyInt* y)
{
return __ge__int__(x , y );
}
PyBool* __eq__(PyInt* x, PyInt* y)
{
return __eq__int__(x , y );
}
PyBool* __ne__(PyInt* x, PyInt* y)
{
return __ne__int__(x , y );
}
PyInt* toint(PyStr* x)
{
return __toint__str__(x );
}
PyStr* __add__(PyStr* x, PyStr* y)
{
return __add__str__(x , y );
}
PyStr* __mul__(PyStr* x, PyInt* y)
{
return __lmul__str__(x , y );
}
PyStr* __mul__(PyInt* x, PyStr* y)
{
return __rmul__str__(x , y );
}
PyBool* __lt__(PyStr* x, PyStr* y)
{
return __lt__str__(x , y );
}
PyBool* __gt__(PyStr* x, PyStr* y)
{
return __gt__str__(x , y );
}
PyBool* __le__(PyStr* x, PyStr* y)
{
return __le__str__(x , y );
}
PyBool* __ge__(PyStr* x, PyStr* y)
{
return __ge__str__(x , y );
}
PyBool* __eq__(PyStr* x, PyStr* y)
{
return __eq__str__(x , y );
}
PyBool* __ne__(PyStr* x, PyStr* y)
{
return __ne__str__(x , y );
}
PyStr* __getitem__(PyStr* S, PyInt* k)
{
return __getitem__str__(S , k );
}
PyStr* __getslice__(PyStr* S, PyInt* L, PyInt* U)
{
return __getslice__str__(S , L , U );
}
PyInt* len(PyStr* S)
{
return __len__str__(S );
}
PyStr* tostr(PyValue x)
{
return __tostr__(x );
}
PyValue __getitem__(PyList* S, PyInt* k)
{
return __getitem__list__(S , k );
}
PyList* __getslice__(PyList* S, PyInt* L, PyInt* U)
{
return __getslice__list__(S , L , U );
}
PyInt* len(PyList* S)
{
return __len__list__(S );
}
void
__main__()
{
__print__(__cons_str__ ("lala\012"));

}
