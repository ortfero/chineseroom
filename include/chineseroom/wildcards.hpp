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


#include <string>
#include "split.hpp"


namespace chineseroom {
  
  
namespace detail {

  template<typename C> bool has_wildcards(C const* chars) {

    if(chars == nullptr)
      return false;

    if(*chars == '!')
      return true;

    for(C const* c = chars; *c != '\0'; ++c)
      switch(*c) {
        case '*': case '?':
          return true;
        default:
          continue;
      }

    return false;
  }

}



inline bool has_wildcards(char const* chars) {
  return detail::has_wildcards(chars);
}

inline bool has_wildcards(wchar_t const* chars) {
  return detail::has_wildcards(chars);
}

inline bool has_wildcards(std::string const& s) {
  return has_wildcards(s.data());
}

inline bool has_wildcards(std::wstring const& s) {
  return has_wildcards(s.data());
}


namespace detail {

template<typename C> bool matched(C const* pattern, C const* text) {
  
  if(pattern == text)
    return true;
  
  if(pattern == nullptr)
    return *text == '\0';
  
  if(text == nullptr)
    return *pattern == '\0';
  
  C const* last_text = nullptr;
  C const* last_pattern = nullptr;
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

} // detail


inline bool matched(char const* pattern, char const* text) {
  return detail::matched(pattern, text);
}

inline bool matched(char const* pattern, std::string const& text) {
  return matched(pattern, text.data());
}

inline bool matched(wchar_t const* pattern, wchar_t const* text) {
  return detail::matched(pattern, text);
}

inline bool matched(wchar_t const* pattern, std::wstring const& text) {
  return matched(pattern, text.data());
}

inline bool matched(std::string const& pattern, char const* text) {
  return matched(pattern.data(), text);
}

inline bool matched(std::string const& pattern, std::string const& text) {
  return matched(pattern.data(), text.data());
}

inline bool matched(std::wstring const& pattern, wchar_t const* text) {
  return matched(pattern.data(), text);
}

inline bool matched(std::wstring const& pattern, std::wstring const& text) {
  return matched(pattern.data(), text.data());
}

inline bool matched_any(std::initializer_list<char const*> const& patterns, char const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_any(std::initializer_list<char const*> const& patterns, std::string const& text) {
  matched_any(patterns, text.data());
}

inline bool matched_any(std::initializer_list<wchar_t const*> const& patterns, wchar_t const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_any(std::initializer_list<wchar_t const*> const& patterns, std::wstring const& text) {
  matched_any(patterns, text.data());
}

inline bool matched_any(std::initializer_list<std::string> const& patterns, char const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_any(std::initializer_list<std::string> const& patterns, std::string const& text) {
  matched_any(patterns, text.data());
}

inline bool matched(std::initializer_list<std::wstring> const& patterns, wchar_t const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_any(std::initializer_list<std::wstring> const& patterns, std::wstring const& text) {
  matched(patterns, text.data());
}

inline bool matched_any(std::vector<char const*> const& patterns, char const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_any(std::vector<char const*> const& patterns, std::string const& text) {
  matched_any(patterns, text.data());
}

inline bool matched_any(std::vector<wchar_t const*> const& patterns, wchar_t const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_any(std::vector<wchar_t const*> const& patterns, std::wstring const& text) {
  matched_any(patterns, text.data());
}

inline bool matched_any(std::vector<std::string> const& patterns, char const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_any(std::vector<std::string> const& patterns, std::string const& text) {
  matched_any(patterns, text.data());
}

inline bool matched_any(std::vector<std::wstring> const& patterns, wchar_t const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_any(std::vector<std::wstring> const& patterns, std::wstring const& text) {
  matched_any(patterns, text.data());
}

inline bool matched_any(std::string const& patterns, char const* text) {
  return matched_any(split(patterns, ','), text);
}

inline bool matched_any(std::string const& patterns, std::string const& text) {
  return matched_any(split(patterns, ','), text);
}

inline bool matched_any(std::wstring const& patterns, wchar_t const* text) {
  return matched_any(split(patterns, ','), text);
}

inline bool matched_any(std::wstring const& patterns, std::wstring const& text) {
  return matched_any(split(patterns, ','), text);
}


} // chineseroom
