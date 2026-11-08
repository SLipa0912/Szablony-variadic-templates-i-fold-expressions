#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// print_with_sep
// ---------------------------------------------------------------------------

// Brak argumentów do wypisania: nic nie drukujemy.
template <typename Sep>
void print_with_sep(std::ostream&, const Sep&) {
    // TODO
}

// Pierwszy argument wypisujemy bez separatora, każdy kolejny poprzedzamy separatorem.
// Dzięki temu na końcu nie ma nadmiarowego separatora.
// Fold po operatorze przecinka gwarantuje kolejność wykonania od lewej do prawej.
template <typename Sep, typename First, typename... Rest>
void print_with_sep(std::ostream& os, [[maybe_unused]] const Sep& sep,
                    const First& first, const Rest&... rest) {
    // TODO
}

// ---------------------------------------------------------------------------
// emplace_all (perfect forwarding)
// ---------------------------------------------------------------------------

// Dodaje wszystkie argumenty do kontenera, zachowując kategorię wartości:
// lvalue zostaje skopiowane, rvalue przeniesione.
// Args&& to "forwarding reference", a std::forward<Args>(args) przekazuje dalej
// dokładnie ten rodzaj wartości, jaki dostaliśmy.
// Fold po przecinku wykonuje emplace_back od lewej do prawej.
template <typename Container, typename... Args>
void emplace_all([[maybe_unused]] Container& c, Args&&... args) {
    // TODO
}

// ---------------------------------------------------------------------------
// Pomocnicze elementy testów
// ---------------------------------------------------------------------------

// Typ liczący kopie i przeniesienia
struct Tracer {
    static inline int copies = 0;
    static inline int moves = 0;
    int id;

    explicit Tracer(int i) : id(i) {}
    Tracer(const Tracer& other) : id(other.id) { ++copies; }
    Tracer(Tracer&& other) noexcept : id(other.id) { ++moves; }
};

template <typename Sep, typename... Args>
std::string to_str(const Sep& sep, const Args&... args) {
    std::ostringstream oss;
    print_with_sep(oss, sep, args...);
    return oss.str();
}

// Sprawdzenia; nie używamy assert, bo znika w trybie Release (NDEBUG).
bool check_eq(const std::string& actual, const std::string& expected) {
    const bool ok = (actual == expected);
    std::cout << (ok ? "[OK]   " : "[FAIL] ") << '"' << actual << '"';
    if (!ok) {
        std::cout << " (oczekiwano: \"" << expected << "\")";
    }
    std::cout << '\n';
    return ok;
}

bool check_true(const std::string& name, bool condition) {
    std::cout << (condition ? "[OK]   " : "[FAIL] ") << name << '\n';
    return condition;
}

int main() {
    std::cout << "print_with_sep bezposrednio na std::cout:\n";
    print_with_sep(std::cout, ", ", 1, 2, 3);
    std::cout << '\n';
    print_with_sep(std::cout, " | ", "a", 'b', 3.5, std::string("str"));
    std::cout << "\n\n";

    bool all_ok = true;

    std::cout << "Testy print_with_sep:\n";
    all_ok &= check_eq(to_str(", ", 1, 2, 3), "1, 2, 3");
    all_ok &= check_eq(to_str(" | ", "a", 'b', 3.5, std::string("str")), "a | b | 3.5 | str");
    all_ok &= check_eq(to_str('-', 1, 2), "1-2");
    all_ok &= check_eq(to_str(";", 42), "42");
    all_ok &= check_eq(to_str(";"), "");

    std::cout << "\nTesty emplace_all:\n";
    {
        // Kopie i przeniesienia: lvalue -> kopia, rvalue -> przeniesienie.
        std::vector<Tracer> v;
        v.reserve(3);  // bez realokacji, żeby nie liczyć dodatkowych przeniesień
        Tracer lvalue(1);
        Tracer::copies = 0;
        Tracer::moves = 0;
        emplace_all(v, lvalue, Tracer(2), Tracer(3));
        all_ok &= check_true("rozmiar kontenera == 3", v.size() == 3);
        all_ok &= check_true("lvalue skopiowane raz (copies == 1)", Tracer::copies == 1);
        all_ok &= check_true("rvalue przeniesione dwa razy (moves == 2)", Tracer::moves == 2);
    }
    {
        // Typ move-only: bez forwardingu (Args... przez wartość) by się nie skompilowało.
        std::vector<std::unique_ptr<int>> ptrs;
        emplace_all(ptrs, std::make_unique<int>(10), std::make_unique<int>(20));
        all_ok &= check_true("typ move-only (unique_ptr)",
                             ptrs.size() == 2 && *ptrs[0] == 10 && *ptrs[1] == 20);
    }
    {
        std::vector<std::string> names;
        emplace_all(names, "ala", std::string("ola"));
        all_ok &= check_true("std::string z const char* i std::string",
                             names.size() == 2 && names[0] == "ala" && names[1] == "ola");
        emplace_all(names);  // zero argumentów: nic się nie dzieje
        all_ok &= check_true("zero argumentow nic nie dodaje", names.size() == 2);
    }

    return all_ok ? 0 : 1;
}
