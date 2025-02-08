// -*- C++ -*-

export module jtest:utils;
import std;

namespace jtest {

  template<std::size_t size, typename CharT = char>
  struct MetaString {
    constexpr MetaString(const CharT (&str)[size]) {
      for (std::size_t i = 0; i < size; ++i) {
        inner[i] = str[i];
      }
    }

    CharT inner[size];
  };

  template<std::size_t N, typename CharT>
  MetaString(const CharT (&str)[N]) -> MetaString<N, CharT>;

} // namespace jtest

namespace std {
  template<std::size_t size, typename CharT>
  struct formatter<jtest::MetaString<size, CharT>, CharT> : formatter<std::string_view, CharT> {
    template<typename FmtContext>
    decltype(auto) format(const jtest::MetaString<size, CharT>& str, FmtContext& ctx) const {
      return formatter<std::string_view, CharT>::format(str.inner, ctx);
    }
  };
} // namespace std
