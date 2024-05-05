#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;
vector<int> generateRandomData(int n);
bool sorted(vector<int>& arr);

// ! helper function (for heap sort)
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
    int pivotIndex = findMedianPivotIndex(arr, low, high);
    const int pivot = arr[pivotIndex];
    swap(arr[high], arr[pivotIndex]);
    int i = low;
    for (int j = low; j < high; ++j) {
        if(arr[j] <= pivot) swap(arr[i++], arr[j]);
    }
    swap(arr[i], arr[high]);
    return i;
}
// ! quick sort function 
void quickSort(vector<int>& arr, int low, int high, clock_t count) {
    if(double(clock()-count)/CLOCKS_PER_SEC>0.02) return;
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1, count);
        quickSort(arr, pi + 1, high, count);
    }
}

// ! merge function
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
// ! merge function (iterative)
void mergeSortIterative(vector<int>& arr, int n){
    for(int currentSize=1; currentSize<n; currentSize*=2){
        for(int l=0; l<n-1; l+=2*currentSize){
            int mid=min(l+currentSize-1, n-1), r=min(l+currentSize*2-1, n-1);
            merge(arr, l, mid, r);
        }
    }
}

// ! heapify function
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
void heapSort(vector<int>& arr, int n, clock_t count) {
    if(double(clock()-count)/CLOCKS_PER_SEC>0.02) return;
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int compositeSort(vector<int>& arr){
    clock_t start=clock();
    quickSort(arr, 0, arr.size()-1, start);
    if(double(clock()-start)/CLOCKS_PER_SEC>0.02){
        start = clock();
        heapSort(arr, arr.size(), start);
        if(double(clock()-start)/CLOCKS_PER_SEC>0.02){
            mergeSortIterative(arr, arr.size());
            return 3; //use merge sort
        }
        return 2; //use heap sort
    }
    return 1; //use quick sort
}
int main(){
    vector<int> ns = {500, 1000, 2000, 3000, 4000, 5000};
    string* word=new string[4];
    word[1]="quick"; word[2]="heap"; word[3]="merge";
    for (int n : ns) {
        vector<int> data = generateRandomData(n);
        int use=compositeSort(data);
        cout<<"use "<<word[use]<<" sort\n";
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
bool sorted(vector<int>& arr){
    int current=0;
    for(auto v:arr){
        if(v<current) return false;
        current=v;
    }
    return true;
}