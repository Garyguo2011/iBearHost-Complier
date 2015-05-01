#include "runtime.h"
struct truth30_local {
PyBool* truth_30(PyValue x_32)
{
return __truth__(x_32);
}
} truth_30;

struct __not__35_local {
PyBool* __not__(PyValue x_37)
{
return __not_bool__(x_37);
}
} __not___35;

struct xrange41_local {
PyRange* xrange_41(PyInt* low_43, PyInt* high_45)
{
return __xrange__(low_43, high_45);
}
} xrange_41;

struct len48_local {
PyInt* len_48(PyRange* r_50)
{
return __len__range__(r_50);
}
} len_48;

struct __add__54_local {
PyInt* __add__(PyInt* x_56, PyInt* y_58)
{
return __add__int__(x_56, y_58);
}
} __add___54;

struct __sub__62_local {
PyInt* __sub__(PyInt* x_64, PyInt* y_66)
{
return __sub__int__(x_64, y_66);
}
} __sub___62;

struct __mul__70_local {
PyInt* __mul__(PyInt* x_72, PyInt* y_74)
{
return __mul__int__(x_72, y_74);
}
} __mul___70;

struct __floordiv__78_local {
PyInt* __floordiv__(PyInt* x_80, PyInt* y_82)
{
return __floordiv__int__(x_80, y_82);
}
} __floordiv___78;

struct __mod__86_local {
PyInt* __mod__(PyInt* x_88, PyInt* y_90)
{
return __mod__int__(x_88, y_90);
}
} __mod___86;

struct __pow__94_local {
PyInt* __pow__(PyInt* x_96, PyInt* y_98)
{
return __pow__int__(x_96, y_98);
}
} __pow___94;

struct __neg__101_local {
PyInt* __neg__(PyInt* x_103)
{
return __neg__int__(x_103);
}
} __neg___101;

struct __pos__106_local {
PyInt* __pos__(PyInt* x_108)
{
return __pos__int__(x_108);
}
} __pos___106;

struct __lt__112_local {
PyBool* __lt__(PyInt* x_114, PyInt* y_116)
{
return __lt__int__(x_114, y_116);
}
} __lt___112;

struct __gt__120_local {
PyBool* __gt__(PyInt* x_122, PyInt* y_124)
{
return __gt__int__(x_122, y_124);
}
} __gt___120;

struct __le__128_local {
PyBool* __le__(PyInt* x_130, PyInt* y_132)
{
return __le__int__(x_130, y_132);
}
} __le___128;

struct __ge__136_local {
PyBool* __ge__(PyInt* x_138, PyInt* y_140)
{
return __ge__int__(x_138, y_140);
}
} __ge___136;

struct __eq__144_local {
PyBool* __eq__(PyInt* x_146, PyInt* y_148)
{
return __eq__int__(x_146, y_148);
}
} __eq___144;

struct __ne__152_local {
PyBool* __ne__(PyInt* x_154, PyInt* y_156)
{
return __ne__int__(x_154, y_156);
}
} __ne___152;

struct toint159_local {
PyInt* toint_159(PyStr* x_161)
{
return __toint__str__(x_161);
}
} toint_159;

struct __add__165_local {
PyStr* __add__(PyStr* x_167, PyStr* y_169)
{
return __add__str__(x_167, y_169);
}
} __add___165;

struct __mul__173_local {
PyStr* __mul__(PyStr* x_175, PyInt* y_177)
{
return __lmul__str__(x_175, y_177);
}
} __mul___173;

struct __mul__181_local {
PyStr* __mul__(PyInt* x_183, PyStr* y_185)
{
return __rmul__str__(x_183, y_185);
}
} __mul___181;

struct __lt__189_local {
PyBool* __lt__(PyStr* x_191, PyStr* y_193)
{
return __lt__str__(x_191, y_193);
}
} __lt___189;

struct __gt__197_local {
PyBool* __gt__(PyStr* x_199, PyStr* y_201)
{
return __gt__str__(x_199, y_201);
}
} __gt___197;

struct __le__205_local {
PyBool* __le__(PyStr* x_207, PyStr* y_209)
{
return __le__str__(x_207, y_209);
}
} __le___205;

struct __ge__213_local {
PyBool* __ge__(PyStr* x_215, PyStr* y_217)
{
return __ge__str__(x_215, y_217);
}
} __ge___213;

struct __eq__221_local {
PyBool* __eq__(PyStr* x_223, PyStr* y_225)
{
return __eq__str__(x_223, y_225);
}
} __eq___221;

struct __ne__229_local {
PyBool* __ne__(PyStr* x_231, PyStr* y_233)
{
return __ne__str__(x_231, y_233);
}
} __ne___229;

