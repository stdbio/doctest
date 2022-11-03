#include <doctest/doctest.h>

#include <cstdio>


#ifndef TEST_FLIP
#define TEST_FLIP 0
#endif

#define TEST_FAIL() printf("FAILED ON: %d (%s)\n", \
     __LINE__, TEST_FLIP ? "EVALUATED" : "DISABLED")

static int test_disabled_var_ = [] {
    // none may return true
    if (TEST_FLIP ^ CHECK(0 == 0)) { TEST_FAIL(); }
    if (TEST_FLIP ^ CHECK_FALSE(0 != 0)) { TEST_FAIL(); }
    if (TEST_FLIP ^ CHECK_EQ(0, 0)) { TEST_FAIL(); }
    if (TEST_FLIP ^ CHECK_UNARY(true)) { TEST_FAIL(); }
    if (TEST_FLIP ^ CHECK_UNARY_FALSE(false)) { TEST_FAIL(); }
#ifndef DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
    if (TEST_FLIP ^ CHECK_THROWS([] { throw 2; }())) { TEST_FAIL(); }
    if (TEST_FLIP ^ CHECK_THROWS_AS([] { throw 2; }(), int)) { TEST_FAIL(); }
    if (TEST_FLIP ^ CHECK_NOTHROW([]{ }())) { TEST_FAIL(); }
    if (CHECK_THROWS_WITH([] { throw 2; }(), "2")) { TEST_FAIL(); }
#endif

    return 0;
}();
