#include <iostream>
#include <map>
#include "vertex.cpp"

#ifndef GRAPH_CPP
#define GRAPH_CPP

template <class Data>
class Graph{
    private:
        map<Vertex<Data>, map<Vertex<Data>, int>> _mapping;
        map<Data, Vertex<Data>> _elements;
    public:
        void add(Data& value);
        void buildEdge(Data& from, Data& to, unsigned weight);

        void applyBFS(Data& origin);

        friend std::ostream& operator<<(std::ostream& os, const Graph<Data>& dt);
};

#endif

template <class Data>
void Graph<Data>::add(Data& value) {
    this->_elements[value] = Vertex(value);
}

template <class Data>
void Graph<Data>::buildEdge(Data& from, Data& to, unsigned weight) {
    Vertex& vertexFrom = this->_elements[from];
    Vertex& vertexTo = this->_elements[to];

    this->_mapping[vertexFrom][vertexTo] = weight;
}

template <class Data>
void Graph<Data>::applyBFS(Data& origin) {
    Vertex& originVertex = this->_elements[origin];

    // make search...
}

template <class Data>
std::ostream& operator<<(std::ostream& os, const Graph<Data>& dt) {
    // make print
    return os;
}

