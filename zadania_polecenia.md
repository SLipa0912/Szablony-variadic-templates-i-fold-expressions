# Treści zadań

* Przypomnienie składni fold dla operatora `op` i paczki `args`:

| Nazwa | Składnia | Rozwija się do |
|---|---|---|
| Unarny lewostronny | `(... op args)` | `((a1 op a2) op a3) op ...` |
| Unarny prawostronny | `(args op ...)` | `a1 op (a2 op (a3 op ...))` |
| Binarny lewostronny | `(init op ... op args)` | `((init op a1) op a2) op ...` |
| Binarny prawostronny | `(args op ... op init)` | `a1 op (a2 op (... op init))` |

Dla pustej paczki unarny fold jest dozwolony tylko dla operatorów `&&` (wynik `true`), `||` (wynik `false`) oraz `,` (wynik `void()`). Dla pozostałych operatorów potrzebna jest wartość początkowa (fold binarny).

---

## Zadanie 1: Suma i iloczyn wariadyczny (5 min)

**Cel:** pierwsze użycie wyrażeń fold z operatorami `+` i `*`.

**Polecenie**

1. Napisz szablon funkcji `fold_sum`, który zwraca sumę wszystkich argumentów:
   ```cpp
   template <typename... Args>
   constexpr auto fold_sum(Args... args);
   ```
2. Napisz szablon funkcji `fold_product`, który zwraca iloczyn wszystkich argumentów:
   ```cpp
   template <typename... Args>
   constexpr auto fold_product(Args... args);
   ```
3. Obie funkcje mają działać dla dowolnej liczby argumentów, także zerowej:
   * `fold_sum()` zwraca `0`,
   * `fold_product()` zwraca `1`.
4. Obie funkcje mają działać dla typów całkowitych i zmiennoprzecinkowych (także mieszanych).

**Oczekiwane wartości**

| Wywołanie | Wynik |
|---|---|
| `fold_sum(1, 2, 3, 4)` | `10` |
| `fold_sum(1.5, 2.25, 3.0)` | `6.75` |
| `fold_sum()` | `0` |
| `fold_product(2, 3, 4)` | `24` |
| `fold_product(1.5, 2, 4)` | `12` |
| `fold_product()` | `1` |

**Wskazówki**

* Użyj binarnego foldu z wartością początkową: `(0 + ... + args)`.
* Zastanów się, jaką wartość początkową wybrać dla mnożenia (element neutralny).

---

## Zadanie 2: Sprawdzanie warunków i typów (5 min)

**Cel:** fold z operatorem `&&` oraz użycie foldu w szablonie zmiennej.

**Polecenie**

1. Napisz funkcję `all_true`, która zwraca `true`, gdy wszystkie argumenty po rzutowaniu na `bool` są prawdziwe:
   ```cpp
   template <typename... Args>
   constexpr bool all_true(const Args&... args);
   ```
   Dla pustej listy argumentów wynik ma być `true`.
2. Napisz szablon zmiennej `all_same_v`, który sprawdza, czy wszystkie podane typy są identyczne z pierwszym:
   ```cpp
   template <typename T, typename... Ts>
   inline constexpr bool all_same_v = /* ... */;
   ```
   `all_same_v<int>` (jeden typ) ma być `true`.

**Oczekiwane wartości**

| Wyrażenie | Wynik |
|---|---|
| `all_true(true, 1, 2.5)` | `true` |
| `all_true(true, 0, 3)` | `false` |
| `all_true()` | `true` |
| `all_same_v<int, int, int>` | `true` |
| `all_same_v<int, int, double>` | `false` |
| `all_same_v<int>` | `true` |
| `all_same_v<int, const int>` | `false` |

**Wskazówki**

* W `all_true` użyj `static_cast<bool>(args)` i foldu po `&&`.
* W `all_same_v` użyj `std::is_same_v<T, Ts>` (nagłówek `<type_traits>`) i foldu po `&&`.

---

## Zadanie 3: Formater strumieniowy z separatorem (10 min)

**Cel:** fold po operatorze przecinka i unikanie nadmiarowego separatora.

**Polecenie**

Napisz funkcję `print_with_sep`, która drukuje do strumienia dowolną liczbę argumentów rozdzielonych separatorem:

```cpp
template <typename Sep, typename... Args>
void print_with_sep(std::ostream& os, const Sep& sep, const Args&... args);
```

Wymagania:

1. Separator jest drukowany **tylko między** argumentami, nigdy na początku ani na końcu.
2. Argumenty mogą mieć różne typy (`int`, `double`, `char`, `const char*`, `std::string`, ...), byle dało się je wypisać przez `operator<<`.
3. Separator może być dowolnym typem wypisywalnym do strumienia (np. `", "` albo `'-'`).
4. Dla zerowej liczby argumentów funkcja nic nie drukuje.

**Przykłady**

| Wywołanie | Wypisany tekst |
|---|---|
| `print_with_sep(std::cout, ", ", 1, 2, 3)` | `1, 2, 3` |
| `print_with_sep(std::cout, " \| ", "a", 'b', 3.5, std::string("str"))` | `a \| b \| 3.5 \| str` |
| `print_with_sep(std::cout, '-', 1, 2)` | `1-2` |
| `print_with_sep(std::cout, ";", 42)` | `42` |
| `print_with_sep(std::cout, ";")` | *(nic)* |

**Wskazówki**

* Pierwszy argument wypisz osobno (bez separatora), a pozostałe wyrażeniem `((os << sep << rest), ...);`. Wymaga to dwóch przeciążeń: jednego dla zerowej liczby argumentów i jednego z parametrami `First` i `Rest...`.
* Alternatywa: jedna funkcja z flagą `bool first = true` i foldem po przecinku.

