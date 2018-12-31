#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class Paragraph {
  int _num_words, _max;
  vector<int> _wlen;
  vector<vector<int> > _neat_dp;

  public:
  Paragraph(int n, int m, vector<int> l):
    _num_words(n),
    _max(m),
    _wlen(l),
    _neat_dp(n) {
    for (int i = 0; i < _num_words; i++) {
      _neat_dp[i] = vector<int>(_num_words);
      _neat_dp[i][i] = _max;
    }
  }

  void format();

  void print() const;
  void print_dp() const;
};

void Paragraph::print() const {
  cout << "max: " << _max << endl;
  for (int i = 0; i < _num_words; i++) cout << _wlen[i] << " ";
  cout << endl;
}

void Paragraph::print_dp() const {
  for (int i = 0; i < _num_words; i++) cout << _wlen[i] << "\t";
  cout << endl << "======================================================" << endl;

  for (int i = 0; i < _num_words; i++) {
    for (int j = 0; j < _num_words; j++) {
      cout << _neat_dp[i][j] << "\t";
    }
    cout << endl;
  }
}

void Paragraph::format() {
  for (int i = 0; i < _num_words; i++) {
    for (int j = i+1; j < _num_words; j++) {
      int score = _neat_dp[i][j-1] - _wlen[j];
      
      //if (i > 0) score = min(score, _neat_dp[i-1][j]);

      if (score >= 0) _neat_dp[i][j] = score;
      else _neat_dp[i][j] = -1;
    }
  }
}

int main() {
  int n, M;
  cin >> n >> M;
  vector<int> l(n);
  for (int i = 0; i < n; i++) cin >> l[i];
  Paragraph paragraph(n, M, l);

  paragraph.print();
  paragraph.format();
  paragraph.print_dp();

}
