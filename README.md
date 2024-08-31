# Competitive Programming

Everything I use as reference during a contest.

## Online Judge Profiles

- [CodeChef](https://www.codechef.com/users/gustavogardusi)
- [Codeforces](https://codeforces.com/profile/binaryLifter)

## Compile options

### C++

```shell
g++-11 \
    -std=c++17 \
    -O3 \
    -Wall \
    -Wl,-stack_size -Wl,10000000 \
```

## CMake

### macOS

#### Build
```shell
rm -rf build && mkdir build && cd build
cmake -D CMAKE_CXX_COMPILER=g++-11 /usr/local/bin ../
make
```

#### Run unit tests
```sh
ctest
```
