#include "runtime.h"
struct truth_29_local  : public PyObject {
PyBool* truth_29(PyValue x_31)
{
return __truth__(x_31);
}
} truth_29;

struct __not___34_local  : public PyObject {
PyBool* __not__(PyValue x_36)
{
return __not_bool__(x_36);
}
} __not___34;

struct xrange_40_local  : public PyObject {
PyRange* xrange_40(PyInt* low_42, PyInt* high_44)
{
return __xrange__(low_42, high_44);
}
} xrange_40;

struct len_47_local  : public PyObject {
PyInt* len_47(PyRange* r_49)
{
return __len__range__(r_49);
}
} len_47;

struct __add___53_local  : public PyObject {
PyInt* __add__(PyInt* x_55, PyInt* y_57)
{
return __add__int__(x_55, y_57);
}
} __add___53;

struct __sub___61_local  : public PyObject {
PyInt* __sub__(PyInt* x_63, PyInt* y_65)
{
return __sub__int__(x_63, y_65);
}
} __sub___61;

struct __mul___69_local  : public PyObject {
PyInt* __mul__(PyInt* x_71, PyInt* y_73)
{
return __mul__int__(x_71, y_73);
}
} __mul___69;

struct __floordiv___77_local  : public PyObject {
PyInt* __floordiv__(PyInt* x_79, PyInt* y_81)
{
return __floordiv__int__(x_79, y_81);
}
} __floordiv___77;

struct __mod___85_local  : public PyObject {
PyInt* __mod__(PyInt* x_87, PyInt* y_89)
{
return __mod__int__(x_87, y_89);
}
} __mod___85;

struct __pow___93_local  : public PyObject {
PyInt* __pow__(PyInt* x_95, PyInt* y_97)
{
return __pow__int__(x_95, y_97);
}
} __pow___93;

struct __neg___100_local  : public PyObject {
PyInt* __neg__(PyInt* x_102)
{
return __neg__int__(x_102);
}
} __neg___100;

struct __pos___105_local  : public PyObject {
PyInt* __pos__(PyInt* x_107)
{
return __pos__int__(x_107);
}
} __pos___105;

struct __lt___111_local  : public PyObject {
PyBool* __lt__(PyInt* x_113, PyInt* y_115)
{
return __lt__int__(x_113, y_115);
}
} __lt___111;

struct __gt___119_local  : public PyObject {
PyBool* __gt__(PyInt* x_121, PyInt* y_123)
{
return __gt__int__(x_121, y_123);
}
} __gt___119;

struct __le___127_local  : public PyObject {
PyBool* __le__(PyInt* x_129, PyInt* y_131)
{
return __le__int__(x_129, y_131);
}
} __le___127;

struct __ge___135_local  : public PyObject {
PyBool* __ge__(PyInt* x_137, PyInt* y_139)
{
return __ge__int__(x_137, y_139);
}
} __ge___135;

struct __eq___143_local  : public PyObject {
PyBool* __eq__(PyInt* x_145, PyInt* y_147)
{
return __eq__int__(x_145, y_147);
}
} __eq___143;

struct __ne___151_local  : public PyObject {
PyBool* __ne__(PyInt* x_153, PyInt* y_155)
{
return __ne__int__(x_153, y_155);
}
} __ne___151;

struct toint_158_local  : public PyObject {
PyInt* toint_158(PyStr* x_160)
{
return __toint__str__(x_160);
}
} toint_158;

struct __add___164_local  : public PyObject {
PyStr* __add__(PyStr* x_166, PyStr* y_168)
{
return __add__str__(x_166, y_168);
}
} __add___164;

struct __mul___172_local  : public PyObject {
PyStr* __mul__(PyStr* x_174, PyInt* y_176)
{
return __lmul__str__(x_174, y_176);
}
} __mul___172;

struct __mul___180_local  : public PyObject {
PyStr* __mul__(PyInt* x_182, PyStr* y_184)
{
return __rmul__str__(x_182, y_184);
}
} __mul___180;

struct __lt___188_local  : public PyObject {
PyBool* __lt__(PyStr* x_190, PyStr* y_192)
{
return __lt__str__(x_190, y_192);
}
} __lt___188;

