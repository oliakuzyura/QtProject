#pragma once
#if __cplusplus == 201703L
#include <optional> // C++17
using std::nullopt;
using std::optional;
#else
#include <experimental/optional> // C++11
using std::experimental::nullopt;
using std::experimental::optional;
#endif