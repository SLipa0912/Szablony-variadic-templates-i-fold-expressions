#include <cassert>
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

// Wynik print_with_sep jako string
template <typename Sep, typename... Args>
std::string to_str(const Sep& sep, const Args&... args) {
    std::ostringstream oss;
    print_with_sep(oss, sep, args...);
    return oss.str();
}

int main() {
    std::cout << "print_with_sep bezposrednio na std::cout:\n";
    print_with_sep(std::cout, ", ", 1, 2, 3);
    std::cout << '\n';
    print_with_sep(std::cout, " | ", "a", 'b', 3.5, std::string("str"));
    std::cout << "\n\n";

    // Testy print_with_sep
    assert(to_str(", ", 1, 2, 3) == "1, 2, 3");
    assert(to_str(" | ", "a", 'b', 3.5, std::string("str")) == "a | b | 3.5 | str");
    assert(to_str('-', 1, 2) == "1-2");
    assert(to_str(";", 42) == "42");
    assert(to_str(";") == "");

    // Testy emplace_all: lvalue -> kopia, rvalue -> przeniesienie
    {
        std::vector<Tracer> v;
        v.reserve(3);
        Tracer lvalue(1);
        Tracer::copies = 0;
        Tracer::moves = 0;
        emplace_all(v, lvalue, Tracer(2), Tracer(3));
        assert(v.size() == 3);
        assert(Tracer::copies == 1);
        assert(Tracer::moves == 2);
    }
    // Typ move-only: bez forwardingu (Args... przez wartość) by się nie skompilowało.
    {
        std::vector<std::unique_ptr<int>> ptrs;
        emplace_all(ptrs, std::make_unique<int>(10), std::make_unique<int>(20));
        assert(ptrs.size() == 2);
        assert(*ptrs[0] == 10);
        assert(*ptrs[1] == 20);
    }
    {
        std::vector<std::string> names;
        emplace_all(names, "ala", std::string("ola"));
        assert(names.size() == 2);
        assert(names[0] == "ala");
        assert(names[1] == "ola");
        emplace_all(names);  // zero argumentów: nic się nie dzieje
        assert(names.size() == 2);
    }

    std::cout << "Wszystkie testy przeszly.\n";
    return 0;
}