struct __getitem__237_local {
PyStr* __getitem__(PyStr* S_239, PyInt* k_241)
{
return __getitem__str__(S_239, k_241);
}
} __getitem___237;

struct __getslice__246_local {
PyStr* __getslice__(PyStr* S_248, PyInt* L_250, PyInt* U_252)
{
return __getslice__str__(S_248, L_250, U_252);
}
} __getslice___246;

struct len255_local {
PyInt* len_255(PyStr* S_257)
{
return __len__str__(S_257);
}
} len_255;

struct tostr260_local {
PyStr* tostr_260(PyValue x_262)
{
return __tostr__(x_262);
}
} tostr_260;

struct __getitem__266_local {
PyValue __getitem__(PyList* S_268, PyInt* k_270)
{
return __getitem__list__(S_268, k_270);
}
} __getitem___266;

struct __getslice__276_local {
PyList* __getslice__(PyList* S_278, PyInt* L_280, PyInt* U_282)
{
return __getslice__list__(S_278, L_280, U_282);
}
} __getslice___276;

struct __setitem__288_local {
PyValue __setitem__(PyList* S_290, PyInt* k_292, PyValue val_294)
{
return __setitem__list__(S_290, k_292, val_294);
}
} __setitem___288;

struct len298_local {
PyInt* len_298(PyList* S_300)
{
return __len__list__(S_300);
}
} len_298;

struct __getitem__305_local {
PyValue __getitem__(PyDictInt* D_307, PyInt* x_309)
{
return __getitem__dict__(D_307, x_309);
}
} __getitem___305;

struct __getitem__314_local {
PyValue __getitem__(PyDictBool* D_316, PyBool* x_318)
{
return __getitem__dict__(D_316, x_318);
}
} __getitem___314;

struct __getitem__323_local {
PyValue __getitem__(PyDictStr* D_325, PyStr* x_327)
{
return __getitem__dict__(D_325, x_327);
}
} __getitem___323;

struct len331_local {
PyInt* len_331(PyDictInt* D_333)
{
return __len__dict__(D_333);
}
} len_331;

struct len337_local {
PyInt* len_337(PyDictBool* D_339)
{
return __len__dict__(D_339);
}
} len_337;

struct len343_local {
PyInt* len_343(PyDictStr* D_345)
{
return __len__dict__(D_345);
}
} len_343;

struct __in__350_local {
PyBool* __in__(PyInt* x_352, PyDictInt* D_354)
{
return __contains__dict__(x_352, D_354);
}
} __in___350;

struct __in__359_local {
PyBool* __in__(PyBool* x_361, PyDictBool* D_363)
{
return __contains__dict__(x_361, D_363);
}
} __in___359;

struct __in__368_local {
PyBool* __in__(PyStr* x_370, PyDictStr* D_372)
{
return __contains__dict__(x_370, D_372);
}
} __in___368;

struct __notin__377_local {
PyBool* __notin__(PyInt* x_379, PyDictInt* D_381)
{
return __notcontains__dict__(x_379, D_381);
}
} __notin___377;

struct __notin__386_local {
PyBool* __notin__(PyBool* x_388, PyDictBool* D_390)
{
return __notcontains__dict__(x_388, D_390);
}
} __notin___386;

struct __notin__395_local {
PyBool* __notin__(PyStr* x_397, PyDictStr* D_399)
{
return __notcontains__dict__(x_397, D_399);
}
} __notin___395;

struct __is__404_local {
PyBool* __is__(PyValue x_406, PyValue y_408)
{
return __is_bool__(x_406, y_408);
}
} __is___404;

struct __isnot__412_local {
PyBool* __isnot__(PyValue x_414, PyValue y_416)
{
return __isnot_bool__(x_414, y_416);
}
} __isnot___412;

PyInt* x_418;
struct f421_local {
PyInt* f_421()
{
PyInt* x_423 = __cons_int__ (6);
return x_423;
}
} f_421;

PyList* a_427;
;
PyInt* b_433;
;
void
__main__()
{
x_418 = __cons_int__ (5);
__print__(1, f_421.f_421());
__newline__();
a_427 = __cons_list__(2, __cons_int__ (1), __cons_int__ (2));
__print__(1, a_427);
__newline__();
a_427 = __cons_list__(4, __cons_int__ (2), __cons_int__ (3), __cons_int__ (4), __cons_int__ (5));
__print__(1, a_427);
__newline__();
b_433 = __cons_int__ (4);
__print__(1, b_433);
__newline__();
b_433 = __cons_int__ (7);
__print__(1, b_433);
__newline__();

}
