#include "runtime.h"
class Hello_419 : public PyObject {
protected:
Hello_419(PyValue a_426)
{
__print__(1, __cons_str__ ("success!"));
__newline__();
}
};
struct truth32_local {
PyBool* truth_32(PyValue x_34)
{
return __truth__(x_34);
}
} truth_32;

struct __not__37_local {
PyBool* __not__(PyValue x_39)
{
return __not_bool__(x_39);
}
} __not___37;

struct xrange43_local {
PyRange* xrange_43(PyInt* low_45, PyInt* high_47)
{
return __xrange__(low_45, high_47);
}
} xrange_43;

struct len50_local {
PyInt* len_50(PyRange* r_52)
{
return __len__range__(r_52);
}
} len_50;

struct __add__56_local {
PyInt* __add__(PyInt* x_58, PyInt* y_60)
{
return __add__int__(x_58, y_60);
}
} __add___56;

struct __sub__64_local {
PyInt* __sub__(PyInt* x_66, PyInt* y_68)
{
return __sub__int__(x_66, y_68);
}
} __sub___64;

struct __mul__72_local {
PyInt* __mul__(PyInt* x_74, PyInt* y_76)
{
return __mul__int__(x_74, y_76);
}
} __mul___72;

struct __floordiv__80_local {
PyInt* __floordiv__(PyInt* x_82, PyInt* y_84)
{
return __floordiv__int__(x_82, y_84);
}
} __floordiv___80;

struct __mod__88_local {
PyInt* __mod__(PyInt* x_90, PyInt* y_92)
{
return __mod__int__(x_90, y_92);
}
} __mod___88;

struct __pow__96_local {
PyInt* __pow__(PyInt* x_98, PyInt* y_100)
{
return __pow__int__(x_98, y_100);
}
} __pow___96;

struct __neg__103_local {
PyInt* __neg__(PyInt* x_105)
{
return __neg__int__(x_105);
}
} __neg___103;

struct __pos__108_local {
PyInt* __pos__(PyInt* x_110)
{
return __pos__int__(x_110);
}
} __pos___108;

struct __lt__114_local {
PyBool* __lt__(PyInt* x_116, PyInt* y_118)
{
return __lt__int__(x_116, y_118);
}
} __lt___114;

struct __gt__122_local {
PyBool* __gt__(PyInt* x_124, PyInt* y_126)
{
return __gt__int__(x_124, y_126);
}
} __gt___122;

struct __le__130_local {
PyBool* __le__(PyInt* x_132, PyInt* y_134)
{
return __le__int__(x_132, y_134);
}
} __le___130;

struct __ge__138_local {
PyBool* __ge__(PyInt* x_140, PyInt* y_142)
{
return __ge__int__(x_140, y_142);
}
} __ge___138;

struct __eq__146_local {
PyBool* __eq__(PyInt* x_148, PyInt* y_150)
{
return __eq__int__(x_148, y_150);
}
} __eq___146;

struct __ne__154_local {
PyBool* __ne__(PyInt* x_156, PyInt* y_158)
{
return __ne__int__(x_156, y_158);
}
} __ne___154;

struct toint161_local {
PyInt* toint_161(PyStr* x_163)
{
return __toint__str__(x_163);
}
} toint_161;

struct __add__167_local {
PyStr* __add__(PyStr* x_169, PyStr* y_171)
{
return __add__str__(x_169, y_171);
}
} __add___167;

struct __mul__175_local {
PyStr* __mul__(PyStr* x_177, PyInt* y_179)
{
return __lmul__str__(x_177, y_179);
}
} __mul___175;

struct __mul__183_local {
PyStr* __mul__(PyInt* x_185, PyStr* y_187)
{
return __rmul__str__(x_185, y_187);
}
} __mul___183;

struct __lt__191_local {
PyBool* __lt__(PyStr* x_193, PyStr* y_195)
{
return __lt__str__(x_193, y_195);
}
} __lt___191;

struct __gt__199_local {
PyBool* __gt__(PyStr* x_201, PyStr* y_203)
{
return __gt__str__(x_201, y_203);
}
} __gt___199;

struct __le__207_local {
PyBool* __le__(PyStr* x_209, PyStr* y_211)
{
return __le__str__(x_209, y_211);
}
} __le___207;

