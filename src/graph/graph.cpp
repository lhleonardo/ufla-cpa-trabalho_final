#include <iostream>
#include <map>
#include <cmath>

#include "vertex.cpp"
#include "../bag/bag.cpp"

#ifndef GRAPH_CPP
#define GRAPH_CPP

template <class Data>
class Graph{
    private:
        map<Vertex<Data>, map<Vertex<Data>, int>> _mapping;
        map<Data, Vertex<Data>> _elements;
    public:
        void add(const Data value);
        void buildEdge(const Data from, const Data to, unsigned weight);

        void applyBFS(Data origin);
};

#endif

template <class Data>
void Graph<Data>::add(const Data value) {
    this->_elements[value] = Vertex<Data>(value);
}

template <class Data>
void Graph<Data>::buildEdge(const Data from, const Data to, unsigned weight) {
    Vertex<Data> vertexFrom = this->_elements[from];
    Vertex<Data> vertexTo = this->_elements[to];

    this->_mapping[vertexFrom][vertexTo] = weight;
}

template <class Data>
void Graph<Data>::applyBFS(const Data origin) {
    Vertex<Data>& originVertex = this->_elements[origin];
    // marca vertice inicial como visitado
    originVertex.visited();

    // tamanho máximo da bag de entrada e saída é a quantidade de vértices do grafo 
    Bag<Vertex<Data>>* inBag = new Bag<Vertex<Data>>(this->_elements.size());
    Bag<Vertex<Data>>* outBag = new Bag<Vertex<Data>>(this->_elements.size());

    inBag->insert(originVertex);

    unsigned layer = 0;

    while (not inBag->isEmpty()) {
        // percorre cada indice do backbone 
        for (unsigned index = 0; index <= floor(log2(inBag->size())); index++) {
            // elementos da pennant atual
            std::list<Vertex<Data>>* currentSection = inBag->getSection(index);

            if (not currentSection) continue;

            // percorre os elementos de cada pennant
            for (Vertex<Data> vertex : *currentSection) {

                // pega os adjacentes de um elemento na pennant
                map<Vertex<Data>, int> adjacentsMapping = this->_mapping[vertex];
                for (auto const& tupla : adjacentsMapping) {
                    Vertex<Data> adjacent = tupla.first;
                    if (not adjacent.isVisited()) {
                        adjacent.visited();
                        adjacent.setDistance(layer + 1);
                        outBag->insert(adjacent);
                    }
                }
            }
        }
        delete inBag;
        inBag = outBag;
        outBag = new Bag<Vertex<Data>>(this->_elements.size());
    }

    // make search...
}

