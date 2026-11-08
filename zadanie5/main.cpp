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
}

// Liczba predykatów, które zwróciły false dla obj.
// Fold po + nie ma krótkiego spięcia: wszystkie predykaty są wywoływane.
// Wartość początkowa std::size_t{0} daje wynik 0 dla pustej paczki
// i ustala typ wyniku.
template <typename T, typename... Preds>
std::size_t count_failed([[maybe_unused]] const T& obj, const Preds&... preds) {
    // TODO
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

// Sprawdza warunek; nie używamy assert, bo znika w trybie Release (NDEBUG).
bool check(const std::string& name, bool condition) {
    std::cout << (condition ? "[OK]   " : "[FAIL] ") << name << '\n';
    return condition;
}

int main() {
    auto name_not_empty = [](const User& u) { return !u.name.empty(); };
    auto adult          = [](const User& u) { return u.age >= 18; };
    auto email_has_at   = [](const User& u) { return u.email.find('@') != std::string::npos; };

    const User ok{"Anna", 25, "anna@example.com"};
    const User bad{"", 15, "brak-maila"};
    const User half{"Bob", 15, "bob@example.com"};

    bool all_ok = true;

    std::cout << "Walidacja:\n";
    all_ok &= check("validate_all(ok, 3 predykaty) == true",
                    validate_all(ok, name_not_empty, adult, email_has_at) == true);
    all_ok &= check("validate_all(bad, 3 predykaty) == false",
                    validate_all(bad, name_not_empty, adult, email_has_at) == false);
    all_ok &= check("validate_all(ok) == true  (brak predykatow)", validate_all(ok) == true);

    std::cout << "\nZliczanie:\n";
    all_ok &= check("count_failed(ok, 3 predykaty) == 0",
                    count_failed(ok, name_not_empty, adult, email_has_at) == 0);
    all_ok &= check("count_failed(bad, 3 predykaty) == 3",
                    count_failed(bad, name_not_empty, adult, email_has_at) == 3);
    all_ok &= check("count_failed(half, 3 predykaty) == 1",
                    count_failed(half, name_not_empty, adult, email_has_at) == 1);
    all_ok &= check("count_failed(ok) == 0  (brak predykatow)", count_failed(ok) == 0);

    std::cout << "\nRozne rodzaje predykatow (funkcja, funktor, lambda):\n";
    all_ok &= check("validate_all(ok, has_name, MinAge{18}, lambda) == true",
                    validate_all(ok, has_name, MinAge{18}, email_has_at) == true);
    all_ok &= check("count_failed(bad, has_name, MinAge{18}, lambda) == 3",
                    count_failed(bad, has_name, MinAge{18}, email_has_at) == 3);

    std::cout << "\nKrotkie spiecie:\n";
    int calls = 0;
    auto always_fail = [&calls](const User&) {
        ++calls;
        return false;
    };

    validate_all(ok, always_fail, always_fail, always_fail);
    all_ok &= check("validate_all wywoluje predykat 1 raz (calls == 1)", calls == 1);

    calls = 0;
    count_failed(ok, always_fail, always_fail, always_fail);
    all_ok &= check("count_failed wywoluje predykat 3 razy (calls == 3)", calls == 3);

    return all_ok ? 0 : 1;
}
