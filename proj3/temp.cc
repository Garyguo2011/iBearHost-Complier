#include "runtime.h"
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
PyInt* f(PyInt* a, PyStr* b, PyValue c)
{
__print__(__cons_str__ ("lala"));
return a ;
}
void
__main__()
{
__print__(__gt__ (__cons_int__ (2), __cons_int__ (10)));
__print__(__ne__ (__cons_int__ (1), __cons_int__ (3)));

}
