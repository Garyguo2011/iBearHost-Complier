#include "runtime.h"
int count_loop; //For keep tracking else stmt belongs to loop.
PyValue x_31;
PyValue x_36;
PyInt* low_42;
PyInt* high_44;
PyRange* r_49;
PyInt* x_55;
PyInt* y_57;
PyInt* x_63;
PyInt* y_65;
PyInt* x_71;
PyInt* y_73;
PyInt* x_79;
PyInt* y_81;
PyInt* x_87;
PyInt* y_89;
PyInt* x_95;
PyInt* y_97;
PyInt* x_102;
PyInt* x_107;
PyInt* x_113;
PyInt* y_115;
PyInt* x_121;
PyInt* y_123;
PyInt* x_129;
PyInt* y_131;
PyInt* x_137;
PyInt* y_139;
PyInt* x_145;
PyInt* y_147;
PyInt* x_153;
PyInt* y_155;
PyStr* x_160;
PyStr* x_166;
PyStr* y_168;
PyStr* x_174;
PyInt* y_176;
PyInt* x_182;
PyStr* y_184;
PyStr* x_190;
PyStr* y_192;
PyStr* x_198;
PyStr* y_200;
PyStr* x_206;
PyStr* y_208;
PyStr* x_214;
PyStr* y_216;
PyStr* x_222;
PyStr* y_224;
PyStr* x_230;
PyStr* y_232;
PyStr* S_238;
PyInt* k_240;
PyStr* S_247;
PyInt* L_249;
PyInt* U_251;
PyStr* S_256;
PyValue x_261;
PyList* S_267;
PyInt* k_269;
PyList* S_277;
PyInt* L_279;
PyInt* U_281;
PyList* S_289;
PyInt* k_291;
PyValue val_293;
PyList* S_302;
PyInt* a_304;
PyInt* b_306;
PyList* val_308;
PyList* S_314;
PyDictInt* D_327;
PyInt* x_329;
PyDictBool* D_336;
PyBool* x_338;
PyDictStr* D_345;
PyStr* x_347;
PyDictInt* S_355;
PyInt* k_357;
PyValue val_359;
PyDictBool* S_367;
PyBool* k_369;
PyValue val_371;
PyDictStr* S_379;
PyStr* k_381;
PyValue val_383;
PyDictInt* D_389;
PyDictBool* D_395;
PyDictStr* D_401;
PyInt* x_408;
PyDictInt* D_410;
PyBool* x_417;
PyDictBool* D_419;
PyStr* x_426;
PyDictStr* D_428;
PyInt* x_435;
PyDictInt* D_437;
PyBool* x_444;
PyDictBool* D_446;
PyStr* x_453;
PyDictStr* D_455;
PyValue x_462;
PyValue y_464;
PyValue x_470;
PyValue y_472;
struct truth_29_local  : public PyObject {
PyBool* truth_29(PyValue x_31_param)
{
x_31 = x_31_param;
return __truth__(x_31);
}
} truth_29;

struct __not___34_local  : public PyObject {
PyBool* __not__(PyValue x_36_param)
{
x_36 = x_36_param;
return __not_bool__(x_36);
}
} __not___34;

struct xrange_40_local  : public PyObject {
PyRange* xrange_40(PyInt* low_42_param, PyInt* high_44_param)
{
low_42 = low_42_param;
high_44 = high_44_param;
return __xrange__(low_42, high_44);
}
} xrange_40;

struct len_47_local  : public PyObject {
PyInt* len_47(PyRange* r_49_param)
{
r_49 = r_49_param;
return __len__range__(r_49);
}
} len_47;

struct __add___53_local  : public PyObject {
PyInt* __add__(PyInt* x_55_param, PyInt* y_57_param)
{
x_55 = x_55_param;
y_57 = y_57_param;
return __add__int__(x_55, y_57);
}
} __add___53;

struct __sub___61_local  : public PyObject {
PyInt* __sub__(PyInt* x_63_param, PyInt* y_65_param)
{
x_63 = x_63_param;
y_65 = y_65_param;
return __sub__int__(x_63, y_65);
}
} __sub___61;

struct __mul___69_local  : public PyObject {
PyInt* __mul__(PyInt* x_71_param, PyInt* y_73_param)
{
x_71 = x_71_param;
y_73 = y_73_param;
return __mul__int__(x_71, y_73);
}
} __mul___69;

