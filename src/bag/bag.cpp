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

        void getSectionAux(Node<Data>* index, std::list< Data>* lista);
        NodeRoot<Data>* compare(NodeRoot<Data>* oneNode, NodeRoot<Data>* otherNode, NodeRoot<Data>* aux);
    public: 
        Bag(unsigned size);
        ~Bag();

        void insert(const Data value);

        unsigned size();
        bool isEmpty();
        
        Bag<Data>& operator+=(const Bag<Data>& otherBag);
        void print();
        
        std::list<Data>* getSection(unsigned index);
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

template<class Data>
NodeRoot<Data>* Bag<Data>::compare(NodeRoot<Data>* oneRoot, NodeRoot<Data>* otherRoot, NodeRoot<Data>* aux){
    
    if(oneRoot != nullptr and otherRoot !=nullptr and aux != nullptr){
        aux = aux->merge(otherRoot);
        return oneRoot;
    }
    else if(oneRoot != nullptr and otherRoot !=nullptr and aux == nullptr){
        aux = oneRoot;
        aux = aux->merge(otherRoot);
        return nullptr;
    }
    else if(oneRoot != nullptr and otherRoot == nullptr and aux != nullptr){
        aux=aux->merge(oneRoot);    
        return nullptr;
    }
    else if(oneRoot == nullptr and otherRoot == nullptr and aux != nullptr){
        oneRoot = aux;
        aux = nullptr;
        return oneRoot;
    }
     else if(oneRoot == nullptr and otherRoot != nullptr and aux == nullptr){
        
        return otherRoot;
    }
    else if(oneRoot != nullptr and otherRoot == nullptr and aux == nullptr){
        return oneRoot;
    }
    else if(oneRoot == nullptr and otherRoot != nullptr and aux != nullptr){
        aux=aux->merge(otherRoot);
        return aux;
    }
    else{
        return nullptr;
    }
}

template <class Data>
Bag<Data>& Bag<Data>::operator+=(const Bag<Data>& otherBag) {
    NodeRoot<Data>* aux = nullptr;
     for(int i=0; i < _lengthBackbone; i++){
         _backbone[i] = compare(_backbone[i], otherBag._backbone[i], aux);
     }

     return *this;
}