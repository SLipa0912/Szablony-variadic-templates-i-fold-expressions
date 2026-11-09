#include <cassert>
#include <cstddef>
#include <iostream>
#include <type_traits>

// Zwraca true, jeśli wszystkie argumenty są "prawdziwe" (po rzutowaniu na bool).
// Unarny prawostronny fold po &&: dla pustej paczki wynik to true.
template <typename... Args>
bool all_true(const Args&... args) {
    // TODO
}

// Zwraca true, jeśli co najmniej jeden argument jest "prawdziwy".
// Unarny prawostronny fold po ||: dla pustej paczki wynik to false.
template <typename... Args>
bool any_true(const Args&... args) {
    // TODO
}

// Zwraca true, jeśli wszystkie typy Ts... są identyczne z T.
// Funkcja nie ma argumentów: typy podaje się jako argumenty szablonu.
// Dla pojedynczego typu (pusta paczka Ts) wynik to true.
template <typename T, typename... Ts>
bool all_same() {
    // TODO
}

// Wariadyczny szablon klasy: lista typów.
template <typename... Ts>
struct TypeList {
    // Liczba typów na liście
    static std::size_t size() {
        // TODO
    }

    // Czy T występuje na liście? Fold po || (dla pustej listy false).
    template <typename T>
    static bool contains() {
        // TODO
    }

    // Ile razy T występuje na liście? Binarny PRAWOSTRONNY fold: (pack + ... + init).
    template <typename T>
    static std::size_t count() {
        // TODO
    }
};

int main() {
    int x = 5;

    // all_true i any_true
    assert(all_true(true, 1, 2.5) == true);
    assert(all_true(true, 0, 3) == false);
    assert(all_true(&x, x > 3) == true);
    assert(all_true() == true);
    assert(any_true(false, 0, 3) == true);
    assert(any_true(0, false) == false);
    assert(any_true() == false);

    // UWAGA: assert jest makrem, więc przecinki w argumentach szablonu
    // (np. all_same<int, int, int>) trzeba zamknąć w dodatkowym nawiasie.

    // all_same
    assert((all_same<int, int, int>() == true));
    assert((all_same<int, int, double>() == false));
    assert(all_same<int>() == true);
    assert((all_same<int, const int>() == false));
    assert((all_same<int, int&>() == false));

    // TypeList
    assert((TypeList<int, char, int>::size() == 3));
    assert(TypeList<>::size() == 0);
    assert((TypeList<int, char>::contains<char>() == true));
    assert((TypeList<int, char>::contains<double>() == false));
    assert(TypeList<>::contains<int>() == false);
    assert((TypeList<int, char, int>::count<int>() == 2));
    assert((TypeList<int, char>::count<double>() == 0));
    assert(TypeList<>::count<int>() == 0);

    std::cout << "Wszystkie testy przeszly.\n";
    return 0;
}
