#include "runtime.h"
int count_loop; //For keep tracking else stmt belongs to loop.
PyValue x_33;
PyValue x_38;
PyInt* low_44;
PyInt* high_46;
PyRange* r_51;
PyInt* x_57;
PyInt* y_59;
PyInt* x_65;
PyInt* y_67;
PyInt* x_73;
PyInt* y_75;
PyInt* x_81;
PyInt* y_83;
PyInt* x_89;
PyInt* y_91;
PyInt* x_97;
PyInt* y_99;
PyInt* x_104;
PyInt* x_109;
PyInt* x_115;
PyInt* y_117;
PyInt* x_123;
PyInt* y_125;
PyInt* x_131;
PyInt* y_133;
PyInt* x_139;
PyInt* y_141;
PyInt* x_147;
PyInt* y_149;
PyInt* x_155;
PyInt* y_157;
PyStr* x_162;
PyStr* x_168;
PyStr* y_170;
PyStr* x_176;
PyInt* y_178;
PyInt* x_184;
PyStr* y_186;
PyStr* x_192;
PyStr* y_194;
PyStr* x_200;
PyStr* y_202;
PyStr* x_208;
PyStr* y_210;
PyStr* x_216;
PyStr* y_218;
PyStr* x_224;
PyStr* y_226;
PyStr* x_232;
PyStr* y_234;
PyStr* S_240;
PyInt* k_242;
PyStr* S_249;
PyInt* L_251;
PyInt* U_253;
PyStr* S_258;
PyValue x_263;
PyList* S_269;
PyInt* k_271;
PyList* S_279;
PyInt* L_281;
PyInt* U_283;
PyList* S_291;
PyInt* k_293;
PyValue val_295;
PyList* S_304;
PyInt* a_306;
PyInt* b_308;
PyList* val_310;
PyList* S_316;
PyDictInt* D_329;
PyInt* x_331;
PyDictBool* D_338;
PyBool* x_340;
PyDictStr* D_347;
PyStr* x_349;
PyDictInt* S_357;
PyInt* k_359;
PyValue val_361;
PyDictBool* S_369;
PyBool* k_371;
PyValue val_373;
PyDictStr* S_381;
PyStr* k_383;
PyValue val_385;
PyDictInt* D_391;
PyDictBool* D_397;
PyDictStr* D_403;
PyInt* x_410;
PyDictInt* D_412;
PyBool* x_419;
PyDictBool* D_421;
PyStr* x_428;
PyDictStr* D_430;
PyInt* x_437;
PyDictInt* D_439;
PyBool* x_446;
PyDictBool* D_448;
PyStr* x_455;
PyDictStr* D_457;
PyValue x_464;
PyValue y_466;
PyValue x_472;
PyValue y_474;
PyInt* n_479;
struct truth_31_local  : public PyObject {
PyBool* truth_31(PyValue x_33_param)
{
x_33 = x_33_param;
return __truth__(x_33);
}
} truth_31;

struct __not___36_local  : public PyObject {
PyBool* __not__(PyValue x_38_param)
{
x_38 = x_38_param;
return __not_bool__(x_38);
}
} __not___36;

struct xrange_42_local  : public PyObject {
PyRange* xrange_42(PyInt* low_44_param, PyInt* high_46_param)
{
low_44 = low_44_param;
high_46 = high_46_param;
return __xrange__(low_44, high_46);
}
} xrange_42;

struct len_49_local  : public PyObject {
PyInt* len_49(PyRange* r_51_param)
{
r_51 = r_51_param;
return __len__range__(r_51);
}
} len_49;

struct __add___55_local  : public PyObject {
PyInt* __add__(PyInt* x_57_param, PyInt* y_59_param)
{
x_57 = x_57_param;
y_59 = y_59_param;
return __add__int__(x_57, y_59);
}
} __add___55;

struct __sub___63_local  : public PyObject {
PyInt* __sub__(PyInt* x_65_param, PyInt* y_67_param)
{
x_65 = x_65_param;
y_67 = y_67_param;
return __sub__int__(x_65, y_67);
}
} __sub___63;

struct __mul___71_local  : public PyObject {
PyInt* __mul__(PyInt* x_73_param, PyInt* y_75_param)
{
x_73 = x_73_param;
y_75 = y_75_param;
return __mul__int__(x_73, y_75);
}
} __mul___71;

