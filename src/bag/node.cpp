#include <iostream>

#ifndef NODE_CPP
#define NODE_CPP

template <class Data>
class Node {
    private:
        Node<Data>* _left;
        Node<Data>* _right;
        Data _value;
    public:
        Node(const Data value);
        ~Node();
        
        void setLeftNode(Node<Data>* left);
        void setRightNode(Node<Data>* right);

        Node<Data>* getLeftNode();
        Node<Data>* getRightNode();

        Data getValue();
        void setValue(const Data value);
    
        void printNode(std::string location);
};

template <class Data>
class NodeRoot {
    private:
        Node<Data>* _next;
        Data _value;
    public:
        NodeRoot(const Data value, Node<Data>* next);
        ~NodeRoot();

        void setValue(const Data value);
        void setNext(Node<Data>* next);
        
        Data getValue();
        Node<Data>* getNext();

        NodeRoot<Data>* merge(NodeRoot<Data>* another);

        void printNodeRoot();
};

#endif

template <class Data>
Node<Data>::Node(const Data value) {
    this->_value = value;
    this->_left = nullptr;
    this->_right = nullptr;

}

template <class Data>
Node<Data>::~Node() {
    delete this->_left;
    delete this->_right;
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
void Node<Data>::setValue(const Data value) {
    this->_value = value;
}

template <class Data>
void Node<Data>::printNode(std::string location){
    std::cout << "(" << this->_value << ", " << location << ") ";
    if (this->_left)
        this->_left->printNode("D");
    
    if (this->_right)
        this->_right->printNode("E");
    
}

template<class Data>
NodeRoot<Data>::NodeRoot(const Data value, Node<Data>* next) {
    this->_next = next;
    this->_value = value;
}

template <class Data>
NodeRoot<Data>::~NodeRoot() {
    delete this->_next;
}

template<class Data>
void NodeRoot<Data>::setValue(const Data value){
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
    std::cout<< "(" << this->_value << ", Rr) ";
    if(this->_next != nullptr){
        this->_next->printNode("R");
    }
}