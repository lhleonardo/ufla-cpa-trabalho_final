#include <iostream>
#include <map>
#include <cmath>
#include <omp.h>

#include "vertex.cpp"
#include "../bag/bag.cpp"

#ifndef GRAPH_CPP
#define GRAPH_CPP

template <class Data>
class Graph{
    private:
        map<Vertex<Data>*, map<Vertex<Data>*, int>> _mapping;
        map<Data, Vertex<Data>*> _elements;
    public:
        void add(const Data value);
        void buildEdge(const Data from, const Data to, unsigned weight);

        void applyBFS(Data origin);
        void print();
};

#endif

template <class Data>
void Graph<Data>::add(const Data value) {
    Vertex<Data>* element = new Vertex<Data>(value);
    _elements[value] = element;
}

template <class Data>
void Graph<Data>::buildEdge(const Data from, const Data to, unsigned weight) {
    Vertex<Data>* vertexFrom = _elements[from];
    Vertex<Data>* vertexTo = _elements[to];

    _mapping[vertexFrom][vertexTo] = weight;
}

template <class Data>
void Graph<Data>::applyBFS(const Data origin) {
    Vertex<Data>* originVertex = _elements[origin];

    // tamanho máximo da bag de entrada e saída é a quantidade de vértices do grafo 
    Bag<Vertex<Data>*> inBag(_elements.size());

    inBag.insert(originVertex);

    unsigned layer = 0;

    while (not inBag.isEmpty()) {
        // percorre cada indice do backbone
        
        Bag<Vertex<Data>*> outBag(_elements.size());

        #pragma omp parallel for reduction(outBag)
        for (unsigned index = 0; index <= floor(log2(inBag.size())); index++) {
            // elementos da pennant atual
            std::list<Vertex<Data>*>* currentSection = inBag.getSection(index);

            if (not currentSection) continue;
            // percorre os elementos de cada pennant
            for (Vertex<Data>* vertex : (*currentSection)) {
                // pega os adjacentes de um elemento na pennant
                vertex->visit();
                
                map<Vertex<Data>*, int> adjacentsMapping = _mapping[vertex];

                for (auto const& tupla : adjacentsMapping) {
                    Vertex<Data>* adjacent = tupla.first;
                    if (not adjacent->isVisited() and not adjacent->isClosed()) {
                        adjacent->visit();
                        adjacent->setDistance(layer + 1);
                        outBag.insert(adjacent);
                    }
                }
                vertex->close();
            }
        }

        layer++;
        // delete inBag;
        inBag = outBag;
    }
    // make search...
}

template <class Data>
void Graph<Data>::print() {
    for (auto const &tupla : _elements) {
        Vertex<Data>* vertex = tupla.second;
        cout << "(" << vertex->getValue() << ":" << vertex->getDistance() << ")" << endl;
    }
}

