### C++-20 modules friendly testing framework
Inside of your ".cppm" file just create specialization of structure `jtest::Test<"#test name">` and add `operator()` implementation.

To run tests, inside of `main` function create registry with `jtest::Registry<"#test name", ...>` and run tests using `registry.run_all_tests()`.

Read `example/main.cpp` for example