struct __floordiv___79_local  : public PyObject {
PyInt* __floordiv__(PyInt* x_81_param, PyInt* y_83_param)
{
x_81 = x_81_param;
y_83 = y_83_param;
return __floordiv__int__(x_81, y_83);
}
} __floordiv___79;

struct __mod___87_local  : public PyObject {
PyInt* __mod__(PyInt* x_89_param, PyInt* y_91_param)
{
x_89 = x_89_param;
y_91 = y_91_param;
return __mod__int__(x_89, y_91);
}
} __mod___87;

struct __pow___95_local  : public PyObject {
PyInt* __pow__(PyInt* x_97_param, PyInt* y_99_param)
{
x_97 = x_97_param;
y_99 = y_99_param;
return __pow__int__(x_97, y_99);
}
} __pow___95;

struct __neg___102_local  : public PyObject {
PyInt* __neg__(PyInt* x_104_param)
{
x_104 = x_104_param;
return __neg__int__(x_104);
}
} __neg___102;

struct __pos___107_local  : public PyObject {
PyInt* __pos__(PyInt* x_109_param)
{
x_109 = x_109_param;
return __pos__int__(x_109);
}
} __pos___107;

struct __lt___113_local  : public PyObject {
PyBool* __lt__(PyInt* x_115_param, PyInt* y_117_param)
{
x_115 = x_115_param;
y_117 = y_117_param;
return __lt__int__(x_115, y_117);
}
} __lt___113;

struct __gt___121_local  : public PyObject {
PyBool* __gt__(PyInt* x_123_param, PyInt* y_125_param)
{
x_123 = x_123_param;
y_125 = y_125_param;
return __gt__int__(x_123, y_125);
}
} __gt___121;

struct __le___129_local  : public PyObject {
PyBool* __le__(PyInt* x_131_param, PyInt* y_133_param)
{
x_131 = x_131_param;
y_133 = y_133_param;
return __le__int__(x_131, y_133);
}
} __le___129;

struct __ge___137_local  : public PyObject {
PyBool* __ge__(PyInt* x_139_param, PyInt* y_141_param)
{
x_139 = x_139_param;
y_141 = y_141_param;
return __ge__int__(x_139, y_141);
}
} __ge___137;

struct __eq___145_local  : public PyObject {
PyBool* __eq__(PyInt* x_147_param, PyInt* y_149_param)
{
x_147 = x_147_param;
y_149 = y_149_param;
return __eq__int__(x_147, y_149);
}
} __eq___145;

struct __ne___153_local  : public PyObject {
PyBool* __ne__(PyInt* x_155_param, PyInt* y_157_param)
{
x_155 = x_155_param;
y_157 = y_157_param;
return __ne__int__(x_155, y_157);
}
} __ne___153;

struct toint_160_local  : public PyObject {
PyInt* toint_160(PyStr* x_162_param)
{
x_162 = x_162_param;
return __toint__str__(x_162);
}
} toint_160;

struct __add___166_local  : public PyObject {
PyStr* __add__(PyStr* x_168_param, PyStr* y_170_param)
{
x_168 = x_168_param;
y_170 = y_170_param;
return __add__str__(x_168, y_170);
}
} __add___166;

struct __mul___174_local  : public PyObject {
PyStr* __mul__(PyStr* x_176_param, PyInt* y_178_param)
{
x_176 = x_176_param;
y_178 = y_178_param;
return __lmul__str__(x_176, y_178);
}
} __mul___174;

struct __mul___182_local  : public PyObject {
PyStr* __mul__(PyInt* x_184_param, PyStr* y_186_param)
{
x_184 = x_184_param;
y_186 = y_186_param;
return __rmul__str__(x_184, y_186);
}
} __mul___182;

struct __lt___190_local  : public PyObject {
PyBool* __lt__(PyStr* x_192_param, PyStr* y_194_param)
{
x_192 = x_192_param;
y_194 = y_194_param;
return __lt__str__(x_192, y_194);
}
} __lt___190;

struct __gt___198_local  : public PyObject {
PyBool* __gt__(PyStr* x_200_param, PyStr* y_202_param)
{
x_200 = x_200_param;
y_202 = y_202_param;
return __gt__str__(x_200, y_202);
}
} __gt___198;

struct __le___206_local  : public PyObject {
PyBool* __le__(PyStr* x_208_param, PyStr* y_210_param)
{
x_208 = x_208_param;
y_210 = y_210_param;
return __le__str__(x_208, y_210);
}
} __le___206;

