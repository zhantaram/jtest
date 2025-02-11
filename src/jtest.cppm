// -*- C++ -*-

export module jtest;

export import :utils;
export import :asserts;

namespace jtest {

  export template<MetaString test_name>
  struct Test {
    void operator()();
  };

  export template<MetaString... test_names>
    requires(std::invocable<Test<test_names>> && ...)
  class Registry {
  public:
    void run_all_tests() noexcept {
      std::size_t num_success = 0;
      std::println("Running total of {} tests", sizeof...(test_names));
      std::println("---------------------------------------------------------------");
      if constexpr (sizeof...(test_names) != 0) {
        ((num_success += this->run_test<test_names>()), ...);
      }
      std::println("{} out of {} tests finished successfuly", num_success, sizeof...(test_names));
    }

  private:
    template<MetaString test_name>
    bool run_test() noexcept {
      std::println("Running test \"{}\"", test_name);
      try {
        std::invoke(std::get<Test<test_name>>(tests_));
      } catch (const AssertionFailure& error) {
        std::println("Test \"{}\" failed:\n\t{}", test_name, error.message);
        std::println("---------------------------------------------------------------");
        return false;
      }
      std::println("Test \"{}\" finished successfuly", test_name);
      std::println("---------------------------------------------------------------");
      return true;
    }

    std::tuple<Test<test_names>...> tests_ = {};
  };

} // namespace jtest
