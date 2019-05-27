#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Veb {
    public:
        int _u, _min, _max;
        Veb* _summary;
        vector<Veb*> _cluster;
        
        Veb(int u) : _u(u), _min(-1), _max(-1) {
            if (u == 2) {
                return;
            }
            _summary = new Veb(sqrt(u));
            _cluster = vector<Veb*>(sqrt(u));
            for (unsigned int i=0; i < _cluster.size(); i++) {
                _cluster[i] = new Veb(sqrt(u));
            }
        };
        
        ~Veb() {
            for (unsigned int i=0; i < _cluster.size(); i++) {
                Veb* curr = _cluster[i];
                curr->~Veb();
            }
            //_summary->~Veb();
        }

        void print_tuple(int u, int min, int max) {
            cout << u << "\t" <<
                ((min == -1) ? " " : to_string(min)) <<
                "\t" <<
                ((max == -1) ? " " : to_string(max)) <<
                endl;

        }

        void print() {
            if (_u == 2) {
                print_tuple(_u, _min, _max);
                return;
            }
            print_tuple(_u, _min, _max);
            _summary->print();
            for (unsigned int i=0; i < _cluster.size(); i++) {
                _cluster[i]->print();
            }
        }

        /* Get cluster index. */
        int high(int x, int u) {
            return x / sqrt(u);
        }

        /* Update value for cluster. */
        int low(int x, int u) {
            return x % (int)sqrt(u);
        }

        void insert(int x) {
            /* Empty tree. */
            if (_min == -1) {
                _min = _max = x;
                return;
            }
            /* A new minimum. */
            if (x < _min) swap(x, _min);
            if (_u > 2) {
                /* high(x) gets cluster by dividing by sqrt(u).
                 * low(x) gets the new index by taking the mod by sqrt(u);
                 * 1) cluster[cluster_index] is empty.
                 * 2) cluster[cluster_index] already exists.
                 */
                if (_cluster[high(x, _u)]->_min == -1) {
                    _summary->insert(high(x, _u));
                    _cluster[high(x, _u)]->insert(low(x, _u));
                } else {
                    _cluster[high(x, _u)]->insert(low(x, _u));
                }
            }
            /* A new maximum. */
            if (x > _max) _max = x;
        }
};

int main() {
    Veb veb(16);
    veb.insert(3);
    veb.insert(2);
    veb.insert(4);
    veb.insert(14);
    veb.insert(15);
    veb.insert(5);
    veb.insert(7);
    //veb.print();
}
