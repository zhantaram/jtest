// -*- C++ -*-

export module jtest:registry;
import :utils;
import :asserts;
import std;

namespace jtest {

  export template<MetaString test_name>
  class Case {
  public:
    Case(std::function<void()> body) noexcept
        : body_{std::move(body)} {
    }

    bool run_test() noexcept {
      std::println("----------------------------------------------------------------------");
      std::println("Running test \"{}\"", test_name);
      try {
        std::invoke(body_);
      } catch (const AssertionError& err) {
        std::println("Test \"{}\" failed:\n{}", test_name, err.what());
        return false;
      }
      std::println("Test \"{}\" passed", test_name);
      return true;
    }

  private:
    std::function<void()> body_;
  };

  class SuiteBase {
  public:
    virtual ~SuiteBase() = default;

  protected:
    virtual void run_tests() noexcept = 0;

    friend void run_all_tests() noexcept;
    static inline std::vector<SuiteBase*> suites_;
  };

  export template<MetaString... test_names>
  class Suite : public SuiteBase {
  public:
    Suite(Case<test_names>... cases,
          std::source_location loc = std::source_location::current()) noexcept
        : cases_{std::forward_as_tuple(std::move(cases)...)}
        , suite_location_{std::move(loc)} {
      suites_.push_back(this);
    }

    void run_tests() noexcept override {
      std::println("======================================================================");
      std::println("Running test suite from {}:{}", suite_location_.file_name(),
                   suite_location_.line());
      std::size_t n_passed = 0;
      ((n_passed += std::get<Case<test_names>>(cases_).run_test()), ...);
      std::println("======================================================================");
      std::println("{} out of {} tests passed", n_passed, sizeof...(test_names));
    }

  private:
    std::tuple<Case<test_names>...> cases_;
    std::source_location suite_location_;
  };

  export template<MetaString... test_names>
  Suite(Case<test_names>...) -> Suite<test_names...>;

  export void run_all_tests() noexcept {
    for (SuiteBase* suite : SuiteBase::suites_) {
      suite->run_tests();
    }
  }

} // namespace jtest
