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

template <class V, class E>
class AdjacencyMatrixGraph : public Graph<V,E> {
  vector<V> _vertices;
  vector<vector<E> > _edges;
  public:
    AdjacencyMatrixGraph<V,E>(vector<V> v) : _vertices(v), _edges(v.size()) {
      for (unsigned int i = 0; i < v.size(); i++) _edges[i] = vector<E>(v.size());
    }
    void print();
};

template <class V, class E>
void AdjacencyMatrixGraph<V,E>::print() {
  /* Header. */
  cout << "\t";
  for (unsigned int i = 0; i < _vertices.size(); i++)
    cout << _vertices[i] << "\t";
  cout << endl;

  for (unsigned int i = 0; i < _vertices.size(); i++) {
    /* Sider. */
    cout << _vertices[i] << "\t";

    /* Content. */
    for (unsigned int j = 0; j < _vertices.size(); j++) {
      if (i <= j) cout << "\t";
      else cout << _edges[i][j] << "\t";
    }
    cout << endl;
  }
}

template <class V, class E>
class AdjacencyListGraph: Graph<V,E> {
  struct Vertex {
  };
  struct Edge {
  };
  public:
    AdjacencyListGraph<V,E>() {cout << "Adjacency List constructor.\n";}
    Vertex insert_vertex(V v);
    Edge insert_edge(Vertex v1, Vertex v2);
};

int main() {
  vector<string> v(10);
  for (int i = 0; i < 10; i++) {
    v[i] = 'a' + i;
  }
  AdjacencyMatrixGraph<string, string> g_mat(v);
  g_mat.print();
}