struct __floordiv___77_local  : public PyObject {
PyInt* __floordiv__(PyInt* x_79_param, PyInt* y_81_param)
{
x_79 = x_79_param;
y_81 = y_81_param;
return __floordiv__int__(x_79, y_81);
}
} __floordiv___77;

struct __mod___85_local  : public PyObject {
PyInt* __mod__(PyInt* x_87_param, PyInt* y_89_param)
{
x_87 = x_87_param;
y_89 = y_89_param;
return __mod__int__(x_87, y_89);
}
} __mod___85;

struct __pow___93_local  : public PyObject {
PyInt* __pow__(PyInt* x_95_param, PyInt* y_97_param)
{
x_95 = x_95_param;
y_97 = y_97_param;
return __pow__int__(x_95, y_97);
}
} __pow___93;

struct __neg___100_local  : public PyObject {
PyInt* __neg__(PyInt* x_102_param)
{
x_102 = x_102_param;
return __neg__int__(x_102);
}
} __neg___100;

struct __pos___105_local  : public PyObject {
PyInt* __pos__(PyInt* x_107_param)
{
x_107 = x_107_param;
return __pos__int__(x_107);
}
} __pos___105;

struct __lt___111_local  : public PyObject {
PyBool* __lt__(PyInt* x_113_param, PyInt* y_115_param)
{
x_113 = x_113_param;
y_115 = y_115_param;
return __lt__int__(x_113, y_115);
}
} __lt___111;

struct __gt___119_local  : public PyObject {
PyBool* __gt__(PyInt* x_121_param, PyInt* y_123_param)
{
x_121 = x_121_param;
y_123 = y_123_param;
return __gt__int__(x_121, y_123);
}
} __gt___119;

struct __le___127_local  : public PyObject {
PyBool* __le__(PyInt* x_129_param, PyInt* y_131_param)
{
x_129 = x_129_param;
y_131 = y_131_param;
return __le__int__(x_129, y_131);
}
} __le___127;

struct __ge___135_local  : public PyObject {
PyBool* __ge__(PyInt* x_137_param, PyInt* y_139_param)
{
x_137 = x_137_param;
y_139 = y_139_param;
return __ge__int__(x_137, y_139);
}
} __ge___135;

struct __eq___143_local  : public PyObject {
PyBool* __eq__(PyInt* x_145_param, PyInt* y_147_param)
{
x_145 = x_145_param;
y_147 = y_147_param;
return __eq__int__(x_145, y_147);
}
} __eq___143;

struct __ne___151_local  : public PyObject {
PyBool* __ne__(PyInt* x_153_param, PyInt* y_155_param)
{
x_153 = x_153_param;
y_155 = y_155_param;
return __ne__int__(x_153, y_155);
}
} __ne___151;

struct toint_158_local  : public PyObject {
PyInt* toint_158(PyStr* x_160_param)
{
x_160 = x_160_param;
return __toint__str__(x_160);
}
} toint_158;

struct __add___164_local  : public PyObject {
PyStr* __add__(PyStr* x_166_param, PyStr* y_168_param)
{
x_166 = x_166_param;
y_168 = y_168_param;
return __add__str__(x_166, y_168);
}
} __add___164;

struct __mul___172_local  : public PyObject {
PyStr* __mul__(PyStr* x_174_param, PyInt* y_176_param)
{
x_174 = x_174_param;
y_176 = y_176_param;
return __lmul__str__(x_174, y_176);
}
} __mul___172;

struct __mul___180_local  : public PyObject {
PyStr* __mul__(PyInt* x_182_param, PyStr* y_184_param)
{
x_182 = x_182_param;
y_184 = y_184_param;
return __rmul__str__(x_182, y_184);
}
} __mul___180;

struct __lt___188_local  : public PyObject {
PyBool* __lt__(PyStr* x_190_param, PyStr* y_192_param)
{
x_190 = x_190_param;
y_192 = y_192_param;
return __lt__str__(x_190, y_192);
}
} __lt___188;

struct __gt___196_local  : public PyObject {
PyBool* __gt__(PyStr* x_198_param, PyStr* y_200_param)
{
x_198 = x_198_param;
y_200 = y_200_param;
return __gt__str__(x_198, y_200);
}
} __gt___196;

struct __le___204_local  : public PyObject {
PyBool* __le__(PyStr* x_206_param, PyStr* y_208_param)
{
x_206 = x_206_param;
y_208 = y_208_param;
return __le__str__(x_206, y_208);
}
} __le___204;

