#include <iostream>
#include <string>
#include <type_traits>

// Suma wszystkich argumentów. Dla pustej listy zwraca 0.
// Binarny lewostronny fold z wartością początkową: (init + ... + pack).
// Unarny fold (... + args) nie skompiluje się dla pustej paczki,
// dlatego potrzebna jest wartość początkowa.
// Fold po && w static_assert sprawdza typy CAŁEJ paczki naraz.
template <typename... Args>
constexpr auto fold_sum(Args... args) {
    // TODO
}

// Iloczyn wszystkich argumentów. Dla pustej listy zwraca 1 (element neutralny mnożenia).
template <typename... Args>
constexpr auto fold_product(Args... args) {
    // TODO
}

// Unarny fold LEWOSTRONNY: ((a1 - a2) - a3) - ...
// Odejmowanie nie jest łączne, więc kierunek foldu zmienia wynik.
template <typename... Args>
constexpr auto fold_minus_left(Args... args) {
    // TODO
}

// Unarny fold PRAWOSTRONNY: a1 - (a2 - (a3 - ...))
template <typename... Args>
constexpr auto fold_minus_right(Args... args) {
    // TODO
}

// Testy w czasie kompilacji
static_assert(fold_sum(1, 2, 3, 4) == 10);
static_assert(fold_sum() == 0);
static_assert(fold_sum(1.5, 2.5) == 4.0);
static_assert(fold_product(2, 3, 4) == 24);
static_assert(fold_product() == 1);
static_assert(fold_product(1.5, 2) == 3.0);

static_assert(fold_minus_left(10, 3, 2) == 5);        // (10 - 3) - 2
static_assert(fold_minus_right(10, 3, 2) == 9);       // 10 - (3 - 2)
static_assert(fold_minus_left(10, 4, 3, 1) == 2);     // ((10 - 4) - 3) - 1
static_assert(fold_minus_right(10, 4, 3, 1) == 8);    // 10 - (4 - (3 - 1))
static_assert(fold_minus_left(7) == 7);
static_assert(fold_minus_right(7) == 7);

int main() {
    std::cout << "fold_sum(1, 2, 3, 4)          = " << fold_sum(1, 2, 3, 4) << '\n';
    std::cout << "fold_sum(1.5, 2.25, 3.0)      = " << fold_sum(1.5, 2.25, 3.0) << '\n';
    std::cout << "fold_sum()                    = " << fold_sum() << '\n';
    std::cout << "fold_product(2, 3, 4)         = " << fold_product(2, 3, 4) << '\n';
    std::cout << "fold_product(1.5, 2, 4)       = " << fold_product(1.5, 2, 4) << '\n';
    std::cout << "fold_product()                = " << fold_product() << '\n';

    std::cout << "fold_minus_left(10, 3, 2)     = " << fold_minus_left(10, 3, 2) << '\n';
    std::cout << "fold_minus_right(10, 3, 2)    = " << fold_minus_right(10, 3, 2) << '\n';
    std::cout << "fold_minus_left(10, 4, 3, 1)  = " << fold_minus_left(10, 4, 3, 1) << '\n';
    std::cout << "fold_minus_right(10, 4, 3, 1) = " << fold_minus_right(10, 4, 3, 1) << '\n';

#ifdef SHOW_STATIC_ASSERT_ERROR
    // Kompilacja z -DSHOW_STATIC_ASSERT_ERROR pokazuje błąd static_assert.
    std::cout << fold_sum(std::string("a")) << '\n';
#endif
    return 0;
}