struct __gt___196_local  : public PyObject {
PyBool* __gt__(PyStr* x_198, PyStr* y_200)
{
return __gt__str__(x_198, y_200);
}
} __gt___196;

struct __le___204_local  : public PyObject {
PyBool* __le__(PyStr* x_206, PyStr* y_208)
{
return __le__str__(x_206, y_208);
}
} __le___204;

struct __ge___212_local  : public PyObject {
PyBool* __ge__(PyStr* x_214, PyStr* y_216)
{
return __ge__str__(x_214, y_216);
}
} __ge___212;

struct __eq___220_local  : public PyObject {
PyBool* __eq__(PyStr* x_222, PyStr* y_224)
{
return __eq__str__(x_222, y_224);
}
} __eq___220;

struct __ne___228_local  : public PyObject {
PyBool* __ne__(PyStr* x_230, PyStr* y_232)
{
return __ne__str__(x_230, y_232);
}
} __ne___228;

struct __getitem___236_local  : public PyObject {
PyStr* __getitem__(PyStr* S_238, PyInt* k_240)
{
return __getitem__str__(S_238, k_240);
}
} __getitem___236;

struct __getslice___245_local  : public PyObject {
PyStr* __getslice__(PyStr* S_247, PyInt* L_249, PyInt* U_251)
{
return __getslice__str__(S_247, L_249, U_251);
}
} __getslice___245;

struct len_254_local  : public PyObject {
PyInt* len_254(PyStr* S_256)
{
return __len__str__(S_256);
}
} len_254;

struct tostr_259_local  : public PyObject {
PyStr* tostr_259(PyValue x_261)
{
return __tostr__(x_261);
}
} tostr_259;

struct __getitem___265_local  : public PyObject {
PyValue __getitem__(PyList* S_267, PyInt* k_269)
{
return __getitem__list__(S_267, k_269);
}
} __getitem___265;

struct __getslice___275_local  : public PyObject {
PyList* __getslice__(PyList* S_277, PyInt* L_279, PyInt* U_281)
{
return __getslice__list__(S_277, L_279, U_281);
}
} __getslice___275;

struct __setitem___287_local  : public PyObject {
PyValue __setitem__(PyList* S_289, PyInt* k_291, PyValue val_293)
{
return __setitem__list__(S_289, k_291, val_293);
}
} __setitem___287;

struct __setslice___300_local  : public PyObject {
PyList* __setslice__(PyList* S_302, PyInt* a_304, PyInt* b_306, PyList* val_308)
{
return __setslice__list__(S_302, a_304, b_306, val_308);
}
} __setslice___300;

struct len_312_local  : public PyObject {
PyInt* len_312(PyList* S_314)
{
return __len__list__(S_314);
}
} len_312;

struct argv_317_local  : public PyObject {
PyList* argv_317()
{
return __argv__();
}
} argv_317;

struct readline_319_local  : public PyObject {
PyStr* readline_319()
{
return __readline__();
}
} readline_319;

struct read_321_local  : public PyObject {
PyStr* read_321()
{
return __read__();
}
} read_321;

struct __getitem___325_local  : public PyObject {
PyValue __getitem__(PyDictInt* D_327, PyInt* x_329)
{
return __getitem__dict__(D_327, x_329);
}
} __getitem___325;

struct __getitem___334_local  : public PyObject {
PyValue __getitem__(PyDictBool* D_336, PyBool* x_338)
{
return __getitem__dict__(D_336, x_338);
}
} __getitem___334;

struct __getitem___343_local  : public PyObject {
PyValue __getitem__(PyDictStr* D_345, PyStr* x_347)
{
return __getitem__dict__(D_345, x_347);
}
} __getitem___343;

struct __setitem___353_local  : public PyObject {
PyValue __setitem__(PyDictInt* S_355, PyInt* k_357, PyValue val_359)
{
return __setitem__dict__(S_355, k_357, val_359);
}
} __setitem___353;

struct __setitem___365_local  : public PyObject {
PyValue __setitem__(PyDictBool* S_367, PyBool* k_369, PyValue val_371)
{
return __setitem__dict__(S_367, k_369, val_371);
}
} __setitem___365;

