import jtest;
import std;

namespace jtest {
  template<>
  struct Test<"Test1"> {
    void operator()() {
      assert_cmp(std::equal_to<>{}, 2 * 2, 4);
    }
  };

  template<>
  struct Test<"Test2"> {
    void operator()() {
      assert_cmp(std::equal_to<>{}, 2 * 2, 5);
    }
  };

  template<>
  struct Test<"Test3"> {
    void operator()() {
      assert_cmp(std::not_equal_to<>{}, 2 * 2, 5);
    }
  };

  template<>
  struct Test<"Test4"> {
    struct NonFormattable {
      bool operator==(auto&&) const {
        return false;
      }
    };

    void operator()() {
      assert_cmp(std::equal_to<>{}, NonFormattable{}, 100);
    }
  };
} // namespace jtest

int main(int argc, const char* argv[]) {
  jtest::TestRegistry<"Test1", "Test2", "Test3", "Test4"> registry;
  registry.run_all_tests();
  return 0;
}
