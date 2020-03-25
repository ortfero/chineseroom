# Chineseroom

C++ functions and types to work with text



## Usage

Just put `include/chineseroom/chineseroom.hpp` at your include path



## Tests

To run tests:

```shell
cd chineseroom
mkdir build
cd build
cmake ../tests
```



## Examples


### Fixed strings

```cpp
namespace chr = chineseroom;
chr::fixed_string<508> text{"Roses are red"};
chr::string roses{text.substr(0, 5)}; // "Roses"
```


### Splitting string

```cpp
namespace chr = chineseroom;
std::vector<std::string> const splitted = chr::split(std::string{"1,2,,3"}, ',');
// splitted: {"1", "2", "3"}
std::vector<std::string> const strict = chr::split_strict(std::string{1,2,,3"}, ',');
// strict: {"1", "2", "", "3"}
```


### Pattern matching

```cpp
namespace chr = chineseroom
chr::has_wildcards("ab?ba"); // true
chr::match("ab?ba", "abba"); // false
chr::match("ab*ba", "abba"); // true
chr::match("!ab*ba", "abba"); // false 
chr::match_list({"ab*ba", "!abba"}, "abba"); // false
chr::match_list(std::string{"ab*ba, !abba"}, "abcba"); // true
```


### Text formatting

```cpp
```
