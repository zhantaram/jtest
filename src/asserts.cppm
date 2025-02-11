// -*- C++ -*-

export module jtest:asserts;
import std;

namespace jtest {

  template<typename... Ts>
  std::string format(std::string_view fmt, Ts&&... args) {
    auto to_format_arg = []<typename T>(T& arg) -> decltype(auto) {
      if constexpr (std::formattable<T, char>) {
        return arg;
      } else {
        return "#unformattable";
      }
    };

    return std::vformat(fmt, std::make_format_args(to_format_arg(args)...));
  }

  struct AssertionFailure {
    std::string message;
    std::source_location location;
  };

  export template<typename T, typename U>
  void assert_eq(const T& actual, const U& expected,
                 std::source_location loc = std::source_location::current()) {
    if (!std::equal_to<>{}(actual, expected)) {
      throw AssertionFailure{
          .message = format("{} (actual) != {} (expected)", actual, expected),
          .location = std::move(loc),
      };
    }
  }

  export template<typename T, typename U>
  void assert_ne(const T& actual, const U& expected,
                 std::source_location loc = std::source_location::current()) {
    if (std::equal_to<>{}(actual, expected)) {
      throw AssertionFailure{
          .message = format("{} (actual) == {} (expected)", actual, expected),
          .location = std::move(loc),
      };
    }
  }

} // namespace jtest
