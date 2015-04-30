#include "runtime.h"
struct xrange25_local {
PyRange* xrange_25(PyInt* low_27, PyInt* high_29)
{
return __xrange__(low_27, high_29);
}
} xrange_25;

struct len32_local {
PyInt* len_32(PyRange* r_34)
{
return __len__range__(r_34);
}
} len_32;

struct __add__38_local {
PyInt* __add__(PyInt* x_40, PyInt* y_42)
{
return __add__int__(x_40, y_42);
}
} __add___38;

struct __sub__46_local {
PyInt* __sub__(PyInt* x_48, PyInt* y_50)
{
return __sub__int__(x_48, y_50);
}
} __sub___46;

struct __mul__54_local {
PyInt* __mul__(PyInt* x_56, PyInt* y_58)
{
return __mul__int__(x_56, y_58);
}
} __mul___54;

struct __floordiv__62_local {
PyInt* __floordiv__(PyInt* x_64, PyInt* y_66)
{
return __floordiv__int__(x_64, y_66);
}
} __floordiv___62;

struct __mod__70_local {
PyInt* __mod__(PyInt* x_72, PyInt* y_74)
{
return __mod__int__(x_72, y_74);
}
} __mod___70;

struct __pow__78_local {
PyInt* __pow__(PyInt* x_80, PyInt* y_82)
{
return __pow__int__(x_80, y_82);
}
} __pow___78;

struct __neg__85_local {
PyInt* __neg__(PyInt* x_87)
{
return __neg__int__(x_87);
}
} __neg___85;

struct __pos__90_local {
PyInt* __pos__(PyInt* x_92)
{
return __pos__int__(x_92);
}
} __pos___90;

struct __lt__96_local {
PyBool* __lt__(PyInt* x_98, PyInt* y_100)
{
return __lt__int__(x_98, y_100);
}
} __lt___96;

struct __gt__104_local {
PyBool* __gt__(PyInt* x_106, PyInt* y_108)
{
return __gt__int__(x_106, y_108);
}
} __gt___104;

struct __le__112_local {
PyBool* __le__(PyInt* x_114, PyInt* y_116)
{
return __le__int__(x_114, y_116);
}
} __le___112;

struct __ge__120_local {
PyBool* __ge__(PyInt* x_122, PyInt* y_124)
{
return __ge__int__(x_122, y_124);
}
} __ge___120;

struct __eq__128_local {
PyBool* __eq__(PyInt* x_130, PyInt* y_132)
{
return __eq__int__(x_130, y_132);
}
} __eq___128;

struct __ne__136_local {
PyBool* __ne__(PyInt* x_138, PyInt* y_140)
{
return __ne__int__(x_138, y_140);
}
} __ne___136;

struct toint143_local {
PyInt* toint_143(PyStr* x_145)
{
return __toint__str__(x_145);
}
} toint_143;

struct __add__149_local {
PyStr* __add__(PyStr* x_151, PyStr* y_153)
{
return __add__str__(x_151, y_153);
}
} __add___149;

struct __mul__157_local {
PyStr* __mul__(PyStr* x_159, PyInt* y_161)
{
return __lmul__str__(x_159, y_161);
}
} __mul___157;

struct __mul__165_local {
PyStr* __mul__(PyInt* x_167, PyStr* y_169)
{
return __rmul__str__(x_167, y_169);
}
} __mul___165;

struct __lt__173_local {
PyBool* __lt__(PyStr* x_175, PyStr* y_177)
{
return __lt__str__(x_175, y_177);
}
} __lt___173;

struct __gt__181_local {
PyBool* __gt__(PyStr* x_183, PyStr* y_185)
{
return __gt__str__(x_183, y_185);
}
} __gt___181;

struct __le__189_local {
PyBool* __le__(PyStr* x_191, PyStr* y_193)
{
return __le__str__(x_191, y_193);
}
} __le___189;

