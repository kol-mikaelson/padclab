#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>
#define MAX_TEST_CASES 100
#define MAX_ARRAY_SIZE 100
#define MIN_ELEMENT 1
#define MAX_ELEMENT 1000
void swap(int* a, int* b) {
int temp = *a;
*a = *b;
*b = temp;
}
void parallel_odd_even_transposition_sort(int* array, int n) {
bool sorted = false;
while (!sorted) {
sorted = true;
#pragma omp parallel for
for (int phase = 0; phase < 2; phase++) {
for (int i = phase; i < n - 1; i += 2) {
if (array[i] > array[i + 1]) {
#pragma omp critical
{
swap(&array[i], &array[i + 1]);
sorted = false;
}
}
}
}
}
}
void print_array(const int* array, int n) {
for (int i = 0; i < n; i++) {
printf("%d ", array[i]);
}
printf("\n");
}
bool validate_input(int value, int min, int max, const char* error_message) {
if (value < min || value > max) {
fprintf(stderr, "%s\n", error_message);
return false;
}
return true;
}
int main() {
int T;
if (scanf("%d", &T) != 1 || !validate_input(T, 1, MAX_TEST_CASES, "Number of
test cases T must
be between 1 and 100.")) {
return 1;
}
while (T--) {
int N;
if (scanf("%d", &N) != 1 || !validate_input(N, 1, MAX_ARRAY_SIZE, "Array size N
must be
between 1 and 100.")) {
return 1;
}
int* array = (int*)malloc(N * sizeof(int));
if (array == NULL) {
fprintf(stderr, "Memory allocation failed.\n");
return 1;
}
for (int i = 0; i < N; i++) {
if (scanf("%d", &array[i]) != 1 || !validate_input(array[i], MIN_ELEMENT,
MAX_ELEMENT,
"Array elements must be between 1 and 1000.")) {
free(array);
return 1;
}
}
parallel_odd_even_transposition_sort(array, N);
print_array(array, N);
free(array);
}
return 0;
}
