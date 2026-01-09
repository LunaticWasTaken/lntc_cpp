#define LNTC_CPP_NAMING_SCHEME 1
#include "lntc_cpp/strings.hpp"
#include "lntc_cpp/math.hpp"
#include "lntc_cpp/collections.hpp"

#include <print>

int main(int argc, char* argv[]) {
  // ====== strings.hpp ======
  std::println("====== strings.hpp ======");
  const std::string str = std::string("Hello World");
  std::println("Equals:                        {}", LntcCpp::Strings::Equals(str, "Hello World"));
  std::println("EqualsIgnoreCase:              {}", LntcCpp::Strings::EqualsIgnoreCase(str, "HeLlO WoRlD"));
  std::println("Contains:                      {}", LntcCpp::Strings::Contains(str, "ell"));
  std::println("ContainsIgnoreCase:            {}", LntcCpp::Strings::ContainsIgnoreCase(str, "ElLo"));
  std::println("StartsWith:                    {}", LntcCpp::Strings::StartsWith(str, "Hel"));
  std::println("StartsWithIgnoreCase:          {}", LntcCpp::Strings::StartsWithIgnoreCase(str, "HeLlO"));
  std::println("EndsWith:                      {}", LntcCpp::Strings::EndsWith(str, "orld"));
  std::println("EndsWithIgnoreCase:            {}", LntcCpp::Strings::EndsWithIgnoreCase(str, "oRlD"));
  std::println("ToLower:                       {}", LntcCpp::Strings::ToLower(str));
  std::println("ToUpper:                       {}", LntcCpp::Strings::ToUpper(str));
  std::println("Split:                         {}", LntcCpp::Strings::Split(str, 'l'));
  std::println("ReplaceAll:                    {}", LntcCpp::Strings::ReplaceAll(str, "World", "Earth"));
  std::println();

  // ====== math.hpp ======
  std::println("====== math.hpp ======");
  std::println("MaxNum:                        {}", LntcCpp::Math::MaxNum(50, 100));
  std::println("MinNum:                        {}", LntcCpp::Math::MinNum(50, 100));
  std::println();

  // ====== math.hpp ======
  std::println("====== collections.hpp ======");
  const std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::println("FindFirst(collection, lambda): {}", LntcCpp::Collections::FindFirst(vec, [](const auto& element) { return element == 5; }).has_value());
  std::println("FindFirst(collection, value):  {}", LntcCpp::Collections::FindFirst(vec, 5).has_value());
  std::println();
}