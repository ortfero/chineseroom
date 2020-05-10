/* This file is part of chineseroom library
 * Copyright 2020 Andrei Ilin <ortfero@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once


#include <algorithm>
#include <vector>
#include <string>
#include <string_view>


namespace chineseroom {
  
  
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

} // detail



inline void split_strictly(std::string const& source, char separator, std::vector<std::string>& splitted) {
  detail::split(source, separator, splitted, true);
}

inline void split_strictly(std::wstring const& source, wchar_t separator, std::vector<std::wstring>& splitted) {
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

inline void split(std::string const& source, char separator, std::vector<std::string>& splitted) {
  detail::split(source, separator, splitted, false);
}

inline void split(std::wstring const& source, wchar_t separator, std::vector<std::wstring>& splitted) {
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


} // chineseroom
