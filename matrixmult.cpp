#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class MatChainMult {
  int _num_mat;
  vector<int> _dim;
  vector<vector<double> > _mult_dp;
  vector<vector<double> > _split_dp;
  
  public:
  MatChainMult(int n, vector<int> p):
    _num_mat(n),
    _dim(p),
    _mult_dp(n+1),
    _split_dp(n+1) {
    for (int i = 0; i < n+1; i++) _mult_dp[i] = vector<double>(n+1);
    for (int i = 0; i < n+1; i++) _split_dp[i] = vector<double>(n+1);
    for (int length = 2; length < _num_mat+1; length++) {
      for (int i = 1; i < _num_mat - length + 2; i++) {
        int j = i + length - 1;
        _mult_dp[i][j] = INFINITY;
      }
    }
  };

  void print() const;
  void print_dp() const;

  void matrix_chain_order();
  void print_optimal_parenthesis(int lo, int hi) const;
};

void MatChainMult::print() const {
  for (int i = 0; i < _num_mat; i++) cout<<"("<<_dim[i]<<", "<<_dim[i+1]<<") ";
  cout << endl;
}

void MatChainMult::print_dp() const {
  cout << "m:" << endl;
  for (int i = 0; i < _num_mat; i++) {
    for (int j = 0; j < _num_mat; j++) cout << _mult_dp[i+1][j+1] << "\t";
    cout << endl;
  }
  cout << "s:" << endl;
  for (int i = 0; i < _num_mat; i++) {
    for (int j = 0; j < _num_mat; j++) cout << _split_dp[i+1][j+1] << "\t";
    cout << endl;
  }
}

void MatChainMult::matrix_chain_order() {
  /* Let A_i be the ith matrix.
   * We slide a window [lo, hi] across the sequence, trying different sizes
   * of windows, and different splits.
   * A[1,2,...,lo,...,split,...,hi]
   */

  /* Vary window length. */
  for (int length = 2; length < _num_mat+1; length++) {

    /* Silde the window. */
    for (int lo = 1; lo < _num_mat - length + 2; lo++) {
      int hi = lo + length - 1;

      /* Try splits in the window. */
      for (int split = lo; split < hi; split++) {
        /* The number of ops to get left partition: A_lo*...*A_split. */
        int ops_before_split = _mult_dp[lo][split];
        /* The number of ops to get right partition: A_split*...*A_hi. */
        int ops_after_split = _mult_dp[split+1][hi];
        /* The number of ops to multiply the two partitions. */
        int ops_multiply_split = _dim[lo-1]*_dim[split]*_dim[hi];
        /* Total number of operations for that window and split combo. */
        int num_ops = ops_before_split + ops_after_split + ops_multiply_split;

        /* Update dp if fewer operations. */
        if (num_ops < _mult_dp[lo][hi]) {
          _mult_dp[lo][hi] = num_ops;
          _split_dp[lo][hi] = split;
        }
      }
    }
  }
}

void MatChainMult::print_optimal_parenthesis(int lo, int hi) const {
  if (lo == hi) cout << "A" << lo;
  else {
    cout << "(";
    print_optimal_parenthesis(lo, _split_dp[lo][hi]);
    print_optimal_parenthesis(_split_dp[lo][hi] + 1, hi);
    cout << ")";
  }
}

int main() {
  int n = 0;
  cin >> n;
  vector<int> p(n+1);
  for (int i = 0; i < n+1; i++) cin >> p[i];

  MatChainMult matchainmult(n, p);
  matchainmult.print();
  cout << "=======" << endl;
  matchainmult.matrix_chain_order();
  matchainmult.print_dp();
  matchainmult.print_optimal_parenthesis(1, n);
  cout << endl;
}
