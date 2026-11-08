# Treści zadań

Szablony wariadyczne (variadic templates) i wyrażenia fold (fold expressions).

* Przypomnienie składni fold dla operatora `op` i paczki `args`:

| Nazwa | Składnia | Rozwija się do |
|---|---|---|
| Unarny lewostronny | `(... op args)` | `((a1 op a2) op a3) op ...` |
| Unarny prawostronny | `(args op ...)` | `a1 op (a2 op (a3 op ...))` |
| Binarny lewostronny | `(init op ... op args)` | `((init op a1) op a2) op ...` |
| Binarny prawostronny | `(args op ... op init)` | `a1 op (a2 op (... op init))` |

Dla pustej paczki unarny fold jest dozwolony tylko dla operatorów `&&` (wynik `true`), `||` (wynik `false`) oraz `,` (wynik `void()`). Dla pozostałych operatorów potrzebna jest wartość początkowa (fold binarny).

---

## Zadanie 1: Suma, iloczyn i kierunek foldu (7 min)

**Cel:** fold binarny z wartością początkową, różnica między foldem lewo- i prawostronnym oraz fold w `static_assert`.

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
   Dla pustej listy `fold_sum()` zwraca `0`, a `fold_product()` zwraca `1`.
3. Obie funkcje mają przyjmować wyłącznie typy arytmetyczne. Dla innych typów (np. `std::string`) kompilacja ma kończyć się błędem ze `static_assert`, którego warunek sprawdza całą paczkę naraz.
4. Napisz funkcje `fold_minus_left` i `fold_minus_right` o tej samej sygnaturze co `fold_sum`:
   * `fold_minus_left(a1, a2, a3, ...)` oblicza `((a1 - a2) - a3) - ...`,
   * `fold_minus_right(a1, a2, a3, ...)` oblicza `a1 - (a2 - (a3 - ...))`.

   Obie wymagają co najmniej jednego argumentu (dla zerowej liczby argumentów mają się nie kompilować).

**Oczekiwane wartości**

| Wywołanie | Wynik |
|---|---|
| `fold_sum(1, 2, 3, 4)` | `10` |
| `fold_sum(1.5, 2.25, 3.0)` | `6.75` |
| `fold_sum()` | `0` |
| `fold_product(2, 3, 4)` | `24` |
| `fold_product(1.5, 2, 4)` | `12` |
| `fold_product()` | `1` |
| `fold_minus_left(10, 3, 2)` | `5` |
| `fold_minus_right(10, 3, 2)` | `9` |
| `fold_minus_left(10, 4, 3, 1)` | `2` |
| `fold_minus_right(10, 4, 3, 1)` | `8` |
| `fold_minus_left(7)` i `fold_minus_right(7)` | `7` |

Dla tych samych argumentów `fold_minus_left` i `fold_minus_right` dają różne wyniki, bo odejmowanie nie jest łączne. Dla `+` i `*` kierunek foldu nie ma znaczenia.

**Wskazówki**

* Dla sumy i iloczynu użyj binarnego foldu z wartością początkową: `(0 + ... + args)`.
* Zastanów się, jaką wartość początkową wybrać dla mnożenia (element neutralny).
* Warunek na typy zapisz jako fold po `&&` nad `std::is_arithmetic_v<Args>` (nagłówek `<type_traits>`).
* Dla `fold_minus_left` i `fold_minus_right` użyj foldów unarnych, po jednym w każdym kierunku.

---

## Zadanie 2: Sprawdzanie warunków i typów (10 min)

**Cel:** fold z operatorami `&&` i `||`, szablon zmiennej oraz wariadyczny szablon klasy.

**Polecenie**

1. Napisz funkcję `all_true`, która zwraca `true`, gdy wszystkie argumenty po rzutowaniu na `bool` są prawdziwe:
   ```cpp
   template <typename... Args>
   constexpr bool all_true(const Args&... args);
   ```
   Dla pustej listy argumentów wynik ma być `true`.
2. Napisz funkcję `any_true`, która zwraca `true`, gdy **co najmniej jeden** argument po rzutowaniu na `bool` jest prawdziwy. Dla pustej listy argumentów wynik ma być `false`.
3. Napisz szablon zmiennej `all_same_v`, który sprawdza, czy wszystkie podane typy są identyczne z pierwszym:
   ```cpp
   template <typename T, typename... Ts>
   inline constexpr bool all_same_v = /* ... */;
   ```
   `all_same_v<int>` (jeden typ) ma być `true`.
4. Napisz wariadyczny szablon klasy `TypeList` z trzema składowymi statycznymi:
   ```cpp
   template <typename... Ts>
   struct TypeList {
       static constexpr std::size_t size = /* ... */;                 // liczba typów na liście

       template <typename T>
       static constexpr bool contains = /* ... */;                    // czy T jest na liście

       template <typename T>
       static constexpr std::size_t count = /* ... */;                // ile razy T jest na liście
   };
   ```
   Dla pustej listy: `size == 0`, `contains<T>` jest `false`, a `count<T>` wynosi `0`.

**Oczekiwane wartości**

