#ifndef ALGORITHMDEMO_ALGORITHMTESTER_H
#define ALGORITHMDEMO_ALGORITHMTESTER_H

#include <iostream>
#include <ctime>
#include <cassert>
#include <string>
#include "UnionFind.h"

using namespace std;

namespace AlgorithmTester
{
    int * generateRandIntArr(int size, int rangeL, int rangeR)
    {
        assert(rangeL < rangeR);

        int *arr = new int[size];

        srand(time(NULL) + clock());
        for(int i = 0; i < size; i++)
        {
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        }
        return arr;
    }

    int * generateNearlyOrderedIntArr(int size, int swapTimes)
    {
        int *arr = new int[size];
        for(int i = 0; i < size; i++) arr[i] = i;
        
        srand(time(NULL) + clock());
        for(int i = 0; i < swapTimes; i++)
        {
            int indexX = rand() % size;
            int indexY = rand() % size;
            swap(arr[indexX], arr[indexY]);
        }
        return arr;
    }

    template <typename T>
    bool isSorted(T arr[], int size)
    {
        for(int i = 0; i < size - 1; i++)
        {
            if(arr[i] > arr[i + 1])
                return false;
        }
        return true;
    }

    template <typename T>
    bool SortAlgorithmTest(string sortName, void(*sortAlgorithm)(T [], int), T arr[], int size)
    {
        bool result;
        clock_t startT = clock();
        sortAlgorithm(arr, size);
        clock_t endT = clock();
        
        cout << sortName;
        if(isSorted(arr, size))
        {
            result = true;
            cout << " Test Succ! ";
        }
        else
        {
            result = false;
            cout << " Test Fail! ";
        }
        cout << "Cost: " << (double)(endT - startT) / CLOCKS_PER_SEC << "s" << endl;
        return result;
    }


    int *CopyIntArray(int arr[], int size)
    {
        int *newArr = new int[size];

        copy(arr, arr + size, newArr);

        return newArr;
    }

    void ShowIntArray(int arr[], int size)
    {
        for(int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }

        cout << endl;
    }

    typedef void (*SortAlgorithmFunc)(int[], int);
    typedef struct
    {
        string algorithmName;
        SortAlgorithmFunc func;
    } SortAlgorithmStruct;

    enum SortAlgorithmTestType
    {
        ChaosIntArr,
        NearlyOrderedIntArr,
        HighRepetitionIntArr
    };

    bool SortAlgorithmTestSuit(SortAlgorithmTestType type,SortAlgorithmStruct arrAlgoStruct[], int sizeOfIntArr)
    {
        bool testResult = true;
        string typeName;
        int *arr = NULL;
        switch(type)
        {
            case ChaosIntArr:
                typeName = "ChaosIntArr";
                arr = generateRandIntArr(sizeOfIntArr, 0, sizeOfIntArr);
                break;
            case NearlyOrderedIntArr:
                typeName = "NearlyOrderedIntArr";
                arr = generateNearlyOrderedIntArr(sizeOfIntArr, sizeOfIntArr / 1000);
                break;
            case HighRepetitionIntArr:
                typeName = "HighRepetitionIntArr";
                arr = generateRandIntArr(sizeOfIntArr, 0, sizeOfIntArr / 1000);
                break;
            default:
                cout << "Error Type of Test Suit!" << endl;
                return false;
        }
        
        cout << "******************* TestSuit " << typeName << ": size(" <<  sizeOfIntArr << ") *******************" << endl;
        for(int i = 0; arrAlgoStruct[i].func != NULL; i++)
        {
            int *tmpArr = CopyIntArray(arr, sizeOfIntArr);
            if(false == SortAlgorithmTest(arrAlgoStruct[i].algorithmName, arrAlgoStruct[i].func, tmpArr, sizeOfIntArr)) testResult = false;
            delete [] tmpArr;
        }

        delete [] arr;
        cout << "******************* Test Result: " << (testResult ? "Succ" : "Fail") << " *******************" << endl << endl;
        return testResult;
    }

    template<typename T>
    bool UnionFindTest(string name, int* pArr, int* qArr, int size)
    {
        assert(NULL != pArr);
        assert(NULL != qArr);

        T u(size);
        bool result = true;

        bool isSameArrs = true;
        for(int i = 0; i < size; i++)
        {
            if(pArr[i] != qArr[i])
            {
                isSameArrs = false;
                break;
            }
        }
        
        if(isSameArrs)
        {
            cout << "Arrays are same! Please check!" << endl;
            return false;
        }
        cout << name << " Test: ";
        clock_t startT = clock();
        for(int i = 0; i < size; i++)
        {
            u.connect(pArr[i], qArr[i]);
        }
        for(int i = 0; i < size; i++)
        {
            if(!u.isConnected(pArr[i], qArr[i]))
                result = false;
        }
        clock_t endT = clock();
        cout << (result ? "Succ" : "Fail") << ". Cost: " << (double)(endT - startT) / CLOCKS_PER_SEC << "s" << endl;
        return result;
    }

    void UnionFindTestSuit(int size)
    {
        bool testResult = true;
        int *pArr = generateRandIntArr(size, 0, size - 1);
        int *qArr = generateRandIntArr(size, 0, size - 1);

        cout << "******************* TestSuit " << "UnionFind" << ": size(" <<  size << ") *******************" << endl;
        if(true != AlgorithmTester::UnionFindTest<UnionFind>("UnionFind", pArr, qArr, size)) testResult == false;
        if(true != AlgorithmTester::UnionFindTest<UnionFind_v1>("UnionFind_v1", pArr, qArr, size)) testResult == false;
        if(true != AlgorithmTester::UnionFindTest<UnionFind_v2>("UnionFind_v2", pArr, qArr, size)) testResult == false;
        if(true != AlgorithmTester::UnionFindTest<UnionFind_v3>("UnionFind_v3", pArr, qArr, size)) testResult == false;
        if(true != AlgorithmTester::UnionFindTest<UnionFind_v4>("UnionFind_v4", pArr, qArr, size)) testResult == false;
        if(true != AlgorithmTester::UnionFindTest<UnionFind_v5>("UnionFind_v5", pArr, qArr, size)) testResult == false;

        cout << "******************* Test Result: " << (testResult ? "Succ" : "Fail") << " *******************" << endl << endl;
        delete [] pArr;
        delete [] qArr;
    }
}


#endif