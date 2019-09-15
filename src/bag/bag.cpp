#include <iostream>
#include <cmath>

#include "node.cpp"

template <class Data> 
class Bag {
    private:
        NodeRoot<Data>** _backbone;
        unsigned _lengthBackbone;
        unsigned _size;
    public: 
        Bag(unsigned size);
        ~Bag();

        void insert(Data value);
        void print();

};

template <class Data>
Bag<Data>::~Bag() {
    for (unsigned i = 0; i < this->_lengthBackbone; i++) {
        delete _backbone[i];
    }

    delete[] _backbone;
}

template<class Data>
Bag<Data>::Bag(unsigned size) {
    this->_size = size;
    this->_lengthBackbone = ceil(log2(this->_size)) + 1;

    this->_backbone = new NodeRoot<Data>*[this->_lengthBackbone];

    for (unsigned i = 0; i < this->_lengthBackbone; i++)
        this->_backbone[i] = nullptr;
}

template<class Data>
void Bag<Data>::insert(Data value) {
    NodeRoot<Data>* newValue = new NodeRoot<Data>(value, nullptr);

    for(unsigned i = 0; i < this->_lengthBackbone; i++) {
        if (this->_backbone[i] == nullptr) {
            this->_backbone[i] = newValue;
            break;
        } else {
            NodeRoot<Data>* temp = this->_backbone[i]->merge(newValue);
            
            newValue->setNext(nullptr);
            delete newValue;

            newValue = temp;

            this->_backbone[i] = nullptr;
        }
    }
}

template<class Data>
void Bag<Data>::print(){
 
    for(unsigned i=0; i < this->_lengthBackbone; i++){
        std::cout << "[" << i << "] => ";
        if(this->_backbone[i]!=nullptr){
            this->_backbone[i]->printNodeRoot();
            std::cout << std::endl;
        } else {
            std::cout << "NULL" << std::endl;
        }
    }
}