struct __setitem___377_local  : public PyObject {
PyValue __setitem__(PyDictStr* S_379, PyStr* k_381, PyValue val_383)
{
return __setitem__dict__(S_379, k_381, val_383);
}
} __setitem___377;

struct len_387_local  : public PyObject {
PyInt* len_387(PyDictInt* D_389)
{
return __len__dict__(D_389);
}
} len_387;

struct len_393_local  : public PyObject {
PyInt* len_393(PyDictBool* D_395)
{
return __len__dict__(D_395);
}
} len_393;

struct len_399_local  : public PyObject {
PyInt* len_399(PyDictStr* D_401)
{
return __len__dict__(D_401);
}
} len_399;

struct __in___406_local  : public PyObject {
PyBool* __in__(PyInt* x_408, PyDictInt* D_410)
{
return __contains__dict__(x_408, D_410);
}
} __in___406;

struct __in___415_local  : public PyObject {
PyBool* __in__(PyBool* x_417, PyDictBool* D_419)
{
return __contains__dict__(x_417, D_419);
}
} __in___415;

struct __in___424_local  : public PyObject {
PyBool* __in__(PyStr* x_426, PyDictStr* D_428)
{
return __contains__dict__(x_426, D_428);
}
} __in___424;

struct __notin___433_local  : public PyObject {
PyBool* __notin__(PyInt* x_435, PyDictInt* D_437)
{
return __notcontains__dict__(x_435, D_437);
}
} __notin___433;

struct __notin___442_local  : public PyObject {
PyBool* __notin__(PyBool* x_444, PyDictBool* D_446)
{
return __notcontains__dict__(x_444, D_446);
}
} __notin___442;

struct __notin___451_local  : public PyObject {
PyBool* __notin__(PyStr* x_453, PyDictStr* D_455)
{
return __notcontains__dict__(x_453, D_455);
}
} __notin___451;

struct __is___460_local  : public PyObject {
PyBool* __is__(PyValue x_462, PyValue y_464)
{
return __is_bool__(x_462, y_464);
}
} __is___460;

struct __isnot___468_local  : public PyObject {
PyBool* __isnot__(PyValue x_470, PyValue y_472)
{
return __isnot_bool__(x_470, y_472);
}
} __isnot___468;

PyList* L_474;
PyInt* x_490;
;
void
__main__()
{
L_474 = __cons_list__(4, __cons_int__ (3), __cons_int__ (7), __cons_int__ (11), __cons_int__ (5));
for (int index_478 = 0; index_478 < L_474->getSize(); index_478++) {
PyInt* i_478 = (PyInt*) L_474->get(index_478);
__print__(1, i_478);
__newline__();
}
for (int index_478 = 0; index_478 < L_474->getSize(); index_478++) {
PyInt* i_478 = (PyInt*) L_474->get(index_478);
__print__(1, i_478);
__newline__();
__print__(1, __pow___93.__pow__(i_478, __cons_int__ (2)));
__newline__();
}
for (int index_478 = 0; index_478 < L_474->getSize(); index_478++) {
PyInt* i_478 = (PyInt*) L_474->get(index_478);
__print__(1, i_478);
__newline__();
__print__(1, __pow___93.__pow__(i_478, __cons_int__ (2)));
__newline__();
}
__print__(1, __neg___100.__neg__(i_478));
__newline__();
x_490 = __cons_int__ (4);
for (int index_478 = 0; index_478 < L_474->getSize(); index_478++) {
PyInt* i_478 = (PyInt*) L_474->get(index_478);
if (__eval_bool__((__gt___119.__gt__(i_478, x_490)))) {
__print__(1, i_478);
__newline__();
break;}
}
x_490 = __cons_int__ (6);
for (int index_478 = 0; index_478 < L_474->getSize(); index_478++) {
PyInt* i_478 = (PyInt*) L_474->get(index_478);
if (__eval_bool__((__gt___119.__gt__(i_478, x_490)))) {
continue;}
__print__(1, i_478);
__newline__();
}

}
