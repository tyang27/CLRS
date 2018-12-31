#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class LCS {
  enum dir {UP=1,  UP_LEFT=2, LEFT=3, NO_MOVE=0};

  string _x, _y;
  vector<vector<double> > _len_dp;
  vector<vector<dir> > _dir_dp;


  public:
  LCS(string a, string b):
    _x(a), _y(b),
    _len_dp(a.length()+1),
    _dir_dp(a.length()+1) {
      for (unsigned int i = 0; i < a.length()+1; i++)
        _len_dp[i] = vector<double>(b.length()+1);
      for (unsigned int i = 0; i < a.length()+1; i++)
        _dir_dp[i] = vector<dir>(b.length()+1);
    }

  /* Page 394. */
  void lcs();
  /* Page 395. */
  void print_lcs(int i, int j) const;

  void print() const { cout << _x << " " << _y << endl; }
  void print_dp() const;
};

void LCS::lcs() {
  for (unsigned int i = 1; i < _x.length()+1; i++) {
    for (unsigned int j = 1; j < _y.length()+1; j++) {
      /* If x_i == y_j, then this is part of the LCS, decrement x and y. */
      if (_x[i-1] == _y[j-1]) {
        _len_dp[i][j] = _len_dp[i-1][j-1] + 1;
        _dir_dp[i][j] = UP_LEFT;

      /* Take the longer subsequence between x[0,i-1] and y[0,j] or
       * x[0,i] and y[0,j-1]. */
      } else if (_len_dp[i-1][j] >= _len_dp[i][j-1]) {
        _len_dp[i][j] = _len_dp[i-1][j];
        _dir_dp[i][j] = UP;

      } else {
        _len_dp[i][j] = _len_dp[i][j-1];
        _dir_dp[i][j] = LEFT;
      }
    }
  }
}

void LCS::print_dp() const {
  /* Header. */
  cout << "\t\t";
  for (unsigned int j = 0; j < _y.length()+1; j++) cout << _y[j] << "\t";
  cout << endl;

  for (unsigned int i = 0; i < _x.length()+1; i++) {
    /* Left margin. */
    cout << ((i > 0) ? _x[i-1] : ' ') << "\t";

    /* Contents. */
    for (unsigned int j = 0; j < _y.length()+1; j++) {
      cout << _len_dp[i][j] << " ";
      if (_dir_dp[i][j] == UP) cout << "|"; 
      if (_dir_dp[i][j] == UP_LEFT) cout << "\\"; 
      if (_dir_dp[i][j] == LEFT) cout << "-"; 
      if (_dir_dp[i][j] == NO_MOVE) cout << " ";
      cout << "\t";
    }
    cout << endl;
  }
}

void LCS::print_lcs(int i, int j) const {
  if (i == 0 || j == 0) return;

  /* If diagonal up, then that letter contributes. */
  if (_dir_dp[i][j] == UP_LEFT) {
    print_lcs(i-1, j-1);
    cout << _x[i-1];

  } else if (_dir_dp[i][j] == UP) {
    print_lcs(i-1, j);

  } else {
    print_lcs(i, j-1);
  }
}

int main() {
  string a, b;
  cin >> a >> b;

  LCS lcs(a, b);
  lcs.lcs();
  lcs.print_dp();
  lcs.print_lcs(a.length(), b.length());
  cout << endl;
}
