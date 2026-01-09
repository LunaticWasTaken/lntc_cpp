#pragma once

#include <string>
#include <algorithm>
#include <ranges>
#include <vector>
#include <sstream>

/// If you want, you can define this macro before including any of the lntc_cpp headers to dynamically change the naming scheme to lower_snake_case (0) or UpperCamelCase (1+).
///
/// This is provided because while the stl uses lower_camel_case, a gigantic amount of libraries don't. So pick whatever you want.
///
/// NOTE: This applies to all headers of this project for consistency
#ifndef LNTC_CPP_NAMING_SCHEME
#define LNTC_CPP_NAMING_SCHEME 0
#endif

#if LNTC_CPP_NAMING_SCHEME
#define LNTC_CPP_STRINGS_NAMESPACE namespace LntcCpp::Strings
#define LNTC_CPP_STRINGS_FUNCTION(upper, lower) upper
#else
#define LNTC_CPP_STRINGS_NAMESPACE namespace lntc_cpp::strings
#define LNTC_CPP_STRINGS_FUNCTION(upper, lower) lower
#endif

LNTC_CPP_STRINGS_NAMESPACE {
  inline void LNTC_CPP_STRINGS_FUNCTION(ToLower, to_lower)(std::string & str) {
    std::ranges::transform(str, str.begin(), [](const unsigned char c) { return std::tolower(c); });
  }

  inline std::string LNTC_CPP_STRINGS_FUNCTION(ToLower, to_lower)(const std::string& str) {
    std::string final_str = str;
    LNTC_CPP_STRINGS_FUNCTION(ToLower, to_lower)(final_str);
    return final_str;
  }

  inline void LNTC_CPP_STRINGS_FUNCTION(ToUpper, to_upper)(std::string & str) {
    std::ranges::transform(str, str.begin(), [](const unsigned char c) { return std::toupper(c); });
  }

  inline std::string LNTC_CPP_STRINGS_FUNCTION(ToUpper, to_upper)(const std::string& str) {
    std::string final_str = str;
    LNTC_CPP_STRINGS_FUNCTION(ToUpper, to_upper)(final_str);
    return final_str;
  }

  inline std::vector<std::string> LNTC_CPP_STRINGS_FUNCTION(Split, split)(const std::string& str, const char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) result.push_back(item);
    return result;
  }

  inline bool LNTC_CPP_STRINGS_FUNCTION(Equals, equals)(const std::string& left, const std::string& right) { return left == right; }

  inline bool LNTC_CPP_STRINGS_FUNCTION(EqualsIgnoreCase, equals_ignore_case)(const std::string& left, const std::string& right) {
    if (left.size() != right.size()) return false;
    for (size_t i = 0; i < left.size(); ++i) {
      if (std::tolower(static_cast<unsigned char>(left[i])) != std::tolower(static_cast<unsigned char>(right[i]))) return false;
    }
    return true;
  }

  inline bool LNTC_CPP_STRINGS_FUNCTION(StartsWith, starts_with)(const std::string& left, const std::string& right) { return left.starts_with(right); }

  inline bool LNTC_CPP_STRINGS_FUNCTION(StartsWithIgnoreCase, starts_with_ignore_case)(const std::string& left, const std::string& right) {
    if (right.empty()) return true;
    for (size_t i = 0; i < right.size(); ++i) {
      if (i >= left.size() || std::tolower(static_cast<unsigned char>(left[i])) != std::tolower(static_cast<unsigned char>(right[i]))) return false;
    }
    return true;
  }

  inline bool LNTC_CPP_STRINGS_FUNCTION(EndsWith, ends_with)(const std::string& left, const std::string& right) { return left.ends_with(right); }

  inline bool LNTC_CPP_STRINGS_FUNCTION(EndsWithIgnoreCase, ends_with_ignore_case)(const std::string& left, const std::string& right) {
    if (right.empty()) return true;
    if (right.size() > left.size()) return false;
    for (size_t i = 0; i < right.size(); ++i) {
      if (std::tolower(static_cast<unsigned char>(left[left.size() - right.size() + i])) != std::tolower(static_cast<unsigned char>(right[i]))) return false;
    }
    return true;
  }

  inline bool LNTC_CPP_STRINGS_FUNCTION(Contains, contains)(const std::string& left, const std::string& right) { return left.contains(right); }

  inline bool LNTC_CPP_STRINGS_FUNCTION(ContainsIgnoreCase, contains_ignore_case)(const std::string& left, const std::string& right) {
    if (right.empty()) return true;
    if (right.size() > left.size()) return false;
    for (size_t i = 0; i <= left.size() - right.size(); ++i) {
      bool found = true;
      for (size_t j = 0; j < right.size(); ++j) {
        if (std::tolower(static_cast<unsigned char>(left[i + j])) != std::tolower(static_cast<unsigned char>(right[j]))) {
          found = false;
          break;
        }
      }
      if (found) return true;
    }
    return false;
  }

  inline void LNTC_CPP_STRINGS_FUNCTION(ReplaceAll, replace_all)(std::string & str, const std::string& old_seq, const std::string& new_seq) {
    if (old_seq.empty()) return;
    size_t pos = 0;
    while ((pos = str.find(old_seq, pos)) != std::string::npos) {
      str.replace(pos, old_seq.length(), new_seq);
      pos += new_seq.length();
    }
  }

  inline std::string LNTC_CPP_STRINGS_FUNCTION(ReplaceAll, replace_all)(const std::string& str, const std::string& old_seq, const std::string& new_seq) {
    std::string result = str;
    LNTC_CPP_STRINGS_FUNCTION(ReplaceAll, replace_all)(result, old_seq, new_seq);
    return result;
  }
}

#undef LNTC_CPP_STRINGS_NAMESPACE
#undef LNTC_CPP_STRINGS_FUNCTION