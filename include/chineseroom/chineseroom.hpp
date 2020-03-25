#pragma once



#include <cstddef>
#include <string>
#include <vector>
#include <array>
#include <initializer_list>

#if __cplusplus >= 201703L
#include <string_view>
#endif

#include <stdexcept>
#include <iostream>
#include <mutex>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cmath>



namespace chineseroom {



template<int N>
struct fixed_string {
  using value_type = char;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = char*;
  using const_pointer = char const*;
  using reference = char&;
  using const_reference = char const&;
  using iterator = char*;
  using const_iterator = char const*;

  static size_type const npos = size_type(-1);

  fixed_string() noexcept: n_(0) { p_[0] = '\0'; }
  fixed_string(fixed_string const& rhs) noexcept { assign(rhs.begin(), rhs.end()); }
  template<int M>
  fixed_string(fixed_string<M> const& rhs) noexcept { assign(rhs.begin(), rhs.end()); }
  explicit fixed_string(char const* data) noexcept { assign(data); }
  fixed_string(char const* b, char const* e) noexcept { assign(b, e); }
  explicit fixed_string(std::string const& rhs) noexcept { assign(rhs.begin(), rhs.end()); }

#if __cplusplus >= 201703L
  explicit fixed_string(std::string_view const& rhs) noexcept { assign(rhs.begin(), rhs.end()); }
#endif

  fixed_string& operator = (fixed_string const& rhs) noexcept { return assign(rhs.begin(), rhs.end()); }
  template<int M>
  fixed_string& operator = (fixed_string<M> const& rhs) noexcept { return assign(rhs.begin(), rhs.end()); }
  fixed_string& operator = (char const* data) noexcept { return assign(data); }
  fixed_string& operator = (std::string const& rhs) noexcept { return assign(rhs.begin(), rhs.end()); }

#if __cplusplus >= 201703L
  fixed_string& operator = (std::string_view const& rhs) noexcept { return assign(rhs.begin(), rhs.end()); }
#endif

  char* begin() noexcept { return p_; }
  char* end() noexcept { return p_ + n_; }
  char const* begin() const noexcept { return p_; }
  char const* end() const noexcept { return p_ + n_; }
  char const* cbegin() const noexcept { return p_; }
  char const* cend() const noexcept { return p_ + n_; }

  size_type size() const noexcept { return n_; }
  size_type length() const noexcept { return n_; }
  size_type max_size() const noexcept { return N; }
  size_type capacity() const noexcept { return N; }
  bool empty() const noexcept { return n_ == 0; }
  void clear() noexcept { n_ = 0; p_[0] = '\0'; }
  void reserve(size_type) noexcept { }

  void resize(size_type n) noexcept {
    if(n > N)
      return;
    n_ = n; p_[n] = '\0';
  }

  char& operator [] (size_type i) noexcept { return p_[i]; }
  char const& operator [] (size_type i) const noexcept { return p_[i]; }

  char& at (size_type i) {
    if(i >= n_)
      throw std::out_of_range("Attempt to access fixed_string out of range");
    return p_[i];
  }

  char const& at (size_type i) const {
    if(i >= n_)
      throw std::out_of_range("Attempt to access fixed_string out of range");
    return p_[i];
  }

  char& back() noexcept { return p_[n_ - 1]; }
  char const& back() const noexcept { return p_[n_ - 1]; }
  char& front() noexcept { return p_[0]; }
  char const& front() const noexcept { return p_[0]; }

  fixed_string& operator += (char c) noexcept { push_back(c); return *this; }
  template<int M>
  fixed_string& operator += (fixed_string<M> const& rhs) noexcept { return append(rhs.begin(), rhs.end()); }
  fixed_string& operator += (char const* cc) noexcept { return append(cc); }
  fixed_string& operator += (std::string const& rhs) noexcept { return append(rhs.data(), rhs.data() + rhs.size()); }

#if __cplusplus >= 201703L
  fixed_string& operator += (std::string_view const& rhs) noexcept { return append(rhs.data(), rhs.data() + rhs.size()); }
#endif

