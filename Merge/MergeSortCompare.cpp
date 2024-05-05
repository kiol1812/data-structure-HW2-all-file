#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <fstream>

using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {
    int n1=m-l+1, n2=r-m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];
    int i=0, j=0, k=l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k]=L[i++];
        else arr[k]=R[j++];
        ++k;
    }
    while (i < n1) arr[k++]=L[i++];
    while (j < n2) arr[k++]=R[j++];
}

void mergeSortRecursion(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m=l+(r-l)/2;
        mergeSortRecursion(arr, l, m);
        mergeSortRecursion(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
void mergeSortIterative(vector<int>& arr, int n){
    for(int currentSize=1; currentSize<n; currentSize*=2){
        for(int l=0; l<n-1; l+=2*currentSize){
            int mid=min(l+currentSize-1, n-1), r=min(l+currentSize*2-1, n-1);
            merge(arr, l, mid, r);
        }
    }
}

vector<int> generateRandomData(int n) {
    vector<int> data(n);
    for (int i = 0; i < n; ++i) data[i]=rand()%n+1;
    return data;
}

double measureTime(void (*func)(vector<int>&, int, int), vector<int>& arr, int l, int r) {
    clock_t start, end;
    start = clock();
    func(arr, l, r);
    end = clock();
    return double(end-start)/CLOCKS_PER_SEC;
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
    ofstream ofs;
    ofs.open("output.txt");
    if(!ofs.is_open()) cout<<"file didn't opened";
    cout << "Merge Sort Average Case Times:\n";
    for (int times=0; times<20; times++) {
        vector<int> data = generateRandomData(1000000), data_copy(1000000);
        for(int i=0; i<1000000; i++) data_copy[i]=data[i];
        double timeOfRecursionMethon = measureTime(mergeSortRecursion, data, 0, data.size() - 1);
        double timeOfIterativeMethon = measureIterativeTime(mergeSortIterative, data, data.size());
        ofs<<timeOfIterativeMethon<<","<<timeOfRecursionMethon<<",";
        cout << "Recursion, n = " << 1000000 << ": " << timeOfRecursionMethon << " seconds\n";
        cout << "Iterative, n = " << 1000000 << ": " << timeOfIterativeMethon << " seconds\n";
    }
    ofs.close();
    return 0;
}
