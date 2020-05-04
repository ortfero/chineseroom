#pragma once



#include <cstdint>
#include <utility>
#include <string_view>
#include "fixed_string.hpp"



namespace chineseroom {



  template<typename S>
  struct basic_texter {

    using size_type = size_t;

    static constexpr auto default_precision = 6;

    basic_texter() noexcept = default;
    basic_texter(basic_texter const&) = default;
    basic_texter& operator = (basic_texter const&) = default;
    basic_texter(basic_texter&&) noexcept = default;
    basic_texter& operator = (basic_texter&&) noexcept = default;

    S const& string() const noexcept { return string_; }
    char const* data() const noexcept { return string_.data(); }
    size_type size() const noexcept { return string_.size(); }
    bool empty() const noexcept { return string_.empty(); }
    void clear() noexcept { string_.clear(); }


    size_type capacity() const noexcept {
      return string_.capacity();
    }


    bool filled() const noexcept {
      return string_.size() == string_.max_size();
    }


    void reserve(size_type n) {

      if(n <= string_.capacity())
        return;

      n = nearest_power_of_2(n);
      string_.reserve(n);
    }


    basic_texter& out(char const* cc, size_type n) {
      string_.append(cc, n);
      return *this;
    }


    template<typename F, typename Arg> basic_texter& as(Arg&& arg, F const& f = F{}) {
      f.print(*this, std::forward<Arg>(arg));
      return *this;
    }


    basic_texter& print() {
      return *this;
    }


    template<typename Arg, typename... Args>
    basic_texter& print(Arg&& arg, Args&&... args) {
      (*this) << arg;
      print(std::forward<Args>(args)...);
      return *this;
    }


    basic_texter& fixed(double x, unsigned precision) {
      return print_fixed_float(x, precision);
    }


    basic_texter& fixed(float x, unsigned precision) {
      return print_fixed_float(x, precision);
    }


    basic_texter& fixed(uint32_t x, unsigned width) {
      constexpr auto digits = 10;
      return print_fixed_int<digits>(x, width);
    }


    basic_texter& fixed(int32_t x, unsigned width) {
      constexpr auto digits = 11;
      return print_fixed_int<digits>(x, width);
    }


    basic_texter& fixed(uint64_t x, unsigned width) {
      constexpr auto digits = 18;
      return print_fixed_int<digits>(x, width);
    }


    basic_texter& fixed(int64_t x, unsigned width) {
      constexpr auto digits = 19;
      return print_fixed_int<digits>(x, width);
    }



    template<typename X>
    friend basic_texter& operator << (basic_texter& p, basic_texter<X> const& q) {
      p.string_.append(q.data(), q.size());
      return p;
    }


    friend basic_texter& operator << (basic_texter& p, char c) {
      p.string_.push_back(c);
      return p;
    }


    friend basic_texter& operator << (basic_texter& p, char const* cc) {
      p.string_.append(cc);
      return p;
    }


    template<size_t N > friend
    basic_texter& operator << (basic_texter& p, char const (&s)[N]) {
      p.string_.append(s, N - 1);
      return p;
    }


    friend basic_texter& operator << (basic_texter& p, std::string_view const& sv) {
      return p.out(sv.data(), sv.size());
    }


    friend basic_texter& operator << (basic_texter& p, std::string const& s) {
      return p.out(s.data(), s.size());
    }


    friend basic_texter& operator << (basic_texter& p, bool x) {
      return x ? p.out("true", 4) : p.out("false", 5);
    }


    friend basic_texter& operator << (basic_texter& p, uint32_t x) {
      constexpr auto digits = 10;
      return p.print_int<digits>(x);
    }


    friend basic_texter& operator << (basic_texter& p, int32_t x) {
      constexpr auto digits = 11;
      return p.print_int<digits>(x);
    }


    friend basic_texter& operator << (basic_texter& p, uint64_t x) {
      constexpr auto digits = 18;
      return p.print_int<digits>(x);
    }


    friend basic_texter& operator << (basic_texter& p, int64_t x) {
      constexpr auto digits = 19;
      return p.print_int<digits>(x);
    }


    friend basic_texter& operator << (basic_texter& p, float x) {
      return p.print_fixed_float(x, default_precision);
    }


    friend basic_texter& operator << (basic_texter& p, double x) {
      return p.print_fixed_float(x, default_precision);
    }


    template<size_t N>
    friend basic_texter& operator << (basic_texter& p, fixed_string<N> const& fs) {
      p.out(fs.data(), fs.size());
      return p;
    }



  private:

    S string_;


    static uint64_t nearest_power_of_2(uint64_t n) {
      if(n < 2)
        return 2;
      n--;
      n |= n >> 1;
      n |= n >> 2;
      n |= n >> 4;
      n |= n >> 8;
      n |= n >> 16;
      n |= n >> 32;
      n++;
      return n;
    }


    char* allocate(unsigned& n) {

      size_type const old_size = string_.size();
      size_type new_size = old_size + n;

      if(new_size > string_.capacity()) {
        new_size = nearest_power_of_2(new_size);
        n = unsigned(new_size - old_size);
      }

      string_.resize(new_size);

      if(string_.size() != new_size)
        return nullptr;
      else
        return &string_[old_size];
    }


    basic_texter& shrink(size_type n) {
      string_.resize(string_.size() - n);
      return *this;
    }


    template<unsigned N, typename T> basic_texter& print_int(T x) {
      unsigned digits = N;
      char* buffer = allocate(digits);
      if(!buffer) return *this;
      char* p = buffer;
      convert(x, p);
      shrink(digits - (p - buffer));
      return *this;
    }


