#include "runtime.h"
struct xrange24_local {
PyRange* xrange_24(PyInt* low_26, PyInt* high_28)
{
return __xrange__(low_26, high_28);
}
} xrange_24;

struct len31_local {
PyInt* len_31(PyRange* r_33)
{
return __len__range__(r_33);
}
} len_31;

struct __add__37_local {
PyInt* __add__(PyInt* x_39, PyInt* y_41)
{
return __add__int__(x_39, y_41);
}
} __add___37;

struct __sub__45_local {
PyInt* __sub__(PyInt* x_47, PyInt* y_49)
{
return __sub__int__(x_47, y_49);
}
} __sub___45;

struct __mul__53_local {
PyInt* __mul__(PyInt* x_55, PyInt* y_57)
{
return __mul__int__(x_55, y_57);
}
} __mul___53;

struct __floordiv__61_local {
PyInt* __floordiv__(PyInt* x_63, PyInt* y_65)
{
return __floordiv__int__(x_63, y_65);
}
} __floordiv___61;

struct __mod__69_local {
PyInt* __mod__(PyInt* x_71, PyInt* y_73)
{
return __mod__int__(x_71, y_73);
}
} __mod___69;

struct __pow__77_local {
PyInt* __pow__(PyInt* x_79, PyInt* y_81)
{
return __pow__int__(x_79, y_81);
}
} __pow___77;

struct __neg__84_local {
PyInt* __neg__(PyInt* x_86)
{
return __neg__int__(x_86);
}
} __neg___84;

struct __pos__89_local {
PyInt* __pos__(PyInt* x_91)
{
return __pos__int__(x_91);
}
} __pos___89;

struct __lt__95_local {
PyBool* __lt__(PyInt* x_97, PyInt* y_99)
{
return __lt__int__(x_97, y_99);
}
} __lt___95;

struct __gt__103_local {
PyBool* __gt__(PyInt* x_105, PyInt* y_107)
{
return __gt__int__(x_105, y_107);
}
} __gt___103;

struct __le__111_local {
PyBool* __le__(PyInt* x_113, PyInt* y_115)
{
return __le__int__(x_113, y_115);
}
} __le___111;

struct __ge__119_local {
PyBool* __ge__(PyInt* x_121, PyInt* y_123)
{
return __ge__int__(x_121, y_123);
}
} __ge___119;

struct __eq__127_local {
PyBool* __eq__(PyInt* x_129, PyInt* y_131)
{
return __eq__int__(x_129, y_131);
}
} __eq___127;

struct __ne__135_local {
PyBool* __ne__(PyInt* x_137, PyInt* y_139)
{
return __ne__int__(x_137, y_139);
}
} __ne___135;

struct toint142_local {
PyInt* toint_142(PyStr* x_144)
{
return __toint__str__(x_144);
}
} toint_142;

struct __add__148_local {
PyStr* __add__(PyStr* x_150, PyStr* y_152)
{
return __add__str__(x_150, y_152);
}
} __add___148;

struct __mul__156_local {
PyStr* __mul__(PyStr* x_158, PyInt* y_160)
{
return __lmul__str__(x_158, y_160);
}
} __mul___156;

struct __mul__164_local {
PyStr* __mul__(PyInt* x_166, PyStr* y_168)
{
return __rmul__str__(x_166, y_168);
}
} __mul___164;

struct __lt__172_local {
PyBool* __lt__(PyStr* x_174, PyStr* y_176)
{
return __lt__str__(x_174, y_176);
}
} __lt___172;

struct __gt__180_local {
PyBool* __gt__(PyStr* x_182, PyStr* y_184)
{
return __gt__str__(x_182, y_184);
}
} __gt___180;

struct __le__188_local {
PyBool* __le__(PyStr* x_190, PyStr* y_192)
{
return __le__str__(x_190, y_192);
}
} __le___188;

