# ConstList

... is a compile-time functional-style list library written in C++.

## Current features:

- `Cons` class template for representing constant list structures at compile time
- `make` method template for easily constructing `Cons` structures
- list constructors such as `make` and `concatenate`
- basic list accessors such as `size`, `head`, `tail`, `nth` and `take`
- higher order list operators such as `foldr`, `foldl` and `map`
- higher order list queries such as `any`, `all` and `none`
- special purpose methods such as `reverse`
- test cases for all of the above
- MIT license

## Requirements:

- C++ compiler with support for C++14
- [Cmake](http://www.cmake.org/) for building
- [GoogleTest](http://code.google.com/p/googletest/) for tests
