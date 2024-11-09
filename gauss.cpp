#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
void gaussianElimination(std::vector<std::vector<double>>& A,
std::vector<double>& b, int N) {
for (int k = 0; k < N - 1; ++k) {
int maxIndex = k;
for (int i = k + 1; i < N; ++i) {
if (abs(A[i][k]) > abs(A[maxIndex][k])) {
maxIndex = i;
}
}
if (maxIndex != k) {
std::swap(A[k], A[maxIndex]);
std::swap(b[k], b[maxIndex]);
}
for (int i = k + 1; i < N; ++i) {
double factor = A[i][k] / A[k][k];
for (int j = k; j < N; ++j) {
A[i][j] -= factor * A[k][j];
}
b[i] -= factor * b[k];
}
}
std::vector<double> x(N);
for (int i = N - 1; i >= 0; --i) {
x[i] = b[i];
for (int j = i + 1; j < N; ++j) {
x[i] -= A[i][j] * x[j];
}
x[i] /= A[i][i];
}
std::cout << "Solution: (";
for (int i = 0; i < N; ++i) {
std::cout << std::fixed << std::setprecision(4) << x[i];
if (i < N - 1) std::cout << ", ";
}
std::cout << ")\n";
}
int main() {
std::cout<< "This code is executed by Purandhar Reddy 2022BCS0179" <<
std::endl;
int N = 3;
std::vector<std::vector<double>> A = {{1, -1, 1}, {1, -4, 2}, {1, 2,
8}};
std::vector<double> b = {4, 8, 12};
auto start = std::chrono::high_resolution_clock::now();
gaussianElimination(A, b, N);
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> elapsed = end - start;
std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
return 0;
}
