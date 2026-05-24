#include <iostream>
#include <clocale>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

const int maxx = 20;
const double t = 0.000000000000001;

void printWektor(const vector<double>& x, int N) {
    cout << "x = ";
    for (int i = 0; i < N; ++i) {
        cout << x[i] << " ";
    }
    cout << endl;
}

void macierzA(vector<vector<double>>& A, double d, int N) {
    for (int i = 0; i < N; ++i) {
        if (i >= 2){
            A[0][i] = 0.1;
        }else{
            A[0][i] = 0.0;
        }

        if (i >= 1){
            A[1][i] = 0.5;
        }else{
            A[1][i] = 0.0;
        }

        A[2][i] = d;

        if (i < N-1){
            A[3][i] = 0.5;
        }else{
            A[3][i] = 0.0;
        }

        if (i < N-2){
            A[4][i] = 0.1;
        }else{
            A[4][i] = 0.0;
        }
    }
}

void wektorB(vector<double>& b, int N){
    for(int i=0; i<N; ++i){
        b[i] = i + 1;
    }
}


void metodaJacobiego(const vector<vector<double>>& A, vector<double>& x, const vector<double>& b, int N, const string& filename) {
    vector<double> x_temp(N);
    double total, blad;
    ofstream outFile(filename);
    for (int k = 0; k < maxx; ++k) {
        for (int i = 0; i < N; ++i) {
            total = 0.0;

            if (i >= 2) {
                total += A[0][i] * x[i-2];
            }
            if (i >= 1) {
                total += A[1][i] * x[i-1];
            }
            if (i < N-1) {
                total += A[3][i] * x[i+1];
            }
            if (i < N-2) {
                total += A[4][i] * x[i+2];
            }

            x_temp[i] = (b[i] - total) / A[2][i];
        }
        blad = 0.0; // b, to błąd zbieżności
        for (int i = 0; i < N; ++i) {
            blad = blad + (x_temp[i] - x[i])*(x_temp[i] - x[i]);
        }
        blad = sqrt(blad);
        outFile << k << " " << blad << endl;
        if (blad < t){ // t, to tolerancja błędu
            break;
        }

        x = x_temp;
    }

    printWektor(x, N);
}

void metodaGaussaSeidela(vector<vector<double>>& A, vector<double>& x, const vector<double>& b, int N, const string& filename) {
    vector<double> x_temp(N);
    double total, blad, x_previous, d;
    ofstream outFile(filename);

    for (int k = 0; k < maxx; ++k) {
        blad = 0.0;
        for (int i = 0; i < N; ++i) {
            total = 0.0;

            if (i >= 2) {
                total += A[0][i] * x[i-2];
            }
            if (i >= 1) {
                total += A[1][i] * x[i-1];
            }
            if (i < N-1) {
                total += A[3][i] * x[i+1];
            }
            if (i < N-2) {
                total += A[4][i] * x[i+2];
            }

            x_previous = x[i]; // x_previous przechowuje starą wartość przed aktualizacją
            x[i] = (b[i] - total) / A[2][i];

            d = x[i] - x_previous; // d przechowuje różnicę między nową a starą wartością
            blad = blad + d * d;
        }

        blad = sqrt(blad);
        outFile << k << " " << blad << endl;

        if (blad < t) {
            break;
        }
    }

    printWektor(x, N);
}

    void wektorZerowy(vector<double>& x, int N) {
        for (int i = 0; i < N; ++i) {
            x[i] = 0;
        }
    }

    void wektorPierwiastkowy(vector<double>& x, int N) {
        for (int i = 0; i < N; ++i) {
            x[i] = sqrt(i);
        }
    }

    void wektorSinus(vector<double>& x, int N) {
        for (int i = 0; i < N; ++i) {
            x[i] = sin(i);
        }
    }

    void wektorKwadratowy(vector<double>& x, int N) {
        for (int i = 0; i < N; ++i) {
            x[i] = pow(i, 2);
        }
    }

