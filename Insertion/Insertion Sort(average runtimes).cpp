#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

vector<int> generateRandomData(int n) {
    vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % n + 1;
    }
    return data;
}

double measureTime(void (*func)(vector<int>&), vector<int>& arr) {
    clock_t start, end;
    start = clock();
    func(arr);
    end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(0)); 
    vector<int> ns = {500, 1000, 2000, 3000, 4000, 5000};
    cout << "Insertion Sort Average Case Times:\n";
    for (int n : ns) {
        vector<int> data = generateRandomData(n);
        double time = measureTime(insertionSort, data);
        cout << "n = " << n << ": " << time << " seconds\n";
    }
    return 0;
}
