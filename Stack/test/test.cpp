

#include "../stack.hpp"

int main() {

    stack<int> st1;
    st1.push(1);
    st1.push(2);
    st1.push(3);
    st1.push(4);
    st1.push(5);

    stack<int> st2;
    st2.push(6);
    st2.push(7);
    st2.push(8);
    st2.push(9);
    st2.push(10);

    //st1.swap(st2);

    std::cout << "empty() : " << st1.empty() << "\n";
    std::cout << "full() : "  << st1.full()  << "\n";
    std::cout << "size() : "  << st1.size()  << "\n";


    std::cout << "displaying st1 : " << std::endl;
    while (!st1.empty())
    {
        std::cout << st1.top();
        st1.pop();
    }


    return 0;
}
