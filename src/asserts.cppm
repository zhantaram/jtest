// -*- C++ -*-

export module jtest:asserts;
import std;

namespace jtest {

  struct AssertionFailure {
    std::string message;
    std::source_location location;
  };

  export template<typename T, typename U>
  void assert_eq(const T& actual, const U& expected,
                 std::source_location loc = std::source_location::current()) {
    if (!std::equal_to<>{}(actual, expected)) {
      if constexpr (std::formattable<T, char> && std::formattable<U, char>) {
        throw AssertionFailure{
            .message = std::format("{} (actual) != {} (expected)", actual, expected),
            .location = std::move(loc),
        };
      } else {
        throw AssertionFailure{
            .message = "(actual) != (expected)",
            .location = std::move(loc),
        };
      }
    }
  }

  export template<typename T, typename U>
  void assert_ne(const T& actual, const U& expected,
                 std::source_location loc = std::source_location::current()) {
    if (std::equal_to<>{}(actual, expected)) {
      if constexpr (std::formattable<T, char> && std::formattable<U, char>) {
        throw AssertionFailure{
            .message = std::format("{} (actual) == {} (expected)", actual, expected),
            .location = std::move(loc),
        };
      } else {
        throw AssertionFailure{
            .message = "(actual) == (expected)",
            .location = std::move(loc),
        };
      }
    }
  }

} // namespace jtest