  template<int M>
  fixed_string& append(fixed_string<M> const& rhs) noexcept { return append(rhs.begin(), rhs.end()); }
  fixed_string& append(std::string const& rhs) noexcept { return append(rhs.data(), rhs.data() + rhs.size()); }

#if __cplusplus >= 201703L
  fixed_string& append(std::string_view const& rhs) noexcept { return append(rhs.data(), rhs.data() + rhs.size()); }
#endif

  fixed_string& append(char const* cc, size_type n) noexcept { return append(cc, cc + n); }

  fixed_string& append(char const* cc) noexcept {
    if(n_ == N || !cc)
      return *this;
    char* c = p_ + n_;
    while(n_ != N && *cc != '\0') {
      *c++ = *cc++;
      ++n_;
    }
    *c = '\0';
    return *this;
  }

  fixed_string& append(char const* b, char const* e) noexcept {
    if(!b || !e || b == e)
      return *this;
    size_type const m = static_cast<size_type>(e - b);
    size_type const l = N - n_;
    size_type const n = m > l ? l : m;
    e = b + n;
    for(char* p = p_ + n_; b != e; ++p, ++b)
      *p = *b;
    n_ += n;
    p_[n_] = '\0';
    return *this;
  }

  void push_back(char c) noexcept { if(n_ >= N) return; p_[n_++] = c; p_[n_] = '\0'; }
  void pop_back() noexcept { if(n_ == 0) return; p_[--n_] = '\0'; }

  fixed_string& assign(fixed_string const& rhs) noexcept { return assign(rhs.begin(), rhs.end()); }
  template<int M>
  fixed_string& assign(fixed_string<M> const& rhs) noexcept { return assign(rhs.begin(), rhs.end()); }
  fixed_string& assign(std::string const& rhs) noexcept { return assign(rhs.begin(), rhs.end()); }

#if __cplusplus >= 201703L
  fixed_string& assign(std::string_view const& rhs) noexcept { return assign(rhs.begin(), rhs.end()); }
#endif

  fixed_string& assign(char const* data) noexcept { n_ = 0; p_[0] = '\0'; return append(data); }
  fixed_string& assign(char const* b, char const* e) noexcept { n_ = 0; p_[0] = '\0'; return append(b, e); }

  char const* c_str() const noexcept { return p_; }
  char const* data() const noexcept { return p_; }

  size_type find_first_of(char c) const noexcept { return find_first_of(c, 0); }

  size_type find_first_of(char c, size_type i) const noexcept {
    if(i >= n_)
      return npos;
    for(char const *p = p_ + i, *e = p_ + n_; p != e; ++p)
      if(*p == c)
        return static_cast<size_type>(p - p_);
    return npos;
  }

  size_type find_last_of(char c) const noexcept { return find_last_of(c, n_ - 1); }

  size_type find_last_of(char c, size_type i) const noexcept {
    for(char const* p = p_ + i; p != p_ - 1; --p)
      if(*p == c)
        return static_cast<size_type>(p - p_);
    return npos;
  }

  fixed_string substr(size_type pos, size_type n) const noexcept {
    return fixed_string(p_ + pos, p_ + pos + n);
  }

  template<int M>
  int compare(fixed_string<M> const& rhs) const noexcept { return compare(rhs.begin(), rhs.end()); }
  int compare(std::string const& rhs) const noexcept { return compare(rhs.begin(), rhs.end()); }

#if __cplusplus >= 201703L
  int compare(std::string_view const& rhs) const noexcept { return compare(rhs.begin(), rhs.end()); }
#endif

  int compare(char const* b, char const* e) const noexcept {
    if(b == e)
      return n_ == 0 ? 0 : 1;
    char const* c = p_;
    while(*c == *b && b != e) {
      ++c; ++b;
    }
    if(b == e) return 0;
    else if(*c > *b) return 1;
    else return -1;
  }

