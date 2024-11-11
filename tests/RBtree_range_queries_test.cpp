#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <fstream>
#include "RBtree.hpp"

extern const char *data_filename;
extern const char *answers_filename;

struct RBtree_RQ : public testing::Test
{
    RBT::Tree<int> tree;

    void SetUp() {};
    void TearDown() {};
};

enum Ioption : char {KEY = 'k', QUERY = 'q'};

TEST_F(RBtree_RQ, TEST_RANGE_QUERIES)
{
    std::ifstream data{data_filename};
    std::ifstream answers{answers_filename};

    char option;
    int test_iter = 1;
    data >> option;
    while(!data.eof())
    {
        if(option == KEY)
        {
            int key {};
            data >> key;
            tree.insert(key);
        }
        else if(option == QUERY)
        {
            ++test_iter;
            int begin {};
            int end {};
            data >> begin >> end;
            int res{};
            res = tree.count(begin, end);

            int expected_res {};
            answers >> expected_res;
            EXPECT_EQ(res, expected_res) << "Test " << test_iter << std::endl << "begin: " << begin << " end: " << end << std::endl;
        }
        else {break;}
        data >> option;
    }
}