struct __ge___214_local  : public PyObject {
PyBool* __ge__(PyStr* x_216_param, PyStr* y_218_param)
{
x_216 = x_216_param;
y_218 = y_218_param;
return __ge__str__(x_216, y_218);
}
} __ge___214;

struct __eq___222_local  : public PyObject {
PyBool* __eq__(PyStr* x_224_param, PyStr* y_226_param)
{
x_224 = x_224_param;
y_226 = y_226_param;
return __eq__str__(x_224, y_226);
}
} __eq___222;

struct __ne___230_local  : public PyObject {
PyBool* __ne__(PyStr* x_232_param, PyStr* y_234_param)
{
x_232 = x_232_param;
y_234 = y_234_param;
return __ne__str__(x_232, y_234);
}
} __ne___230;

struct __getitem___238_local  : public PyObject {
PyStr* __getitem__(PyStr* S_240_param, PyInt* k_242_param)
{
S_240 = S_240_param;
k_242 = k_242_param;
return __getitem__str__(S_240, k_242);
}
} __getitem___238;

struct __getslice___247_local  : public PyObject {
PyStr* __getslice__(PyStr* S_249_param, PyInt* L_251_param, PyInt* U_253_param)
{
S_249 = S_249_param;
L_251 = L_251_param;
U_253 = U_253_param;
return __getslice__str__(S_249, L_251, U_253);
}
} __getslice___247;

struct len_256_local  : public PyObject {
PyInt* len_256(PyStr* S_258_param)
{
S_258 = S_258_param;
return __len__str__(S_258);
}
} len_256;

struct tostr_261_local  : public PyObject {
PyStr* tostr_261(PyValue x_263_param)
{
x_263 = x_263_param;
return __tostr__(x_263);
}
} tostr_261;

struct __getitem___267_local  : public PyObject {
PyValue __getitem__(PyList* S_269_param, PyInt* k_271_param)
{
S_269 = S_269_param;
k_271 = k_271_param;
return __getitem__list__(S_269, k_271);
}
} __getitem___267;

struct __getslice___277_local  : public PyObject {
PyList* __getslice__(PyList* S_279_param, PyInt* L_281_param, PyInt* U_283_param)
{
S_279 = S_279_param;
L_281 = L_281_param;
U_283 = U_283_param;
return __getslice__list__(S_279, L_281, U_283);
}
} __getslice___277;

struct __setitem___289_local  : public PyObject {
PyValue __setitem__(PyList* S_291_param, PyInt* k_293_param, PyValue val_295_param)
{
S_291 = S_291_param;
k_293 = k_293_param;
val_295 = val_295_param;
return __setitem__list__(S_291, k_293, val_295);
}
} __setitem___289;

struct __setslice___302_local  : public PyObject {
PyList* __setslice__(PyList* S_304_param, PyInt* a_306_param, PyInt* b_308_param, PyList* val_310_param)
{
S_304 = S_304_param;
a_306 = a_306_param;
b_308 = b_308_param;
val_310 = val_310_param;
return __setslice__list__(S_304, a_306, b_308, val_310);
}
} __setslice___302;

struct len_314_local  : public PyObject {
PyInt* len_314(PyList* S_316_param)
{
S_316 = S_316_param;
return __len__list__(S_316);
}
} len_314;

struct argv_319_local  : public PyObject {
PyList* argv_319()
{
return __argv__();
}
} argv_319;

struct readline_321_local  : public PyObject {
PyStr* readline_321()
{
return __readline__();
}
} readline_321;

struct read_323_local  : public PyObject {
PyStr* read_323()
{
return __read__();
}
} read_323;

struct __getitem___327_local  : public PyObject {
PyValue __getitem__(PyDictInt* D_329_param, PyInt* x_331_param)
{
D_329 = D_329_param;
x_331 = x_331_param;
return __getitem__dict__(D_329, x_331);
}
} __getitem___327;

struct __getitem___336_local  : public PyObject {
PyValue __getitem__(PyDictBool* D_338_param, PyBool* x_340_param)
{
D_338 = D_338_param;
x_340 = x_340_param;
return __getitem__dict__(D_338, x_340);
}
} __getitem___336;

struct __getitem___345_local  : public PyObject {
PyValue __getitem__(PyDictStr* D_347_param, PyStr* x_349_param)
{
D_347 = D_347_param;
x_349 = x_349_param;
return __getitem__dict__(D_347, x_349);
}
} __getitem___345;

