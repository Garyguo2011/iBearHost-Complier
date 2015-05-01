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

struct len286_local {
PyInt* len_286(PyList* S_288)
{
return __len__list__(S_288);
}
} len_286;

struct __getitem__293_local {
PyValue __getitem__(PyDictInt* D_295, PyInt* x_297)
{
return __getitem__dict__(D_295, x_297);
}
} __getitem___293;

struct __getitem__302_local {
PyValue __getitem__(PyDictBool* D_304, PyBool* x_306)
{
return __getitem__dict__(D_304, x_306);
}
} __getitem___302;

struct __getitem__311_local {
PyValue __getitem__(PyDictStr* D_313, PyStr* x_315)
{
return __getitem__dict__(D_313, x_315);
}
} __getitem___311;

struct len319_local {
PyInt* len_319(PyDictInt* D_321)
{
return __len__dict__(D_321);
}
} len_319;

struct len325_local {
PyInt* len_325(PyDictBool* D_327)
{
return __len__dict__(D_327);
}
} len_325;

struct len331_local {
PyInt* len_331(PyDictStr* D_333)
{
return __len__dict__(D_333);
}
} len_331;

struct __in__338_local {
PyBool* __in__(PyInt* x_340, PyDictInt* D_342)
{
return __contains__dict__(x_340, D_342);
}
} __in___338;

struct __in__347_local {
PyBool* __in__(PyBool* x_349, PyDictBool* D_351)
{
return __contains__dict__(x_349, D_351);
}
} __in___347;

struct __in__356_local {
PyBool* __in__(PyStr* x_358, PyDictStr* D_360)
{
return __contains__dict__(x_358, D_360);
}
} __in___356;

struct __notin__365_local {
PyBool* __notin__(PyInt* x_367, PyDictInt* D_369)
{
return __notcontains__dict__(x_367, D_369);
}
} __notin___365;

struct __notin__374_local {
PyBool* __notin__(PyBool* x_376, PyDictBool* D_378)
{
return __notcontains__dict__(x_376, D_378);
}
} __notin___374;

struct __notin__383_local {
PyBool* __notin__(PyStr* x_385, PyDictStr* D_387)
{
return __notcontains__dict__(x_385, D_387);
}
} __notin___383;

struct __is__392_local {
PyBool* __is__(PyValue x_394, PyValue y_396)
{
return __is_bool__(x_394, y_396);
}
} __is___392;

struct __isnot__400_local {
PyBool* __isnot__(PyValue x_402, PyValue y_404)
{
return __isnot_bool__(x_402, y_404);
}
} __isnot___400;

PyInt* x_406;
struct f409_local {
PyInt* f_409()
{
return x_406;
}
} f_409;

void
__main__()
{
x_406 = __cons_int__ (5);
__print__(1, f_409.f_409());
__newline__();

}
