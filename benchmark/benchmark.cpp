#include <iostream>
#include <cstdio>
#include <fmt/format.h>
#include <ubench/ubench.hpp>
#include <chineseroom/texter.hpp>



int main() {

  using namespace std;

  chineseroom::texter texter;
  char charz[256];

  auto const texter_char = ubench::run([&]{ texter.print('a'); });
  auto const snprintf_char = ubench::run([&]{ snprintf(charz, sizeof (charz), "%c", 'a'); });
  auto const fmt_char = ubench::run([&]{ fmt::format_to(charz, "{}", 'a'); });

  cout << "texter.print(char) - " << texter_char << endl;
  cout << "snprintf(char)     - " << snprintf_char << endl;
  cout << "fmt::format(char)  - " << fmt_char << endl;
  cout << endl;

  auto const texter_literal = ubench::run([&]{ texter.print("some literal"); });
  auto const snprintf_literal = ubench::run([&]{ snprintf(charz, sizeof (charz), "%s", "some literal"); });
  auto const fmt_literal = ubench::run([&]{ fmt::format_to(charz, "{}", "some literal"); });

  cout << "texter.print(char[N]) - " << texter_literal << endl;
  cout << "snprintf(char[N])     - " << snprintf_literal << endl;
  cout << "fmt::format(char[N])  - " << fmt_literal << endl;
  cout << endl;

  char const* benchmark = "benchmark";
  auto const texter_chars = ubench::run([&]{ texter.print(benchmark); });
  auto const snprintf_chars = ubench::run([&]{ snprintf(charz, sizeof (charz), "%s", benchmark); });
  auto const fmt_chars = ubench::run([&]{ fmt::format_to(charz, "{}", benchmark); });

  cout << "texter.print(char*) - " << texter_chars << endl;
  cout << "snprintf(char*)     - " << snprintf_chars << endl;
  cout << "fmt::format(char*)  - " << fmt_chars << endl;
  cout << endl;

  auto const texter_int = ubench::run([&]{ texter.print(-127562); });
  auto const snprintf_int = ubench::run([&]{ snprintf(charz, sizeof (charz), "%d", -127562); });
  auto const fmt_int = ubench::run([&]{ fmt::format_to(charz, "{}", -127562); });

  cout << "texter.print(int) - " << texter_int << endl;
  cout << "snprintf(int)     - " << snprintf_int << endl;
  cout << "fmt::format(int)  - " << fmt_int << endl;
  cout << endl;

  auto const texter_double = ubench::run([&]{ texter.print(-127562.127562); });
  auto const snprintf_double = ubench::run([&]{ snprintf(charz, sizeof (charz), "%f", -127562.127562); });
  auto const fmt_double = ubench::run([&]{ fmt::format_to(charz, "{}", -127562.127562); });

  cout << "texter.print(double) - " << texter_double << endl;
  cout << "snprintf(double)     - " << snprintf_double << endl;
  cout << "fmt::format(double)  - " << fmt_double << endl;
  cout << endl;


  return 0;
}
