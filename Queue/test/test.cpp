
int main() {

    queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    q1.push(4);
    q1.push(5);

    queue<int> q2;
    q2.push(6);
    q2.push(7);
    q2.push(8);
    q2.push(9);
    q2.push(10);

    //q1.swap(q2);

    std::cout << "empty() : " << q1.empty() << "\n";
    std::cout << "front() : " << q1.front() << "\n";
    std::cout << "back() : "  << q1.back()  << "\n";


    std::cout << "displaying q1 : " << std::endl;
    while (!q1.empty())
    {
        std::cout << q1.front();
        q1.pop();
    }
  
    return 0;
}
