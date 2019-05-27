#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Sets {
  public:
  int num_nodes;
  vector<int> rank;
  vector<int> nodes;

  Sets(int n): num_nodes(n), rank(n), nodes(n) {};

  /**
   * Creates a set.
   * Nodes in a new set point to themselves.
   * They have no children.
   * Page 571.
   */
  void create(int x) {
    nodes[x] = x;
    rank[x] = 0;
  };
  
  /**
   * Finds the set that a node belongs to.
   * Recurses to the root.
   * Page 571.
   */
  int find(int x) {
    if (x != nodes[x])
      nodes[x] = find(nodes[x]);
    return nodes[x];
  }

  /**
   * Merges two sets together.
   * Finds who x and y belong to.
   * Connects the lower rank set to the higher.
   * Update rank.
   * Page 571.
   */
  void merge(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (rank[px] > rank[py]) {
      nodes[py] = px;
    } else {
      nodes[px] = py;
    }
    if (rank[px] == rank[py]) {
      rank[py]++;
    }

    void offline_min(int m) {
        //m is the current operation
        //n is the number of elements
        for (int i = 0; i < num_nodes; i++) {
            int j = find(i);
            if (j != m+1) {
                cout << j << endl;
                merge(find(l), j);
            }
        }

    }
  }

  /**
   * Returns true if two components are of the same set.
   */
  bool connected(int x, int y) {
    return find(x) == find(y);
  }

  friend ostream& operator<< (ostream& strm, const Sets& s) {
    strm << "index\t";
    for (int i = 0; i < s.num_nodes; i++) strm << i << "\t";
    strm << endl << "parent\t";
    for (int i = 0; i < s.num_nodes; i++) strm << s.nodes[i] << "\t";
    strm << endl << "rank\t";
    for (int i = 0; i < s.num_nodes; i++) strm << s.rank[i] << "\t";
    return strm;
  }
};

int main(void) {
  int n = 10;
  Sets s(n);
  for (int i = 0; i < n; i++) {
    s.create(i);
  }
  //s.merge(0, 1);
  //s.merge(8, 9);
  //s.merge(0, 2);
  //assert(!s.connected(5, 2));
  
  cout << s << endl;

}
