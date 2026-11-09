#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>

// true, gdy KAŻDY predykat zwraca true dla obj.
// Unarny prawostronny fold po &&: ma krótkie spięcie (short-circuit),
// więc po pierwszym predykacie zwracającym false kolejne nie są wywoływane.
// Dla pustej paczki wynik to true.
// [[maybe_unused]] usuwa ostrzeżenie, gdy paczka jest pusta i obj nie jest użyty.
template <typename T, typename... Preds>
bool validate_all([[maybe_unused]] const T& obj, const Preds&... preds) {
    // TODO
    return false;
}

// Liczba predykatów, które zwróciły false dla obj.
// Fold po + nie ma krótkiego spięcia: wszystkie predykaty są wywoływane.
// Wartość początkowa std::size_t{0} daje wynik 0 dla pustej paczki
// i ustala typ wyniku.
template <typename T, typename... Preds>
std::size_t count_failed([[maybe_unused]] const T& obj, const Preds&... preds) {
    // TODO
    return 0;
}

// ---- Dane i predykaty do testów ----

struct User {
    std::string name;
    int age;
    std::string email;
};

// Zwykła funkcja jako predykat
bool has_name(const User& u) { return !u.name.empty(); }

// Obiekt funkcyjny jako predykat
struct MinAge {
    int min;
    bool operator()(const User& u) const { return u.age >= min; }
};

int main() {
    auto name_not_empty = [](const User& u) { return !u.name.empty(); };
    auto adult          = [](const User& u) { return u.age >= 18; };
    auto email_has_at   = [](const User& u) { return u.email.find('@') != std::string::npos; };

    const User ok{"Anna", 25, "anna@example.com"};
    const User bad{"", 15, "brak-maila"};
    const User half{"Bob", 15, "bob@example.com"};

    // Walidacja
    assert(validate_all(ok, name_not_empty, adult, email_has_at) == true);
    assert(validate_all(bad, name_not_empty, adult, email_has_at) == false);
    assert(validate_all(ok) == true);  // brak predykatów

    // Zliczanie
    assert(count_failed(ok, name_not_empty, adult, email_has_at) == 0);
    assert(count_failed(bad, name_not_empty, adult, email_has_at) == 3);
    assert(count_failed(half, name_not_empty, adult, email_has_at) == 1);
    assert(count_failed(ok) == 0);  // brak predykatów

    // Różne rodzaje predykatów: funkcja, funktor, lambda
    assert(validate_all(ok, has_name, MinAge{18}, email_has_at) == true);
    assert(count_failed(bad, has_name, MinAge{18}, email_has_at) == 3);

    // Krótkie spięcie: wywołania liczymy poza assert, żeby nie zależały od jego działania.
    int calls = 0;
    auto always_fail = [&calls](const User&) {
        ++calls;
        return false;
    };

    validate_all(ok, always_fail, always_fail, always_fail);
    assert(calls == 1);

    calls = 0;
    count_failed(ok, always_fail, always_fail, always_fail);
    assert(calls == 3);

    std::cout << "Wszystkie testy przeszly.\n";
    return 0;
}
