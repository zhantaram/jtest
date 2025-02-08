// -*- C++ -*-

export module jtest:asserts;
import std;

namespace jtest {

  class AssertionError : public std::exception {
  public:
    AssertionError(std::source_location loc)
        : what_{std::format("Assertion failed in {}:{}\n"
                            "(actual) != (expected)",
                            loc.file_name(), loc.line())} {
    }

    template<std::formattable<char> T>
    AssertionError(std::source_location loc, const T& actual,
                   const std::type_identity_t<T>& expected)
        : what_{std::format("Assertion failed in {}:{}\n"
                            "{} (actual) != {} (expected)",
                            loc.file_name(), loc.line(), actual, expected)} {
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
        throw AssertionError{std::move(loc), actual, expected};
      } else {
        throw AssertionError{std::move(loc)};
      }
    }
  }

} // namespace jtest