    template<unsigned N, typename T> basic_texter& print_fixed_int(T x, unsigned width) {
      if(width > N)
        width = N;
      unsigned digits = width;
      char* buffer = allocate(digits);
      if(!buffer) return *this;
      char* p = buffer;
      convert(x, p);
      unsigned const actual_width = unsigned(p - buffer);
      if(actual_width >= width)
        return shrink(digits - actual_width);
      unsigned const leadings_count = width - actual_width;
      for(p = buffer + actual_width - 1; p != buffer + leadings_count - 1; --p)
        p[leadings_count] = p[0];
      for(; p != buffer - 1; --p) {
        p[leadings_count] = p[0];
        p[0] = '0';
      }
      shrink(digits - width);
      return *this;
    }


    template<typename T> basic_texter& print_fixed_float(T x, unsigned precision) {
      unsigned digits = 38;
      char* buffer = allocate(digits);
      if(!buffer) return *this;
      char* p = buffer;
      convert(double(x), p, precision);
      return shrink(digits - (p - buffer));
    }


    static void convert(double x, char*& p, unsigned precision) {
      static double pow10[18] = {
        1E0, 1E1, 1E2, 1E3, 1E4, 1E5, 1E6, 1E7, 1E8, 1E9, 1E10, 1E11, 1E12, 1E13,
        1E14, 1E15, 1E16, 1E17
      };
      if(precision > 16)
        precision = 16;
      if(isinf(x)) {
        *p++ = 'I'; *p++ = 'N'; *p++ = 'F';
        return;
      }
      if(isnan(x)) {
        *p++ = 'N'; *p++ = 'a'; *p++ = 'N';
        return;
      }
      if(x < 0.0) {
        *p++ = '-';
        x = -x;
      }
      
      uint64_t integer = uint64_t(x);
      convert(integer, p);
      *p++ = '.';
      x -= double(integer);
      x *= pow10[precision];
      x += 0.5;
      convert(uint64_t(x), p);
      //while(*(p - 1) == '0')
      //  --p;
    }


    static void convert(uint32_t x, char*& p) {
      if(x < 100000000) {
        if(x == 0)
          *p++ = '0';
        else
          begin8(p, x);
      } else {
        begin2(p, x / 100000000);
        middle8(p, x % 100000000);
      }
    }


    static void convert(int32_t x, char*& p) {
      if(x < 0) {
        *p++ = '-';
        x = -x;
      }
      convert(uint32_t(x), p);
    }


    static void convert(uint64_t x, char*& p) {
      if(x < 100000000) {
        if(x == 0)
          *p++ = '0';
        else
          begin8(p, uint32_t(x));
      } else if(x < 10000000000000000) {
        begin8(p, uint32_t(x / 100000000));
        middle8(p, x % 100000000);
      } else {
        begin4(p, uint32_t(x / 10000000000000000));
        middle16(p, x % 10000000000000000);
      }
    }


    static void convert(int64_t x, char*& p) {
      if(x < 0) {
        *p++ = '-';
        x = -x;
      }
      convert(uint64_t(x), p);
    }


    static void begin2(char*& p, uint32_t n) {
      if(n < 10)
        *p++ = char('0' + n);
      else
        middle2(p, n);
    }


    static void middle2(char*& p, uint32_t n) {
      static char const digits_lut[200] = {
        '0','0','0','1','0','2','0','3','0','4','0','5','0','6','0','7','0','8','0','9',
        '1','0','1','1','1','2','1','3','1','4','1','5','1','6','1','7','1','8','1','9',
        '2','0','2','1','2','2','2','3','2','4','2','5','2','6','2','7','2','8','2','9',
        '3','0','3','1','3','2','3','3','3','4','3','5','3','6','3','7','3','8','3','9',
        '4','0','4','1','4','2','4','3','4','4','4','5','4','6','4','7','4','8','4','9',
        '5','0','5','1','5','2','5','3','5','4','5','5','5','6','5','7','5','8','5','9',
        '6','0','6','1','6','2','6','3','6','4','6','5','6','6','6','7','6','8','6','9',
        '7','0','7','1','7','2','7','3','7','4','7','5','7','6','7','7','7','8','7','9',
        '8','0','8','1','8','2','8','3','8','4','8','5','8','6','8','7','8','8','8','9',
        '9','0','9','1','9','2','9','3','9','4','9','5','9','6','9','7','9','8','9','9'
      };
      uint32_t const t = n * 2;
      *p++ = digits_lut[t];
      *p++ = digits_lut[t + 1];
    }


    static void begin4(char*& p, uint32_t n) {
      if(n < 100)
        begin2(p, n);
      else {
        begin2(p, n / 100);
        middle2(p, n % 100);
      }
    }


    static void middle4(char*& p, uint32_t n) {
      middle2(p, n / 100);
      middle2(p, n % 100);
    }


    static void begin8(char*& p, uint32_t n) {
      if(n < 10000)
        begin4(p, n);
      else {
        begin4(p, n / 10000);
        middle4(p, n % 10000);
      }
    }


    static void middle8(char*& p, uint32_t n) {
      middle4(p, n / 10000);
      middle4(p, n % 10000);
    }


    static void middle16(char*& p, uint64_t n) {
      middle8(p, uint32_t(n / 100000000));
      middle8(p, uint32_t(n % 100000000));
    }
  }; // texter


  using std_texter = basic_texter<std::string>;
  using short_texter = basic_texter<short_string>;
  using texter = basic_texter<string>;
  using long_texter = basic_texter<long_string>;
  using page_texter = basic_texter<page_string>;
  using dpage_texter = basic_texter<dpage_string>;
  using large_texter = basic_texter<large_string>;


} // chineseroom
