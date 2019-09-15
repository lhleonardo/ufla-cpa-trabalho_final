#include <iostream>
#include "bag/bag.cpp"

using namespace std;

int main() {

    Bag<int> umaBag(64);
    for(int i=0; i<64; i++){
        umaBag.insert(i);
        umaBag.print();
    }

    return 0;
}

