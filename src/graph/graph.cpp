#include <iostream>
#include <map>
#include <cmath>
#include <any>
#include <omp.h>

#include "vertex.cpp"
#include "../bag/bag.cpp"

#ifndef GRAPH_CPP
#define GRAPH_CPP

template <class Data>
class Graph{
    private:
        std::map<Vertex<Data>*, std::map<Vertex<Data>*, int>> _mapping;
        std::map<Data, Vertex<Data>*> _elements;

        void proccessSection(std::list<Vertex<Data>*>& section, Bag<Vertex<Data>*>& outBag);
        void proccessAdjacents(Vertex<Data>* vertex, Bag<Vertex<Data>*>& outBag);
    public:
        void add(const Data value);
        void buildEdge(const Data from, const Data to, unsigned weight);

        void applyBFS(Data origin);
        void print();
};

#endif

// ----------------------- METHODS IMPLEMENTATION -----------------------------
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

    Bag<Vertex<Data>*> inBag(_elements.size()); // tamanho máximo definido como qtd de vértices
    inBag.insert(originVertex); // adiciona primeiro vértice - camada 0

    unsigned layer = 0; // camada 0, vértice inicial

    while (not inBag.isEmpty()) { // processa todos os níveis. Bag vazia significa sem vértices para explorar
        Bag<Vertex<Data>*> outBag(_elements.size()); // guarda o próximo nível de exploração

        unsigned sectionLimit = int(floor(log2(inBag.size())));

        #pragma omp parallel for
        for (unsigned index = 0; index < sectionLimit; index++) {
            list<Vertex<Data>*>* section = inBag.getSection(index);
            if (section)
                this->proccessSection(*section, outBag);
        }

        layer++;
        inBag = outBag;
    }
}

template <class Data>
void Graph<Data>::proccessSection(std::list<Vertex<Data>*>& section, Bag<Vertex<Data>*>& outBag) {
    // #pragma omp parallel for
    for (std::list<Vertex<Data>*>::iterator it = section.begin(); it != section.end(); it++) {
        Vertex<Data>* vertex = *it;
        
        if (not vertex->isVisited()) vertex->visit();

        proccessAdjacents(vertex, outBag);

        vertex->close();
    }
}

template <class Data>
void Graph<Data>::proccessAdjacents(Vertex<Data>* vertex, Bag<Vertex<Data>*>& outBag) {
    std::map<Vertex<Data>*, int> adjacentsMapping = _mapping[vertex];

    // #pragma omp parallel for
    for (std::map<Vertex<Data>*, int>::iterator it = adjacentsMapping.begin(); 
        it != adjacentsMapping.end(); it++) {
        
        Vertex<Data>* adjacent = it->first;

        #pragma omp critical
        {
            if (not adjacent->isVisited() and not adjacent->isClosed()) { // guarda apenas vértices não visitados
                adjacent->visit();
                adjacent->setDistance(vertex->getDistance() + 1); // pertencente a próxima camada
                outBag.insert(adjacent);

            }
        } 
    }
}

template <class Data>
void Graph<Data>::print() {
    for (auto const &tupla : _elements) {
        Vertex<Data>* vertex = tupla.second;
        cout << "(" << vertex->getValue() << ":" << vertex->getDistance() << ")" << endl;
    }
}

// ----------------------- METHODS IMPLEMENTATION -----------------------------
