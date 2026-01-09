#pragma once

#include <type_traits>

#ifndef LNTC_CPP_NAMING_SCHEME
#define LNTC_CPP_NAMING_SCHEME 0
#endif

#if LNTC_CPP_NAMING_SCHEME
#define LNTC_CPP_MATH_NAMESPACE namespace LntcCpp::Math
#define LNTC_CPP_MATH_FUNCTION(upper, lower) upper
#else
#define LNTC_CPP_MATH_NAMESPACE namespace lntc_cpp::math
#define LNTC_CPP_MATH_FUNCTION(upper, lower) lower
#endif

LNTC_CPP_MATH_NAMESPACE {
  /// Returns the smaller value of `left` and `right`.
  /// @param left the left number
  /// @param right the right number
  /// @return the smaller of the two numbers.
  template <class T>
    requires std::is_arithmetic_v<T>
  T LNTC_CPP_MATH_FUNCTION(MinNum, min_num)(const T& left, const T& right) {
    return left < right ? left : right;
  }

  /// Returns the bigger value of `left` and `right`.
  /// @param left the left number
  /// @param right the right number
  /// @return the bigger of the two numbers.
  template <class T>
    requires std::is_arithmetic_v<T>
  T LNTC_CPP_MATH_FUNCTION(MaxNum, max_num)(const T& left, const T& right) {
    return left > right ? left : right;
  }
}

#undef LNTC_CPP_MATH_NAMESPACE
#undef LNTC_CPP_MATH_FUNCTION