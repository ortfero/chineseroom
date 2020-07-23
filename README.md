# chineseroom

C++ header-only library to process strings



## Usage

Just put all files from `include/chineseroom` at your include path



## Tests

To run tests:

```shell
cd chineseroom
mkdir build
cd build
cmake ../test
```



## Examples

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
