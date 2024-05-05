#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1);
    vector<int> R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

vector<int> generateWorstCaseDataMergeSort(int n) {
    vector<int> data;
    for (int i = n; i >= 1; --i) {
        data.push_back(i);
    }
    return data;
}

double measureTime(void (*func)(vector<int>&, int, int), vector<int>& arr, int l, int r) {
    clock_t start, end;
    start = clock();
    func(arr, l, r);
    end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}
void mergeSortIterative(vector<int>& arr, int n){
    for(int currentSize=1; currentSize<n; currentSize*=2){
        for(int l=0; l<n-1; l+=2*currentSize){
            int mid=min(l+currentSize-1, n-1), r=min(l+currentSize*2-1, n-1);
            merge(arr, l, mid, r);
        }
    }
}
double measureIterativeTime(void (*func)(vector<int>&, int), vector<int>& arr, int size) {
    clock_t start, end;
    start = clock();
    func(arr, size);
    end = clock();
    return double(end-start)/CLOCKS_PER_SEC;
}

int main() {
    srand(time(0)); 
    vector<int> ns = {500, 1000, 2000, 3000, 4000, 5000, 1000000};
    cout << "Merge Sort Worst Case Times:\n";
    for (int n : ns) {
        vector<int> data = generateWorstCaseDataMergeSort(n);
        double time = measureIterativeTime(mergeSortIterative, data, data.size());
        // double time = measureTime(mergeSort, data, 0, data.size() - 1);
        cout << "n = " << n << ": " << time << " seconds\n";
    }
    return 0;
}
