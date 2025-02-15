### C++-20 modules friendly testing and benchmarking framework

In contrast to other testing frameworks, jtest does not need macros and can be incorporated into module units with zero link time overhead

Inside of your ".cppm" file just create specialization of structure `jtest::Test<"#test name">` and add `operator()` implementation. For benchmarks, you should use `jtest::Benchmark<"#benchmark name">` specialization

To run tests, inside of `main` function create registry with `jtest::TestRegistry<"#test name", ...>` and run tests using `registry.run_all_tests()`. For benchmarks that would be `jtest::BenchmarkRegistry<"#bench name", ...>`

Read `example/main.cpp` for example
