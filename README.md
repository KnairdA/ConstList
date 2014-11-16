# ConstList

... is a compile-time functional-style list library written in C++.

## Current features:

- `Cons` class template for representing constant list structures at compile time
- `make` method template for easily constructing `Cons` structures
- basic list accessors such as `size`, `head`, `tail`, `nth` and `take`
- some list operators such as `concatenate`, `foldr`, `foldl`, `map`, `reverse`, `any` and `all`
- test cases

## Requirements:

- C++ compiler with support for C++14
- [Cmake](http://www.cmake.org/) for building
- [GoogleTest](http://code.google.com/p/googletest/) for tests
