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

| # | Katalog | Zadanie | Poziom | Szacowany czas |
|---|---|---|---|---|
| 1 | `zadanie1/` | Suma i iloczyn wariadyczny (`fold_sum`, `fold_product`) | Proste | 5 min |
| 2 | `zadanie2/` | Sprawdzanie warunków i typów (`all_true`, `all_same_v`) | Proste | 5 min |
| 3 | `zadanie3/` | Formater strumieniowy z separatorem (`print_with_sep`) | Średnie | 10 min |
| 4 | `zadanie4/` | System logowania kontekstowego (`StructuredLogger`) | Zaawansowane | 20 min |
| 5 | `zadanie5/` | Silnik walidacji obiektów (`validate_all`) | Średnie | 15–20 min |

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
cmake --build build
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

* **`zadanie1/`**: Implementacja `fold_sum` oraz `fold_product` z wykorzystaniem unarnych lub binarnych wyrażeń fold (lewo- lub prawostronnych).
* **`zadanie2/`**: Funkcja `all_true` sprawdzająca warunki logiczne oraz szablon zmiennej `all_same_v` weryfikujący zgodność typów.
* **`zadanie3/`**: Funkcja `print_with_sep` drukująca dowolną liczbę argumentów rozdzielonych separatorem, bez nadmiarowego separatora na końcu.
* **`zadanie4/`**: Klasa `StructuredLogger` z metodą `log`, która przyjmuje poziom, komunikat oraz dowolną liczbę par klucz–wartość (poprawność liczby argumentów sprawdza `static_assert`) i drukuje je w jednej linii.
* **`zadanie5/`**: Funkcja `validate_all` uruchamiająca dowolną liczbę predykatów walidujących na podanym obiekcie (fold `&&`) oraz zliczająca niespełnione warunki.