struct __ge__215_local {
PyBool* __ge__(PyStr* x_217, PyStr* y_219)
{
return __ge__str__(x_217, y_219);
}
} __ge___215;

struct __eq__223_local {
PyBool* __eq__(PyStr* x_225, PyStr* y_227)
{
return __eq__str__(x_225, y_227);
}
} __eq___223;

struct __ne__231_local {
PyBool* __ne__(PyStr* x_233, PyStr* y_235)
{
return __ne__str__(x_233, y_235);
}
} __ne___231;

struct __getitem__239_local {
PyStr* __getitem__(PyStr* S_241, PyInt* k_243)
{
return __getitem__str__(S_241, k_243);
}
} __getitem___239;

struct __getslice__248_local {
PyStr* __getslice__(PyStr* S_250, PyInt* L_252, PyInt* U_254)
{
return __getslice__str__(S_250, L_252, U_254);
}
} __getslice___248;

struct len257_local {
PyInt* len_257(PyStr* S_259)
{
return __len__str__(S_259);
}
} len_257;

struct tostr262_local {
PyStr* tostr_262(PyValue x_264)
{
return __tostr__(x_264);
}
} tostr_262;

struct __getitem__268_local {
PyValue __getitem__(PyList* S_270, PyInt* k_272)
{
return __getitem__list__(S_270, k_272);
}
} __getitem___268;

struct __getslice__278_local {
PyList* __getslice__(PyList* S_280, PyInt* L_282, PyInt* U_284)
{
return __getslice__list__(S_280, L_282, U_284);
}
} __getslice___278;

struct __setitem__290_local {
PyValue __setitem__(PyList* S_292, PyInt* k_294, PyValue val_296)
{
return __setitem__list__(S_292, k_294, val_296);
}
} __setitem___290;

struct len300_local {
PyInt* len_300(PyList* S_302)
{
return __len__list__(S_302);
}
} len_300;

struct __getitem__307_local {
PyValue __getitem__(PyDictInt* D_309, PyInt* x_311)
{
return __getitem__dict__(D_309, x_311);
}
} __getitem___307;

struct __getitem__316_local {
PyValue __getitem__(PyDictBool* D_318, PyBool* x_320)
{
return __getitem__dict__(D_318, x_320);
}
} __getitem___316;

struct __getitem__325_local {
PyValue __getitem__(PyDictStr* D_327, PyStr* x_329)
{
return __getitem__dict__(D_327, x_329);
}
} __getitem___325;

struct len333_local {
PyInt* len_333(PyDictInt* D_335)
{
return __len__dict__(D_335);
}
} len_333;

struct len339_local {
PyInt* len_339(PyDictBool* D_341)
{
return __len__dict__(D_341);
}
} len_339;

struct len345_local {
PyInt* len_345(PyDictStr* D_347)
{
return __len__dict__(D_347);
}
} len_345;

struct __in__352_local {
PyBool* __in__(PyInt* x_354, PyDictInt* D_356)
{
return __contains__dict__(x_354, D_356);
}
} __in___352;

struct __in__361_local {
PyBool* __in__(PyBool* x_363, PyDictBool* D_365)
{
return __contains__dict__(x_363, D_365);
}
} __in___361;

struct __in__370_local {
PyBool* __in__(PyStr* x_372, PyDictStr* D_374)
{
return __contains__dict__(x_372, D_374);
}
} __in___370;

struct __notin__379_local {
PyBool* __notin__(PyInt* x_381, PyDictInt* D_383)
{
return __notcontains__dict__(x_381, D_383);
}
} __notin___379;

struct __notin__388_local {
PyBool* __notin__(PyBool* x_390, PyDictBool* D_392)
{
return __notcontains__dict__(x_390, D_392);
}
} __notin___388;

struct __notin__397_local {
PyBool* __notin__(PyStr* x_399, PyDictStr* D_401)
{
return __notcontains__dict__(x_399, D_401);
}
} __notin___397;

struct __is__406_local {
PyBool* __is__(PyValue x_408, PyValue y_410)
{
return __is_bool__(x_408, y_410);
}
} __is___406;

struct __isnot__414_local {
PyBool* __isnot__(PyValue x_416, PyValue y_418)
{
return __isnot_bool__(x_416, y_418);
}
} __isnot___414;

PyInt* i_428;
PyValue b_431;
void
__main__()
{
i_428 = __cons_int__ (4);
b_431 = new Hello_419(i_428);

}
