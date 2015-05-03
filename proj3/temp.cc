#include "runtime.h"
struct truth_31_local  : public PyObject {
PyBool* truth_31(PyValue x_33)
{
return __truth__(x_33);
}
} truth_31;

struct __not___36_local  : public PyObject {
PyBool* __not__(PyValue x_38)
{
return __not_bool__(x_38);
}
} __not___36;

struct xrange_42_local  : public PyObject {
PyRange* xrange_42(PyInt* low_44, PyInt* high_46)
{
return __xrange__(low_44, high_46);
}
} xrange_42;

struct len_49_local  : public PyObject {
PyInt* len_49(PyRange* r_51)
{
return __len__range__(r_51);
}
} len_49;

struct __add___55_local  : public PyObject {
PyInt* __add__(PyInt* x_57, PyInt* y_59)
{
return __add__int__(x_57, y_59);
}
} __add___55;

struct __sub___63_local  : public PyObject {
PyInt* __sub__(PyInt* x_65, PyInt* y_67)
{
return __sub__int__(x_65, y_67);
}
} __sub___63;

struct __mul___71_local  : public PyObject {
PyInt* __mul__(PyInt* x_73, PyInt* y_75)
{
return __mul__int__(x_73, y_75);
}
} __mul___71;

struct __floordiv___79_local  : public PyObject {
PyInt* __floordiv__(PyInt* x_81, PyInt* y_83)
{
return __floordiv__int__(x_81, y_83);
}
} __floordiv___79;

struct __mod___87_local  : public PyObject {
PyInt* __mod__(PyInt* x_89, PyInt* y_91)
{
return __mod__int__(x_89, y_91);
}
} __mod___87;

struct __pow___95_local  : public PyObject {
PyInt* __pow__(PyInt* x_97, PyInt* y_99)
{
return __pow__int__(x_97, y_99);
}
} __pow___95;

struct __neg___102_local  : public PyObject {
PyInt* __neg__(PyInt* x_104)
{
return __neg__int__(x_104);
}
} __neg___102;

struct __pos___107_local  : public PyObject {
PyInt* __pos__(PyInt* x_109)
{
return __pos__int__(x_109);
}
} __pos___107;

struct __lt___113_local  : public PyObject {
PyBool* __lt__(PyInt* x_115, PyInt* y_117)
{
return __lt__int__(x_115, y_117);
}
} __lt___113;

struct __gt___121_local  : public PyObject {
PyBool* __gt__(PyInt* x_123, PyInt* y_125)
{
return __gt__int__(x_123, y_125);
}
} __gt___121;

struct __le___129_local  : public PyObject {
PyBool* __le__(PyInt* x_131, PyInt* y_133)
{
return __le__int__(x_131, y_133);
}
} __le___129;

struct __ge___137_local  : public PyObject {
PyBool* __ge__(PyInt* x_139, PyInt* y_141)
{
return __ge__int__(x_139, y_141);
}
} __ge___137;

struct __eq___145_local  : public PyObject {
PyBool* __eq__(PyInt* x_147, PyInt* y_149)
{
return __eq__int__(x_147, y_149);
}
} __eq___145;

struct __ne___153_local  : public PyObject {
PyBool* __ne__(PyInt* x_155, PyInt* y_157)
{
return __ne__int__(x_155, y_157);
}
} __ne___153;

struct toint_160_local  : public PyObject {
PyInt* toint_160(PyStr* x_162)
{
return __toint__str__(x_162);
}
} toint_160;

struct __add___166_local  : public PyObject {
PyStr* __add__(PyStr* x_168, PyStr* y_170)
{
return __add__str__(x_168, y_170);
}
} __add___166;

struct __mul___174_local  : public PyObject {
PyStr* __mul__(PyStr* x_176, PyInt* y_178)
{
return __lmul__str__(x_176, y_178);
}
} __mul___174;

struct __mul___182_local  : public PyObject {
PyStr* __mul__(PyInt* x_184, PyStr* y_186)
{
return __rmul__str__(x_184, y_186);
}
} __mul___182;

