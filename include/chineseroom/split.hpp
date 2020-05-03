#pragma once


#include <algorithm>
#include <vector>
#include <string>


namespace hydra {
  
  
namespace detail {

  template<typename S> void split(S const& source,
                                  typename S::value_type separator,
                                  std::vector<S>& splitted,
                                  bool strict) {
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

inline void split_strictly(std::wstring const& source, wchar_t separator, std::vector<std::wstring>& splitted) {
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

inline std::vector<std::wstring> split_strictly(std::wstring const& source, wchar_t separator) {
  std::vector<std::wstring> splitted;
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

inline void split(std::wstring const& source, wchar_t separator, std::vector<std::wstring>& splitted) {
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

inline std::vector<std::wstring> split(std::wstring const& source, wchar_t separator) {
  std::vector<std::wstring> splitted;
  split(source, separator, splitted);
  return splitted;
}

template<int N> std::vector<fixed_string<N>> split(fixed_string<N> const& source, char separator) {
  std::vector<fixed_string<N>> splitted;
  split(source, separator, splitted);
  return splitted;
}


} // hydra