| Wyrażenie | Wynik |
|---|---|
| `all_true(true, 1, 2.5)` | `true` |
| `all_true(true, 0, 3)` | `false` |
| `all_true()` | `true` |
| `any_true(false, 0, 3)` | `true` |
| `any_true(0, false)` | `false` |
| `any_true()` | `false` |
| `all_same_v<int, int, int>` | `true` |
| `all_same_v<int, int, double>` | `false` |
| `all_same_v<int>` | `true` |
| `all_same_v<int, const int>` | `false` |
| `TypeList<int, char, int>::size` | `3` |
| `TypeList<int, char>::contains<char>` | `true` |
| `TypeList<int, char>::contains<double>` | `false` |
| `TypeList<int, char, int>::count<int>` | `2` |
| `TypeList<>::size` | `0` |

`std::is_same_v` rozróżnia `const` i referencje, dlatego `all_same_v<int, const int>` jest `false`.

**Wskazówki**

* W `all_true` i `any_true` użyj `static_cast<bool>(args)` i foldu unarnego po `&&` lub `||`.
* W `all_same_v` użyj `std::is_same_v<T, Ts>` (nagłówek `<type_traits>`) i foldu po `&&`.
* `size` to zadanie dla operatora `sizeof...`.
* `contains` to fold po `||` nad `std::is_same_v<T, Ts>`.
* `count` zbuduj z foldu binarnego prawostronnego `(wyrażenie + ... + 0)`, gdzie wyrażenie daje `1` dla pasującego typu i `0` dla pozostałych.


---

## Zadanie 3: Fold po przecinku (12 min)

**Cel:** fold po operatorze przecinka w dwóch zastosowaniach: wypisywanie z separatorem oraz dodawanie do kontenera z perfect forwarding.

### Część A: `print_with_sep`

Napisz funkcję, która drukuje do strumienia dowolną liczbę argumentów rozdzielonych separatorem:

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
* Operator przecinka gwarantuje kolejność wykonania od lewej do prawej, więc argumenty zostaną wypisane w podanej kolejności.

### Część B: `emplace_all`

Napisz funkcję, która dodaje wszystkie argumenty na koniec kontenera, zachowując rodzaj każdej wartości:

```cpp
template <typename Container, typename... Args>
void emplace_all(Container& c, Args&&... args);
```

Wymagania:

1. Dla każdego argumentu wywołaj `c.emplace_back(...)`, od lewej do prawej.
2. Wartość lvalue ma zostać **skopiowana**, a wartość rvalue **przeniesiona**.
3. Funkcja ma działać dla typów move-only, np. `std::unique_ptr<int>`.
4. Dla zerowej liczby argumentów nic się nie dzieje.

**Oczekiwane zachowanie**

| Wywołanie | Wynik |
|---|---|
| `emplace_all(v, lvalue, Tracer(2), Tracer(3))` (`v` to `std::vector<Tracer>`, `Tracer` liczy kopie i przeniesienia) | 1 kopia, 2 przeniesienia |
| `emplace_all(ptrs, std::make_unique<int>(10), std::make_unique<int>(20))` | kontener ma 2 elementy: `10` i `20` |
| `emplace_all(names, "ala", std::string("ola"))` (`names` to `std::vector<std::string>`) | kontener ma 2 elementy: `"ala"` i `"ola"` |

**Wskazówki**

* Przyjmij argumenty jako `Args&&...` i przekaż je dalej przez `std::forward<Args>(args)` (nagłówek `<utility>`) w wyrażeniu pod foldem po przecinku.
* Przy `Args... args` (przez wartość) każdy argument byłby kopiowany, a `std::unique_ptr` w ogóle by się nie skompilował. Dlatego potrzebne jest `Args&&...` z `std::forward`.

---

## Zadanie 4: System logowania kontekstowego (15 min)

**Cel:** przetwarzanie argumentów w parach, `static_assert` na rozmiarze paczki (`sizeof...`) oraz rekurencyjne rozwijanie paczki.

**Polecenie**

Zaimplementuj klasę `StructuredLogger`. Typ `Level` oraz funkcja `level_name(Level)`, która zwraca tekst `"DEBUG"`, `"INFO"`, `"WARNING"` lub `"ERROR"`, są już zdefiniowane w pliku i nie są częścią zadania.

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
3. Format linii: `[POZIOM] komunikat`, gdzie `POZIOM` to wynik `level_name(level)`. Jeśli są dane kontekstowe, dopisz ` | klucz1=wartość1 klucz2=wartość2 ...`. Bez kontekstu nie wypisuj znaku `|`.
4. Wartości `bool` wypisuj jako `true` / `false` (`std::boolalpha`).
5. Każde wywołanie `log` kończy się znakiem nowej linii.

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
* Fold widzi pojedyncze elementy paczki, a tu trzeba brać po dwa naraz, dlatego użyj rekurencji.

---

## Zadanie 5: Silnik walidacji obiektów (15 min)

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

**Krótkie spięcie w praktyce**

```cpp
int calls = 0;
auto always_fail = [&calls](const User&) { ++calls; return false; };

validate_all(ok, always_fail, always_fail, always_fail);   // po wywołaniu: calls == 1
calls = 0;
count_failed(ok, always_fail, always_fail, always_fail);   // po wywołaniu: calls == 3
```

Różnica wynika z operatorów: `&&` przerywa obliczanie po pierwszym `false`, a `+` zawsze oblicza wszystkie operandy.

**Wskazówki**

* `validate_all`: `(preds(obj) && ...)`.
* `count_failed`: zamień wynik każdego predykatu na `0` lub `1` i zsumuj foldem z wartością początkową typu `std::size_t`.
* Przy pustej paczce parametr `obj` jest nieużywany, więc oznacz go `[[maybe_unused]]`, żeby uniknąć ostrzeżenia.
