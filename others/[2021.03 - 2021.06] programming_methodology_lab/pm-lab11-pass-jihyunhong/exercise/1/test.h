#ifndef TEST_H_
#define TEST_H_

#include <iostream>
#include <type_traits>

void TEST();

// intentionally written in cryptic way
using ta = decltype(1);
using tb = ta*;
using tc = tb*;
using td = ta&;
using te = tb&;
using va = void (ta, ta);
using vb = void (tb, tb);
using vc = void (tc, tc);
using vd = void (td, td);
using ve = void (te, te);

#endif // TEST_H_
