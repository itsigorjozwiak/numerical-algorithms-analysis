# Analiza błędu przybliżenia pochodnej

Projekt realizuje numeryczne wyznaczanie pochodnej funkcji przy użyciu ilorazu różnicowego progresywnego (wprzód) oraz centralnego. Głównym celem zadania jest analiza zachowania błędu aproksymacji w zależności od malejącego kroku dyskretyzacji `h`.

Program bada zjawisko stabilności numerycznej, zestawiając teoretyczny błąd obcięcia z błędem zaokrągleń. Porównuje moment utraty precyzji dla różnych typów zmiennoprzecinkowych (`float` oraz `double`), aż do granicy epsilona maszynowego.

## Implementacja
Testy numeryczne przeprowadzono dla funkcji:
* `f(x) = sin(x^3)` (dla punktów x = 0.2 i x = 0.4)
* `f(x) = x^2 + 4x + 2` (dla punktu x = 0.2)

Kod generuje surowe dane wyjściowe (wartości `h` oraz wartości błędów całkowitych dla obu wzorów), które posłużyły do wykreślenia zależności w skali logarytmicznej.

## Uruchomienie i kompilacja (Linux / macOS)

Aby skompilować program i wygenerować pliki z danymi wynikowymi, wykonaj:

```bash
make clean
make all
make run
