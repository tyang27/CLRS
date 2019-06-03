#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class Knapsack {
  vector<int> _cost;
  vector<int> _value;
  int _amt;
  vector<vector<int> > _dp;

  public:
  Knapsack(vector<int> c, vector<int> v) :
    _cost(c), _value(v), _amt(v.size()), _dp(v.size()+2) {
      _cost.insert(_cost.begin(), -1);
      _value.insert(_value.begin(), -1);
    }

  int stuff(int cap) {
    for (int i=0; i <= _amt+1; i++) {
      _dp[i] = vector<int>(cap+1);
    }

    /* _dp[i, j] represents the maximum value if we stuff i items
     * given j capacity. */
    for (int i = 1; i < _amt+1; i++) {
      for (int j = 1; j < cap+1; j++) {
        /* We can do at least as good as if we had i-1 items. */
        _dp[i][j] = _dp[i-1][j];

        /* If we have the capacity to stuff one more thing, would doing make
         * an improvement?
         */
        if (_cost[i] <= j) {
          _dp[i][j] = max(_dp[i][j], _value[i] + _dp[i-1][j-_cost[i]]);
        }
      }
    }
    return _dp[_amt][cap];
  }

  void print() const {
    for (int i=1; i < _amt+1; i++) cout << _cost[i] << "\t";
    cout << endl;
    for (int i=1; i < _amt+1; i++) cout << _value[i] << "\t";
    cout << endl;
  }

  void print_dp() const {
    for (int i = 1; i < _amt+1; i++) {
      for (int j = 1; j < (int) _dp[0].size(); j++) {
        cout << _dp[i][j] << "\t";
      }
      cout << endl;
    }
    cout << endl;
  }
};

int main() {
  int n;
  n = -1;

  cin >> n; 
  vector<int> cost(n);
  vector<int> value(n);

  for (int i=0; i < n; i++) cin >> value[i];
  for (int i=0; i < n; i++) cin >> cost[i];

  Knapsack ks(cost, value);
  //ks.print();

  int stuffed_val = ks.stuff(50);
  cout << stuffed_val << endl;
}