struct __ge___212_local  : public PyObject {
PyBool* __ge__(PyStr* x_214_param, PyStr* y_216_param)
{
x_214 = x_214_param;
y_216 = y_216_param;
return __ge__str__(x_214, y_216);
}
} __ge___212;

struct __eq___220_local  : public PyObject {
PyBool* __eq__(PyStr* x_222_param, PyStr* y_224_param)
{
x_222 = x_222_param;
y_224 = y_224_param;
return __eq__str__(x_222, y_224);
}
} __eq___220;

struct __ne___228_local  : public PyObject {
PyBool* __ne__(PyStr* x_230_param, PyStr* y_232_param)
{
x_230 = x_230_param;
y_232 = y_232_param;
return __ne__str__(x_230, y_232);
}
} __ne___228;

struct __getitem___236_local  : public PyObject {
PyStr* __getitem__(PyStr* S_238_param, PyInt* k_240_param)
{
S_238 = S_238_param;
k_240 = k_240_param;
return __getitem__str__(S_238, k_240);
}
} __getitem___236;

struct __getslice___245_local  : public PyObject {
PyStr* __getslice__(PyStr* S_247_param, PyInt* L_249_param, PyInt* U_251_param)
{
S_247 = S_247_param;
L_249 = L_249_param;
U_251 = U_251_param;
return __getslice__str__(S_247, L_249, U_251);
}
} __getslice___245;

struct len_254_local  : public PyObject {
PyInt* len_254(PyStr* S_256_param)
{
S_256 = S_256_param;
return __len__str__(S_256);
}
} len_254;

struct tostr_259_local  : public PyObject {
PyStr* tostr_259(PyValue x_261_param)
{
x_261 = x_261_param;
return __tostr__(x_261);
}
} tostr_259;

struct __getitem___265_local  : public PyObject {
PyValue __getitem__(PyList* S_267_param, PyInt* k_269_param)
{
S_267 = S_267_param;
k_269 = k_269_param;
return __getitem__list__(S_267, k_269);
}
} __getitem___265;

struct __getslice___275_local  : public PyObject {
PyList* __getslice__(PyList* S_277_param, PyInt* L_279_param, PyInt* U_281_param)
{
S_277 = S_277_param;
L_279 = L_279_param;
U_281 = U_281_param;
return __getslice__list__(S_277, L_279, U_281);
}
} __getslice___275;

struct __setitem___287_local  : public PyObject {
PyValue __setitem__(PyList* S_289_param, PyInt* k_291_param, PyValue val_293_param)
{
S_289 = S_289_param;
k_291 = k_291_param;
val_293 = val_293_param;
return __setitem__list__(S_289, k_291, val_293);
}
} __setitem___287;

struct __setslice___300_local  : public PyObject {
PyList* __setslice__(PyList* S_302_param, PyInt* a_304_param, PyInt* b_306_param, PyList* val_308_param)
{
S_302 = S_302_param;
a_304 = a_304_param;
b_306 = b_306_param;
val_308 = val_308_param;
return __setslice__list__(S_302, a_304, b_306, val_308);
}
} __setslice___300;

