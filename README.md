### C++-20 modules friendly testing framework
Inside of your ".cppm" file just create static variable of type `jtest::Suite` that and pass one or more `jtest::Case` items.

To run tests, inside of `main` function, run `jtest::run_all_tests` function