---

## Zadanie 4: System logowania kontekstowego (20 min)

**Cel:** przetwarzanie argumentów w parach, `static_assert` na rozmiarze paczki (`sizeof...`) oraz rekurencyjne rozwijanie paczki.

**Polecenie**

Zaimplementuj klasę `StructuredLogger`:

```cpp
enum class Level { Debug, Info, Warning, Error };

class StructuredLogger {
public:
    explicit StructuredLogger(std::ostream& os = std::cout);

    template <typename... Args>
    void log(Level level, const std::string& message, const Args&... context);
};
```

Wymagania:

1. Argumenty `context` to pary **klucz, wartość**: `klucz1, wartość1, klucz2, wartość2, ...`. Klucze i wartości mogą mieć dowolne typy wypisywalne do strumienia.
2. Liczba argumentów `context` musi być parzysta. Sprawdź to przez `static_assert(sizeof...(Args) % 2 == 0, "...")`, żeby błąd pojawiał się w czasie kompilacji.
3. Format linii: `[POZIOM] komunikat`. Jeśli są dane kontekstowe, dopisz ` | klucz1=wartość1 klucz2=wartość2 ...`. Bez kontekstu nie wypisuj znaku `|`.
4. Nazwy poziomów w wyjściu: `DEBUG`, `INFO`, `WARNING`, `ERROR`.
5. Wartości `bool` wypisuj jako `true` / `false` (`std::boolalpha`).
6. Każde wywołanie `log` kończy się znakiem nowej linii.

**Przykład użycia**

```cpp
StructuredLogger logger(std::cout);
logger.log(Level::Info, "Server started");
logger.log(Level::Info, "User logged in", "user", "anna", "id", 42);
logger.log(Level::Error, "Payment failed", "order", 1001, "amount", 49.99, "retry", true);
```

**Oczekiwane wyjście**

```
[INFO] Server started
[INFO] User logged in | user=anna id=42
[ERROR] Payment failed | order=1001 amount=49.99 retry=true
```

Wywołanie `logger.log(Level::Warning, "Odd args", "key");` ma się **nie skompilować** z komunikatem ze `static_assert`.

**Wskazówki**

* Pary najłatwiej przetworzyć rekurencyjnie: funkcja pomocnicza z parametrami `(os, const K& key, const V& value, const Rest&... rest)` wypisuje jedną parę i wywołuje samą siebie dla `rest...`, a przeciążenie bez argumentów kończy rekurencję.
* Do pominięcia części ` | ...` użyj `if constexpr (sizeof...(Args) > 0)`.
* Zamianę `Level` na tekst zrób osobną funkcją z `switch`.
---

## Zadanie 5: Silnik walidacji obiektów (15–20 min)

**Cel:** fold z predykatami wywoływanymi na wspólnym obiekcie, krótkie spięcie (short-circuit) oraz zliczanie.

**Polecenie**

Napisz dwa szablony funkcji:

```cpp
// true, gdy KAŻDY predykat zwraca true dla obiektu obj
template <typename T, typename... Preds>
bool validate_all(const T& obj, const Preds&... preds);

// liczba predykatów, które zwróciły false dla obiektu obj
template <typename T, typename... Preds>
std::size_t count_failed(const T& obj, const Preds&... preds);
```

Wymagania:

1. `validate_all` bez predykatów zwraca `true`, a `count_failed` bez predykatów zwraca `0`.
2. `validate_all` korzysta z krótkiego spięcia: po pierwszym predykacie zwracającym `false` kolejne **nie są** wywoływane.
3. `count_failed` wywołuje **wszystkie** predykaty (bez krótkiego spięcia).
4. Predykaty mogą być lambdami, wskaźnikami na funkcje lub obiektami funkcyjnymi.

**Przykład użycia**

```cpp
struct User {
    std::string name;
    int age;
    std::string email;
};

auto name_not_empty = [](const User& u) { return !u.name.empty(); };
auto adult          = [](const User& u) { return u.age >= 18; };
auto email_has_at   = [](const User& u) { return u.email.find('@') != std::string::npos; };

User ok{"Anna", 25, "anna@example.com"};
User bad{"", 15, "brak-maila"};
```

**Oczekiwane wartości**

| Wywołanie | Wynik |
|---|---|
| `validate_all(ok, name_not_empty, adult, email_has_at)` | `true` |
| `validate_all(bad, name_not_empty, adult, email_has_at)` | `false` |
| `count_failed(ok, name_not_empty, adult, email_has_at)` | `0` |
| `count_failed(bad, name_not_empty, adult, email_has_at)` | `3` |
| `validate_all(ok)` | `true` |
| `count_failed(ok)` | `0` |

**Test krótkiego spięcia**

```cpp
int calls = 0;
auto always_fail = [&calls](const User&) { ++calls; return false; };

validate_all(ok, always_fail, always_fail, always_fail);   // po wywołaniu: calls == 1
calls = 0;
count_failed(ok, always_fail, always_fail, always_fail);   // po wywołaniu: calls == 3
```

**Wskazówki**

* `validate_all`: `(preds(obj) && ...)`.
* `count_failed`: zamień wynik każdego predykatu na `0` lub `1` i zsumuj foldem z wartością początkową typu `std::size_t`.
* Przy pustej paczce parametr `obj` jest nieużywany, więc oznacz go `[[maybe_unused]]`, żeby uniknąć ostrzeżenia.
