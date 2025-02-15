import jtest;
import std;

namespace jtest {
  template<>
  struct Test<"TrivialPass"> {
    void operator()() {
      assert_cmp(std::equal_to<>{}, 2 * 2, 4);
    }
  };

  template<>
  struct Test<"TrivialFail"> {
    void operator()() {
      assert_cmp(std::equal_to<>{}, 2 * 2, 5);
    }
  };

  template<>
  struct Test<"MultipleAsserts"> {
    void operator()() {
      assert_cmp(std::not_equal_to<>{}, 2 * 2, 5);
      assert_cmp(std::less_equal<>{}, 2 * 2, 4);
    }
  };

  template<>
  struct Test<"NonFormattableFail"> {
    struct NonFormattable {
      bool operator==(auto&&) const {
        return false;
      }
    };

    void operator()() {
      assert_cmp(std::equal_to<>{}, NonFormattable{}, 100);
    }
  };

  template<>
  struct Benchmark<"FetchAdd"> {
    void operator()() {
      counter.fetch_add(1);
    }

    std::atomic<unsigned> counter = 0;
  };

  template<>
  struct Benchmark<"Logarithm"> {
    void operator()() {
      value = std::log(value) * 10;
      volatile auto _ = value;
    }

    double value =
        static_cast<double>(std::chrono::system_clock::now().time_since_epoch().count()) / 123;
  };

} // namespace jtest

int main(int argc, const char* argv[]) {
  jtest::TestRegistry<"TrivialPass", "TrivialFail", "MultipleAsserts", "NonFormattableFail"> tests;
  tests.run_all_tests();

  jtest::BenchmarkRegistry<"FetchAdd", "Logarithm"> benchmarks;
  benchmarks.run_all_benchmarks();
  return 0;
}
