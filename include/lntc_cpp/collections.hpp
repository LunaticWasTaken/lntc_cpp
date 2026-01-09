#pragma once

#include <optional>

#ifndef LNTC_CPP_NAMING_SCHEME
#define LNTC_CPP_NAMING_SCHEME 0
#endif

#if LNTC_CPP_NAMING_SCHEME
#define LNTC_CPP_COLLECTIONS_NAMESPACE namespace LntcCpp::Collections
#define LNTC_CPP_COLLECTIONS_FUNCTION(upper, lower) upper
#else
#define LNTC_CPP_COLLECTIONS_NAMESPACE namespace lntc_cpp::collections
#define LNTC_CPP_COLLECTIONS_FUNCTION(upper, lower) lower
#endif

LNTC_CPP_COLLECTIONS_NAMESPACE {
  /**
   * Searches the given list for the first object that matches the given predicate, and returns it in an optional if found.
   * @tparam list_t the list type
   * @tparam predicate the predicate to match
   * @param list the list object.
   * @param pred the predicate to match.
   * @return an optional with the first matching object found, or a nullopt if none found.
   */
  template <class list_t, class predicate>
    requires std::invocable<predicate, typename list_t::value_type>
  std::optional<typename list_t::value_type> LNTC_CPP_COLLECTIONS_FUNCTION(FindFirst, find_first)(const list_t& list, predicate pred) {
    if (const auto& it = std::ranges::find_if(list, pred); it != list.end()) return *it;
    return std::nullopt;
  }

  template <class list_t, class element_type>
    requires(!std::invocable<element_type, typename list_t::value_type>)
  std::optional<element_type> LNTC_CPP_COLLECTIONS_FUNCTION(FindFirst, find_first)(const list_t& list, const element_type& element) {
    if (const auto& it = std::ranges::find(list, element); it != list.end()) return *it;
    return std::nullopt;
  }
}

#undef LNTC_CPP_COLLECTIONS_NAMESPACE
#undef LNTC_CPP_COLLECTIONS_FUNCTION
