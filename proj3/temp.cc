#include "runtime.h"
struct truth_33_local  : public PyObject {
PyBool* truth_33(PyValue x_35)
{
return __truth__(x_35);
}
} truth_33;

struct __not___38_local  : public PyObject {
PyBool* __not__(PyValue x_40)
{
return __not_bool__(x_40);
}
} __not___38;

struct xrange_44_local  : public PyObject {
PyRange* xrange_44(PyInt* low_46, PyInt* high_48)
{
return __xrange__(low_46, high_48);
}
} xrange_44;

struct len_51_local  : public PyObject {
PyInt* len_51(PyRange* r_53)
{
return __len__range__(r_53);
}
} len_51;

struct __add___57_local  : public PyObject {
PyInt* __add__(PyInt* x_59, PyInt* y_61)
{
return __add__int__(x_59, y_61);
}
} __add___57;

struct __sub___65_local  : public PyObject {
PyInt* __sub__(PyInt* x_67, PyInt* y_69)
{
return __sub__int__(x_67, y_69);
}
} __sub___65;

struct __mul___73_local  : public PyObject {
PyInt* __mul__(PyInt* x_75, PyInt* y_77)
{
return __mul__int__(x_75, y_77);
}
} __mul___73;

struct __floordiv___81_local  : public PyObject {
PyInt* __floordiv__(PyInt* x_83, PyInt* y_85)
{
return __floordiv__int__(x_83, y_85);
}
} __floordiv___81;

struct __mod___89_local  : public PyObject {
PyInt* __mod__(PyInt* x_91, PyInt* y_93)
{
return __mod__int__(x_91, y_93);
}
} __mod___89;

struct __pow___97_local  : public PyObject {
PyInt* __pow__(PyInt* x_99, PyInt* y_101)
{
return __pow__int__(x_99, y_101);
}
} __pow___97;

struct __neg___104_local  : public PyObject {
PyInt* __neg__(PyInt* x_106)
{
return __neg__int__(x_106);
}
} __neg___104;

struct __pos___109_local  : public PyObject {
PyInt* __pos__(PyInt* x_111)
{
return __pos__int__(x_111);
}
} __pos___109;

struct __lt___115_local  : public PyObject {
PyBool* __lt__(PyInt* x_117, PyInt* y_119)
{
return __lt__int__(x_117, y_119);
}
} __lt___115;

struct __gt___123_local  : public PyObject {
PyBool* __gt__(PyInt* x_125, PyInt* y_127)
{
return __gt__int__(x_125, y_127);
}
} __gt___123;

struct __le___131_local  : public PyObject {
PyBool* __le__(PyInt* x_133, PyInt* y_135)
{
return __le__int__(x_133, y_135);
}
} __le___131;

struct __ge___139_local  : public PyObject {
PyBool* __ge__(PyInt* x_141, PyInt* y_143)
{
return __ge__int__(x_141, y_143);
}
} __ge___139;

struct __eq___147_local  : public PyObject {
PyBool* __eq__(PyInt* x_149, PyInt* y_151)
{
return __eq__int__(x_149, y_151);
}
} __eq___147;

struct __ne___155_local  : public PyObject {
PyBool* __ne__(PyInt* x_157, PyInt* y_159)
{
return __ne__int__(x_157, y_159);
}
} __ne___155;

struct toint_162_local  : public PyObject {
PyInt* toint_162(PyStr* x_164)
{
return __toint__str__(x_164);
}
} toint_162;

struct __add___168_local  : public PyObject {
PyStr* __add__(PyStr* x_170, PyStr* y_172)
{
return __add__str__(x_170, y_172);
}
} __add___168;

struct __mul___176_local  : public PyObject {
PyStr* __mul__(PyStr* x_178, PyInt* y_180)
{
return __lmul__str__(x_178, y_180);
}
} __mul___176;

struct __mul___184_local  : public PyObject {
PyStr* __mul__(PyInt* x_186, PyStr* y_188)
{
return __rmul__str__(x_186, y_188);
}
} __mul___184;

struct __lt___192_local  : public PyObject {
PyBool* __lt__(PyStr* x_194, PyStr* y_196)
{
return __lt__str__(x_194, y_196);
}
} __lt___192;

struct __gt___200_local  : public PyObject {
PyBool* __gt__(PyStr* x_202, PyStr* y_204)
{
return __gt__str__(x_202, y_204);
}
} __gt___200;

struct __le___208_local  : public PyObject {
PyBool* __le__(PyStr* x_210, PyStr* y_212)
{
return __le__str__(x_210, y_212);
}
} __le___208;

struct __ge___216_local  : public PyObject {
PyBool* __ge__(PyStr* x_218, PyStr* y_220)
{
return __ge__str__(x_218, y_220);
}
} __ge___216;

struct __eq___224_local  : public PyObject {
PyBool* __eq__(PyStr* x_226, PyStr* y_228)
{
return __eq__str__(x_226, y_228);
}
} __eq___224;

struct __ne___232_local  : public PyObject {
PyBool* __ne__(PyStr* x_234, PyStr* y_236)
{
return __ne__str__(x_234, y_236);
}
} __ne___232;

struct __getitem___240_local  : public PyObject {
PyStr* __getitem__(PyStr* S_242, PyInt* k_244)
{
return __getitem__str__(S_242, k_244);
}
} __getitem___240;

struct __getslice___249_local  : public PyObject {
PyStr* __getslice__(PyStr* S_251, PyInt* L_253, PyInt* U_255)
{
return __getslice__str__(S_251, L_253, U_255);
}
} __getslice___249;

