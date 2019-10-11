#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <cmath>
#include <any>
#include <omp.h>
#include <queue>

#include "vertex.cpp"
#include "../bag/bag.cpp"

#ifndef GRAPH_CPP
#define GRAPH_CPP

template <class Data>
class Graph{
    private:
        std::map<Vertex<Data>*, std::map<Vertex<Data>*, int>> _mapping;
        std::map<Data, Vertex<Data>*> _elements;

        void proccessSection(std::list<Vertex<Data>*>* section, Bag<Vertex<Data>*>& outBag);
        void proccessAdjacents(Vertex<Data>* vertex, Bag<Vertex<Data>*>& outBag);
    public:
        ~Graph();
        void add(const Data value);
        void buildEdge(const Data from, const Data to, unsigned weight);

        void applySerialBFS(Data origin);
        void applyBFS(Data origin);
        void print();
};

#endif

// ----------------------- METHODS IMPLEMENTATION -----------------------------
template<class Data>
Graph<Data>::~Graph() {
    std::vector<Vertex<Data>*> vertexes;
    for (auto &tupla : this->_elements) {
        vertexes.push_back(tupla.second);
    }

    for (unsigned int i = 0; i < vertexes.size(); i++)
        delete vertexes[i];
    
    vertexes.clear();
    this->_mapping.clear();
    this->_elements.clear();
}

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
void Graph<Data> :: applySerialBFS(const Data origin){
    Vertex<Data>* originVertex = _elements[origin]; //vértice inicial

    queue<Vertex<Data>*> myQueue;
    myQueue.push(originVertex);
    originVertex->setDistance(0);

    while(not myQueue.empty()){
        for (auto const &tupla : _mapping[myQueue.front()]) {//percorre os elementos adjacentes a cada vértice na fila
            Vertex<Data>* previousVertex = myQueue.front();
            Vertex<Data>* vertex = tupla.first;
            if (not vertex->isVisited()){ //Caso o vértice seja nao visitado, vertice = visitado
                vertex->visit();
                vertex->setDistance(previousVertex->getDistance()+1); //guarda a camada em que o vértice foi visitado
                myQueue.push(vertex);      
            }
        }
        myQueue.pop();
    }
}



template <class Data>
void Graph<Data>::applyBFS(const Data origin) {
 
    Vertex<Data>* originVertex = _elements[origin];

    Bag<Vertex<Data>*>* inBag = new Bag<Vertex<Data>*>(_elements.size()); // tamanho máximo definido como qtd de vértices
    Bag<Vertex<Data>*>* outBag = new Bag<Vertex<Data>*>(_elements.size()); // guarda o próximo nível de exploração
    
    inBag->insert(originVertex); // adiciona primeiro vértice - camada 0
    while (not inBag->isEmpty()) { // processa todos os níveis. Bag vazia significa sem vértices para explorar
        unsigned sectionLimit = int(ceil(log2(inBag->size()+1)));

        #pragma omp parallel for
        for (unsigned index = 0; index < sectionLimit; index++) {
            list<Vertex<Data>*>* section = inBag->getSection(index);
            if (section)
                this->proccessSection(section, *outBag);
        }

        delete inBag;
        inBag = outBag;
        outBag = new Bag<Vertex<Data>*>(_elements.size());
    }
}

template <class Data>
void Graph<Data>::proccessSection(list<Vertex<Data>*>* section, Bag<Vertex<Data>*>& outBag) {

    #pragma omp parallel 
    for (typename list<Vertex<Data>*>::iterator it = section->begin(); it != section->end(); it++) {    
        #pragma omp single nowait 
        {
            if (not (*it)->isVisited()) (*it)->visit();

            proccessAdjacents((*it), outBag);

            (*it)->close();
        }
    }
}

template <class Data>
void Graph<Data>::proccessAdjacents(Vertex<Data>* vertex, Bag<Vertex<Data>*>& outBag) {
    std::map<Vertex<Data>*, int> adjacentsMapping = _mapping[vertex];

    #pragma omp parallel 
    for (typename std::map<Vertex<Data>*, int>::iterator it = adjacentsMapping.begin(); 
        it != adjacentsMapping.end(); it++) {
            #pragma omp single nowait 
            {
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
}

template <class Data>
void Graph<Data>::print() {
    for (auto const &tupla : _elements) {
        Vertex<Data>* vertex = tupla.second;
        if(vertex->getDistance()>0){
            cout << "(" << vertex->getValue() << ":" << vertex->getDistance() << ")" << endl;
        }
    }
}

// ----------------------- METHODS IMPLEMENTATION -----------------------------
