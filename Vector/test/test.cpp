
#include "../vector.hpp"


int main() {


    vector <int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::cout << "fornt() : " << vec.front() << "\n";
    std::cout << "back() : "  << vec.back()  << "\n";

    std::cout << "displaying vec : ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;


    vector<int>::iterator it1 = vec.begin();
    vector<int>::iterator it2 = vec.end();

    std::cout << "displaying iterator it1: ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << *it1 << " ";
        it1++;
    }
    std::cout << std::endl;


    return 0;

};