import jtest;
import std;

namespace {
  static jtest::Suite tests{
      jtest::Case<"test1">{[] {
        jtest::assert_eq(2 * 2, 5);
      }},
      jtest::Case<"test2">{[] {
        jtest::assert_eq(2 * 2, 4);
      }},
  };

} // namespace

template<>
struct jtest::TestSuite<"my"> {};

int main(int argc, const char* argv[]) {
  jtest::run_all_tests();

  jtest::TestSuite<"asd"> suite;

  return 0;
}
