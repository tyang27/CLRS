#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class OrderStatistics {
  vector<int> _arr;

  int rand_between(int lo, int hi) const;
  int randomized_partition(int lo, int hi);
  /* Page 216. */
  int randomized_select(int lo, int hi, int i);

  public:

  OrderStatistics(vector<int> v): _arr(v) { srand(time(NULL)); }
  /* Page 126. */
  void random_permutation();
  /* Page 214. */
  int min() const;
  /* Page 214. */
  int max() const;
  /* Page 215. */
  int minmax(int& min_res, int& max_res) const;
 
  /* Page 216. */
  int nth_order(int n) {return randomized_select(0, _arr.size()-1, n); }

  void print_arr() const;
};

int OrderStatistics::rand_between(int lo, int hi) const {
  return lo + (rand() % (hi-lo));
}

void OrderStatistics::random_permutation() {
  for (unsigned int i = 0; i < _arr.size(); i++) {
    /* Swap values at i, rand(i,n). */
    // Not sure about modulus bias -- a problem for later!
    int rand_i = rand_between(i, _arr.size());
    int arr_at_i = _arr[i];
    _arr[i] = _arr[rand_i];
    _arr[rand_i] = arr_at_i;
  }
}

int OrderStatistics::randomized_partition(int lo, int hi) {
  /* Randomly generate the pivot. */
  const int pivot = rand_between(lo, hi); 

  /* Set the pivot aside for now. */
  int arr_at_pivot = _arr[pivot];
  _arr[pivot] = _arr[hi];
  _arr[hi] = arr_at_pivot;

  /* lo  div     curr        hi-1 hi=pivot
   * |----|-------|------------|--|
   */
  int div = lo-1;
  for (int curr = lo; curr < hi; curr++) {
    /* If smaller than pivot, push to the left by swapping with div. */
    if (_arr[curr] < arr_at_pivot) {
      div++;
      int temp = _arr[curr];
      _arr[curr] = _arr[div];
      _arr[div] = temp;
    }
  }
  /* Put the pivot back. */
  div++;
  int temp = _arr[hi];
  _arr[hi] = _arr[div];
  _arr[div] = temp;

  return div;
}

int OrderStatistics::randomized_select(int lo, int hi, int i) {
  /* Empty subarray. */
  if (lo == hi) return _arr[lo];

  /* Randomized partition makes it so that there are k elements before the
   * partition, in that range.
   * lo          partition     hi
   * |------------|------------|
   *     <-k->
   * */
  int partition = randomized_partition(lo, hi);
  int k = partition - lo + 1;

  /* If we have k==i, we have found the ith order statistic.
   * If i < k, then we know that the ith order statistic is before the pivot.
   * If I > k, then we know that the ith order statistic is after the pivot,
   * and since we ignore the k elements in the left partition, we now look for
   * the ith-k order statistic.
   */
  if (i == k) return _arr[partition];
  else if (i < k) return randomized_select(lo, partition-1, i);
  else return randomized_select(partition+1, hi, i-k);
}

int OrderStatistics::min() const {
  /* No elements, so no min. */
  if (_arr.size() == 0) return 0;

  int min = _arr[0];
  for (unsigned int i = 1; i < _arr.size(); i++) {
    min = _arr[i] < min ? _arr[i] : min;
  }
  return min;
}

int OrderStatistics::max() const {
  /* No elements, so no max. */
  if (_arr.size() == 0) return 0;

  int max = _arr[0];
  for (unsigned int i = 1; i < _arr.size(); i++) {
    max = _arr[i] > max ? _arr[i] : max;
  }
  return max;
}

int OrderStatistics::minmax(int& min_res, int& max_res) const {
  /* No elements, so no min or max. */
  if (_arr.size() == 0) return -1;

  /* We need to determine the starting min and max.
   * If size of arr is odd, then we take the first element as both.
   * If even, then we compare the first two pairs, then set min/max.
   * One comparison. */
  int min = _arr[0];
  int max = _arr[0];
  bool even = _arr.size() % 2 == 0;
  if (even) {
    if (_arr[0] < _arr[1]) {
      min = _arr[0];
      max = _arr[1];
    } else {
      min = _arr[1];
      max = _arr[0];
    }
  }

  /* We need to update the min/max.
   * Though this looks messy, we go through 2 elements for only 3 comparisons.
   * Three comparisons. */
  unsigned int i = even ? 2 : 1;
  for (; i < _arr.size(); i+=2) {
    if (_arr[i] < _arr[i+1]) {
      min = _arr[i] < min ? _arr[i] : min;
      max = _arr[i+1] > max ? _arr[i+1] : max;
    } else {
      min = _arr[i+1] < min ? _arr[i+1] : min;
      max = _arr[i] > max ? _arr[i] : max;
    }
  }
  /* Cpp can't return multiple, so use references. */
  min_res = min;
  max_res = max;
  return 0;
}

void OrderStatistics::print_arr() const {
  for (unsigned int i = 0; i < _arr.size(); i++) {
    cout << _arr[i] << " ";
  }
  cout << endl;
}

int main(void) {
  vector<int> arr(10);

  //for (int i = 0; i < 10; i++) arr[i] = 5-i;
  for (int i = 0; i < 10; i++) cin >> arr[i];

  OrderStatistics ordstat(arr);

  ordstat.random_permutation();

  ordstat.print_arr();
  cout << "======" << endl;

  int ordstatmin = ordstat.min();
  int ordstatmax = ordstat.max();
  int ordstatmin1, ordstatmax1;
  ordstat.minmax(ordstatmin1, ordstatmax1);

  assert(ordstat.nth_order(1) == -4);
  assert(ordstat.nth_order(3) == -2);
  assert(ordstat.nth_order(5) == 0);
  assert(ordstat.nth_order(7) == 2);
  assert(ordstat.nth_order(10) == 5);

  assert(ordstatmin == -4);
  assert(ordstatmax == 5);
  assert(ordstatmin1 == -4);
  assert(ordstatmax1 == 5);
  cout << "All tests passed." << endl;
}


