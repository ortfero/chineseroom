#pragma once


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

template<int N>
bool has_wildcards(fixed_string<N> const& fs) {
  return has_wildcards(fs.data());
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

template<int N> bool matched(char const* pattern, fixed_string<N> const& text) {
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

template<int N> bool matched(std::string const& pattern, fixed_string<N> const& text) {
  return matched(pattern.data(), text.data());
}

inline bool matched(std::wstring const& pattern, wchar_t const* text) {
  return matched(pattern.data(), text);
}

inline bool matched(std::wstring const& pattern, std::wstring const& text) {
  return matched(pattern.data(), text.data());
}

template<int N> bool matched(fixed_string<N> const& pattern, char const* text) {
  return matched(pattern.data(), text);
}

template<int N> bool matched(fixed_string<N> const& pattern, std::string const& text) {
  return matched(pattern.data(), text.data());
}

template<int N, int M> bool matched(fixed_string<N> const& pattern, fixed_string<M> const& text) {
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

inline bool matched_list(std::initializer_list<wchar_t const*> const& patterns, wchar_t const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_list(std::initializer_list<wchar_t const*> const& patterns, std::wstring const& text) {
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

inline bool matched_list(std::initializer_list<std::wstring> const& patterns, wchar_t const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_list(std::initializer_list<std::wstring> const& patterns, std::wstring const& text) {
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

inline bool matched_list(std::vector<wchar_t const*> const& patterns, wchar_t const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_list(std::vector<wchar_t const*> const& patterns, std::wstring const& text) {
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

inline bool matched_list(std::vector<std::wstring> const& patterns, wchar_t const* text) {
  for(auto const& each_pattern: patterns)
    if(!matched(each_pattern, text))
      return false;
  return true;
}

inline bool matched_list(std::vector<std::wstring> const& patterns, std::wstring const& text) {
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

inline bool matched_list(std::wstring const& patterns, wchar_t const* text) {
  return matched_list(split(patterns, ','), text);
}

inline bool matched_list(std::wstring const& patterns, std::wstring const& text) {
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


} // chineseroom