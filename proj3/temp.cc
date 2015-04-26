#include "runtime.h"
PyInt* __add__(PyInt* x, PyInt* y)
{
return __add__int__(x , y );
}
PyInt* f(PyInt* a, PyStr* b, PyValue c)
{
__print__(__cons_str__ ("lala"));
return a ;
}
void
__main__()
{
__print__(__add__ (__cons_int__ (3), __cons_int__ (8)));

}
