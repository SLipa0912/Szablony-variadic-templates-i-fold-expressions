#include <cstddef>
#include <iostream>
#include <type_traits>

// Zwraca true, jeśli wszystkie argumenty są "prawdziwe" (po rzutowaniu na bool).
// Unarny prawostronny fold po &&: dla pustej paczki wynik to true.
template <typename... Args>
constexpr bool all_true(const Args&... args) {
    // TODO
}

// Zwraca true, jeśli co najmniej jeden argument jest "prawdziwy".
// Unarny prawostronny fold po ||: dla pustej paczki wynik to false.
template <typename... Args>
constexpr bool any_true(const Args&... args) {
    // TODO
}

// Zwraca true, jeśli wszystkie typy Ts... są identyczne z T.
// Dla pojedynczego typu (pusta paczka Ts) wynik to true.
template <typename T, typename... Ts>
inline constexpr bool all_same_v = (std::is_same_v<T, Ts> && ...);

// Wariadyczny szablon klasy: lista typów.
template <typename... Ts>
struct TypeList {
    // Liczba typów na liście
    static constexpr std::size_t size = sizeof...(Ts);

    // Czy T występuje na liście? Fold po || (dla pustej listy false).
    template <typename T>
    static constexpr bool contains = (std::is_same_v<T, Ts> || ...);

    // Ile razy T występuje na liście? Binarny PRAWOSTRONNY fold: (pack + ... + init).
    template <typename T>
    static constexpr std::size_t count =
        ((std::is_same_v<T, Ts> ? std::size_t{1} : std::size_t{0}) + ... + std::size_t{0});
};

// Testy w czasie kompilacji
static_assert(all_true(true, 1, 2.5));
static_assert(!all_true(true, 0, 3));
static_assert(all_true());

static_assert(any_true(false, 0, 3));
static_assert(!any_true(0, false));
static_assert(!any_true());

static_assert(all_same_v<int, int, int>);
static_assert(!all_same_v<int, int, double>);
static_assert(all_same_v<int>);
static_assert(!all_same_v<int, const int>);  // is_same_v rozróżnia const
static_assert(!all_same_v<int, int&>);       // oraz referencje

static_assert(TypeList<int, char, int>::size == 3);
static_assert(TypeList<>::size == 0);
static_assert(TypeList<int, char>::contains<char>);
static_assert(!TypeList<int, char>::contains<double>);
static_assert(!TypeList<>::contains<int>);
static_assert(TypeList<int, char, int>::count<int> == 2);
static_assert(TypeList<int, char>::count<double> == 0);
static_assert(TypeList<>::count<int> == 0);

int main() {
    int x = 5;

    std::cout << std::boolalpha;
    std::cout << "all_true(true, 1, 2.5)                  = " << all_true(true, 1, 2.5) << '\n';
    std::cout << "all_true(true, 0, 3)                    = " << all_true(true, 0, 3) << '\n';
    std::cout << "all_true(&x, x > 3)                     = " << all_true(&x, x > 3) << '\n';
    std::cout << "all_true()                              = " << all_true() << '\n';

    std::cout << "any_true(false, 0, 3)                   = " << any_true(false, 0, 3) << '\n';
    std::cout << "any_true(0, false)                      = " << any_true(0, false) << '\n';
    std::cout << "any_true()                              = " << any_true() << '\n';

    std::cout << "all_same_v<int, int, int>               = " << all_same_v<int, int, int> << '\n';
    std::cout << "all_same_v<int, int, double>            = " << all_same_v<int, int, double> << '\n';
    std::cout << "all_same_v<int>                         = " << all_same_v<int> << '\n';
    std::cout << "all_same_v<int, const int>              = " << all_same_v<int, const int> << '\n';

    std::cout << "TypeList<int, char, int>::size          = "
              << TypeList<int, char, int>::size << '\n';
    std::cout << "TypeList<int, char>::contains<char>     = "
              << TypeList<int, char>::contains<char> << '\n';
    std::cout << "TypeList<int, char>::contains<double>   = "
              << TypeList<int, char>::contains<double> << '\n';
    std::cout << "TypeList<int, char, int>::count<int>    = "
              << TypeList<int, char, int>::count<int> << '\n';
    std::cout << "TypeList<>::size                        = " << TypeList<>::size << '\n';
    return 0;
}
