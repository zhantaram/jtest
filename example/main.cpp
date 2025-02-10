import jtest;
import std;

namespace {
  static jtest::Suite tests{
      jtest::Case<"test1">{[] {
        jtest::assert_eq(2 * 2, 5);
      }},
      jtest::Case<"test2">{[] {
        jtest::assert_ne(2 * 2, 4);
      }},
      jtest::Case<"test3">{[] {
        jtest::assert_eq(2 * 2, 4);
      }},
  };
} // namespace

int main(int argc, const char* argv[]) {
  jtest::run_all_tests();
  return 0;
}
