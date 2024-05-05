/* 41143263-吳柏毅 & 41143264-楊育哲 */
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;
vector<int> generateRandomData(int n);
vector<int> generateWorstCaseData(int n);
double measureTime(void (*func)(vector<int>&, int), vector<int>& arr, int n);
void Permute(vector<int>& arr, int n);

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

// ! heap sort function
void heapSort(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ! main function
int main() {
    srand(time(0));
    vector<int> ns = {500, 1000, 2000, 3000, 4000, 5000};

    // Average case: (Random)
    cout << "Heap Sort Average Case Times:\n";
    for (int n : ns) {
        vector<int> data = generateRandomData(n);
        double time = measureTime(heapSort, data, n);
        cout << "n = " << n << ": " << time << " seconds\n";
    }

    // Worst case:
    cout << "Heap Sort Worst Case Times:\n";
    for (int n : ns) {
        vector<int> data = generateWorstCaseData(n);
        double time = measureTime(heapSort, data, n);
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
double measureTime(void (*func)(vector<int>&, int), vector<int>& arr, int n) {
    clock_t start, end;
    start = clock();
    func(arr, n);
    end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}
void Permute(vector<int>& arr, int n){
    for(int i=n; i>=2; i--){
        int j=rand()%i+1;
        swap(arr[j], arr[i]);
    }
}
vector<int> copyVector(vector<int> arr){
    vector<int> data(arr.size());
    for(int i=0; i<arr.size(); i++) data[i]=arr[i]-0;
    return data;
}
vector<int> generateWorstCaseData(int n){
    vector<int> data(n), data_old(n);
    for(int i=0; i<n; i++) data[i]=data_old[i]=i+1;
    for(int times=0; times<20; times++){
        Permute(data, n);
        vector<int> curr=copyVector(data), curr_old=copyVector(data_old);
        if(measureTime(heapSort, curr, n)>=measureTime(heapSort, curr_old, n)) data_old=copyVector(data);
        else data=copyVector(data_old);
    }
    return data;
}
