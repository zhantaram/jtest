// -*- C++ -*-

export module jtest:asserts;
import std;

namespace jtest {

  template<typename... Ts>
  std::string try_format(Ts&&... args) {
    auto to_format_arg = []<typename T>(T& arg) -> decltype(auto) {
      if constexpr (std::formattable<T, char>) {
        return arg;
      } else {
        return "#unfmt";
      }
    };
    std::stringstream stream;
    stream << "Assertion failed, with args:";
    ((stream << ' ' << to_format_arg(args)), ...);
    return std::move(stream.str());
  }

  struct AssertionFailure {
    std::string message;
    std::source_location location;
  };

  export template<typename Cmp, typename... Args>
    requires(std::invocable<Cmp, Args...>)
  struct assert_cmp {
    assert_cmp(Cmp&& cmp, Args&&... args,
               std::source_location loc = std::source_location::current()) {
      if (!std::invoke(std::forward<Cmp>(cmp), std::forward<Args>(args)...)) {
        throw AssertionFailure{
            .message = try_format(std::forward<Args>(args)...),
            .location = std::move(loc),
        };
      }
    }
  };

  template<typename Cmp, typename... Ts>
  assert_cmp(Cmp&&, Ts&&...) -> assert_cmp<Cmp, Ts...>;

} // namespace jtest
