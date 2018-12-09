#include <iostream>
#include "SortAlgorithm.h"
#include "AlgorithmTester.h"
#include "BinarySearchTree.h"
#include "Graph.h"
#include "ReadGraph.h"
#include "GraphAlgorithm.h"
#include "Maze.h"

using namespace std;
#define SWITCH_SORT_ALGORITHM_TEST      0
#define SWITCH_BINARY_SEARCH_TREE_TEST  0
#define SWITCH_UNION_FIND_TEST          0
#define SWITCH_GRAPH_ALGORITHM_TEST     1


int main() 
{
#if SWITCH_SORT_ALGORITHM_TEST
    /* Sort Algorithm */
    AlgorithmTester::SortAlgorithmStruct arrAlgorithmStruct[] = 
    {
        //{"SelectionSort", SortAlgorithm::SelectionSort<int>},
        //{"InsertionSort_v1", SortAlgorithm::InsertionSort_v1<int>},
        //{"BubbleSort", SortAlgorithm::BubbleSort<int>},
        {"MergeSort", SortAlgorithm::MergeSort<int>},
        {"MergeSort_v1", SortAlgorithm::MergeSort_v1<int>},
        {"QuickSort", SortAlgorithm::QuickSort<int>},
        {"QuickSort_TwoWays", SortAlgorithm::QuickSort_TwoWays<int>},
        {"QuickSort_ThreeWays", SortAlgorithm::QuickSort_ThreeWays<int>},
        {"HeapSort", SortAlgorithm::HeapSort<int>},
        {"HeapSort_v1", SortAlgorithm::HeapSort_v1<int>},
        {"HeapSort_v2", SortAlgorithm::HeapSort_v2<int>},
        {"EOS", NULL}
    };

    int size = 500000;
    AlgorithmTester::SortAlgorithmTestSuit(AlgorithmTester::ChaosIntArr, arrAlgorithmStruct, size);
    AlgorithmTester::SortAlgorithmTestSuit(AlgorithmTester::NearlyOrderedIntArr, arrAlgorithmStruct, size);
    AlgorithmTester::SortAlgorithmTestSuit(AlgorithmTester::HighRepetitionIntArr, arrAlgorithmStruct, size);
#endif

#if SWITCH_BINARY_SEARCH_TREE_TEST
    BinarySearchTree<int, int> bst;
    int* arr = AlgorithmTester::generateRandIntArr(35, 0, 100);
    AlgorithmTester::ShowIntArray(arr, 35);
    for(int i = 0; i < 35; i++) bst.insert(arr[i], (bst.contain(arr[i]) ? bst.getValue(arr[i]) + 1 : 1));
    bst.inOrder();
    cout << "Bst has " << bst.size() << " nodes." << endl;
    cout << "Min: " << bst.min() << " Max: " << bst.max() << endl << endl;

    cout << "Del " << arr[10] << endl;
    bst.delKey(arr[10]);
    bst.inOrder();
    cout << "Bst has " << bst.size() << " nodes." << endl << endl;

    int key = rand() % 100;
    int* ceil = bst.ceil(key);
    int* floor = bst.floor(key);
    if(NULL != ceil)
        cout << "Ceil(" << key << ") = " << *ceil << endl << endl;
    else
        cout << key << " is bigger than any key of bst!" << endl << endl;

    if(NULL != floor)
        cout << "floor(" << key << ") = " << *floor << endl << endl;
    else
        cout << key << " is smaller than any key of bst!" << endl << endl;
#endif

#if SWITCH_SORT_ALGORITHM_TEST
    AlgorithmTester::UnionFindTestSuit(10000000);
#endif

#if SWITCH_GRAPH_ALGORITHM_TEST
    clock_t start, end;
    AdjacencyMatrix<double> amGraph(10000, false);
    AdjacencyLists<double> alGraph(10000, false);
    string filePath1 = "testG4.txt";
    string filePath2 = "graph1.txt";
    start = clock();
    ReadGraph<AdjacencyMatrix<double>, double>(amGraph, filePath1);
    end = clock();
    cout << "AdjacencyMatrix read from file done! Cost " << ((double)(end - start) / CLOCKS_PER_SEC) << "s" << endl;

    start = clock();
    ReadGraph<AdjacencyLists<double>, double>(alGraph, filePath1);
    end = clock();
    cout << "AdjacencyLists read from file done! Cost " << ((double)(end - start) / CLOCKS_PER_SEC) << "s" << endl;

    start = clock();
    GraphAlgorithm::MinimalSpanningTree::LazyPrim<AdjacencyMatrix<double>, double> amMstLz(amGraph);
    end = clock();
    cout << "AdjacencyMatrix MST by LazyPrim result:" << amMstLz.result() << " Cost:" << (double)(end - start) / CLOCKS_PER_SEC << endl;

    start = clock();
    GraphAlgorithm::MinimalSpanningTree::LazyPrim<AdjacencyLists<double>, double> alMstLz(alGraph);
    end = clock();
    cout << "AdjacencyLists MST by LazyPrim result:" << alMstLz.result() << " Cost:" << (double)(end - start) / CLOCKS_PER_SEC << endl;

    start = clock();
    GraphAlgorithm::MinimalSpanningTree::Prim<AdjacencyMatrix<double>, double> amMst(amGraph);
    end = clock();
    cout << "AdjacencyMatrix MST by Prim result:" << amMst.result() << " Cost:" << (double)(end - start) / CLOCKS_PER_SEC << endl;

    start = clock();
    GraphAlgorithm::MinimalSpanningTree::Prim<AdjacencyLists<double>, double> alMst(alGraph);
    end = clock();
    cout << "AdjacencyLists MST by Prim result:" << alMst.result() << " Cost:" << (double)(end - start) / CLOCKS_PER_SEC << endl;
#endif
    return 0;
}
