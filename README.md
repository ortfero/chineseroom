# Chineseroom

C++ functions and types to work with text



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
chineseroom::texter texter;
texter.print("Value: ", -127562.127562); // texter contains "Value: -127562.127562"

```

### Benchmarks

#### Formatting

| Code                                                         | Time (ns) | Ratio |
|--------------------------------------------------------------|----------:|------:|
| ```texter.print('a');```                                     | 1.3       | x1    |
| ```snprintf(charz, sizeof (charz), "%c", 'a');```            | 212.0     | x163  |
| ```fmt::format_to(charz, "{}", 'a');```                      | 187.0     | x143  |
| ```texter.print("some literal");```                          | 1.3       | x1    |
| ```snprintf(charz, sizeof (charz), "%s", "some literal");``` | 141.5     | x108  |
| ```fmt::format_to(charz, "{}", "some literal");```           | 63.9      | x49   |
| ```texter.print(-127562);```                                 | 7.7       | x1    |
| ```snprintf(charz, sizeof (charz), "%d", -127562);```        | 220.5     | x28   |
| ```fmt::format_to(charz, "{}", -127562);```                  | 79.3      | x10   |
| ```texter.print(-127562.127562);```                          | 8.2       | x1    |
| ```snprintf(charz, sizeof (charz), "%f", -127562.127562);``` | 775.0     | x94   |
| ```fmt::format_to(charz, "{}", -127562.127562);```           | 412.0     | x50   |
