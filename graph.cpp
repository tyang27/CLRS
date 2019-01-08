#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

template <class V, class E>
class Graph {
  public:
    Graph() {}
};

/*---------------------------------------------------------------------------*/
template <class V, class E>
class AdjacencyMatrixGraph : public Graph<V,E> {
  protected:
    vector<V> _vertices;
    vector<vector<E> > _edges;
  public:
    virtual void insert_edge(int i, int j) = 0;
    virtual void remove_edge(int i, int j) = 0;
    void print();
};

/*---------------------------------------------------------------------------*/
template <class V, class E>
class AdjacencyMatrixDirGraph : public AdjacencyMatrixGraph<V,E> {
  public:
    AdjacencyMatrixDirGraph<V,E>(vector<V> v) {
      this->_vertices = vector<V>(v);
      this->_edges = vector<vector<E> >(v.size());
      for (unsigned int i = 0; i < v.size(); i++)
        this->_edges[i] = vector<E>(v.size());
    }
    void insert_edge(int i, int j) { this->_edges[i][j] += 1; }
    void remove_edge(int i, int j) { this->_edges[i][j] -= 1; }
};

template <class V, class E>
class AdjacencyMatrixUndirGraph : public AdjacencyMatrixGraph<V,E> {
  public:
    AdjacencyMatrixUndirGraph<V,E>(vector<V> v) {
      this->_vertices = vector<V>(v);
      this->_edges = vector<vector<E> >(v.size());
      for (unsigned int i = 0; i < v.size(); i++)
        this->_edges[i] = vector<E>(v.size());
    }
    void insert_edge(int i, int j) {
      this->_edges[i][j] += 1;
      this->_edges[j][i] += 1;
    }
    void remove_edge(int i, int j) {
      this->_edges[i][j] -= 1;
      this->_edges[j][i] -= 1;
    }
};

template <class V, class E>
void AdjacencyMatrixGraph<V,E>::print() {
  cout << "\t";
  for (unsigned int i = 0; i < _vertices.size(); i++)
    cout << _vertices[i] << "\t";
  cout << endl;

  for (unsigned int i = 0; i < _vertices.size(); i++) {
    cout << _vertices[i] << "\t";
    for (unsigned int j = 0; j < _vertices.size(); j++) {
      cout << _edges[i][j] << "\t";
    }
    cout << endl;
  }
}

/*---------------------------------------------------------------------------*/
template <class V, class E>
class AdjacencyListGraph: Graph<V,E> {
  protected:
  map<V, vector<E> > _edges;
  public:
  void insert_vertex(V v) { }
  void insert_edge(V v1, V v2) {
    _edges[v1].push_back(v2);
  }
  void print();
};

template <class V, class E>
void AdjacencyListGraph<V,E>::print() {
  for (auto it : _edges) {
    cout << it.first << "\t";
    for (auto itv : it.second) {
      cout << itv << "\t";
    }
    cout << endl;
  }
}
/*---------------------------------------------------------------------------*/

int main() {
}
