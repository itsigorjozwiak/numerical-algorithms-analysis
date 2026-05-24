# Rozwiązywanie układów równań dla macierzy rzadkich

Projekt realizuje efektywne pamięciowo i czasowo rozwiązanie układu równań liniowych $Ay = x$ dla asymetrycznej macierzy pasmowej (cztery niezerowe diagonale).

Głównym celem modułu jest optymalizacja złożoności obliczeniowej. Zamiast klasycznych operacji na macierzach gęstych rzędu $O(N^3)$, zaimplementowano autorską, zoptymalizowaną wersję faktoryzacji LU (algorytm Doolittle'a) operującą wyłącznie na niezerowych wstęgach. Pozwoliło to na redukcję złożoności czasowej do $O(N)$. Dodatkowo program oblicza wyznacznik macierzy głównej oraz przeprowadza benchmarking czasu dzaiałania algorytmu w zależności od wymiaru $N$.

## Uruchomienie i kompilacja (Linux / macOS)

Aby skompilować program, wykonaj:  

```bash
make clean
make all
make run
