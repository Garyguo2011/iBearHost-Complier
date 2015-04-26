#include "runtime.h"
PyInt* f(PyInt* a, PyStr* b, PyValue c)
{
__print__(__cons_str__ ("lala"));
return a ;
}
void
__main__()
{
__print__(f(__cons_int__ (1), __cons_str__ ("a"), __cons_int__ (3))
);

}
