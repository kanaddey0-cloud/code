// C++26 Reflection example

// #include <meta>
// #include <iostream>
// #include <string>

// enum class Color { Red, Green, Blue };

// template <typename E>
// constexpr std::string enum_to_string(E value) {
//     template for (constexpr auto e : std::meta::enumerators_of(^^E)) {
//         if (value == [:e:])
//             return std::string(std::meta::identifier_of(e));
//     }
//     return "<unknown>";
// }

// int main() {
//     Color c = Color::Green;

//     std::cout << enum_to_string(c) << '\n';
// }


// Reflection Example Count enum values automatically:

#include <meta>

enum class Day { Mon, Tue, Wed, Thu, Fri };

constexpr int count_days() {
    int count = 0;
    template for (constexpr auto e : std::meta::enumerators_of(^^Day)) {
        ++count;
    }
    return count;
}
static_assert(count_days() == 5);