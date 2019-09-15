#include <iostream>
#include <cmath>

using namespace std;

template <class Data>
class Node {
    private:
        Node<Data>* _left;
        Node<Data>* _right;
        Data _value;
    public:
        Node(Data value);
        
        void setLeftNode(Node<Data>* left);
        void setRightNode(Node<Data>* right);

        Node<Data>* getLeftNode();
        Node<Data>* getRightNode();

        Data getValue();
        void setValue(Data value);
    
        void printNode(string location);
};

template <class Data>
Node<Data>::Node(Data value) {
    this->_value = value;
    this->_left = nullptr;
    this->_right = nullptr;

}

template <class Data>
void Node<Data>::setLeftNode(Node<Data>* left) {
    this->_left = left;
}

template <class Data>
void Node<Data>::setRightNode(Node<Data>* right) {
    this->_right = right;
}

template <class Data>
Node<Data>* Node<Data>::getLeftNode() {
    return this->_left;
}

template <class Data>
Node<Data>* Node<Data>::getRightNode() {
    return this->_right;
}

template <class Data>
Data Node<Data>::getValue() {
    return this->_value;
}

template <class Data>
void Node<Data>::setValue(Data value) {
    this->_value = value;
}

template <class Data>
void Node<Data>::printNode(string location){
    cout << "(" << this->_value << ", " << location << ") ";
    if (this->_left)
        this->_left->printNode("D");
    
    if (this->_right)
        this->_right->printNode("E");
    
}

template <class Data>
class NodeRoot {
    private:
        Node<Data>* _next;
        Data _value;
    public:
        NodeRoot(Data value, Node<Data>* next);

        void setValue(Data value);
        void setNext(Node<Data>* next);
        
        Data getValue();
        Node<Data>* getNext();

        NodeRoot<Data>* merge(NodeRoot<Data>* another);

        void printNodeRoot();
};

template<class Data>
NodeRoot<Data>::NodeRoot(Data value, Node<Data>* next) {
    this->_next = next;
    this->_value = value;
}

template<class Data>
void NodeRoot<Data>::setValue(Data value){
    this->_value = value;
}

template<class Data>
void NodeRoot<Data>::setNext(Node<Data>* next){
    this->_next = next;
}

template<class Data>
Data NodeRoot<Data>::getValue(){
    return this->_value;
} 

template <class Data>
Node<Data>* NodeRoot<Data>::getNext() {
    return this->_next;
}

template <class Data>
NodeRoot<Data>* NodeRoot<Data>::merge(NodeRoot<Data>* another) {
    Node<Data>* oldNext = another->getNext();
    
    Node<Data>* next = new Node<Data>(another->getValue());
    next->setLeftNode(another->getNext());
    next->setRightNode(this->_next);

    this->setNext(next);

    return this;
}

template <class Data>
void NodeRoot<Data>::printNodeRoot(){
    cout<< "(" << this->_value << ", Rr) ";
    if(this->_next != nullptr){
        this->_next->printNode("R");
    }
}

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
            newValue = this->_backbone[i]->merge(newValue);
            this->_backbone[i] = nullptr;
        }
    }
}

template<class Data>
void Bag<Data>::print(){
 
    for(unsigned i=0; i < this->_lengthBackbone; i++){
        cout << "[" << i << "] => ";
        if(this->_backbone[i]!=nullptr){
            this->_backbone[i]->printNodeRoot();
            cout << endl;
        } else {
            cout << "NULL" << endl;
        }
    }
}



int main() {

    Bag<int> umaBag(64);
    for(int i=0; i<64; i++){
        umaBag.insert(i);
        umaBag.print();
    }

    return 0;
}

