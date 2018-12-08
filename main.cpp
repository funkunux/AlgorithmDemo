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
#define SWITCH_GRAPH_ALGORITHM_TEST     0


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
    AdjacencyMatrix amGraph(13, false);
    AdjacencyLists alGraph(7, false);
    string filePath1 = "graph1.txt";
    string filePath2 = "graph2.txt";
    ReadGraph<AdjacencyMatrix>(amGraph, filePath1);
    ReadGraph<AdjacencyLists>(alGraph, filePath2);
    amGraph.show();
    alGraph.show();

    GraphAlgorithm::Component<AdjacencyMatrix> amComponent(amGraph);
    GraphAlgorithm::Component<AdjacencyLists> alComponent(alGraph);
    cout << "graph1 component: " << amComponent.count() << endl;
    cout << "graph2 component: " << alComponent.count() << endl;

    GraphAlgorithm::Path<AdjacencyMatrix> amPath(amGraph);
    amPath.ShowDftPath(0, 6);
    amPath.ShowBftPath(0, 6);
#endif

    return 0;
}
