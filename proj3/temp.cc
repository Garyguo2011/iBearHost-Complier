#include "runtime.h"
class Hello {
PyInt* a_424;
Hello (PyInt* x_431)
{
PyInt* x_431 = a_424;
}
PyInt* f (PyInt* y_438)
{
return __add___59.__add__(a_424, y_438);
}
};
struct truth35_local {
PyBool* truth_35(PyValue x_37)
{
return __truth__(x_37);
}
} truth_35;

struct __not__40_local {
PyBool* __not__(PyValue x_42)
{
return __not_bool__(x_42);
}
} __not___40;

struct xrange46_local {
PyRange* xrange_46(PyInt* low_48, PyInt* high_50)
{
return __xrange__(low_48, high_50);
}
} xrange_46;

struct len53_local {
PyInt* len_53(PyRange* r_55)
{
return __len__range__(r_55);
}
} len_53;

struct __add__59_local {
PyInt* __add__(PyInt* x_61, PyInt* y_63)
{
return __add__int__(x_61, y_63);
}
} __add___59;

struct __sub__67_local {
PyInt* __sub__(PyInt* x_69, PyInt* y_71)
{
return __sub__int__(x_69, y_71);
}
} __sub___67;

struct __mul__75_local {
PyInt* __mul__(PyInt* x_77, PyInt* y_79)
{
return __mul__int__(x_77, y_79);
}
} __mul___75;

struct __floordiv__83_local {
PyInt* __floordiv__(PyInt* x_85, PyInt* y_87)
{
return __floordiv__int__(x_85, y_87);
}
} __floordiv___83;

struct __mod__91_local {
PyInt* __mod__(PyInt* x_93, PyInt* y_95)
{
return __mod__int__(x_93, y_95);
}
} __mod___91;

struct __pow__99_local {
PyInt* __pow__(PyInt* x_101, PyInt* y_103)
{
return __pow__int__(x_101, y_103);
}
} __pow___99;

struct __neg__106_local {
PyInt* __neg__(PyInt* x_108)
{
return __neg__int__(x_108);
}
} __neg___106;

struct __pos__111_local {
PyInt* __pos__(PyInt* x_113)
{
return __pos__int__(x_113);
}
} __pos___111;

struct __lt__117_local {
PyBool* __lt__(PyInt* x_119, PyInt* y_121)
{
return __lt__int__(x_119, y_121);
}
} __lt___117;

struct __gt__125_local {
PyBool* __gt__(PyInt* x_127, PyInt* y_129)
{
return __gt__int__(x_127, y_129);
}
} __gt___125;

struct __le__133_local {
PyBool* __le__(PyInt* x_135, PyInt* y_137)
{
return __le__int__(x_135, y_137);
}
} __le___133;

struct __ge__141_local {
PyBool* __ge__(PyInt* x_143, PyInt* y_145)
{
return __ge__int__(x_143, y_145);
}
} __ge___141;

struct __eq__149_local {
PyBool* __eq__(PyInt* x_151, PyInt* y_153)
{
return __eq__int__(x_151, y_153);
}
} __eq___149;

struct __ne__157_local {
PyBool* __ne__(PyInt* x_159, PyInt* y_161)
{
return __ne__int__(x_159, y_161);
}
} __ne___157;

struct toint164_local {
PyInt* toint_164(PyStr* x_166)
{
return __toint__str__(x_166);
}
} toint_164;

struct __add__170_local {
PyStr* __add__(PyStr* x_172, PyStr* y_174)
{
return __add__str__(x_172, y_174);
}
} __add___170;

struct __mul__178_local {
PyStr* __mul__(PyStr* x_180, PyInt* y_182)
{
return __lmul__str__(x_180, y_182);
}
} __mul___178;

struct __mul__186_local {
PyStr* __mul__(PyInt* x_188, PyStr* y_190)
{
return __rmul__str__(x_188, y_190);
}
} __mul___186;

struct __lt__194_local {
PyBool* __lt__(PyStr* x_196, PyStr* y_198)
{
return __lt__str__(x_196, y_198);
}
} __lt___194;

struct __gt__202_local {
PyBool* __gt__(PyStr* x_204, PyStr* y_206)
{
return __gt__str__(x_204, y_206);
}
} __gt___202;

struct __le__210_local {
PyBool* __le__(PyStr* x_212, PyStr* y_214)
{
return __le__str__(x_212, y_214);
}
} __le___210;

