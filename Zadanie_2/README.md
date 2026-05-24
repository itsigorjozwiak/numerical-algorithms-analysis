# Uwarunkowanie macierzy

Projekt analizuje wrażliwość układów równań liniowych $Ax = b$ na mikroskopijne zaburzenia wektora wyrazów wolnych ($\Delta b$). Głównym celem modułu jest zbadanie wpływu wskaźnika uwarunkowania macierzy na stabilność numeryczną rozwiązań.

## Realizacja i wyniki
Obliczenia opierają się na badaniu norm macierzowych (norma nieskończoność) i zestawiają ze sobą dwa skrajne przypadki:
1. **Macierz dobrze uwarunkowana** ($\kappa \approx 7$): zaburzenie rzędu $10^{-6}$ powoduje pomijalnie małe odchylenie wektora wynikowego.
2. **Macierz źle uwarunkowana** ($\kappa \approx 1.16 \cdot 10^{11}$): mikroskopijny szum całkowicie zniekształca poprawność wektora rozwiązań.

## Uruchomienie (Wolfram Mathematica)

Całość obliczeń oraz weryfikacja analityczna zostały przeprowadzone w środowisku Wolfram Mathematica. 

Aby odtworzyć proces, otwórz plik źródłowy `NUM2.nb` bezpośrednio w programie Mathematica. Pełne wnioski i macierze wyników dostępne są w raporcie PDF