struct __lt___190_local  : public PyObject {
PyBool* __lt__(PyStr* x_192, PyStr* y_194)
{
return __lt__str__(x_192, y_194);
}
} __lt___190;

struct __gt___198_local  : public PyObject {
PyBool* __gt__(PyStr* x_200, PyStr* y_202)
{
return __gt__str__(x_200, y_202);
}
} __gt___198;

struct __le___206_local  : public PyObject {
PyBool* __le__(PyStr* x_208, PyStr* y_210)
{
return __le__str__(x_208, y_210);
}
} __le___206;

struct __ge___214_local  : public PyObject {
PyBool* __ge__(PyStr* x_216, PyStr* y_218)
{
return __ge__str__(x_216, y_218);
}
} __ge___214;

struct __eq___222_local  : public PyObject {
PyBool* __eq__(PyStr* x_224, PyStr* y_226)
{
return __eq__str__(x_224, y_226);
}
} __eq___222;

struct __ne___230_local  : public PyObject {
PyBool* __ne__(PyStr* x_232, PyStr* y_234)
{
return __ne__str__(x_232, y_234);
}
} __ne___230;

struct __getitem___238_local  : public PyObject {
PyStr* __getitem__(PyStr* S_240, PyInt* k_242)
{
return __getitem__str__(S_240, k_242);
}
} __getitem___238;

struct __getslice___247_local  : public PyObject {
PyStr* __getslice__(PyStr* S_249, PyInt* L_251, PyInt* U_253)
{
return __getslice__str__(S_249, L_251, U_253);
}
} __getslice___247;

struct len_256_local  : public PyObject {
PyInt* len_256(PyStr* S_258)
{
return __len__str__(S_258);
}
} len_256;

struct tostr_261_local  : public PyObject {
PyStr* tostr_261(PyValue x_263)
{
return __tostr__(x_263);
}
} tostr_261;

struct __getitem___267_local  : public PyObject {
PyValue __getitem__(PyList* S_269, PyInt* k_271)
{
return __getitem__list__(S_269, k_271);
}
} __getitem___267;

struct __getslice___277_local  : public PyObject {
PyList* __getslice__(PyList* S_279, PyInt* L_281, PyInt* U_283)
{
return __getslice__list__(S_279, L_281, U_283);
}
} __getslice___277;

struct __setitem___289_local  : public PyObject {
PyValue __setitem__(PyList* S_291, PyInt* k_293, PyValue val_295)
{
return __setitem__list__(S_291, k_293, val_295);
}
} __setitem___289;

struct __setslice___302_local  : public PyObject {
PyList* __setslice__(PyList* S_304, PyInt* a_306, PyInt* b_308, PyList* val_310)
{
return __setslice__list__(S_304, a_306, b_308, val_310);
}
} __setslice___302;

struct len_314_local  : public PyObject {
PyInt* len_314(PyList* S_316)
{
return __len__list__(S_316);
}
} len_314;

struct argv_319_local  : public PyObject {
PyList* argv_319()
{
return __argv__();
}
} argv_319;

struct readline_321_local  : public PyObject {
PyStr* readline_321()
{
return __readline__();
}
} readline_321;

struct read_323_local  : public PyObject {
PyStr* read_323()
{
return __read__();
}
} read_323;

struct __getitem___327_local  : public PyObject {
PyValue __getitem__(PyDictInt* D_329, PyInt* x_331)
{
return __getitem__dict__(D_329, x_331);
}
} __getitem___327;

struct __getitem___336_local  : public PyObject {
PyValue __getitem__(PyDictBool* D_338, PyBool* x_340)
{
return __getitem__dict__(D_338, x_340);
}
} __getitem___336;

struct __getitem___345_local  : public PyObject {
PyValue __getitem__(PyDictStr* D_347, PyStr* x_349)
{
return __getitem__dict__(D_347, x_349);
}
} __getitem___345;

