#include "RBtree.hpp"
#include <iostream>
#include <istream>

enum Ioption : char {KEY = 'k', QUERY = 'q'};

int main()
{
    RBT::Tree<int> tree{};
    char option;
    while(1)
    {
        std::cin >> option;
        if(option == KEY)
        {
            int key {};
            std::cin >> key;
            tree.insert(key);
        }
        else if(option == QUERY)
        {
            int begin {};
            int end{};
            std::cin >> begin >> end;
            int res{};
            res = tree.count(begin, end);
            std::cout << res << " ";
        }
        else {break;}
    }
    return 0;
};

