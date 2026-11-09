#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

enum class Level { Debug, Info, Warning, Error };

const char* level_name(Level level) {
    switch (level) {
        case Level::Debug:   return "DEBUG";
        case Level::Info:    return "INFO";
        case Level::Warning: return "WARNING";
        case Level::Error:   return "ERROR";
    }
    return "UNKNOWN";
}

namespace detail {

// Koniec rekurencji: nie ma już nic do wypisania.
inline void print_pairs(std::ostream&) {
    // TODO
}

// Klucz bez wartości (nieparzysta liczba argumentów): wypisujemy "klucz=?".
template <typename K>
void print_pairs(std::ostream& os, const K& key) {
    // TODO
}

// Wypisuje jedną parę klucz=wartość i rekurencyjnie przetwarza resztę paczki.
// Pary trudno wyrazić pojedynczym foldem, bo fold widzi pojedyncze elementy paczki,
// a tu potrzebujemy brać po dwa na raz.
template <typename K, typename V, typename... Rest>
void print_pairs(std::ostream& os, const K& key, const V& value, const Rest&... rest) {
    // TODO
}

// Brak kontekstu: nie wypisujemy nic (także znaku '|').
inline void print_context(std::ostream&) {
    // TODO
}

// Jest kontekst: wypisujemy " |" i wszystkie pary.
template <typename K, typename... Rest>
void print_context(std::ostream& os, const K& first, const Rest&... rest) {
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

int main() {
    std::cout << "Przyklad dzialania:\n";
    StructuredLogger logger(std::cout);
    logger.log(Level::Info, "Server started");
    logger.log(Level::Info, "User logged in", "user", "anna", "id", 42);
    logger.log(Level::Error, "Payment failed", "order", 1001, "amount", 49.99, "retry", true);
    logger.log(Level::Warning, "Odd args", "key");
    std::cout << '\n';

    // Testy: każde wywołanie loguje do własnego strumienia w pamięci.
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Info, "Server started");
        assert(oss.str() == "[INFO] Server started\n");
    }
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Info, "User logged in", "user", "anna", "id", 42);
        assert(oss.str() == "[INFO] User logged in | user=anna id=42\n");
    }
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Error, "Payment failed", "order", 1001, "amount", 49.99, "retry", true);
        assert(oss.str() == "[ERROR] Payment failed | order=1001 amount=49.99 retry=true\n");
    }
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Debug, "Cache", std::string("hits"), 10, 'x', 2.5);
        assert(oss.str() == "[DEBUG] Cache | hits=10 x=2.5\n");
    }
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Warning, "Low disk", "free_mb", 120);
        assert(oss.str() == "[WARNING] Low disk | free_mb=120\n");
    }
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Warning, "Odd args", "key");
        assert(oss.str() == "[WARNING] Odd args | key=?\n");
    }
    {
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Warning, "Odd args 3", "a", 1, "b");
        assert(oss.str() == "[WARNING] Odd args 3 | a=1 b=?\n");
    }
    {
        // boolalpha nie może zostać włączony na stałe w strumieniu użytkownika.
        std::ostringstream oss;
        StructuredLogger l(oss);
        l.log(Level::Info, "flag", "ok", true);
        oss.str("");
        oss << true;
        assert(oss.str() == "1");
    }

    std::cout << "Wszystkie testy przeszly.\n";
    return 0;
}