struct __setitem___355_local  : public PyObject {
PyValue __setitem__(PyDictInt* S_357, PyInt* k_359, PyValue val_361)
{
return __setitem__dict__(S_357, k_359, val_361);
}
} __setitem___355;

struct __setitem___367_local  : public PyObject {
PyValue __setitem__(PyDictBool* S_369, PyBool* k_371, PyValue val_373)
{
return __setitem__dict__(S_369, k_371, val_373);
}
} __setitem___367;

struct __setitem___379_local  : public PyObject {
PyValue __setitem__(PyDictStr* S_381, PyStr* k_383, PyValue val_385)
{
return __setitem__dict__(S_381, k_383, val_385);
}
} __setitem___379;

struct len_389_local  : public PyObject {
PyInt* len_389(PyDictInt* D_391)
{
return __len__dict__(D_391);
}
} len_389;

struct len_395_local  : public PyObject {
PyInt* len_395(PyDictBool* D_397)
{
return __len__dict__(D_397);
}
} len_395;

struct len_401_local  : public PyObject {
PyInt* len_401(PyDictStr* D_403)
{
return __len__dict__(D_403);
}
} len_401;

struct __in___408_local  : public PyObject {
PyBool* __in__(PyInt* x_410, PyDictInt* D_412)
{
return __contains__dict__(x_410, D_412);
}
} __in___408;

struct __in___417_local  : public PyObject {
PyBool* __in__(PyBool* x_419, PyDictBool* D_421)
{
return __contains__dict__(x_419, D_421);
}
} __in___417;

struct __in___426_local  : public PyObject {
PyBool* __in__(PyStr* x_428, PyDictStr* D_430)
{
return __contains__dict__(x_428, D_430);
}
} __in___426;

struct __notin___435_local  : public PyObject {
PyBool* __notin__(PyInt* x_437, PyDictInt* D_439)
{
return __notcontains__dict__(x_437, D_439);
}
} __notin___435;

struct __notin___444_local  : public PyObject {
PyBool* __notin__(PyBool* x_446, PyDictBool* D_448)
{
return __notcontains__dict__(x_446, D_448);
}
} __notin___444;

struct __notin___453_local  : public PyObject {
PyBool* __notin__(PyStr* x_455, PyDictStr* D_457)
{
return __notcontains__dict__(x_455, D_457);
}
} __notin___453;

struct __is___462_local  : public PyObject {
PyBool* __is__(PyValue x_464, PyValue y_466)
{
return __is_bool__(x_464, y_466);
}
} __is___462;

struct __isnot___470_local  : public PyObject {
PyBool* __isnot__(PyValue x_472, PyValue y_474)
{
return __isnot_bool__(x_472, y_474);
}
} __isnot___470;

struct f_477_local  : public PyObject {
PyInt* f_477(PyInt* n_479)
{
static PyInt* i_481 = __cons_int__ (0);
static PyInt* t_483 = __cons_int__ (3);
while (__eval_bool__((__lt___113.__lt__(i_481, n_479)))) {
if (__eval_bool__(((PyBool*) __and__(__le___129.__le__(__mod___87.__mod__(i_481, __cons_int__ (7)), __cons_int__ (2)),(__lt___113.__lt__(__cons_int__ (1), __mod___87.__mod__(i_481, __cons_int__ (7)))))))) {
__print__(1, i_481);
}
i_481 = __add___55.__add__(i_481, __cons_int__ (1));
}
PyInt* s_485 = __add___55.__add__(i_481, __cons_int__ (2));
t_483 = __add___55.__add__(t_483, __pow___95.__pow__(s_485, __cons_int__ (2)));
__print__(4, __cons_str__ ("s ="), s_485, __cons_str__ ("t ="), t_483);
__newline__();
i_481 = __add___55.__add__(i_481, __cons_int__ (1));
return i_481;
}
} f_477;

void
__main__()
{
__print__(1, f_477.f_477(__cons_int__ (5)));
__newline__();

}
