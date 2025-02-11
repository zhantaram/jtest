import jtest;
import std;

template<>
struct jtest::Test<"Test1"> {
  void operator()() {
    jtest::assert_eq(2 * 2, 4);
  }
};

template<>
struct jtest::Test<"Test2"> {
  void operator()() {
    jtest::assert_eq(2 * 2, 5);
  }
};

template<>
struct jtest::Test<"Test3"> {
  void operator()() {
    jtest::assert_ne(2 * 2, 5);
  }
};

template<>
struct jtest::Test<"Test4"> {
  struct NonFormattable {
    bool operator==(auto&&) const {
      return false;
    }
  };

  void operator()() {
    jtest::assert_eq(NonFormattable{}, 100);
  }
};

int main(int argc, const char* argv[]) {
  jtest::Registry<"Test1", "Test2", "Test3", "Test4"> registry;
  registry.run_all_tests();
  return 0;
}
