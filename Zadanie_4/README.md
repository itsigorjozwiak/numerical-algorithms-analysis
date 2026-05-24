# Metody iteracyjne: Jacobi vs Gauss-Seidel

Projekt realizuje numeryczne rozwiązywanie układu równań liniowych $Ax = b$ dla rzadkiej macierzy wstęgowej przy użyciu dwóch metod iteracyjnych: algorytmu Jacobiego oraz algorytmu Gaussa-Seidela.

Głównym celem modułu jest benchmarking tempa zbieżności obu metod. Weryfikowany jest wpływ warunku silnej dominacji przekątnej (manipulacja parametrem $d$) oraz dobór różnych wektorów startowych na szybkość osiągnięcia zadanej tolerancji błędu. Zaimplementowana logika dowodzi wyższej efektywności obliczeniowej metody Gaussa-Seidela, która w procesie iteracji wykorzystuje na bieżąco zaktualizowane wartości niewiadomych.

## Uruchomienie i kompilacja

Projekt kompiluje się przy użyciu standardowego kompilatora C++ (np. `g++`). W terminalu przejdź do katalogu źródłowego i wykonaj:

```bash
g++ -std=c++11 main.cpp -o main
./main
```
