#include "RBtree.hpp"
#include <iostream>

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
            double key {};
            std::cin >> key;
            tree.insert(static_cast<int>(key));
        }
        else if(option == QUERY)
        {
            double begin {};
            double end{};
            std::cin >> begin >> end;

            int res{};
            res = tree.count(static_cast<int>(begin), static_cast<int>(end));
            std::cout << res << " ";
        }
        else {break;}
    }
    return 0;
};

