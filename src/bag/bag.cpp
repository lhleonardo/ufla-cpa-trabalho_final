#include <iostream>
#include <cmath>
#include <list>

#include "node.cpp"

template <class Data> 
class Bag {
    private:
        NodeRoot<Data>** _backbone;
        unsigned _lengthBackbone;
        unsigned _size;

        void getSectionAux(Node<Data>* index, std::list<Data>* lista);
    public: 
        Bag(unsigned size);
        ~Bag();

        void insert(const Data value);
        void print();

        bool isEmpty();

        std::list<Data>* getSection(unsigned index);

        unsigned size();
};

template <class Data>
Bag<Data>::~Bag() {
    delete[] _backbone;
}

template<class Data>
Bag<Data>::Bag(unsigned size) {
    this->_size = 0;
    this->_lengthBackbone = ceil(log2(size)) + 1;

    this->_backbone = new NodeRoot<Data>*[this->_lengthBackbone];

    for (unsigned i = 0; i < this->_lengthBackbone; i++)
        this->_backbone[i] = nullptr;
}

template<class Data>
void Bag<Data>::insert(const Data value) {
    NodeRoot<Data>* newValue = new NodeRoot<Data>(value, nullptr);

    for(unsigned i = 0; i < this->_lengthBackbone; i++) {
        if (this->_backbone[i] == nullptr) {
            this->_backbone[i] = newValue;
            _size++;
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

template<class Data>
bool Bag<Data>::isEmpty(){
    return this->_size == 0;
}

template <class Data>
void Bag<Data>::getSectionAux(Node<Data>* index, std::list<Data>* lista){
    if(index){	
        lista->push_back(index->getValue());
		getSectionAux(index->getLeftNode(), lista);
		getSectionAux(index->getRightNode(), lista);
	}
}

template <class Data>
std::list<Data>* Bag<Data>::getSection(unsigned index) { 
    if (this->_backbone[index]) {
        // cria uma lista com o conteudo corrente da pennant
        std::list<Data>* lista = new std::list<Data>();
        
        // adiciona a raiz da pennant na listagem
        lista->push_back(this->_backbone[index]->getValue());
        
        // adiciona os outros elementos da pennant na listagem (recursiva)
        Node<Data>* root = this->_backbone[index]->getNext();
        getSectionAux(root, lista);

        // retorna a listagem
        return lista;  
    }

    return nullptr;
}

template <class Data>
unsigned Bag<Data>::size() {
    return this->_size;
}