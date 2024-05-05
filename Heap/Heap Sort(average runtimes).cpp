#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

vector<int> generateRandomData(int n) {
    vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % n + 1;
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
    cout << "Heap Sort Average Case Times:\n";
    for (int n : ns) {
        vector<int> data = generateRandomData(n);
        double time = measureTime(heapSort, data, n);
        cout << "n = " << n << ": " << time << " seconds\n";
    }
    return 0;
}
