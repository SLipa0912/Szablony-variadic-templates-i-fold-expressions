#include <cassert>
#include <iostream>

// Suma wszystkich argumentów. Dla pustej listy zwraca 0.
// Binarny lewostronny fold z wartością początkową: (init + ... + pack).
// Unarny fold (... + args) nie skompiluje się dla pustej paczki,
// dlatego potrzebna jest wartość początkowa.
template <typename... Args>
auto fold_sum(Args... args) {
    // TODO
}

// Iloczyn wszystkich argumentów. Dla pustej listy zwraca 1 (element neutralny mnożenia).
template <typename... Args>
auto fold_product(Args... args) {
    // TODO
}

// Unarny fold LEWOSTRONNY: ((a1 - a2) - a3) - ...
// Odejmowanie nie jest łączne, więc kierunek foldu zmienia wynik.
// Wymaga co najmniej jednego argumentu.
template <typename... Args>
auto fold_minus_left(Args... args) {
    // TODO
}

// Unarny fold PRAWOSTRONNY: a1 - (a2 - (a3 - ...))
template <typename... Args>
auto fold_minus_right(Args... args) {
    // TODO
}

int main() {
    // Suma i iloczyn
    assert(fold_sum(1, 2, 3, 4) == 10);
    assert(fold_sum(1.5, 2.25, 3.0) == 6.75);
    assert(fold_sum() == 0);
    assert(fold_product(2, 3, 4) == 24);
    assert(fold_product(1.5, 2, 4) == 12);
    assert(fold_product() == 1);

    // Kierunek foldu
    assert(fold_minus_left(10, 3, 2) == 5);       // (10 - 3) - 2
    assert(fold_minus_right(10, 3, 2) == 9);      // 10 - (3 - 2)
    assert(fold_minus_left(10, 4, 3, 1) == 2);    // ((10 - 4) - 3) - 1
    assert(fold_minus_right(10, 4, 3, 1) == 8);   // 10 - (4 - (3 - 1))
    assert(fold_minus_left(7) == 7);
    assert(fold_minus_right(7) == 7);

    std::cout << "Wszystkie testy przeszly.\n";
    return 0;
}