  int compare(char const* s) const noexcept {
    if(!s || *s == '\0')
      return n_ == 0 ? 0 : 1;
    char const* c = p_;
    while(*c == *s && *c != '\0') {
      ++c; ++s;
    }
    if(*c == *s) return 0;
    else if(*c > *s) return 1;
    else return -1;
  }

private:
  size_type n_;
  char p_[N + 1];
}; //  fixed_string



typedef fixed_string<68> short_string;
typedef fixed_string<252> string;
typedef fixed_string<1020> long_string;
typedef fixed_string<4092> page_string;
typedef fixed_string<8188> dpage_string;
typedef fixed_string<65532> large_string;



template<int N>
std::string& operator += (std::string const& x, fixed_string<N> const& y) { return x.append(y.data(), y.size()); }

template<int N, int M>
bool operator == (fixed_string<N> const& x, fixed_string<M> const& y) { return x.compare(y) == 0; }
template<int N>
bool operator == (fixed_string<N> const& x, char const* y) { return x.compare(y) == 0; }
template<int N>
bool operator == (char const* x, fixed_string<N> const& y) { return y.compare(x) == 0; }
template<int N>
bool operator == (fixed_string<N> const& x, std::string const& y) { return x.compare(y) == 0; }
template<int N>
bool operator == (std::string const& x, fixed_string<N> const& y) { return y.compare(x) == 0; }

#if __cplusplus >= 201703L
template<int N>
bool operator == (fixed_string<N> const& x, std::string_view const& y) { return x.compare(y) == 0; }
template<int N>
bool operator == (std::string_view const& x, fixed_string<N> const& y) { return y.compare(x) == 0; }
#endif

template<int N, int M>
bool operator != (fixed_string<N> const& x, fixed_string<M> const& y) { return x.compare(y) != 0; }
template<int N>
bool operator != (fixed_string<N> const& x, char const* y) { return x.compare(y) != 0; }
template<int N>
bool operator != (char const* x, fixed_string<N> const& y) { return y.compare(x) != 0; }
template<int N>
bool operator != (fixed_string<N> const& x, std::string const& y) { return x.compare(y) != 0; }
template<int N>
bool operator != (std::string const& x, fixed_string<N> const& y) { return y.compare(x) != 0; }
#if __cplusplus >= 201703L
template<int N>
bool operator != (fixed_string<N> const& x, std::string_view const& y) { return x.compare(y) != 0; }
template<int N>
bool operator != (std::string_view const& x, fixed_string<N> const& y) { return y.compare(x) != 0; }
#endif

template<int N, int M>
bool operator < (fixed_string<N> const& x, fixed_string<M> const& y) { return x.compare(y) != 0; }
template<int N>
bool operator < (fixed_string<N> const& x, char const* y) { return x.compare(y) != 0; }
template<int N>
bool operator < (char const* x, fixed_string<N> const& y) { return y.compare(x) != 0; }
template<int N>
bool operator < (fixed_string<N> const& x, std::string const& y) { return x.compare(y) != 0; }
template<int N>
bool operator < (std::string const& x, fixed_string<N> const& y) { return y.compare(x) != 0; }
#if __cplusplus >= 201703L
template<int N>
bool operator < (fixed_string<N> const& x, std::string_view const& y) { return x.compare(y) != 0; }
template<int N>
bool operator < (std::string_view const& x, fixed_string<N> const& y) { return y.compare(x) != 0; }
#endif

template<int N, int M>
bool operator <= (fixed_string<N> const& x, fixed_string<M> const& y) { return x.compare(y) != 0; }
template<int N>
bool operator <= (fixed_string<N> const& x, char const* y) { return x.compare(y) != 0; }
template<int N>
bool operator <= (char const* x, fixed_string<N> const& y) { return y.compare(x) != 0; }
template<int N>
bool operator <= (fixed_string<N> const& x, std::string const& y) { return x.compare(y) != 0; }
template<int N>
bool operator <= (std::string const& x, fixed_string<N> const& y) { return y.compare(x) != 0; }
#if __cplusplus >= 201703L
template<int N>
bool operator <= (fixed_string<N> const& x, std::string_view const& y) { return x.compare(y) != 0; }
template<int N>
bool operator <= (std::string_view const& x, fixed_string<N> const& y) { return y.compare(x) != 0; }
#endif

template<int N, int M>
bool operator > (fixed_string<N> const& x, fixed_string<M> const& y) { return x.compare(y) != 0; }
template<int N>
bool operator > (fixed_string<N> const& x, char const* y) { return x.compare(y) != 0; }
template<int N>
bool operator > (char const* x, fixed_string<N> const& y) { return y.compare(x) != 0; }
template<int N>
bool operator > (fixed_string<N> const& x, std::string const& y) { return x.compare(y) != 0; }
template<int N>
bool operator > (std::string const& x, fixed_string<N> const& y) { return y.compare(x) != 0; }
#if __cplusplus >= 201703L
template<int N>
bool operator > (fixed_string<N> const& x, std::string_view const& y) { return x.compare(y) != 0; }
template<int N>
bool operator > (std::string_view const& x, fixed_string<N> const& y) { return y.compare(x) != 0; }
#endif

template<int N, int M>
bool operator >= (fixed_string<N> const& x, fixed_string<M> const& y) { return x.compare(y) != 0; }
template<int N>
bool operator >= (fixed_string<N> const& x, char const* y) { return x.compare(y) != 0; }
template<int N>
bool operator >= (char const* x, fixed_string<N> const& y) { return y.compare(x) != 0; }
template<int N>
bool operator >= (fixed_string<N> const& x, std::string const& y) { return x.compare(y) != 0; }
template<int N>
bool operator >= (std::string const& x, fixed_string<N> const& y) { return y.compare(x) != 0; }

#if __cplusplus >= 201703L
template<int N>
bool operator >= (fixed_string<N> const& x, std::string_view const& y) { return x.compare(y) != 0; }
template<int N>
bool operator >= (std::string_view const& x, fixed_string<N> const& y) { return y.compare(x) != 0; }
#endif

template<int N>
std::istream& operator >> (std::istream& stream, fixed_string<N>& fs) {
  return stream >> fs.begin();
}

template<int N>
std::ostream& operator << (std::ostream& stream, fixed_string<N> const& fs) {
  return stream << fs.begin();
}

}



