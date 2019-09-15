#include <iostream>

using namespace std;

#ifndef VERTEX_CPP
#define VERTEX_CPP

template<class Data>
class Vertex{
    private:
        Data _value;

        int _distance;
    public:

        Vertex(Data& value);

        Data getValue();
        void setValue(Data& value);

        int getDistance();
        void setDistance(int distance);
};

#endif

template <class Data>
Vertex<Data>::Vertex(Data& value) {
    this->_value = value;
    this->_distance = -1;
}

template <class Data>
Data Vertex<Data>:: getValue(){
    return this->_value;
}

template<class Data>
void Vertex<Data> :: setValue(Data& value){
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