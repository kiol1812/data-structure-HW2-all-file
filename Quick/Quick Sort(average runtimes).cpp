#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

int bigger(vector<int>& arr, int a, int b){
    if(arr[a]>arr[b]) return a;
    return b;
}
int findMedianPivotIndex(vector<int>& arr, int start, int end){
    const int mid = (start+end)/2;
    const int biggest = bigger(arr, start, bigger(arr, mid, end));
    if(biggest==start) return bigger(arr, mid, end);
    if(biggest==end) return bigger(arr, start, mid);
    return bigger(arr, start, end);
}

int partition(vector<int>& arr, int low, int high) {
    // int pivot = arr[high];
    int pivotIndex = findMedianPivotIndex(arr, low, high);
    const int pivot = arr[pivotIndex];
    swap(arr[high], arr[pivotIndex]);
    int i = low;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

vector<int> generateRandomData(int n) {
    vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % n + 1;
    }
    return data;
}

double measureTime(void (*func)(vector<int>&, int, int), vector<int>& arr, int low, int high) {
    clock_t start, end;
    start = clock();
    func(arr, low, high);
    end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(0)); 
    vector<int> ns = {500, 1000, 2000, 3000, 4000, 5000};
    cout << "Quick Sort Average Case Times:\n";
    for (int n : ns) {
        vector<int> data = generateRandomData(n);
        double time = measureTime(quickSort, data, 0, data.size() - 1);
        cout << "n = " << n << ": " << time << " seconds\n";
    }
    return 0;
}
