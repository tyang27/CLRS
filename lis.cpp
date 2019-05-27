#include <iostream>
#include <vector>

using namespace std;

class LIS {
    public:
        vector<int> _arr;
        vector<int> _dp;
        LIS(vector<int> arr) : _arr(arr) {}
        void print() {
            for (unsigned int i = 1; i < _arr.size(); i++) { cout << _arr[i] << "\t"; }
            cout << endl;
        }

        int longestincreasingsubsequence() {
            /* |--------|--------|--------|
             * 1        j        i        n
             *          -->      -->
             * dp[i] = max_{1<=j<i} {
             *          dp[j] + 1 if x[j] < x[i] (increasing)
             *          dp[i] o/w
             *         }
             * Complexity: \sum_{i=1}^{n} \sum_{j=1}^{i} O(1) = O(n^2)
             */
            int m = 0;
            vector<int> dp(_arr.size());
            for (int i = 1; i < _arr.size(); i++) {
                dp[i] = 1;
                for (int j = 1; j < i; j++) {
                    if (_arr[i] > _arr[j]) {
                        dp[i] = max(dp[j] + 1, dp[i]);
                    }
                }
                m = max(m, dp[i]);
            }
            for (int i = 1; i < dp.size(); i++) {
                cout << dp[i] << "\t";
            }
            cout << endl;
            _dp = dp;
            return m;
        }

        void printincsub_helper(int n, int l) {
            if (n == 0) return;
            if (_dp[n] == l) {
                printincsub_helper(n-1, l-1);
                cout << _arr[n] << "\t";
                return;
            }
            printincsub_helper(n-1, l);
        }
        void printincreasingsubsequence(int lookingfor) {
            printincsub_helper(_dp.size()-1, lookingfor);
            cout << endl;
        }
};

int main() {
    vector<int> a;
    a.push_back(0);
    a.push_back(5);
    a.push_back(3);
    a.push_back(2);
    a.push_back(1);
    a.push_back(3);
    a.push_back(4);
    LIS lis1(a);
    cout << "LIS 1" << endl;
    lis1.print();
    int lis1_res = lis1.longestincreasingsubsequence();
    lis1.printincreasingsubsequence(lis1_res);
    cout << lis1_res << endl;

    vector<int> b;
    //int arr[] = {24, 24, 7, 19, 2, 5, 25, 16, 17, 3, 20, 18};
    int arr[] = {1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
    for (int i = 0; i < 12; i++) {
        b.push_back(arr[i]);
    }
    cout << "LIS 2" << endl;
    LIS lis2(b);
    lis2.print();
    int lis2_res = lis2.longestincreasingsubsequence();
    lis2.printincreasingsubsequence(lis2_res);
    cout << lis2_res << endl;
}
