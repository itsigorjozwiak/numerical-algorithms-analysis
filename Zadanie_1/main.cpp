#include <iostream>
#include <clocale>
#include <cmath>
#include <limits>
#include <fstream>
#include <iomanip>
const float hp_f = 1.0f;
const float hk_f = std::numeric_limits<float>::epsilon(); // epsilon maszynowy dla float
const double hp_d = 1.0;
const double hk_d = std::numeric_limits<double>::epsilon(); // epsilon maszynowy dla double

using namespace std;

template <typename T>
T sinus(T x){ // obliczanie funkcji sin(x^3) dla konkretnego x (uniwersalne dla float i double)
    return sin(pow(x, 3));
}
template <typename T>
T sinus_p(T x){ // obliczanie pochodnej funkcji sin(x^3) dla konkretnego x (uniwersalne dla float i double)
    return 3*pow(x, 2)*cos(pow(x, 3));
}
template <typename T>
T Dh_sinus_a(T x, T h){ // obliczanie przybliżenia pochodnej funkcji sin(x^3) ze wzoru z pkt.a (uniwersalne dla float i double)
    return (sinus(x + h) - sinus(x))/h;
}
template <typename T>
T Dh_sinus_b(T x, T h){ // obliczanie przybliżenia pochodnej funkcji sin(x^3) ze wzoru z pkt.b (uniwersalne dla float i double)
    return (sinus(x + h) - sinus(x - h))/(2*h);
}
template <typename T>
void blad_sinus(T x, const string &filename, T hp, T hk){ // funkcja licząca błędy numeryczne E(h) dla przybliżonego wzoru Dh(a) oraz Dh(b)
ofstream file(filename);
    cout <<"h " <<"-- Błąd E(h) (wzór-podpunkt a) --" << " Błąd E(h) (wzór-podpunkt b)" << endl;
    T h = hp;
    while (h >= hk) {
        T D1 = abs(Dh_sinus_a(x, h) - sinus_p(x));
        T D2 = abs(Dh_sinus_b(x, h) - sinus_p(x));
        file << h << " " << D1 << " " << D2 << endl;
        cout << h << " " << D1 << " " << D2 << endl;
        h = h/2; // wziąłem pod uwagę charakter logarytmiczny wykresu, który chcemy uzyskać :)
    }
    file.close();
}
template <typename T>
T kwadratowa(T x){ // obliczanie funkcji x^2+4x+2 dla konkretnego x (uniwersalne dla float i double)
    return pow(x, 2) + 4*x + 2;
}
template <typename T>
T kwadratowa_p(T x){ // obliczanie pochodnej funkcji x^2+4x+2 dla konkretnego x (uniwersalne dla float i double)
    return 2*x + 4;
}
template <typename T>
T Dh_kwadratowa_a(T x, T h){ // obliczanie przybliżenia pochodnej funkcji x^2+4x+2 ze wzoru z pkt.a (uniwersalne dla float i double)
    return (kwadratowa(x + h) - kwadratowa(x))/h;
}
template <typename T>
T Dh_kwadratowa_b(T x, T h){ // obliczanie przybliżenia pochodnej funkcji x^2+4x+2 ze wzoru z pkt.b (uniwersalne dla float i double)
    return (kwadratowa(x + h) - kwadratowa(x - h))/(2*h);
}
template <typename T>
void blad_kwadratowa(T x, const string &filename, T hp, T hk){ // funkcja licząca błędy numeryczne E(h) dla przybliżonego wzoru Dh(a) oraz Dh(b)
ofstream file(filename);
    cout <<"h " <<"-- Błąd E(h) (wzór-podpunkt a) --" << " Błąd E(h) (wzór-podpunkt b)" << endl;
    T h = hp;
    while (h >= hk) {
        T D1 = abs(Dh_kwadratowa_a(x, h) - kwadratowa_p(x));
        T D2 = abs(Dh_kwadratowa_b(x, h) - kwadratowa_p(x));
        file << h << " " << D1 << " " << D2 << endl;
        cout << h << " " << D1 << " " << D2 << endl;
        h = h/2; // wziąłem pod uwagę charakter logarytmiczny wykresu, który chcemy uzyskać :)
    }
    file.close();
}
int main(){
    setlocale(LC_CTYPE,"pl_PL.UTF-8");
    cout << "Błędy numeryczne dla zmiennej h, funkcji f(x) = sin(x^3) oraz punktu x = 0.2, typu float :" << endl;
    blad_sinus(0.2f, "sinus_f.csv",  hp_f, hk_f);
    cout << "Błędy numeryczne dla zmiennej h, funkcji f(x) = sin(x^3) oraz punktu x = 0.2, typu double :" << endl;
    blad_sinus(0.2, "sinus_d.csv",  hp_d, hk_d);

    cout << "Błędy numeryczne dla zmiennej h, funkcji f(x) = sin(x^3) oraz punktu x = 0.4, typu float :" << endl;
    blad_sinus(0.4f, "sinuss_f.csv",  hp_f, hk_f);
    cout << "Błędy numeryczne dla zmiennej h, funkcji f(x) = sin(x^3) oraz punktu x = 0.4, typu double :" << endl;
    blad_sinus(0.4, "sinuss_d.csv",  hp_d, hk_d);

    cout << "Błędy numeryczne dla zmiennej h, funkcji f(x) = x^2 + 4x + 2 oraz punktu x = 0.2, typu float :" << endl;
    blad_kwadratowa(0.2f, "kwadratowa_f.csv",  hp_f, hk_f);
    cout << "Błędy numeryczne dla zmiennej h, funkcji f(x) = x^2 + 4x + 2 oraz punktu x = 0.2, typu double :" << endl;
    blad_kwadratowa(0.2, "kwadratowa_d.csv",  hp_d, hk_d);
    return 0;
}
//Autor: Igor Jóźwiak