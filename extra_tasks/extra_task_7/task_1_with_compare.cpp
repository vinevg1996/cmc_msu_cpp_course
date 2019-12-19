#include <iostream>
#include <cassert>

template<char ...c>
struct TString {
    static constexpr const char value[sizeof...(c) + 1] = {c...,'\0'};
    static constexpr int size = sizeof...(c);

    template <char ...add_str> 
    constexpr auto operator+(TString<add_str...> const &str_to_add) const {
        return TString<c..., add_str...>();
    }

    template <char ...comp_str>
    constexpr bool operator==(TString<comp_str...> const &other_str) const {
        if (size == other_str.size) {
            return true;
        }
    }
};

template<char ... c>
constexpr const char TString<c...>::value[sizeof...(c)+1];

template<typename CharT, CharT ...String>
constexpr TString<String...> operator"" _s()
{
    return TString<String...>();
}


int main(int argc, const char *argv[]) {
  constexpr auto hello = "hello"_s + " world"_s;
  static_assert(hello == "hello world"_s);

  return 0;
}
