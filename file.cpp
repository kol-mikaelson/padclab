#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <mutex>
#include <omp.h>
using namespace std;
void toLower(string& str) {
transform(str.begin(), str.end(), str.begin(), ::tolower);
}
bool isNumeric(const string& str) {
return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}
void processLine(const string& line, map<string, int>& localCount) {
stringstream ss(line);
string word;
while (ss >> word) {
toLower(word);
word.erase(remove_if(word.begin(), word.end(), ::ispunct),
word.end());
if (!word.empty() && !isNumeric(word)) {
localCount[word]++;
}
}
}
int partition(pair<string, int>* arr, int low, int high) {
int pivot = arr[high].second;
int i = low - 1;
for (int j = low; j < high; j++) {
if (arr[j].second > pivot) {
i++;
swap(arr[i], arr[j]);
}
}
swap(arr[i + 1], arr[high]);
return i + 1;
}
void quickSort(pair<string, int>* arr, int low, int high) {
if (low < high) {
int pi = partition(arr, low, high);
#pragma omp task shared(arr) if(high - low > 100)
quickSort(arr, low, pi - 1);
#pragma omp task shared(arr) if(high - low > 100)
quickSort(arr, pi + 1, high);
#pragma omp taskwait
}
}
int main() {
cout << "This code is executed by Purandhar Reddy 2022BCS0179" <<
endl;
double start = omp_get_wtime();
ifstream file("C:\\Users\\IIITK\\Documents\\PDE Batch
2\\Lab6\\chandrayaan.txt");
if (!file.is_open()) {
cerr << "Error opening file!" << endl;
return 1;
}
map<string, int> wordCount;
vector<string> lines;
string line;
while (getline(file, line)) {
lines.push_back(line);
}
file.close();
#pragma omp parallel
{
map<string, int> localCount;
#pragma omp for
for (size_t i = 0; i < lines.size(); ++i) {
processLine(lines[i], localCount);
}
#pragma omp critical
{
for (const auto& pair : localCount) {
wordCount[pair.first] += pair.second;
}
}
}
vector<pair<string, int>> wordArray(wordCount.begin(),
wordCount.end());
#pragma omp parallel
{
#pragma omp single
quickSort(wordArray.data(), 0, wordArray.size() - 1);
}
double end = omp_get_wtime();
cout << "Top 10 words based on counts:\n";
for (int i = 0; i < min(10, static_cast<int>(wordArray.size())); i++)
{
cout << "(" << wordArray[i].first << ", " << wordArray[i].second
<< ")\n";
}
cout << "Execution time: " << end - start << " seconds" << endl;
return 0;
}
