#include <iostream>
#include <sstream>
#include <string>

enum class Level { Debug, Info, Warning, Error };

constexpr const char* level_name(Level level) {
    // TODO
}

namespace detail {

// Koniec rekurencji: nie ma już par do wypisania.
inline void print_pairs(std::ostream&) {
    // TODO
}

// Wypisuje jedną parę klucz=wartość i rekurencyjnie przetwarza resztę paczki.
// Pary trudno wyrazić pojedynczym foldem, bo fold widzi pojedyncze elementy paczki,
// a tu potrzebujemy brać po dwa na raz.
template <typename K, typename V, typename... Rest>
void print_pairs(std::ostream& os, const K& key, const V& value, const Rest&... rest) {
    // TODO
}

}  // namespace detail

class StructuredLogger {
public:
    explicit StructuredLogger(std::ostream& os = std::cout) : os_(os) {}

    template <typename... Args>
    void log(Level level, const std::string& message, const Args&... context) {
        // Zapamiętujemy flagi strumienia, żeby boolalpha nie "wyciekło" na zewnątrz.
        // TODO
    }

private:
    std::ostream& os_;
};

// Sprawdza wynik; nie używamy assert, bo znika w trybie Release (NDEBUG).
bool check(const std::string& name, const std::string& actual, const std::string& expected) {
    const bool ok = (actual == expected);
    std::cout << (ok ? "[OK]   " : "[FAIL] ") << name;
    if (!ok) {
        std::cout << "\n       otrzymano:  \"" << actual << "\""
                  << "\n       oczekiwano: \"" << expected << "\"";
    }
    std::cout << '\n';
    return ok;
}

int main() {
    std::cout << "Przyklad dzialania:\n";
    StructuredLogger logger(std::cout);
    logger.log(Level::Info, "Server started");
    logger.log(Level::Info, "User logged in", "user", "anna", "id", 42);
    logger.log(Level::Error, "Payment failed", "order", 1001, "amount", 49.99, "retry", true);

#ifdef SHOW_STATIC_ASSERT_ERROR
    // Kompilacja z -DSHOW_STATIC_ASSERT_ERROR pokazuje błąd static_assert.
    logger.log(Level::Warning, "Odd args", "key");
#endif

    std::cout << "\nTesty:\n";
    bool all_ok = true;

    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Info, "Server started");
        all_ok &= check("bez kontekstu", oss.str(), "[INFO] Server started\n");
    }
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Info, "User logged in", "user", "anna", "id", 42);
        all_ok &= check("dwie pary", oss.str(), "[INFO] User logged in | user=anna id=42\n");
    }
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Error, "Payment failed", "order", 1001, "amount", 49.99, "retry", true);
        all_ok &= check("rozne typy wartosci", oss.str(),
                        "[ERROR] Payment failed | order=1001 amount=49.99 retry=true\n");
    }
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Debug, "Cache", std::string("hits"), 10, 'x', 2.5);
        all_ok &= check("klucze std::string i char", oss.str(), "[DEBUG] Cache | hits=10 x=2.5\n");
    }
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Warning, "Low disk", "free_mb", 120);
        all_ok &= check("poziom WARNING", oss.str(), "[WARNING] Low disk | free_mb=120\n");
    }
    {
        // boolalpha nie może zostać włączony na stałe w strumieniu użytkownika.
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Info, "flag", "ok", true);
        oss.str("");
        oss << true;
        all_ok &= check("flagi strumienia przywrocone", oss.str(), "1");
    }

    return all_ok ? 0 : 1;
}
