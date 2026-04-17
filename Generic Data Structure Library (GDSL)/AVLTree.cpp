#include <iostream>
#include "GDSL/include/Non Linear/Tree/BinarySearchTree.hpp"
#include <GDSLstack.hpp>
#include <GDSLqueue.hpp>

template<typename D>
class AVLTREE: public BSTREE<D>{
    int H: 3;
public:
    AVLTREE();
};

template<typename D>
AVLTREE<D>::AVLTREE():BSTREE<D>(), H(0) {}

using namespace std;
int main(){
    
    return 0;
}