struct len_312_local  : public PyObject {
PyInt* len_312(PyList* S_314_param)
{
S_314 = S_314_param;
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
PyValue __getitem__(PyDictInt* D_327_param, PyInt* x_329_param)
{
D_327 = D_327_param;
x_329 = x_329_param;
return __getitem__dict__(D_327, x_329);
}
} __getitem___325;

struct __getitem___334_local  : public PyObject {
PyValue __getitem__(PyDictBool* D_336_param, PyBool* x_338_param)
{
D_336 = D_336_param;
x_338 = x_338_param;
return __getitem__dict__(D_336, x_338);
}
} __getitem___334;

struct __getitem___343_local  : public PyObject {
PyValue __getitem__(PyDictStr* D_345_param, PyStr* x_347_param)
{
D_345 = D_345_param;
x_347 = x_347_param;
return __getitem__dict__(D_345, x_347);
}
} __getitem___343;

struct __setitem___353_local  : public PyObject {
PyValue __setitem__(PyDictInt* S_355_param, PyInt* k_357_param, PyValue val_359_param)
{
S_355 = S_355_param;
k_357 = k_357_param;
val_359 = val_359_param;
return __setitem__dict__(S_355, k_357, val_359);
}
} __setitem___353;

struct __setitem___365_local  : public PyObject {
PyValue __setitem__(PyDictBool* S_367_param, PyBool* k_369_param, PyValue val_371_param)
{
S_367 = S_367_param;
k_369 = k_369_param;
val_371 = val_371_param;
return __setitem__dict__(S_367, k_369, val_371);
}
} __setitem___365;

struct __setitem___377_local  : public PyObject {
PyValue __setitem__(PyDictStr* S_379_param, PyStr* k_381_param, PyValue val_383_param)
{
S_379 = S_379_param;
k_381 = k_381_param;
val_383 = val_383_param;
return __setitem__dict__(S_379, k_381, val_383);
}
} __setitem___377;

struct len_387_local  : public PyObject {
PyInt* len_387(PyDictInt* D_389_param)
{
D_389 = D_389_param;
return __len__dict__(D_389);
}
} len_387;

struct len_393_local  : public PyObject {
PyInt* len_393(PyDictBool* D_395_param)
{
D_395 = D_395_param;
return __len__dict__(D_395);
}
} len_393;

struct len_399_local  : public PyObject {
PyInt* len_399(PyDictStr* D_401_param)
{
D_401 = D_401_param;
return __len__dict__(D_401);
}
} len_399;

struct __in___406_local  : public PyObject {
PyBool* __in__(PyInt* x_408_param, PyDictInt* D_410_param)
{
x_408 = x_408_param;
D_410 = D_410_param;
return __contains__dict__(x_408, D_410);
}
} __in___406;

struct __in___415_local  : public PyObject {
PyBool* __in__(PyBool* x_417_param, PyDictBool* D_419_param)
{
x_417 = x_417_param;
D_419 = D_419_param;
return __contains__dict__(x_417, D_419);
}
} __in___415;

struct __in___424_local  : public PyObject {
PyBool* __in__(PyStr* x_426_param, PyDictStr* D_428_param)
{
x_426 = x_426_param;
D_428 = D_428_param;
return __contains__dict__(x_426, D_428);
}
} __in___424;

struct __notin___433_local  : public PyObject {
PyBool* __notin__(PyInt* x_435_param, PyDictInt* D_437_param)
{
x_435 = x_435_param;
D_437 = D_437_param;
return __notcontains__dict__(x_435, D_437);
}
} __notin___433;

struct __notin___442_local  : public PyObject {
PyBool* __notin__(PyBool* x_444_param, PyDictBool* D_446_param)
{
x_444 = x_444_param;
D_446 = D_446_param;
return __notcontains__dict__(x_444, D_446);
}
} __notin___442;

struct __notin___451_local  : public PyObject {
PyBool* __notin__(PyStr* x_453_param, PyDictStr* D_455_param)
{
x_453 = x_453_param;
D_455 = D_455_param;
return __notcontains__dict__(x_453, D_455);
}
} __notin___451;

struct __is___460_local  : public PyObject {
PyBool* __is__(PyValue x_462_param, PyValue y_464_param)
{
x_462 = x_462_param;
y_464 = y_464_param;
return __is_bool__(x_462, y_464);
}
} __is___460;

struct __isnot___468_local  : public PyObject {
PyBool* __isnot__(PyValue x_470_param, PyValue y_472_param)
{
x_470 = x_470_param;
y_472 = y_472_param;
return __isnot_bool__(x_470, y_472);
}
} __isnot___468;

PyList* L_474;
PyDictStr* D_483;
void
__main__()
{
L_474 = __cons_list__(5, __cons_tuple2__(__cons_str__ ("chicken"), __cons_str__ ("chick")), __cons_tuple2__(__cons_str__ ("goose"), __cons_str__ ("gosling")), __cons_tuple2__(__cons_str__ ("duck"), __cons_str__ ("duckling")), __cons_tuple2__(__cons_str__ ("cow"), __cons_str__ ("calf")), __cons_tuple2__(__cons_str__ ("horse"), __cons_str__ ("colt")));
D_483 = __cons_dictstr__(1, __cons_pair__(__cons_str__ ("dog"), __cons_str__ (" puppy")));
PyTuple2* d_487;
count_loop = 0;
for (int index_487 = 0; index_487 < L_474->getSize(); index_487++) {
d_487 = (PyTuple2*) L_474->get(index_487);
__print__(1, __cons_int__ (1));
__newline__();
}
count_loop = 0;
PyStr* animal_496;
PyStr* child_498;
count_loop = 0;
for (int index_496 = 0; index_496 < L_474->getSize(); index_496++) {
animal_496 = (PyStr*) L_474->get(index_496)->get(0);
child_498 = (PyStr*) L_474->get(index_496)->get(1);
__print__(1, animal_496);
__newline__();
__print__(1, child_498);
__newline__();
}
count_loop = 0;

free(str_8);
free(int_9);
free(bool_10);
free(range_11);
free(list_12);
free(dict_14);
free(tuple0_17);
free(tuple1_18);
free(tuple2_20);
free(tuple3_23);
free(truth_29);
free(x_31);
free(bool_10);
free(__not__);
free(x_36);
free(bool_10);
free(xrange_40);
free(low_42);
free(high_44);
free(range_11);
free(len_47);
free(r_49);
free(int_9);
free(__add__);
free(x_55);
free(y_57);
free(int_9);
free(__sub__);
free(x_63);
free(y_65);
free(int_9);
free(__mul__);
free(x_71);
free(y_73);
free(int_9);
free(__floordiv__);
free(x_79);
free(y_81);
free(int_9);
free(__mod__);
free(x_87);
free(y_89);
free(int_9);
free(__pow__);
free(x_95);
free(y_97);
free(int_9);
free(__neg__);
free(x_102);
free(int_9);
free(__pos__);
free(x_107);
free(int_9);
free(__lt__);
free(x_113);
free(y_115);
free(bool_10);
free(__gt__);
free(x_121);
free(y_123);
free(bool_10);
free(__le__);
free(x_129);
free(y_131);
free(bool_10);
free(__ge__);
free(x_137);
free(y_139);
free(bool_10);
free(__eq__);
free(x_145);
free(y_147);
free(bool_10);
free(__ne__);
free(x_153);
free(y_155);
free(bool_10);
free(toint_158);
free(x_160);
free(int_9);
free(__add__);
free(x_166);
free(y_168);
free(str_8);
free(__mul__);
free(x_174);
free(y_176);
free(str_8);
free(__mul__);
free(x_182);
free(y_184);
free(str_8);
free(__lt__);
free(x_190);
free(y_192);
free(bool_10);
free(__gt__);
free(x_198);
free(y_200);
free(bool_10);
free(__le__);
free(x_206);
free(y_208);
free(bool_10);
free(__ge__);
free(x_214);
free(y_216);
free(bool_10);
free(__eq__);
free(x_222);
free(y_224);
free(bool_10);
free(__ne__);
free(x_230);
free(y_232);
free(bool_10);
free(__getitem__);
free(S_238);
free(k_240);
free(str_8);
free(__getslice__);
free(S_247);
free(L_249);
free(U_251);
free(str_8);
free(len_254);
free(S_256);
free(int_9);
free(tostr_259);
free(x_261);
free(str_8);
free(__getitem__);
free(S_267);
free(k_269);
free(__getslice__);
free(S_277);
free(L_279);
free(U_281);
free(list_12);
free(__setitem__);
free(S_289);
free(k_291);
free(val_293);
free(__setslice__);
free(S_302);
free(a_304);
free(b_306);
free(val_308);
free(list_12);
free(len_312);
free(S_314);
free(int_9);
free(argv_317);
free(list_12);
free(str_8);
free(readline_319);
free(str_8);
free(read_321);
free(str_8);
free(__getitem__);
free(D_327);
free(x_329);
free(__getitem__);
free(D_336);
free(x_338);
free(__getitem__);
free(D_345);
free(x_347);
free(__setitem__);
free(S_355);
free(k_357);
free(val_359);
free(__setitem__);
free(S_367);
free(k_369);
free(val_371);
free(__setitem__);
free(S_379);
free(k_381);
free(val_383);
free(len_387);
free(D_389);
free(int_9);
free(len_393);
free(D_395);
free(int_9);
free(len_399);
free(D_401);
free(int_9);
free(__in__);
free(x_408);
free(D_410);
free(bool_10);
free(__in__);
free(x_417);
free(D_419);
free(bool_10);
free(__in__);
free(x_426);
free(D_428);
free(bool_10);
free(__notin__);
free(x_435);
free(D_437);
free(bool_10);
free(__notin__);
free(x_444);
free(D_446);
free(bool_10);
free(__notin__);
free(x_453);
free(D_455);
free(bool_10);
free(__is__);
free(x_462);
free(y_464);
free(bool_10);
free(__isnot__);
free(x_470);
free(y_472);
free(bool_10);
free(L_474);
free(D_483);
free(d_487);
free(L_474);
free(animal_496);
free(child_498);
free(L_474);
free(animal_496);
free(child_498);
}
