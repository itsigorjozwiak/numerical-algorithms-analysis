#include <iostream>
#include <clocale>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

vector<vector<double>> macierzA(int N){
    vector<vector<double>> A(4, vector<double>(N, 0.0));
    A[0][0] = 0;
    for(int i=1; i<N; ++i){
        A[0][i] = 0.3;
    }
    for(int i=0; i<N; ++i){
        A[1][i] = 1.01;
    }
    for(int i=0; i<N-1; ++i){
        A[2][i] = 0.2/(i+1);
    }
    A[2][N-1] = 0;
    for(int i=0; i<N-2; ++i){
        A[3][i] = 0.15/pow(i+1,3);
    }
    A[3][N - 2] = 0;
    A[3][N - 1] = 0;

    return A;
}

vector<double> wektorX(int N){
    vector<double> x(N);
    for(int i=0; i<=N-1; ++i){
        x[i] = i+1;
    }
    return x;
}

void LU(vector<vector<double>>& A, int N){
    for(int i = 0; i < N-2; ++i) {
    A[0][i] /= A[1][i-1];
    A[1][i] -= A[0][i] * A[2][i-1];
    A[2][i] -= A[0][i] * A[3][i-1];
    }

    A[0][N - 2] /= A[1][N - 3];
    A[1][N - 2] -= A[0][N - 2] * A[2][N - 3];
    A[2][N - 2] -= A[0][N - 2] * A[3][N - 3];

    A[0][N - 1] /= A[1][N - 2];
    A[1][N - 1] -= A[0][N - 1] * A[2][N - 2];
}

vector<double> forward(const vector<vector<double>>& A, vector<double>& x, int N){
    for(int i=1; i<N; ++i){
        x[i] -= A[0][i]*x[i-1];
    }
    return x;
}

vector<double> back(const vector<vector<double>>& A, vector<double>& x, int N){
    x[N-1] /= A[1][N-1];
    x[N-2] = (x[N-2] - A[2][N-2] * x[N-1])/A[1][N-2];
    for(int i=N-3; i>=0; --i){
        x[i] = (x[i] - A[3][i] * x[i + 2] - A[2][i] * x[i + 1]) / A[1][i];
    }
    return x;
}

double det(const vector<vector<double>>& A, int N){
    double d = 1.0;
    for(int i=0; i<N; ++i){
        d *= A[1][i];
    }
    return d;
}

int main(){
    setlocale(LC_CTYPE,"pl_PL.UTF-8");
    int N, N1, N2;
    N = 300;
    N1 = 10;
    N2 = 500;
    
    ofstream file("dane.txt", ios::out | ios::trunc);
    if (!file) {
        cerr << "Problem z otworzeniem pliku!!!" << endl;
        return 1;
    }

    for (int i = N1; i <= N2; ++i) {
        double result2 = 0.0;
        for(int j=0; j<200; ++j){
            vector<vector<double>> A = macierzA(i);
            vector<double> x = wektorX(i);

            auto start = chrono::high_resolution_clock::now();

            LU(A, i);

            x = forward(A, x, i);
            x = back(A, x, i);

            double dett = det(A, i);

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> result = end - start;
            result2 += result.count();
        }
        double sr = result2 / 200;
        file << i << " " << sr << endl;
    }
    vector<vector<double>> Ar = macierzA(N);
    vector<double> x = wektorX(N);

    LU(Ar, N);

    x = forward(Ar, x, N);
    x = back(Ar, x, N);

    double detr = det(Ar, N);

    cout << "Rozwiązanie układu równań: ";
    cout << fixed << setprecision(20);
    for (double val : x) {
        cout << val << " ";
    }
    cout << endl;
    cout << "Wyznacznik: " << detr << endl;

    file.flush();
    file.close();
    return 0;
}
//Autor: Igor Jóźwiak