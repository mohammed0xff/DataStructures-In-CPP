#include <iostream>
#include "HashMap.hpp"



int main() {

    HashMap<int, int> map;
    map.put(0, 0);
    map.put(1, 1);
    map.put(2, 2);
    map.put(3, 3);
    
    //map.remove(3);
    std::cout << map.get(3) << "\n";


    return 0;
}
