#include <iostream>

using namespace std;

#ifndef VERTEX_CPP
#define VERTEX_CPP

template<class Data>
class Vertex{
    private:
        Data _value;
        int _distance;
        bool _visited;
    public:
        Vertex();
        Vertex(const Data value);

        Data getValue();
        void setValue(const Data value);

        int getDistance();
        void setDistance(int distance);

        bool isVisited();

        void visited();

        bool operator<(const Vertex<Data>& other) const {
            return this->_value < other._value;
        }
};

#endif

template <class Data>
Vertex<Data>::Vertex() {
    this->_distance = -1;
    this->_visited = false;
}

template <class Data>
Vertex<Data>::Vertex(const Data value) {
    this->_value = value;
    this->_distance = -1;
    this->_visited = false;
}

template <class Data>
Data Vertex<Data>:: getValue(){
    return this->_value;
}

template<class Data>
void Vertex<Data> :: setValue(const Data value){
    this->_value = value;
}

template <class Data>
void Vertex<Data>::setDistance(int distance) {
    this->_distance = distance;
}

template <class Data>
int Vertex<Data>::getDistance() {
    return this->_distance;
}

template <class Data>
bool Vertex<Data>::isVisited() {
    return this->_visited;
}

template <class Data>
void Vertex<Data>::visited() {
    this->_visited = true;
}