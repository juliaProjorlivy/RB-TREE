#include <set>
#include "benchmark/benchmark.h"
#include "RBtree.hpp"

static void MyRBtreeBench(benchmark::State &s)
{
    int tree_size = s.range(0);
    RBT::Tree<int> tree;

    for(auto _ : s)
    {
        for(int i = 0; i < tree_size; ++i)
        {
            tree.insert(i);
        }

        for(int i = 0; i <= tree_size; ++i)
        {
            tree.count(0, i);
        }
    }
}

static void SetBench(benchmark::State &s)
{
    int set_size = s.range(0);
    std::set<int> set;

    for(auto _ : s)
    {
        for(int i = 0; i < set_size; ++i)
        {
            set.insert(i);
        }

        int res = 0;
        for(int i = 0; i <= set_size; ++i)
        {
            for(int j = 0; j < i; ++j)
            {
                res += set.count( j);
            }
        }
    }
}

static void MyRBtreeBench_v2(benchmark::State &s)
{
    int tree_size = s.range(0);
    RBT::Tree<int> tree;

    for(auto _ : s)
    {
        for(int i = 0; i < tree_size; ++i)
        {
            tree.insert(i);
        }

        int res = 0;
        for(int i = 0; i <= tree_size; ++i)
        {
            for(int j = 0; j < i; ++j)
            {
                res += tree.count( j);
            }
        }
    }
}

BENCHMARK(MyRBtreeBench)->DenseRange(10000, 10001);
BENCHMARK(SetBench)->DenseRange(10000, 10001);
BENCHMARK(MyRBtreeBench_v2)->DenseRange(10000, 10001);
BENCHMARK_MAIN();