int main(){
    setlocale(LC_CTYPE,"pl_PL.UTF-8");
    const int N = 200;
    double d1 = 5.27;
    double d2 = 8.0;
    vector<vector<double>> A(5, vector<double>(N));
    vector<double> b(N);
    vector<double> x(N);

    macierzA(A, d1, N);
    wektorB(b, N);

    wektorZerowy(x, N);
    
    cout << "Rozwiązanie Jacobiego dla początkowego wektora zerowego i d1:" << endl;
    metodaJacobiego(A, x, b, N, "jacobi_d1_zerowy.txt");
    cout << "Rozwiązanie Gaussa-Seidela dla początkowego wektora zerowego i d1:" << endl;
    metodaGaussaSeidela(A, x, b, N, "gauss_seidel_d1_zerowy.txt");

    wektorPierwiastkowy(x, N);
    cout << "Rozwiązanie Jacobiego dla początkowego wektora pierwiastkowego i d1:" << endl;
    metodaJacobiego(A, x, b, N, "jacobi_d1_pierwiastkowy.txt");
    cout << "Rozwiązanie Gaussa-Seidela dla początkowego wektora pierwiastkowego i d1:" << endl;
    metodaGaussaSeidela(A, x, b, N, "gauss_seidel_d1_pierwiastkowy.txt");

    wektorSinus(x, N);
    cout << "Rozwiązanie Jacobiego dla początkowego wektora 'sinus' i d1:" << endl;
    metodaJacobiego(A, x, b, N, "jacobi_d1_sinus.txt");
    cout << "Rozwiązanie Gaussa-Seidela dla początkowego wektora 'sinus' i d1:" << endl;
    metodaGaussaSeidela(A, x, b, N, "gauss_seidel_d1_sinus.txt");

    wektorKwadratowy(x, N);
    cout << "Rozwiązanie Jacobiego dla początkowego wektora kwadratowego i d1:" << endl;
    metodaJacobiego(A, x, b, N, "jacobi_d1_kwadratowy.txt");
    cout << "Rozwiązanie Gaussa-Seidela dla początkowego wektora kwadratowego i d1:" << endl;
    metodaGaussaSeidela(A, x, b, N, "gauss_seidel_d1_kwadratowy.txt");



    macierzA(A, d2, N);
    wektorB(b, N);

    wektorZerowy(x, N);
    cout << "Rozwiązanie Jacobiego dla początkowego wektora zerowego i d2:" << endl;
    metodaJacobiego(A, x, b, N, "jacobi_d2_zerowy.txt");
    cout << "Rozwiązanie Gaussa-Seidela dla początkowego wektora zerowego i d2:" << endl;
    metodaGaussaSeidela(A, x, b, N, "gauss_seidel_d2_zerowy.txt");

    wektorPierwiastkowy(x, N);
    cout << "Rozwiązanie Jacobiego dla początkowego wektora pierwiastkowego i d2:" << endl;
    metodaJacobiego(A, x, b, N, "jacobi_d2_pierwiastkowy.txt");
    cout << "Rozwiązanie Gaussa-Seidela dla początkowego wektora pierwiastkowego i d2:" << endl;
    metodaGaussaSeidela(A, x, b, N, "gauss_seidel_d2_pierwiastkowy.txt");

    wektorSinus(x, N);
    cout << "Rozwiązanie Jacobiego dla początkowego wektora 'sinus' i d2:" << endl;
    metodaJacobiego(A, x, b, N, "jacobi_d2_sinus.txt");
    cout << "Rozwiązanie Gaussa-Seidela dla początkowego wektora 'sinus' i d2:" << endl;
    metodaGaussaSeidela(A, x, b, N, "gauss_seidel_d2_sinus.txt");

    wektorKwadratowy(x, N);
    cout << "Rozwiązanie Jacobiego dla początkowego wektora kwadratowego i d2:" << endl;
    metodaJacobiego(A, x, b, N, "jacobi_d2_kwadratowy.txt");
    cout << "Rozwiązanie Gaussa-Seidela dla początkowego wektora kwadratowego i d2:" << endl;
    metodaGaussaSeidela(A, x, b, N, "gauss_seidel_d2_kwadratowy.txt");
    return 0;
}
//Autor: Igor Jóźwiak