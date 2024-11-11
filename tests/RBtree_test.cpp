#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "RBtree.hpp"

struct RBtree : public testing::Test
{
    static const int root_key = 80;
    RBT::Tree<int> tree{root_key};

    void SetUp() {};
    void TearDown() {};
};

TEST_F(RBtree, TEST_insert)
{
    int new_key = 70;
    tree.insert(new_key);
    RBT::Node<int> *inserted_node = tree.find(new_key);

    EXPECT_EQ(inserted_node->key_, new_key);
}

TEST_F(RBtree, TEST_erase)
{
    //erase regular node
    int new_key = 70;
    tree.insert(new_key);
    tree.erase(new_key);
    RBT::Node<int> *node = tree.find(new_key);
    EXPECT_EQ(node, tree.get_nil());

    //erase root
    tree.erase(root_key);
    node = tree.find(root_key);
    EXPECT_EQ(node, tree.get_nil());
}

TEST_F(RBtree, TEST_count_1)
{
    tree.insert(1);
    tree.insert(2);
    EXPECT_EQ(tree.count(1, 2), 2);
}

TEST_F(RBtree, TEST_count_2)
{
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    EXPECT_EQ(tree.count(0, 3), 3);
}

TEST_F(RBtree, TEST_count_3)
{
    for(int i = 0; i < 20; ++i)
    {
        tree.insert(i);
    }
    EXPECT_EQ(tree.count(0, 20), 20);
}