struct __ge__218_local {
PyBool* __ge__(PyStr* x_220, PyStr* y_222)
{
return __ge__str__(x_220, y_222);
}
} __ge___218;

struct __eq__226_local {
PyBool* __eq__(PyStr* x_228, PyStr* y_230)
{
return __eq__str__(x_228, y_230);
}
} __eq___226;

struct __ne__234_local {
PyBool* __ne__(PyStr* x_236, PyStr* y_238)
{
return __ne__str__(x_236, y_238);
}
} __ne___234;

struct __getitem__242_local {
PyStr* __getitem__(PyStr* S_244, PyInt* k_246)
{
return __getitem__str__(S_244, k_246);
}
} __getitem___242;

struct __getslice__251_local {
PyStr* __getslice__(PyStr* S_253, PyInt* L_255, PyInt* U_257)
{
return __getslice__str__(S_253, L_255, U_257);
}
} __getslice___251;

struct len260_local {
PyInt* len_260(PyStr* S_262)
{
return __len__str__(S_262);
}
} len_260;

struct tostr265_local {
PyStr* tostr_265(PyValue x_267)
{
return __tostr__(x_267);
}
} tostr_265;

struct __getitem__271_local {
PyValue __getitem__(PyList* S_273, PyInt* k_275)
{
return __getitem__list__(S_273, k_275);
}
} __getitem___271;

struct __getslice__281_local {
PyList* __getslice__(PyList* S_283, PyInt* L_285, PyInt* U_287)
{
return __getslice__list__(S_283, L_285, U_287);
}
} __getslice___281;

struct __setitem__293_local {
PyValue __setitem__(PyList* S_295, PyInt* k_297, PyValue val_299)
{
return __setitem__list__(S_295, k_297, val_299);
}
} __setitem___293;

struct len303_local {
PyInt* len_303(PyList* S_305)
{
return __len__list__(S_305);
}
} len_303;

struct __getitem__310_local {
PyValue __getitem__(PyDictInt* D_312, PyInt* x_314)
{
return __getitem__dict__(D_312, x_314);
}
} __getitem___310;

struct __getitem__319_local {
PyValue __getitem__(PyDictBool* D_321, PyBool* x_323)
{
return __getitem__dict__(D_321, x_323);
}
} __getitem___319;

struct __getitem__328_local {
PyValue __getitem__(PyDictStr* D_330, PyStr* x_332)
{
return __getitem__dict__(D_330, x_332);
}
} __getitem___328;

struct len336_local {
PyInt* len_336(PyDictInt* D_338)
{
return __len__dict__(D_338);
}
} len_336;

struct len342_local {
PyInt* len_342(PyDictBool* D_344)
{
return __len__dict__(D_344);
}
} len_342;

struct len348_local {
PyInt* len_348(PyDictStr* D_350)
{
return __len__dict__(D_350);
}
} len_348;

struct __in__355_local {
PyBool* __in__(PyInt* x_357, PyDictInt* D_359)
{
return __contains__dict__(x_357, D_359);
}
} __in___355;

struct __in__364_local {
PyBool* __in__(PyBool* x_366, PyDictBool* D_368)
{
return __contains__dict__(x_366, D_368);
}
} __in___364;

struct __in__373_local {
PyBool* __in__(PyStr* x_375, PyDictStr* D_377)
{
return __contains__dict__(x_375, D_377);
}
} __in___373;

struct __notin__382_local {
PyBool* __notin__(PyInt* x_384, PyDictInt* D_386)
{
return __notcontains__dict__(x_384, D_386);
}
} __notin___382;

struct __notin__391_local {
PyBool* __notin__(PyBool* x_393, PyDictBool* D_395)
{
return __notcontains__dict__(x_393, D_395);
}
} __notin___391;

struct __notin__400_local {
PyBool* __notin__(PyStr* x_402, PyDictStr* D_404)
{
return __notcontains__dict__(x_402, D_404);
}
} __notin___400;

struct __is__409_local {
PyBool* __is__(PyValue x_411, PyValue y_413)
{
return __is_bool__(x_411, y_413);
}
} __is___409;

struct __isnot__417_local {
PyBool* __isnot__(PyValue x_419, PyValue y_421)
{
return __isnot_bool__(x_419, y_421);
}
} __isnot___417;

PyInt* i_446;
PyValue obj_449;
void
__main__()
{
i_446 = __cons_int__ (9);
obj_449 = new Hello_422(__cons_int__ (9));
__print__(1, obj_449.a_424);
__newline__();

}
