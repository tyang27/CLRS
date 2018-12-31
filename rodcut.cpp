#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class RodCut {
	public:
		int maxlength;
		vector<double> prices;
		vector<double> dp;
		vector<double> numcuts;

		void parse_maxlength();
		void parse_prices();
    /* Naive solution. */
		double cut(double x);
    /* Page 366. */
		double cut_bottom_up(double x);
    /* Page 366. */
		double cut_top_down(double x);
		void print() const;
	};

void RodCut::print() const {
	cout << "i" << "\t";
	for (double i = 1; i <= maxlength; i++) cout << i << "\t";
	cout << endl;
	cout << "prices" << "\t";
	for (double i = 1; i <= maxlength; i++) cout << prices[i] << "\t";
	cout << endl;
	cout << "dp" << "\t";
	for (double i = 1; i <= maxlength; i++) cout << dp[i] << "\t";
	cout << endl;
	cout << "cuts" << "\t";
	for (double i = 1; i <= maxlength; i++) cout << numcuts[i] << "\t";
	cout << endl;
}

double RodCut::cut(double x) {
	if (x == 0) return 0;

	double q = -INFINITY;

	for (int i = 1; i <= x ; i++) {
		double remainder = cut(x-i);
		double split_cost = prices[i] + remainder;
		q = max(q, split_cost);
	}

	return q;
}

double RodCut::cut_top_down(double x) {
	if (dp[x] >= 0) return dp[x];
	if (x == 0) return 0;

	double q = -INFINITY;

	for (int i = 1; i <= x ; i++) {
		double remainder = cut_top_down(x-i);
		double split_cost = prices[i] + remainder;
		q = max(q, split_cost);
	}
	dp[x] = q;

	return q;
}

double RodCut::cut_bottom_up(double x) {
	dp[0] = 0;
	numcuts[0] = 0;
	for (int j = 1; j <= x; j++) {
		double q = -INFINITY;
		for (int i = 1; i <= j; i++) {
			double remainder = dp[j-i];
			double split_cost = prices[i] + remainder;
			q = max(q, split_cost);
		}
		dp[j] = q;
	}
	return dp[x];
}

void RodCut::parse_prices() {
	for (int i = 1; i <= maxlength; i++) {
		cin >> prices[i];
		dp[i] = -INFINITY;
	}
}

void RodCut::parse_maxlength() {
	cin >> maxlength;
	prices = vector<double>(maxlength+1);
	dp = vector<double>(maxlength+1);
	numcuts = vector<double>(maxlength+1);
}

int main() {
	RodCut rodcut;

	rodcut.parse_maxlength();
	rodcut.parse_prices();

	rodcut.print();

	cout << rodcut.cut(10) << endl;
	rodcut.print();

	cout << rodcut.cut_top_down(10) << endl;
	rodcut.print();

	cout << rodcut.cut_bottom_up(10) << endl;
	rodcut.print();
}
