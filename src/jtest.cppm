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
  class TestRegistry {
  public:
    void run_all_tests() noexcept {
      std::size_t num_success = 0;
      std::println("Running total of {} tests", sizeof...(test_names));
      std::println("---------------------------------------------------------------");
      ((num_success += this->run_test<test_names>()), ...);
      std::println("{} out of {} tests finished successfuly", num_success, sizeof...(test_names));
    }

  private:
    template<MetaString test_name>
    bool run_test() noexcept {
      std::println("Running test \"{}\"", test_name);
      try {
        std::invoke(std::get<Test<test_name>>(tests_));
        std::println("Test \"{}\" finished successfuly", test_name);
        std::println("---------------------------------------------------------------");
        return true;
      } catch (const AssertionFailure& error) {
        std::println("Test \"{}\" failed:\n{}:{}\n\t{}", test_name, error.location.file_name(),
                     error.location.line(), error.message);
        std::println("---------------------------------------------------------------");
        return false;
      }
    }

    std::tuple<Test<test_names>...> tests_ = {};
  };

  export template<MetaString benchmark_name>
  struct Benchmark {
    void operator()();
  };

  export template<MetaString... benchmark_names>
    requires(std::invocable<Benchmark<benchmark_names>> && ...)
  class BenchmarkRegistry {
  public:
    static void run_all_benchmarks() noexcept {
      std::println("Running total of {} benchmarks", sizeof...(benchmark_names));
      std::println("---------------------------------------------------------------");
      (run_benchmark<benchmark_names>(), ...);
      std::println("Ran all benchmarks");
    }

  private:
    template<MetaString benchmark_name>
    static void run_benchmark() noexcept {
      std::println("Running benchmark \"{}\"", benchmark_name);
      std::size_t total_iterations = 0;
      std::chrono::high_resolution_clock::duration total_duration = {};
      for (std::size_t iterations : {1, 10, 100, 1'000, 10'000, 100'000, 1'000'000, 10'000'000}) {
        Benchmark<benchmark_name> benchmark{};
        auto before = std::chrono::high_resolution_clock::now();
        for (auto _ : std::views::iota(0ul, iterations)) {
          std::invoke(benchmark);
        }
        total_duration += std::chrono::high_resolution_clock::now() - before;
        total_iterations += iterations;
        if (total_duration > std::chrono::seconds{3}) {
          break;
        }
      }
      std::println(
          "Benchmark \"{}\" did {} iterations with average of {:.3f} ns per iteration",
          benchmark_name, total_iterations,
          static_cast<double>(
              std::chrono::duration_cast<std::chrono::nanoseconds>(total_duration).count()) /
              total_iterations);
      std::println("---------------------------------------------------------------");
    }
  };

} // namespace jtest
