#include <iostream>
#include <vector>

#include <algorithm>

using namespace std;

class Sort {
    public:
    Sort() {}
    virtual vector<int> sort(vector<int> arr) = 0;
    void print(vector<int> arr) {
        for (unsigned int i=0; i<arr.size(); i++) {
            cout << arr[i] << "\t";
        }
        cout << endl;
    }
};

class HeapSort : public Sort {
    public:
    HeapSort() {}
    vector<int> sort(vector<int> arr) override {
        vector<int> heap(arr);
        
        /* Make the heap. */
        make_heap(heap.begin(), heap.end());

        /* Not the O(n) implementation, but that's okay. */
        for (unsigned int i=0; i<arr.size(); i++) {
            arr[i] = heap.back();
            heap.pop_back();
        }
        return arr;
    }
};

int main() {
    vector<int> arr{5, 4, 3, 2, 1};

    HeapSort heapsort;
    heapsort.print(heapsort.sort(arr));
}
