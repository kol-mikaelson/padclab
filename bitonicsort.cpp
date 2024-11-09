#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>
using namespace std;
void exchangeAndCompare(vector<int>& sequence, int index1, int index2, int
order) {
if (order == (sequence[index1] > sequence[index2])) {
cout << "Before Swap: " << sequence[index1] << " and " <<
sequence[index2] <<" ";
swap(sequence[index1], sequence[index2]);
cout << "After Swap: " << sequence[index1] << " and " <<
sequence[index2] << endl;
}
}
void mergeBitonic(vector<int>& sequence, int start, int length, int order)
{
if (length > 1) {
int half = length / 2;
for (int i = start; i < start + half; i++) {
exchangeAndCompare(sequence, i, i + half, order);
}
mergeBitonic(sequence, start, half, order);
mergeBitonic(sequence, start + half, half, order);
}
}
void sortBitonic(vector<int>& sequence, int start, int length, int order){
if (length > 1) {
int half = length / 2;
#pragma omp parallel sections
{
#pragma omp section
sortBitonic(sequence, start, half, 1); // ascending
#pragma omp section
sortBitonic(sequence, start + half, half, 0); // descending
}
mergeBitonic(sequence, start, length, order);
}
}
void executeSort(vector<int>& sequence, int size, int direction) {
sortBitonic(sequence, 0, size, direction);
}
void printArray(const vector<int>& sequence) {
for (int element : sequence) {
cout << element << " ";
}
cout << endl;
}
int main() {
vector<int> sequence = {3, 7, 4, 8, 6, 2, 1, 5};
int size = sequence.size();
int direction = 1; // 1 for ascending order
cout << "Code is executed by Madduri Purandhar Reddy 2022BCS0179" <<
endl;
auto startTime = chrono::high_resolution_clock::now();
cout << "Initial array: ";
printArray(sequence);
#pragma omp parallel
{
#pragma omp single
{
cout << "Number of threads used: " << omp_get_num_threads() <<
endl;
}
}
cout << "\nPhase 1: Creating 4-bit bitonic sequences" << endl;
sortBitonic(sequence, 0, size / 2, 1); // First half ascending
sortBitonic(sequence, size / 2, size / 2, 0); // Second half
descending
cout << "After Phase 1: ";
printArray(sequence);
cout << "\nPhase 2: Sorting 4-bit bitonic sequences" << endl;
mergeBitonic(sequence, 0, size / 2, 1); // Merge first half
mergeBitonic(sequence, size / 2, size / 2, 0); // Merge second half
cout << "After Phase 2: ";
printArray(sequence);
cout << "\nPhase 3: Sorting entire array" << endl;
mergeBitonic(sequence, 0, size, 1); // Final merge
cout << "After Phase 3: ";
printArray(sequence);
auto endTime = chrono::high_resolution_clock::now();
chrono::duration<double> executionTime = endTime - startTime;
cout << "Final sorted array: ";
printArray(sequence);
cout << "Execution time: " << executionTime.count() << " seconds" <<
endl;
return 0;
}
