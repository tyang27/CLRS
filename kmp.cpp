#include <iostream>
#include <vector>

using namespace std;

class Kmp {
  public:
    string p, s;
    vector<int> pi;
    int found;

    Kmp(string a, string b): p(a), s(b), pi(p.length()) {
      compute_prefix();
      found = find();
    };

    /**
     * Construct pi array, index notes the location to backtrack to upon 
     * mismatch occurs.
     * Iterate through the entire string (fast).
     * If p[slow] != p[fast], backtrack slow to the first instance.
     * Increment slow if there is a repetition.
     * Save slow to p[fast]
     * Page 1006.
     */
    void compute_prefix() {
      for (unsigned int fast = 1, slow = 0; fast < pi.size(); fast++) {
        while (slow > 0 && p[slow] != p[fast])
          slow = pi[slow-1];
        pi[fast] = p[slow] == p[fast] ? ++slow : slow;
      }
    }

    /**
     * Find prefix in substring. If not found, return -1.
     * Iterate through the entire string (fast).
     * If p[slow] != s[fast], backtrack slow to the first instance.
     * Increment slow if there is a match.
     * If we hit the first instance, return index.
     * Page 1005.
     */
    int find() {
      for (unsigned int fast = 0, slow = 0; fast < s.size(); fast++) {
        while (slow > 0 && p[slow] != s[fast])
          slow = pi[slow-1];
        if (p[slow] == s[fast])
          slow++;
        if (slow == p.length()) {
          return fast - p.length() + 1;
        }
      }
      return -1;
    }

    friend ostream& operator<< (ostream& strm, const Kmp& kmp) {
      for (unsigned int i = 0; i < kmp.p.length(); i++) strm << kmp.p[i] << "\t";
      strm << endl;
      for (unsigned int i = 0; i < kmp.pi.size(); i++) strm << kmp.pi[i] << "\t";
      strm << endl;
      for (int i = 0; i < (int) kmp.s.size(); i++) {
        if (i == kmp.found) {
          strm << "[";
        } else if (kmp.found != -1 && i == (kmp.found + (int) kmp.p.length())) {
          strm << "]";
        }
        strm << kmp.s[i];
      }

      return strm;
    }
};

int main(void) {
  string prefix("guccigugang");
  string str("gucigang gucci guccigucciguccigugang gucci gucci");
  Kmp kmp(prefix, str);
  cout << kmp << endl;
}
