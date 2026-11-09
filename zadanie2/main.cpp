#include <cassert>
#include <cstddef>
#include <iostream>
#include <type_traits>

// Zwraca true, jeśli wszystkie argumenty są "prawdziwe" (po rzutowaniu na bool).
// Unarny prawostronny fold po &&: dla pustej paczki wynik to true.
template <typename... Args>
bool all_true(const Args&... args) {
    // TODO
    return false;
}

// Zwraca true, jeśli co najmniej jeden argument jest "prawdziwy".
// Unarny prawostronny fold po ||: dla pustej paczki wynik to false.
template <typename... Args>
bool any_true(const Args&... args) {
    // TODO
    return false;
}

// Zwraca true, jeśli wszystkie typy Ts... są identyczne z T.
// Funkcja nie ma argumentów: typy podaje się jako argumenty szablonu.
// Dla pojedynczego typu (pusta paczka Ts) wynik to true.
template <typename T, typename... Ts>
bool all_same() {
    // TODO
    return false;
}

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

    std::cout << "Wszystkie testy przeszly.\n";
    return 0;
}