struct __ge__196_local {
PyBool* __ge__(PyStr* x_198, PyStr* y_200)
{
return __ge__str__(x_198, y_200);
}
} __ge___196;

struct __eq__204_local {
PyBool* __eq__(PyStr* x_206, PyStr* y_208)
{
return __eq__str__(x_206, y_208);
}
} __eq___204;

struct __ne__212_local {
PyBool* __ne__(PyStr* x_214, PyStr* y_216)
{
return __ne__str__(x_214, y_216);
}
} __ne___212;

struct __getitem__220_local {
PyStr* __getitem__(PyStr* S_222, PyInt* k_224)
{
return __getitem__str__(S_222, k_224);
}
} __getitem___220;

struct __getslice__229_local {
PyStr* __getslice__(PyStr* S_231, PyInt* L_233, PyInt* U_235)
{
return __getslice__str__(S_231, L_233, U_235);
}
} __getslice___229;

struct len238_local {
PyInt* len_238(PyStr* S_240)
{
return __len__str__(S_240);
}
} len_238;

struct tostr243_local {
PyStr* tostr_243(PyValue x_245)
{
return __tostr__(x_245);
}
} tostr_243;

struct __getitem__249_local {
PyValue __getitem__(PyList* S_251, PyInt* k_253)
{
return __getitem__list__(S_251, k_253);
}
} __getitem___249;

struct __getslice__259_local {
PyList* __getslice__(PyList* S_261, PyInt* L_263, PyInt* U_265)
{
return __getslice__list__(S_261, L_263, U_265);
}
} __getslice___259;

struct len269_local {
PyInt* len_269(PyList* S_271)
{
return __len__list__(S_271);
}
} len_269;

struct __getitem__276_local {
PyValue __getitem__(PyDictInt* D_278, PyInt* x_280)
{
return __getitem__dict__(D_278, x_280);
}
} __getitem___276;

struct __getitem__285_local {
PyValue __getitem__(PyDictBool* D_287, PyBool* x_289)
{
return __getitem__dict__(D_287, x_289);
}
} __getitem___285;

struct __getitem__294_local {
PyValue __getitem__(PyDictStr* D_296, PyStr* x_298)
{
return __getitem__dict__(D_296, x_298);
}
} __getitem___294;

struct len302_local {
PyInt* len_302(PyDictInt* D_304)
{
return __len__dict__(D_304);
}
} len_302;

struct len308_local {
PyInt* len_308(PyDictBool* D_310)
{
return __len__dict__(D_310);
}
} len_308;

struct len314_local {
PyInt* len_314(PyDictStr* D_316)
{
return __len__dict__(D_316);
}
} len_314;

struct __in__321_local {
PyBool* __in__(PyInt* x_323, PyDictInt* D_325)
{
return __contains__dict__(x_323, D_325);
}
} __in___321;

struct __in__330_local {
PyBool* __in__(PyBool* x_332, PyDictBool* D_334)
{
return __contains__dict__(x_332, D_334);
}
} __in___330;

struct __in__339_local {
PyBool* __in__(PyStr* x_341, PyDictStr* D_343)
{
return __contains__dict__(x_341, D_343);
}
} __in___339;

struct __notin__348_local {
PyBool* __notin__(PyInt* x_350, PyDictInt* D_352)
{
return __notcontains__dict__(x_350, D_352);
}
} __notin___348;

struct __notin__357_local {
PyBool* __notin__(PyBool* x_359, PyDictBool* D_361)
{
return __notcontains__dict__(x_359, D_361);
}
} __notin___357;

struct __notin__366_local {
PyBool* __notin__(PyStr* x_368, PyDictStr* D_370)
{
return __notcontains__dict__(x_368, D_370);
}
} __notin___366;

void
__main__()
{
PyList* a_373 = __cons_list__(4, __cons_int__ (1), __cons_int__ (2), __cons_int__ (3), __cons_int__ (4));

}
