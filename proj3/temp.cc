#include "runtime.h"
struct truth33_local {
PyBool* truth_33(PyValue x_35)
{
return __truth__(x_35);
}
} truth_33;

struct __not__38_local {
PyBool* __not__(PyValue x_40)
{
return __not_bool__(x_40);
}
} __not___38;

struct xrange44_local {
PyRange* xrange_44(PyInt* low_46, PyInt* high_48)
{
return __xrange__(low_46, high_48);
}
} xrange_44;

struct len51_local {
PyInt* len_51(PyRange* r_53)
{
return __len__range__(r_53);
}
} len_51;

struct __add__57_local {
PyInt* __add__(PyInt* x_59, PyInt* y_61)
{
return __add__int__(x_59, y_61);
}
} __add___57;

struct __sub__65_local {
PyInt* __sub__(PyInt* x_67, PyInt* y_69)
{
return __sub__int__(x_67, y_69);
}
} __sub___65;

struct __mul__73_local {
PyInt* __mul__(PyInt* x_75, PyInt* y_77)
{
return __mul__int__(x_75, y_77);
}
} __mul___73;

struct __floordiv__81_local {
PyInt* __floordiv__(PyInt* x_83, PyInt* y_85)
{
return __floordiv__int__(x_83, y_85);
}
} __floordiv___81;

struct __mod__89_local {
PyInt* __mod__(PyInt* x_91, PyInt* y_93)
{
return __mod__int__(x_91, y_93);
}
} __mod___89;

struct __pow__97_local {
PyInt* __pow__(PyInt* x_99, PyInt* y_101)
{
return __pow__int__(x_99, y_101);
}
} __pow___97;

struct __neg__104_local {
PyInt* __neg__(PyInt* x_106)
{
return __neg__int__(x_106);
}
} __neg___104;

struct __pos__109_local {
PyInt* __pos__(PyInt* x_111)
{
return __pos__int__(x_111);
}
} __pos___109;

struct __lt__115_local {
PyBool* __lt__(PyInt* x_117, PyInt* y_119)
{
return __lt__int__(x_117, y_119);
}
} __lt___115;

struct __gt__123_local {
PyBool* __gt__(PyInt* x_125, PyInt* y_127)
{
return __gt__int__(x_125, y_127);
}
} __gt___123;

struct __le__131_local {
PyBool* __le__(PyInt* x_133, PyInt* y_135)
{
return __le__int__(x_133, y_135);
}
} __le___131;

struct __ge__139_local {
PyBool* __ge__(PyInt* x_141, PyInt* y_143)
{
return __ge__int__(x_141, y_143);
}
} __ge___139;

struct __eq__147_local {
PyBool* __eq__(PyInt* x_149, PyInt* y_151)
{
return __eq__int__(x_149, y_151);
}
} __eq___147;

struct __ne__155_local {
PyBool* __ne__(PyInt* x_157, PyInt* y_159)
{
return __ne__int__(x_157, y_159);
}
} __ne___155;

struct toint162_local {
PyInt* toint_162(PyStr* x_164)
{
return __toint__str__(x_164);
}
} toint_162;

struct __add__168_local {
PyStr* __add__(PyStr* x_170, PyStr* y_172)
{
return __add__str__(x_170, y_172);
}
} __add___168;

struct __mul__176_local {
PyStr* __mul__(PyStr* x_178, PyInt* y_180)
{
return __lmul__str__(x_178, y_180);
}
} __mul___176;

struct __mul__184_local {
PyStr* __mul__(PyInt* x_186, PyStr* y_188)
{
return __rmul__str__(x_186, y_188);
}
} __mul___184;

struct __lt__192_local {
PyBool* __lt__(PyStr* x_194, PyStr* y_196)
{
return __lt__str__(x_194, y_196);
}
} __lt___192;

struct __gt__200_local {
PyBool* __gt__(PyStr* x_202, PyStr* y_204)
{
return __gt__str__(x_202, y_204);
}
} __gt___200;

struct __le__208_local {
PyBool* __le__(PyStr* x_210, PyStr* y_212)
{
return __le__str__(x_210, y_212);
}
} __le___208;

struct __ge__216_local {
PyBool* __ge__(PyStr* x_218, PyStr* y_220)
{
return __ge__str__(x_218, y_220);
}
} __ge___216;

struct __eq__224_local {
PyBool* __eq__(PyStr* x_226, PyStr* y_228)
{
return __eq__str__(x_226, y_228);
}
} __eq___224;

