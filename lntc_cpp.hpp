#pragma once

#include <memory>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <random>
#include <functional>
#include <thread>
#include <filesystem>
#include <fstream>

#define LNTC_CPP_REL_VERSION 1

namespace lntc_cpp {
  /// Core-Utilities
  namespace core {
    /// A simple singleton helper.
    template <class T>
    class Singleton {
    public:
      static T* get_singleton() {
        static T singleton;
        return std::addressof(singleton);
      }

    protected:
      Singleton() = default;
      ~Singleton() = default;
      Singleton(const Singleton&) = delete;
      Singleton(Singleton&&) = delete;
      Singleton& operator=(const Singleton&) = delete;
      Singleton& operator=(Singleton&&) = delete;
    };

    inline void run_async(const std::function<void()>& func) { std::thread(func).detach(); }
  }

  /// String-Utilities
  namespace str {
    /// converts `str` to all-lowercase.
    /// @param str the string to convert.
    inline void to_lower(std::string& str) {
      std::ranges::transform(str, str.begin(), [](const unsigned char c) { return std::tolower(c); });
    }

    /// Returns a copy of `str`, converted to all-lowercase.
    /// @param str the input string to convert.
    /// @return an all-lowercase copy of `str`.
    inline std::string to_lower_cpy(const std::string& str) {
      std::string lower = str;
      to_lower(lower);
      return lower;
    }

    /// converts `str` to all-uppercase.
    /// @param str the string to convert.
    inline void to_upper(std::string& str) {
      std::ranges::transform(str, str.begin(), [](const unsigned char c) { return std::tolower(c); });
    }

    /// Returns a copy of `str`, converted to all-uppercase.
    /// @param str the input string to convert.
    /// @return an all-uppercase copy of `str`.
    inline std::string to_upper_cpy(const std::string& str) {
      std::string lower = str;
      to_lower(lower);
      return lower;
    }

    /// Splits `str` by the given delimiter-char, and returns a list with the split parts.
    /// @param str the string to split
    /// @param delimiter the delimiter-char to split by
    /// @return a list containing all the split parts.
    inline std::vector<std::string> split(const std::string& str, const char delimiter) {
      std::vector<std::string> result;
      std::stringstream ss(str);
      std::string item;
      while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
      }
      return result;
    }

    /// Performs an equality-check between `left` and `right`.
    /// @param left the first string
    /// @param right the second string
    /// @return true if both strings are equal, false otherwise.
    inline bool equals(const std::string& left, const std::string& right) { return left == right; }

    /// Performs a case-insensitive equality-check between `left` and `right`.
    /// @param left the first string
    /// @param right the second string
    /// @return true if both strings are equal, false otherwise.
    inline bool equals_ci(const std::string& left, const std::string& right) { return equals(to_lower_cpy(left), to_lower_cpy(right)); }

    /// Checks if `left` starts with `left`.
    /// @param left the full string
    /// @param right the part to check for at the start of `left`
    /// @return true if `left` starts with `right`, false otherwise.
    inline bool starts_with(const std::string& left, const std::string& right) { return left.starts_with(right); }

    /// Checks if `left` starts with `left`, case-insensitive.
    /// @param left the full string
    /// @param right the part to check for at the start of `left`
    /// @return true if `left` starts with `right`, false otherwise.
    inline bool starts_with_ci(const std::string& left, const std::string& right) { return starts_with(to_lower_cpy(left), to_lower_cpy(right)); }

    /// Checks if `left` ends with `left`.
    /// @param left the full string
    /// @param right the part to check for at the end of `left`
    /// @return true if `left` ends with `right`, false otherwise.
    inline bool ends_with(const std::string& left, const std::string& right) { return left.ends_with(right); }

    /// Checks if `left` ends with `left`, case-insensitive.
    /// @param left the full string
    /// @param right the part to check for at the end of `left`
    /// @return true if `left` ends with `right`, false otherwise.
    inline bool ends_with_ci(const std::string& left, const std::string& right) { return ends_with(to_lower_cpy(left), to_lower_cpy(right)); }

    /// Checks if `left` contains `right`.
    /// @param left the full string
    /// @param right the part to check for inside `right`
    /// @return true if `left` contains `right`, false otherwise.
    inline bool contains(const std::string& left, const std::string& right) { return left.contains(right); }

    /// Checks if `left` contains `right`, case-insensitive.
    /// @param left the full string
    /// @param right the part to check for inside `right`
    /// @return true if `left` contains `right`, false otherwise.
    inline bool contains_ci(const std::string& left, const std::string& right) { return contains(to_lower_cpy(left), to_lower_cpy(right)); }
  }

  /// Math/Number-Utilities
  namespace math {
    /// Returns the smaller value of `left` and `right`.
    /// @tparam T the type of the values.
    /// @param left the left number
    /// @param right the right number
    /// @return the smaller of the two numbers.
    template <class T>
    T min_num(const T& left, const T& right) {
      return left < right ? left : right;
    }

    /// Returns the bigger value of `left` and `right`.
    /// @tparam T the type of the values.
    /// @param left the left number
    /// @param right the right number
    /// @return the bigger of the two numbers.
    template <class T>
    T max_num(const T& left, const T& right) {
      return left > right ? left : right;
    }
  }

  /// IO-Utilities
  namespace io {
    /// Attempts to read all lines from the file at `path` and returns them as list.
    /// @param path the path of the file.
    /// @return a list with all lines from the file. Will be empty if an error occured.
    inline std::vector<std::string> file_read_lines(const std::filesystem::path& path) {
      try {
        if (std::filesystem::is_regular_file(path)) {
          std::ifstream in(path);
          std::string line;
          std::vector<std::string> result;
          while (std::getline(in, line)) result.push_back(line);
          return result;
        }
      } catch (...) {
      }
      return {};
    }

    /// Attempts to write `lines` into the file at `path`.
    /// @param lines the lines to write to the file
    /// @param path the path of the file to write to
    /// @param append If true, `lines` will be appended, otherwise they will replace the old content (if existing). Will replace by default.
    /// @return true if successful, false if an error occured.
    inline bool file_write_lines(const std::vector<std::string>& lines, const std::filesystem::path& path, const bool append = false) {
      try {
        if (std::filesystem::exists(path) && !std::filesystem::is_regular_file(path)) return false;
        std::vector<std::string> out_lines = append ? file_read_lines(path) : std::vector<std::string>();
        out_lines.insert(out_lines.end(), lines.begin(), lines.end());
        std::ofstream out(path);
        for (const std::string& line : out_lines) out << line << std::endl;
        return true;
      } catch (...) {
      }
      return false;
    }
  }
}