struct __ge__197_local {
PyBool* __ge__(PyStr* x_199, PyStr* y_201)
{
return __ge__str__(x_199, y_201);
}
} __ge___197;

struct __eq__205_local {
PyBool* __eq__(PyStr* x_207, PyStr* y_209)
{
return __eq__str__(x_207, y_209);
}
} __eq___205;

struct __ne__213_local {
PyBool* __ne__(PyStr* x_215, PyStr* y_217)
{
return __ne__str__(x_215, y_217);
}
} __ne___213;

struct __getitem__221_local {
PyStr* __getitem__(PyStr* S_223, PyInt* k_225)
{
return __getitem__str__(S_223, k_225);
}
} __getitem___221;

struct __getslice__230_local {
PyStr* __getslice__(PyStr* S_232, PyInt* L_234, PyInt* U_236)
{
return __getslice__str__(S_232, L_234, U_236);
}
} __getslice___230;

struct len239_local {
PyInt* len_239(PyStr* S_241)
{
return __len__str__(S_241);
}
} len_239;

struct tostr244_local {
PyStr* tostr_244(PyValue x_246)
{
return __tostr__(x_246);
}
} tostr_244;

struct __getitem__250_local {
PyValue __getitem__(PyList* S_252, PyInt* k_254)
{
return __getitem__list__(S_252, k_254);
}
} __getitem___250;

struct __getslice__260_local {
PyList* __getslice__(PyList* S_262, PyInt* L_264, PyInt* U_266)
{
return __getslice__list__(S_262, L_264, U_266);
}
} __getslice___260;

struct len270_local {
PyInt* len_270(PyList* S_272)
{
return __len__list__(S_272);
}
} len_270;

struct __getitem__277_local {
PyValue __getitem__(PyDictInt* D_279, PyInt* x_281)
{
return __getitem__dict__(D_279, x_281);
}
} __getitem___277;

struct __getitem__286_local {
PyValue __getitem__(PyDictBool* D_288, PyBool* x_290)
{
return __getitem__dict__(D_288, x_290);
}
} __getitem___286;

struct __getitem__295_local {
PyValue __getitem__(PyDictStr* D_297, PyStr* x_299)
{
return __getitem__dict__(D_297, x_299);
}
} __getitem___295;

struct len303_local {
PyInt* len_303(PyDictInt* D_305)
{
return __len__dict__(D_305);
}
} len_303;

struct len309_local {
PyInt* len_309(PyDictBool* D_311)
{
return __len__dict__(D_311);
}
} len_309;

struct len315_local {
PyInt* len_315(PyDictStr* D_317)
{
return __len__dict__(D_317);
}
} len_315;

struct __in__322_local {
PyBool* __in__(PyInt* x_324, PyDictInt* D_326)
{
return __contains__dict__(x_324, D_326);
}
} __in___322;

struct __in__331_local {
PyBool* __in__(PyBool* x_333, PyDictBool* D_335)
{
return __contains__dict__(x_333, D_335);
}
} __in___331;

struct __in__340_local {
PyBool* __in__(PyStr* x_342, PyDictStr* D_344)
{
return __contains__dict__(x_342, D_344);
}
} __in___340;

struct __notin__349_local {
PyBool* __notin__(PyInt* x_351, PyDictInt* D_353)
{
return __notcontains__dict__(x_351, D_353);
}
} __notin___349;

struct __notin__358_local {
PyBool* __notin__(PyBool* x_360, PyDictBool* D_362)
{
return __notcontains__dict__(x_360, D_362);
}
} __notin___358;

struct __notin__367_local {
PyBool* __notin__(PyStr* x_369, PyDictStr* D_371)
{
return __notcontains__dict__(x_369, D_371);
}
} __notin___367;

struct f377_local {
PyInt* f_377()
{
PyInt* a_379 = __cons_int__ (4);
a_379 = __cons_int__ (5);
return a_379;
}
} f_377;

void
__main__()
{
PyInt* b_374 = __cons_int__ (4);
__print__(1, f_377.f_377());
__newline__();

}