struct __setitem___355_local  : public PyObject {
PyValue __setitem__(PyDictInt* S_357_param, PyInt* k_359_param, PyValue val_361_param)
{
S_357 = S_357_param;
k_359 = k_359_param;
val_361 = val_361_param;
return __setitem__dict__(S_357, k_359, val_361);
}
} __setitem___355;

struct __setitem___367_local  : public PyObject {
PyValue __setitem__(PyDictBool* S_369_param, PyBool* k_371_param, PyValue val_373_param)
{
S_369 = S_369_param;
k_371 = k_371_param;
val_373 = val_373_param;
return __setitem__dict__(S_369, k_371, val_373);
}
} __setitem___367;

struct __setitem___379_local  : public PyObject {
PyValue __setitem__(PyDictStr* S_381_param, PyStr* k_383_param, PyValue val_385_param)
{
S_381 = S_381_param;
k_383 = k_383_param;
val_385 = val_385_param;
return __setitem__dict__(S_381, k_383, val_385);
}
} __setitem___379;

struct len_389_local  : public PyObject {
PyInt* len_389(PyDictInt* D_391_param)
{
D_391 = D_391_param;
return __len__dict__(D_391);
}
} len_389;

struct len_395_local  : public PyObject {
PyInt* len_395(PyDictBool* D_397_param)
{
D_397 = D_397_param;
return __len__dict__(D_397);
}
} len_395;

struct len_401_local  : public PyObject {
PyInt* len_401(PyDictStr* D_403_param)
{
D_403 = D_403_param;
return __len__dict__(D_403);
}
} len_401;

struct __in___408_local  : public PyObject {
PyBool* __in__(PyInt* x_410_param, PyDictInt* D_412_param)
{
x_410 = x_410_param;
D_412 = D_412_param;
return __contains__dict__(x_410, D_412);
}
} __in___408;

struct __in___417_local  : public PyObject {
PyBool* __in__(PyBool* x_419_param, PyDictBool* D_421_param)
{
x_419 = x_419_param;
D_421 = D_421_param;
return __contains__dict__(x_419, D_421);
}
} __in___417;

struct __in___426_local  : public PyObject {
PyBool* __in__(PyStr* x_428_param, PyDictStr* D_430_param)
{
x_428 = x_428_param;
D_430 = D_430_param;
return __contains__dict__(x_428, D_430);
}
} __in___426;

struct __notin___435_local  : public PyObject {
PyBool* __notin__(PyInt* x_437_param, PyDictInt* D_439_param)
{
x_437 = x_437_param;
D_439 = D_439_param;
return __notcontains__dict__(x_437, D_439);
}
} __notin___435;

struct __notin___444_local  : public PyObject {
PyBool* __notin__(PyBool* x_446_param, PyDictBool* D_448_param)
{
x_446 = x_446_param;
D_448 = D_448_param;
return __notcontains__dict__(x_446, D_448);
}
} __notin___444;

struct __notin___453_local  : public PyObject {
PyBool* __notin__(PyStr* x_455_param, PyDictStr* D_457_param)
{
x_455 = x_455_param;
D_457 = D_457_param;
return __notcontains__dict__(x_455, D_457);
}
} __notin___453;

struct __is___462_local  : public PyObject {
PyBool* __is__(PyValue x_464_param, PyValue y_466_param)
{
x_464 = x_464_param;
y_466 = y_466_param;
return __is_bool__(x_464, y_466);
}
} __is___462;

struct __isnot___470_local  : public PyObject {
PyBool* __isnot__(PyValue x_472_param, PyValue y_474_param)
{
x_472 = x_472_param;
y_474 = y_474_param;
return __isnot_bool__(x_472, y_474);
}
} __isnot___470;

struct fib_477_local  : public PyObject {
PyInt* fib_477(PyInt* n_479_param)
{
n_479 = n_479_param;
if (__eval_bool__((__lt___113.__lt__(n_479, __cons_int__ (2))))) {
return n_479;
}
return __add___55.__add__(fib_477(__sub___63.__sub__(n_479_param, __cons_int__ (2))), fib_477(__sub___63.__sub__(n_479_param, __cons_int__ (1))));
}
} fib_477;

void
__main__()
{
PyInt* i_488;
count_loop = 0;
for (int index_488 = 0; index_488 < xrange_42.xrange_42(__cons_int__ (0), __cons_int__ (7))->getSize(); index_488++) {
i_488 = (PyInt*) xrange_42.xrange_42(__cons_int__ (0), __cons_int__ (7))->get(index_488);
__print__(1, fib_477.fib_477(i_488));
__newline__();
}
count_loop = 0;

}
