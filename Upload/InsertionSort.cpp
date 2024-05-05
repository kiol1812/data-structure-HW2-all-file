/* 41143263-吳柏毅 & 41143264-楊育哲 */
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;
vector<int> generateRandomData(int n);
vector<int> generateWorstCaseData(int n);
double measureTime(void (*func)(vector<int>&), vector<int>& arr);

// ! insertion sort function
void insertionSort(vector<int>& arr) {
    for (int i=1; i<arr.size(); ++i) {
        int key=arr[i], j=i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// ! main function
int main() {
    srand(time(0)); 
    vector<int> ns = {500, 1000, 2000, 3000, 4000, 5000};

    // Average case: (random)
    cout << "Insertion Sort Average Case Times:\n";
    for (int n : ns) {
        vector<int> data = generateRandomData(n);
        double time = measureTime(insertionSort, data);
        cout << "n = " << n << ": " << time << " seconds\n";
    }

    //Worst case: 
    cout << "Insertion Sort Worst Case Times:\n";
    for (int n : ns) {
        vector<int> data = generateWorstCaseData(n);
        double time = measureTime(insertionSort, data);
        cout << "n = " << n << ": " << time << " seconds\n";
    }

    return 0;
}

vector<int> generateRandomData(int n) {
    vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % n + 1;
    }
    return data;
}
vector<int> generateWorstCaseData(int n) {
    vector<int> data;
    for (int i = n; i >= 1; --i) {
        data.push_back(i);
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