struct len_258_local  : public PyObject {
PyInt* len_258(PyStr* S_260)
{
return __len__str__(S_260);
}
} len_258;

struct tostr_263_local  : public PyObject {
PyStr* tostr_263(PyValue x_265)
{
return __tostr__(x_265);
}
} tostr_263;

struct __getitem___269_local  : public PyObject {
PyValue __getitem__(PyList* S_271, PyInt* k_273)
{
return __getitem__list__(S_271, k_273);
}
} __getitem___269;

struct __getslice___279_local  : public PyObject {
PyList* __getslice__(PyList* S_281, PyInt* L_283, PyInt* U_285)
{
return __getslice__list__(S_281, L_283, U_285);
}
} __getslice___279;

struct __setitem___291_local  : public PyObject {
PyValue __setitem__(PyList* S_293, PyInt* k_295, PyValue val_297)
{
return __setitem__list__(S_293, k_295, val_297);
}
} __setitem___291;

struct __setslice___304_local  : public PyObject {
PyList* __setslice__(PyList* S_306, PyInt* a_308, PyInt* b_310, PyList* val_312)
{
return __setslice__list__(S_306, a_308, b_310, val_312);
}
} __setslice___304;

struct len_316_local  : public PyObject {
PyInt* len_316(PyList* S_318)
{
return __len__list__(S_318);
}
} len_316;

struct argv_321_local  : public PyObject {
PyList* argv_321()
{
return __argv__();
}
} argv_321;

struct readline_323_local  : public PyObject {
PyStr* readline_323()
{
return __readline__();
}
} readline_323;

struct read_325_local  : public PyObject {
PyStr* read_325()
{
return __read__();
}
} read_325;

struct __getitem___329_local  : public PyObject {
PyValue __getitem__(PyDictInt* D_331, PyInt* x_333)
{
return __getitem__dict__(D_331, x_333);
}
} __getitem___329;

struct __getitem___338_local  : public PyObject {
PyValue __getitem__(PyDictBool* D_340, PyBool* x_342)
{
return __getitem__dict__(D_340, x_342);
}
} __getitem___338;

struct __getitem___347_local  : public PyObject {
PyValue __getitem__(PyDictStr* D_349, PyStr* x_351)
{
return __getitem__dict__(D_349, x_351);
}
} __getitem___347;

struct __setitem___357_local  : public PyObject {
PyValue __setitem__(PyDictInt* S_359, PyInt* k_361, PyValue val_363)
{
return __setitem__dict__(S_359, k_361, val_363);
}
} __setitem___357;

struct __setitem___369_local  : public PyObject {
PyValue __setitem__(PyDictBool* S_371, PyBool* k_373, PyValue val_375)
{
return __setitem__dict__(S_371, k_373, val_375);
}
} __setitem___369;

struct __setitem___381_local  : public PyObject {
PyValue __setitem__(PyDictStr* S_383, PyStr* k_385, PyValue val_387)
{
return __setitem__dict__(S_383, k_385, val_387);
}
} __setitem___381;

struct len_391_local  : public PyObject {
PyInt* len_391(PyDictInt* D_393)
{
return __len__dict__(D_393);
}
} len_391;

struct len_397_local  : public PyObject {
PyInt* len_397(PyDictBool* D_399)
{
return __len__dict__(D_399);
}
} len_397;

struct len_403_local  : public PyObject {
PyInt* len_403(PyDictStr* D_405)
{
return __len__dict__(D_405);
}
} len_403;

struct __in___410_local  : public PyObject {
PyBool* __in__(PyInt* x_412, PyDictInt* D_414)
{
return __contains__dict__(x_412, D_414);
}
} __in___410;

struct __in___419_local  : public PyObject {
PyBool* __in__(PyBool* x_421, PyDictBool* D_423)
{
return __contains__dict__(x_421, D_423);
}
} __in___419;

struct __in___428_local  : public PyObject {
PyBool* __in__(PyStr* x_430, PyDictStr* D_432)
{
return __contains__dict__(x_430, D_432);
}
} __in___428;

struct __notin___437_local  : public PyObject {
PyBool* __notin__(PyInt* x_439, PyDictInt* D_441)
{
return __notcontains__dict__(x_439, D_441);
}
} __notin___437;

struct __notin___446_local  : public PyObject {
PyBool* __notin__(PyBool* x_448, PyDictBool* D_450)
{
return __notcontains__dict__(x_448, D_450);
}
} __notin___446;

struct __notin___455_local  : public PyObject {
PyBool* __notin__(PyStr* x_457, PyDictStr* D_459)
{
return __notcontains__dict__(x_457, D_459);
}
} __notin___455;

struct __is___464_local  : public PyObject {
PyBool* __is__(PyValue x_466, PyValue y_468)
{
return __is_bool__(x_466, y_468);
}
} __is___464;

struct __isnot___472_local  : public PyObject {
PyBool* __isnot__(PyValue x_474, PyValue y_476)
{
return __isnot_bool__(x_474, y_476);
}
} __isnot___472;

struct make_adder_479_local  : public PyObject {
PyValue make_adder_479(PyValue x_481)
{
struct adder_484_local  : public PyObject {
PyValue adder_484(PyValue y_486)
{
return y_486;
}
} adder_484;

return adder_484;
}
} make_adder_479;

PyValue a_488;
void
__main__()
{
a_488 = make_adder_479.make_adder_479(__cons_int__ (5));
__print__(1, a_488.a_488(__cons_int__ (10)));
__newline__();

}
