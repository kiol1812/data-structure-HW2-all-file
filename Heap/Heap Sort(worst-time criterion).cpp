#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

void heap(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heap(arr, n, largest);
    }
}

void heapSort(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; --i)
        heap(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heap(arr, i, 0);
    }
}

vector<int> generateWorstCaseDataHeapSort(int n) {
    vector<int> data;
    for (int i = n; i >= 1; --i) {
        data.push_back(i);
    }
    return data;
}

double measureTime(void (*func)(vector<int>&, int), vector<int>& arr, int n) {
    clock_t start, end;
    start = clock();
    func(arr, n);
    end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(0)); 
    vector<int> ns = {500, 1000, 2000, 3000, 4000, 5000};
    cout << "Heap Sort Worst Case Times:\n";
    for (int n : ns) {
        vector<int> data = generateWorstCaseDataHeapSort(n);
        double time = measureTime(heapSort, data, n);
        cout << "n = " << n << ": " << time << " seconds\n";
    }
    return 0;
}
