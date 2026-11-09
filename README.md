# Szablony wariadyczne (Variadic Templates) i wyrażenia fold (Fold Expressions)

Każde zadanie znajduje się w osobnym katalogu (`zadanie1/`, `zadanie2/`, `zadanie3/`, `zadanie4/`, `zadanie5/`) i posiada własny plik `CMakeLists.txt`.

Szczegółowe treści zadań, wyjaśnienia i przykładowe użycie znajdują się w pliku [zadania.md](zadania.md).

---

## Wymagania techniczne

* **Kompilator:** z obsługą C++17 lub nowszy (GCC >= 7, Clang >= 5, MSVC >= 19.14 / Visual Studio 2017 15.7)
* **System budowania:** CMake >= 3.14

Nazwa pliku wykonywalnego w każdym zadaniu jest taka sama jak nazwa jego katalogu (np. `add_executable(zadanie1 ...)` w `zadanie1/CMakeLists.txt`).

---

## Podział czasu (55–60 min)

| # | Katalog | Zadanie | Poziom |
|---|---|---|---|---|
| 1 | `zadanie1/` | Suma, iloczyn i kierunek foldu (`fold_sum`, `fold_product`, `fold_minus_left`, `fold_minus_right`) | Proste |
| 2 | `zadanie2/` | Warunki i typy (`all_true`, `any_true`, `all_same`) | Proste |
| 3 | `zadanie3/` | Fold po przecinku (`print_with_sep`, `emplace_all`) | Średnie |
| 4 | `zadanie4/` | System logowania kontekstowego (`StructuredLogger`) | Zaawansowane |
| 5 | `zadanie5/` | Silnik walidacji obiektów (`validate_all`, `count_failed`) | Średnie |

---

## Kompilacja i uruchomienie

Wszystkie polecenia należy wykonywać po przejściu do katalogu konkretnego zadania.

### Linux / macOS

```bash
cd zadanie1
cmake -B build
cmake --build build
./build/zadanie1
```

### Windows

#### Visual Studio / MSVC (PowerShell / Command Prompt)

```cmd
cd zadanie1
cmake -B build
cmake --build build --config Debug
.\build\Debug\zadanie1.exe
```

#### MinGW / GCC (PowerShell / Command Prompt)

```cmd
cd zadanie1
cmake -B build -G "MinGW Makefiles"
cmake --build build
.\build\zadanie1.exe
```

---

## Krótki indeks zadań

* **`zadanie1/`**: Funkcje `fold_sum` i `fold_product` (fold binarny z wartością początkową) oraz `fold_minus_left` i `fold_minus_right`, które pokazują różnicę między foldem lewo- i prawostronnym.
* **`zadanie2/`**: Funkcje `all_true` i `any_true` (fold `&&` i `||`), szablon funkcji `all_same`.
* **`zadanie3/`**: Funkcja `print_with_sep` drukująca dowolną liczbę argumentów rozdzielonych separatorem, bez nadmiarowego separatora na końcu, oraz `emplace_all` z perfect forwarding (`Args&&...`, `std::forward`).
* **`zadanie4/`**: Klasa `StructuredLogger` z metodą `log`, która przyjmuje poziom, komunikat oraz dowolną liczbę par klucz–wartość (przy nieparzystej liczbie argumentów ostatni klucz jest wypisywany jako `klucz=?`) i drukuje je w jednej linii.
* **`zadanie5/`**: Funkcja `validate_all` uruchamiająca dowolną liczbę predykatów walidujących na podanym obiekcie (fold `&&`, z krótkim spięciem) oraz funkcja `count_failed` zliczająca niespełnione warunki (fold `+`).
