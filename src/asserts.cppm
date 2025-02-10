// -*- C++ -*-

export module jtest:asserts;
import std;

namespace jtest {

  class AssertionError : public std::exception {
  public:
    AssertionError(std::source_location loc, bool expect_equal)
        : what_{std::format("Assertion failed in {}:{}\n"
                            "(actual) {} (expected)",
                            loc.file_name(), loc.line(), expect_equal ? "!=" : "==")} {
    }

    template<std::formattable<char> T>
    AssertionError(std::source_location loc, const T& actual,
                   const std::type_identity_t<T>& expected, bool expect_equal)
        : what_{std::format("Assertion failed in {}:{}\n"
                            "{} (actual) {} {} (expected)",
                            loc.file_name(), loc.line(), actual,
                            expect_equal ? "!=" : "==", expected)} {
    }

    const char* what() const noexcept override {
      return what_.c_str();
    }

  private:
    const std::string what_;
  };

  export template<typename T>
  void assert_eq(const T& actual, const std::type_identity_t<T>& expected,
                 std::source_location loc = std::source_location::current()) {
    if (!std::equal_to<T>{}(actual, expected)) {
      if constexpr (std::formattable<T, char>) {
        throw AssertionError{std::move(loc), actual, expected, /*expect_equal=*/true};
      } else {
        throw AssertionError{std::move(loc), /*expect_equal=*/true};
      }
    }
  }

  export template<typename T>
  void assert_ne(const T& actual, const std::type_identity_t<T>& expected,
                 std::source_location loc = std::source_location::current()) {
    if (std::equal_to<T>{}(actual, expected)) {
      if constexpr (std::formattable<T, char>) {
        throw AssertionError{std::move(loc), actual, expected, /*expect_equal=*/false};
      } else {
        throw AssertionError{std::move(loc), /*expect_equal=*/false};
      }
    }
  }

} // namespace jtest