struct __ne__232_local {
PyBool* __ne__(PyStr* x_234, PyStr* y_236)
{
return __ne__str__(x_234, y_236);
}
} __ne___232;

struct __getitem__240_local {
PyStr* __getitem__(PyStr* S_242, PyInt* k_244)
{
return __getitem__str__(S_242, k_244);
}
} __getitem___240;

struct __getslice__249_local {
PyStr* __getslice__(PyStr* S_251, PyInt* L_253, PyInt* U_255)
{
return __getslice__str__(S_251, L_253, U_255);
}
} __getslice___249;

struct len258_local {
PyInt* len_258(PyStr* S_260)
{
return __len__str__(S_260);
}
} len_258;

struct tostr263_local {
PyStr* tostr_263(PyValue x_265)
{
return __tostr__(x_265);
}
} tostr_263;

struct __getitem__269_local {
PyValue __getitem__(PyList* S_271, PyInt* k_273)
{
return __getitem__list__(S_271, k_273);
}
} __getitem___269;

struct __getslice__279_local {
PyList* __getslice__(PyList* S_281, PyInt* L_283, PyInt* U_285)
{
return __getslice__list__(S_281, L_283, U_285);
}
} __getslice___279;

struct __setitem__291_local {
PyValue __setitem__(PyList* S_293, PyInt* k_295, PyValue val_297)
{
return __setitem__list__(S_293, k_295, val_297);
}
} __setitem___291;

struct len301_local {
PyInt* len_301(PyList* S_303)
{
return __len__list__(S_303);
}
} len_301;

struct argv306_local {
PyList* argv_306()
{
return __argv__();
}
} argv_306;

struct readline308_local {
PyStr* readline_308()
{
return __readline__();
}
} readline_308;

struct read310_local {
PyStr* read_310()
{
return __read__();
}
} read_310;

struct __getitem__314_local {
PyValue __getitem__(PyDictInt* D_316, PyInt* x_318)
{
return __getitem__dict__(D_316, x_318);
}
} __getitem___314;

struct __getitem__323_local {
PyValue __getitem__(PyDictBool* D_325, PyBool* x_327)
{
return __getitem__dict__(D_325, x_327);
}
} __getitem___323;

struct __getitem__332_local {
PyValue __getitem__(PyDictStr* D_334, PyStr* x_336)
{
return __getitem__dict__(D_334, x_336);
}
} __getitem___332;

struct len340_local {
PyInt* len_340(PyDictInt* D_342)
{
return __len__dict__(D_342);
}
} len_340;

struct len346_local {
PyInt* len_346(PyDictBool* D_348)
{
return __len__dict__(D_348);
}
} len_346;

struct len352_local {
PyInt* len_352(PyDictStr* D_354)
{
return __len__dict__(D_354);
}
} len_352;

struct __in__359_local {
PyBool* __in__(PyInt* x_361, PyDictInt* D_363)
{
return __contains__dict__(x_361, D_363);
}
} __in___359;

struct __in__368_local {
PyBool* __in__(PyBool* x_370, PyDictBool* D_372)
{
return __contains__dict__(x_370, D_372);
}
} __in___368;

struct __in__377_local {
PyBool* __in__(PyStr* x_379, PyDictStr* D_381)
{
return __contains__dict__(x_379, D_381);
}
} __in___377;

struct __notin__386_local {
PyBool* __notin__(PyInt* x_388, PyDictInt* D_390)
{
return __notcontains__dict__(x_388, D_390);
}
} __notin___386;

struct __notin__395_local {
PyBool* __notin__(PyBool* x_397, PyDictBool* D_399)
{
return __notcontains__dict__(x_397, D_399);
}
} __notin___395;

struct __notin__404_local {
PyBool* __notin__(PyStr* x_406, PyDictStr* D_408)
{
return __notcontains__dict__(x_406, D_408);
}
} __notin___404;

struct __is__413_local {
PyBool* __is__(PyValue x_415, PyValue y_417)
{
return __is_bool__(x_415, y_417);
}
} __is___413;

struct __isnot__421_local {
PyBool* __isnot__(PyValue x_423, PyValue y_425)
{
return __isnot_bool__(x_423, y_425);
}
} __isnot___421;

struct make_adder428_local {
PyValue make_adder_428(PyValue x_430)
{
struct adder433_local {
PyValue adder_433(PyValue y_435)
{
return y_435;
}
} adder_433;

return adder_433;
}
} make_adder_428;

PyValue a_437;
void
__main__()
{
a_437 = make_adder_428.make_adder_428(__cons_int__ (5));
__print__(1, a_437.a_437(__cons_int__ (10)));
__newline__();

}
