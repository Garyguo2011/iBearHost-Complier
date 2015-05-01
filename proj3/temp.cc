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

struct len285_local {
PyInt* len_285(PyList* S_287)
{
return __len__list__(S_287);
}
} len_285;

struct __getitem__292_local {
PyValue __getitem__(PyDictInt* D_294, PyInt* x_296)
{
return __getitem__dict__(D_294, x_296);
}
} __getitem___292;

struct __getitem__301_local {
PyValue __getitem__(PyDictBool* D_303, PyBool* x_305)
{
return __getitem__dict__(D_303, x_305);
}
} __getitem___301;

struct __getitem__310_local {
PyValue __getitem__(PyDictStr* D_312, PyStr* x_314)
{
return __getitem__dict__(D_312, x_314);
}
} __getitem___310;

struct len318_local {
PyInt* len_318(PyDictInt* D_320)
{
return __len__dict__(D_320);
}
} len_318;

struct len324_local {
PyInt* len_324(PyDictBool* D_326)
{
return __len__dict__(D_326);
}
} len_324;

struct len330_local {
PyInt* len_330(PyDictStr* D_332)
{
return __len__dict__(D_332);
}
} len_330;

struct __in__337_local {
PyBool* __in__(PyInt* x_339, PyDictInt* D_341)
{
return __contains__dict__(x_339, D_341);
}
} __in___337;

struct __in__346_local {
PyBool* __in__(PyBool* x_348, PyDictBool* D_350)
{
return __contains__dict__(x_348, D_350);
}
} __in___346;

struct __in__355_local {
PyBool* __in__(PyStr* x_357, PyDictStr* D_359)
{
return __contains__dict__(x_357, D_359);
}
} __in___355;

struct __notin__364_local {
PyBool* __notin__(PyInt* x_366, PyDictInt* D_368)
{
return __notcontains__dict__(x_366, D_368);
}
} __notin___364;

struct __notin__373_local {
PyBool* __notin__(PyBool* x_375, PyDictBool* D_377)
{
return __notcontains__dict__(x_375, D_377);
}
} __notin___373;

struct __notin__382_local {
PyBool* __notin__(PyStr* x_384, PyDictStr* D_386)
{
return __notcontains__dict__(x_384, D_386);
}
} __notin___382;

struct __is__391_local {
PyBool* __is__(PyValue x_393, PyValue y_395)
{
return __is_bool__(x_393, y_395);
}
} __is___391;

struct __isnot__399_local {
PyBool* __isnot__(PyValue x_401, PyValue y_403)
{
return __isnot_bool__(x_401, y_403);
}
} __isnot___399;

void
__main__()
{
for (x_405) {
xrange_40.xrange_40(__cons_int__ (1), __cons_int__ (4))}
__print__(1, x_405);
__newline__();

}
