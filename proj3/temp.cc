#include "runtime.h"
struct truth29_local {
PyBool* truth_29(PyValue x_31)
{
return __truth__(x_31);
}
} truth_29;

struct __not__34_local {
PyBool* __not__(PyValue x_36)
{
return __not_bool__(x_36);
}
} __not___34;

struct xrange40_local {
PyRange* xrange_40(PyInt* low_42, PyInt* high_44)
{
return __xrange__(low_42, high_44);
}
} xrange_40;

struct len47_local {
PyInt* len_47(PyRange* r_49)
{
return __len__range__(r_49);
}
} len_47;

struct __add__53_local {
PyInt* __add__(PyInt* x_55, PyInt* y_57)
{
return __add__int__(x_55, y_57);
}
} __add___53;

struct __sub__61_local {
PyInt* __sub__(PyInt* x_63, PyInt* y_65)
{
return __sub__int__(x_63, y_65);
}
} __sub___61;

struct __mul__69_local {
PyInt* __mul__(PyInt* x_71, PyInt* y_73)
{
return __mul__int__(x_71, y_73);
}
} __mul___69;

struct __floordiv__77_local {
PyInt* __floordiv__(PyInt* x_79, PyInt* y_81)
{
return __floordiv__int__(x_79, y_81);
}
} __floordiv___77;

struct __mod__85_local {
PyInt* __mod__(PyInt* x_87, PyInt* y_89)
{
return __mod__int__(x_87, y_89);
}
} __mod___85;

struct __pow__93_local {
PyInt* __pow__(PyInt* x_95, PyInt* y_97)
{
return __pow__int__(x_95, y_97);
}
} __pow___93;

struct __neg__100_local {
PyInt* __neg__(PyInt* x_102)
{
return __neg__int__(x_102);
}
} __neg___100;

struct __pos__105_local {
PyInt* __pos__(PyInt* x_107)
{
return __pos__int__(x_107);
}
} __pos___105;

struct __lt__111_local {
PyBool* __lt__(PyInt* x_113, PyInt* y_115)
{
return __lt__int__(x_113, y_115);
}
} __lt___111;

struct __gt__119_local {
PyBool* __gt__(PyInt* x_121, PyInt* y_123)
{
return __gt__int__(x_121, y_123);
}
} __gt___119;

struct __le__127_local {
PyBool* __le__(PyInt* x_129, PyInt* y_131)
{
return __le__int__(x_129, y_131);
}
} __le___127;

struct __ge__135_local {
PyBool* __ge__(PyInt* x_137, PyInt* y_139)
{
return __ge__int__(x_137, y_139);
}
} __ge___135;

struct __eq__143_local {
PyBool* __eq__(PyInt* x_145, PyInt* y_147)
{
return __eq__int__(x_145, y_147);
}
} __eq___143;

struct __ne__151_local {
PyBool* __ne__(PyInt* x_153, PyInt* y_155)
{
return __ne__int__(x_153, y_155);
}
} __ne___151;

struct toint158_local {
PyInt* toint_158(PyStr* x_160)
{
return __toint__str__(x_160);
}
} toint_158;

struct __add__164_local {
PyStr* __add__(PyStr* x_166, PyStr* y_168)
{
return __add__str__(x_166, y_168);
}
} __add___164;

struct __mul__172_local {
PyStr* __mul__(PyStr* x_174, PyInt* y_176)
{
return __lmul__str__(x_174, y_176);
}
} __mul___172;

struct __mul__180_local {
PyStr* __mul__(PyInt* x_182, PyStr* y_184)
{
return __rmul__str__(x_182, y_184);
}
} __mul___180;

struct __lt__188_local {
PyBool* __lt__(PyStr* x_190, PyStr* y_192)
{
return __lt__str__(x_190, y_192);
}
} __lt___188;

struct __gt__196_local {
PyBool* __gt__(PyStr* x_198, PyStr* y_200)
{
return __gt__str__(x_198, y_200);
}
} __gt___196;

struct __le__204_local {
PyBool* __le__(PyStr* x_206, PyStr* y_208)
{
return __le__str__(x_206, y_208);
}
} __le___204;

struct __ge__212_local {
PyBool* __ge__(PyStr* x_214, PyStr* y_216)
{
return __ge__str__(x_214, y_216);
}
} __ge___212;

struct __eq__220_local {
PyBool* __eq__(PyStr* x_222, PyStr* y_224)
{
return __eq__str__(x_222, y_224);
}
} __eq___220;

struct __ne__228_local {
PyBool* __ne__(PyStr* x_230, PyStr* y_232)
{
return __ne__str__(x_230, y_232);
}
} __ne___228;

struct __getitem__236_local {
PyStr* __getitem__(PyStr* S_238, PyInt* k_240)
{
return __getitem__str__(S_238, k_240);
}
} __getitem___236;

struct __getslice__245_local {
PyStr* __getslice__(PyStr* S_247, PyInt* L_249, PyInt* U_251)
{
return __getslice__str__(S_247, L_249, U_251);
}
} __getslice___245;

struct len254_local {
PyInt* len_254(PyStr* S_256)
{
return __len__str__(S_256);
}
} len_254;

struct tostr259_local {
PyStr* tostr_259(PyValue x_261)
{
return __tostr__(x_261);
}
} tostr_259;

struct __getitem__265_local {
PyValue __getitem__(PyList* S_267, PyInt* k_269)
{
return __getitem__list__(S_267, k_269);
}
} __getitem___265;

struct __getslice__275_local {
PyList* __getslice__(PyList* S_277, PyInt* L_279, PyInt* U_281)
{
return __getslice__list__(S_277, L_279, U_281);
}
} __getslice___275;

struct __setitem__287_local {
PyValue __setitem__(PyList* S_289, PyInt* k_291, PyValue val_293)
{
return __setitem__list__(S_289, k_291, val_293);
}
} __setitem___287;

struct len297_local {
PyInt* len_297(PyList* S_299)
{
return __len__list__(S_299);
}
} len_297;

struct argv302_local {
PyList* argv_302()
{
return __argv__();
}
} argv_302;

struct readline304_local {
PyStr* readline_304()
{
return __readline__();
}
} readline_304;

struct read306_local {
PyStr* read_306()
{
return __read__();
}
} read_306;

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

void
__main__()
{
__print__(1, __and__(__and__(__cons_bool__ (1), __cons_bool__ (1)), __cons_bool__ (1)));
__newline__();

}
