#include <cgreen/cgreen.h>

Describe(Foo);
BeforeEach(Foo);
AfterEach(Foo);

Ensure(Foo, it_finds_and_runs_the_test) {
    assert_that(true, "it runs");
}

TestSuite *our_tests() {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, Foo, it_finds_and_runs_the_test);
    return suite;
}
