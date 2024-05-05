#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

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
bool sorted(vector<int>& arr){
    int current=0;
    for(auto v:arr){
        if(v<current) return false;
        current=v;
    }
    return true;
}
int main(){
    return 0;
}