namespace std {



  template<int N> struct hash<chineseroom::fixed_string<N>> {
    size_t operator()(chineseroom::fixed_string<N> const& s) const {
      size_t h = 0; char const* cc = s.data();
      while(*cc) h = h * 101 + static_cast<size_t>(*cc++);
      return h;
    }
  }; // hash



}



namespace chineseroom {


namespace detail {

  template<typename S> void split(S const& source, char separator, std::vector<S>& splitted, bool strict) {
    splitted.clear();
    typename S::const_iterator start = source.begin();
    typename S::const_iterator end = source.end();
    typename S::const_iterator next = std::find(start, end, separator);
    while(next != end) {
      if(next - start > 0 || strict)
        splitted.emplace_back(S{start, next});
      start = next + 1;
      next = std::find(start, end, separator);
    }
    if(next - start > 0 || strict)
      splitted.emplace_back(S{start, next});
  }

}



inline void split_strictly(std::string const& source, char separator, std::vector<std::string>& splitted) {
  detail::split(source, separator, splitted, true);
}

template<int N> void split_strictly(fixed_string<N> const& source, char separator, std::vector<fixed_string<N>>& splitted) {
  detail::split(source, separator, splitted, true);
}

inline std::vector<std::string> split_strictly(std::string const& source, char separator) {
  std::vector<std::string> splitted;
  split_strictly(source, separator, splitted);
  return splitted;
}

template<int N> std::vector<fixed_string<N>> split_strictly(fixed_string<N> const& source, char separator) {
  std::vector<fixed_string<N>> splitted;
  split_strictly(source, separator, splitted);
  return splitted;
}

inline void split(std::string const& source, char separator, std::vector<std::string>& splitted) {
  detail::split(source, separator, splitted, false);
}

template<int N> void split(fixed_string<N> const& source, char separator, std::vector<fixed_string<N>>& splitted) {
  detail::split(source, separator, splitted, false);
}

inline std::vector<std::string> split(std::string const& source, char separator) {
  std::vector<std::string> splitted;
  split(source, separator, splitted);
  return splitted;
}

template<int N> std::vector<fixed_string<N>> split(fixed_string<N> const& source, char separator) {
  std::vector<fixed_string<N>> splitted;
  split(source, separator, splitted);
  return splitted;
}



inline bool has_wildcards(char const* chars) {
  
  if(chars == nullptr)
    return false;
  
  for(char const* c = chars; *c != '\0'; ++c)
    switch(*c) {
      case '*': case '?': case '!':
        return true;
      default:
        continue;
    }
    
  return false;
}



inline bool has_wildcards(std::string const& s) {
  return has_wildcards(s.data());
}

template<int N>
bool has_wildcards(fixed_string<N> const& fs) {
  return has_wildcards(fs.data());
}



inline bool matched(char const* pattern, char const* text) {
  
  if(pattern == text)
    return true;
  
  if(pattern == nullptr)
    return *text == '\0';
  
  if(text == nullptr)
    return *pattern == '\0';
  
  char const* last_text = nullptr;
  char const* last_pattern = nullptr;
  bool without_negation = true;

  if(*pattern == '!') {
    without_negation = false;
    ++pattern;
  }
  
  while(*text != '\0')
    switch(*pattern) {
      case '*':
        // new star-loop: backup positions in pattern and text
        last_text = text;
        last_pattern = ++pattern;
        continue;
      case '?':
        // ? matched any character or we matched the current non-NUL character
        text++;
        pattern++;
        continue;
      default:
        if(*pattern == *text) {
          // we matched the current non-NUL character
          text++;
          pattern++;
        } else {
          // if no stars we fail to match
          if (last_pattern == nullptr)
            return without_negation ? false : true;
          // star-loop: backtrack to the last * by restoring the backup positions 
          // in the pattern and text
          text = ++last_text;
          pattern = last_pattern;
        }
    }
  
  // ignore trailing stars
  while(*pattern == '*')
    ++pattern;
  
  // at end of text means success if nothing else is left to match
  if(*pattern != '\0')
    return without_negation ? false : true;
  
  return without_negation ? true : false;
}



inline bool matched(char const* pattern, std::string const& text) {
  return matched(pattern, text.data());
}

template<int N> bool matched(char const* pattern, fixed_string<N> const& text) {
  return matched(pattern, text.data());
}

inline bool matched(std::string const& pattern, char const* text) {
  return matched(pattern.data(), text);
}

template<int N> bool matched(fixed_string<N> const& pattern, char const* text) {
  return matched(pattern.data(), text);
}

template<int N> bool matched(std::string const& pattern, fixed_string<N> const& text) {
  return matched(pattern.data(), text.data());
}

template<int N> bool matched(fixed_string<N> const& pattern, std::string const& text) {
  return matched(pattern.data(), text.data());
}

inline bool matched_list(std::initializer_list<char const*> const& patterns, char const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_list(std::initializer_list<char const*> const& patterns, std::string const& text) {
  matched_list(patterns, text.data());
}

template<int N> bool matched_list(std::initializer_list<char const*> const& patterns, fixed_string<N> const& text) {
  matched_list(patterns, text.data());
}

inline bool matched_list(std::initializer_list<std::string> const& patterns, char const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_list(std::initializer_list<std::string> const& patterns, std::string const& text) {
  matched_list(patterns, text.data());
}

template<int N> bool matched_list(std::initializer_list<std::string> const& patterns, fixed_string<N> const& text) {
  matched_list(patterns, text.data());
}

template<int N> bool matched_list(std::initializer_list<fixed_string<N>> const& patterns, char const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

template<int N> bool matched_list(std::initializer_list<fixed_string<N>> const& patterns, std::string const& text) {
  return matched_list(patterns, text.data());
}

template<int N, int M> bool matched_list(std::initializer_list<fixed_string<N>> const& patterns, fixed_string<M> const& text) {
  return matched_list(patterns, text.data());
}

inline bool matched_list(std::vector<char const*> const& patterns, char const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_list(std::vector<char const*> const& patterns, std::string const& text) {
  matched_list(patterns, text.data());
}

template<int N> bool matched_list(std::vector<char const*> const& patterns, fixed_string<N> const& text) {
  matched_list(patterns, text.data());
}

inline bool matched_list(std::vector<std::string> const& patterns, char const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_list(std::vector<std::string> const& patterns, std::string const& text) {
  matched_list(patterns, text.data());
}

template<int N> bool matched_list(std::vector<std::string> const& patterns, fixed_string<N> const& text) {
  matched_list(patterns, text.data());
}

template<int N> bool matched_list(std::vector<fixed_string<N>> const& patterns, char const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

template<int N> bool matched_list(std::vector<fixed_string<N>> const& patterns, std::string const& text) {
  return matched_list(patterns, text.data());
}

template<int N, int M> bool matched_list(std::vector<fixed_string<N>> const& patterns, fixed_string<M> const& text) {
  return matched_list(patterns, text.data());
}

inline bool matched_list(std::string const& patterns, char const* text) {
  return matched_list(split(patterns, ','), text);
}

inline bool matched_list(std::string const& patterns, std::string const& text) {
  return matched_list(split(patterns, ','), text);
}

template<int N> bool matched_list(std::string const& patterns, fixed_string<N> const& text) {
  return matched_list(split(patterns, ','), text);
}

template<int N> bool matched_list(fixed_string<N> const& patterns, char const* text) {
  return matched_list(split(patterns, ','), text);
}

template<int N> bool matched_list(fixed_string<N> const& patterns, std::string const& text) {
  return matched_list(split(patterns, ','), text);
}

template<int N, int M> bool matched_list(fixed_string<N> const& patterns, fixed_string<M> const& text) {
  return matched_list(split(patterns, ','), text);
}



template<typename T> struct zero {
  unsigned width;
  T value;
}; // zero



template<typename T> struct fp {
  unsigned precision;
  T value;
}; // fp



template<typename T> struct quoted {
  T const& item;
  quoted(T const& item): item(item) { }
}; // quoted



/////////////////////////////////////////////////////////////////////////
// @example
// atoys::string_printer p;
// p.print("It's", ' ', atoys::zero{6, 2}, ':', atoys::zero{0, 2}, "pm");
// Result: It's 06:00pm
// p.clear();
// p.print("Radius is ", atoys::fp{189.887, 2});
// Result: Radius is 189.89
// p.clear();
// p.format("Addition", "x", -1, "y", -2, "r", (-1) + (-2));
// Result: Addition { x:'-1' y:'-2' r:'-3' }
//////////////////////////////////////////////////////////////////////////
template<typename S> struct printer {
  typedef size_t size_type;

  static int const uint32_digits = 10;
  static int const int32_digits = uint32_digits + 1;
  static int const uint64_digits = 18;
  static int const int64_digits = uint64_digits + 1;
  static int const double_digits = uint64_digits * 2 + 2;
  static int const default_precision = 6;

  printer() noexcept = default;
  printer(printer const&) noexcept = default;
  printer& operator = (printer const&) noexcept = default;
  bool is_filled() const noexcept { return string_.size() == string_.max_size(); }
  S const& string() const noexcept { return string_; }
  char const* data() const noexcept { return string_.data(); }
  size_type size() const noexcept { return string_.size(); }
  void clear() noexcept { string_.clear(); }
  size_type capacity() const noexcept { return string_.capacity(); }
  void reserve(size_type n) { string_.reserve(n); }

  printer& out(char const* cc, size_type n) {
    string_.append(cc, n);
    return *this;
  }

  void print() { }

  template<typename A, typename... As>
  void print(A const& arg, As const&... args) {
    (*this) << arg;
    print(args...);
  }

  void format() { }

  template<typename A, typename... As>
  void format(char const* name, A const& arg, As const&... args) {
    string_ += ' '; string_ += '{'; string_ += ' ';
    format_args(name, arg, args...);
    string_ += '}';
  }

  template<typename SS> friend printer& operator << (printer& p, printer<SS> const& q) {
    p.string_ += q.buffer();
    return p;
  }

  friend printer& operator << (printer& p, char c) {
    p.string_.push_back(c);
    return p;
  }

  friend printer& operator << (printer& p, char const* cc) {
    p.string_.append(cc);
    return p;
  }

#if __cplusplus >= 201703L
  friend printer& operator << (printer& p, std::string_view const& sv) {
    return p.out(sv.data(), sv.size());
  }
#endif

  friend printer& operator << (printer& p, std::string const& s) {
    return p.out(s.data(), s.size());
  }

  template<int N> friend printer& operator << (printer& p, std::array<char, N> const& ca) {
    p.string_.append(ca.data());
    return p;
  }

  friend printer& operator << (printer& p, bool x) {
    return x ? p.out("true", 4) : p.out("false", 5);
  }

  friend printer& operator << (printer& p, uint32_t x) {
    return p.integral<uint32_t, uint32_digits>(x);
  }

  friend printer& operator << (printer& p, int32_t x) {
    return p.integral<int32_t, int32_digits>(x);
  }

  friend printer& operator << (printer& p, uint64_t x) {
    return p.integral<uint64_t, uint64_digits>(x);
  }

  friend printer& operator << (printer& p, int64_t x) {
    return p.integral<int64_t, int64_digits>(x);
  }

  friend printer& operator << (printer& p, float x) {
    return p.floating_point(x, default_precision);
  }

  friend printer& operator << (printer& p, double x) {
    return p.floating_point(x, default_precision);
  }

  friend printer& operator << (printer& p, zero<uint32_t> const& z) {
    return p.integral_zeros<uint32_t, uint32_digits>(z);
  }

  friend printer& operator << (printer& p, zero<int32_t> const& z) {
    return p.integral_zeros<int32_t, int32_digits>(z);
  }

  friend printer& operator << (printer& p, zero<uint64_t> const& z) {
    return p.integral_zeros<uint64_t, uint64_digits>(z);
  }

  friend printer& operator << (printer& p, zero<int64_t> const& z) {
    return p.integral_zeros<int64_t, int64_digits>(z);
  }

  friend printer& operator << (printer& p, fp<float> const& fp) {
    return p.floating_point(fp.value, fp.precision);
  }

  friend printer& operator << (printer& p, fp<double> const& fp) {
    return p.floating_point(fp.value, fp.precision);
  }
  
  template<typename T> friend printer& operator << (printer& p, quoted<T> const& q) {
    p.string_.push_back('\'');
    p << q.item;
    p.string_.push_back('\'');
    return p;
  }

  template<int N> friend printer& operator << (printer& p, fixed_string<N> const& fs) {
    p.string_ += fs;
    return p;
  }

private:
  S string_;

  void format_args() { }
  template<typename A, typename... As>
  void format_args(char const* name, A const& arg, As const&... args) {
    string_ += name; string_ += ':'; string_ += '\'';
    *this << arg; string_ += '\''; string_ += ' ';
    format_args(args...);
  }

  char* allocate(size_type n) {
    size_type const old_size = string_.size();
    size_type const new_size = old_size + n;
    string_.resize(new_size);
    char* p;
    if(string_.size() != new_size)
      p = nullptr;
    else
      p = &string_[old_size];
    return p;
  }

  printer& shrink(size_type n) {
    string_.resize(string_.size() - n);
    return *this;
  }

  template<typename T, int N> printer& integral(T x) {
    char* buffer = allocate(N);
    char* p = buffer;
    if(!p) return *this;
    convert(x, p);
    shrink(N - (p - buffer));
    return *this;
  }

  template<typename T, int N> printer& integral_zeros(zero<T> const& z) {
    char* buffer = allocate(N);
    char* p = buffer;
    if(!p) return *this;
    convert(z.value, p);
    size_type const width = size_type(p - buffer);
    if(width >= z.width)
      return shrink(N - width);
    size_type zeros = z.width < N ? z.width : N;
    size_type const n = zeros - width;
    for(p = buffer; p != buffer + n; ++p) {
      p[width] = p[0];
      p[0] = '0';
    }
    return shrink(N - zeros);
  }

  template<typename T> printer& floating_point(T x, unsigned precision) {
    char* buffer = allocate(double_digits);
    char* p = buffer;
    if(!p) return *this;
    convert(double(x), p, precision);
    return shrink(double_digits - (p - buffer));
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
      *p++ = 'N'; *p++ = 'A'; *p++ = 'N';
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
    while(*(p - 1) == '0')
      --p;
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


}; // printer
typedef printer<std::string> string_printer;
typedef printer<short_string> short_printer;
typedef printer<string> fixed_printer;
typedef printer<long_string> long_printer;
typedef printer<page_string> page_printer;
typedef printer<dpage_string> dpage_printer;
typedef printer<large_string> large_printer;



template<typename... As>
void print(As const&... as) {
  thread_local long_printer p;
  p.print(as..., '\n');
  fwrite(p.data(), sizeof(char), p.size(), stdout);
}



template<typename R, typename... As>
R print_with(R&& r, As const&... as) {
  print(as...);
  return std::forward<R>(r);
}



} // chineseroom
