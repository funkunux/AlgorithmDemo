#ifndef ALGORITHMDEMO_SORTALGORITHM_H
#define ALGORITHMDEMO_SORTALGORITHM_H

#include <iostream>
#include <ctime>
#include "AlgorithmTester.h"
#include "Heap.h"

#define Swap(a, b, t) t __tmp = a; a = b; b = __tmp;

using namespace std;

namespace SortAlgorithm
{
    template<typename T>
    void SelectionSort(T arr[], int size)
    {
        int minIndex;
        for(int i = 0; i < size; i++)
        {
            minIndex = i;
            for(int j = i + 1; j < size; j++)
            {
                if(arr[j] < arr[minIndex])
                {
                    minIndex = j;
                }
            }
            //swap(arr[i], arr[minIndex]);
            int tmp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = tmp;
        }
    }

    template <typename T>
    void InsertionSort(T arr[], int size)
    {
        for(int i = 1; i < size; i++)
        {
            for(int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
            {
                //swap(arr[j], arr[j - 1]);
                T tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
            }
        }
    }


    template <typename T>
    void InsertionSort_v1(T arr[], int size)
    {
        for(int i = 1; i < size; i++)
        {
            int j = i;
            T val = arr[i];
            for(; j > 0 && val < arr[j - 1]; j--)
            {
                //swap(arr[j], arr[j - 1]);
                arr[j] = arr[j - 1];
            }
            if(j != i) arr[j] = val;
        }
    }

    template <typename T>
    void BubbleSort(T arr[], int size)
    {
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size - i - 1; j++)
            {
                if(arr[j] > arr[j + 1])
                {
                    int tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                }
            }
        }
    }

    template <typename T>
    void MergeSort(T arr[], int size)
    {
        if(size < 2) return;

        /*
         *    Index Setting:
         *    l for left
         *    r for right
         *    m for middle
         *    i for index of first part
         *    j for index of second part
         *    t for index of final result
         */
        int l = 0;
        int r = size - 1;
        int m = size / 2 - 1;
        int i = 0;
        int j = m + 1;
        int t = 0;
        
        MergeSort(arr, size / 2);
        MergeSort(arr + (size / 2), size - (size / 2));

        T *tmpArr = new T[size];
        for(int k = 0; k < size; k++)
        {
            tmpArr[k] = arr[k];
        }

        while(t < size)
        {
            if(i > m && j <= r)
            {
                arr[t++] = tmpArr[j++];
                continue;
            }

            if(i <= m && j > r)
            {
                arr[t++] = tmpArr[i++];
                continue;
            }

            if(tmpArr[i] < tmpArr[j]) arr[t++] = tmpArr[i++];
            else arr[t++] = tmpArr[j++];
        }

    }

    template <typename T>
    void MergeSort_v1(T arr[], int size)
    {
        if(size < 2) return;

        /*
         *    Index Setting:
         *    l for left
         *    r for right
         *    m for middle
         *    i for index of first part
         *    j for index of second part
         *    t for index of final result
         */
        int l = 0;
        int r = size - 1;
        int m = size / 2 - 1;
        int i = 0;
        int j = m + 1;
        int t = 0;
        
        MergeSort_v1(arr, size / 2);
        MergeSort_v1(arr + (size / 2), size - (size / 2));

        if(arr[m] <= arr[m + 1]) return;

        /* Merge process */
        T *tmpArr = new T[size];
        for(int k = 0; k < size; k++)
        {
            tmpArr[k] = arr[k];
        }

        while(t < size)
        {
            if(i > m && j <= r)
            {
                arr[t++] = tmpArr[j++];
                continue;
            }

            if(i <= m && j > r)
            {
                arr[t++] = tmpArr[i++];
                continue;
            }

            if(tmpArr[i] < tmpArr[j]) arr[t++] = tmpArr[i++];
            else arr[t++] = tmpArr[j++];
        }
    }

    template <typename T>
    void QuickSort(T arr[], int size)
    {
        if(size < 2) return;

        /* ��ֹ�����������������������˻�ΪO(n^2)���Ӷȵ��㷨 */
        srand(time(NULL) + clock());
        int v = rand() % size;
        int tmp = arr[v];
        arr[v] = arr[0];
        arr[0] = tmp;

        int i = 1;
        int j = 1;

        while(i < size)
        {
            if(arr[i] < arr[0])
            {
                tmp = arr[j];
                arr[j++] = arr[i];
                arr[i++] = tmp;
            }
            else
            {
                i++;
            }
        }
        tmp = arr[j - 1];
        arr[j - 1] = arr[0];
        arr[0] = tmp;

        if(j - 1 > 1) QuickSort(arr, j - 1);
        if(i - j > 1) QuickSort(arr + j, i - j);
    }

    template <typename T>
    void QuickSort_TwoWays(T arr[], int size)
    {
        if(size < 2) return;

        /* ��ֹ�����������������������˻�ΪO(n^2)���Ӷȵ��㷨 */
        srand(time(NULL) + clock());
        int v = rand() % size;
        int tmp = arr[v];
        arr[v] = arr[0];
        arr[0] = tmp;

        int l = 1;
        int r = size - 1;
        T head = arr[0];

        while(true)
        {
            /*
             * �˴������ж� l <= r �������ж� l < r, ��Ϊǰ�߻ᵼ�� break �� l == r ���������, �޷��ж�arr[r]�Ƿ�С��head, �����ߵ�break����Ϊr < l, arr[r] ��С�� head��
             * �Ҵ˴������ж� arr[l] < head, arr[r] > head �������ж� arr[l] <= head, arr[r] >= head����Ȼ�ᵼ�µ�arr��Ԫ���д����ظ�Ԫ��ʱ, ���㷨�˻�Ϊ O(n^2) ���㷨��
             */
            while(l <= r && arr[l] < head) l++;
            while(l <= r && arr[r] > head) r--;
            
            if(r < l) break;

            /*
             * �˴� l, r ����ǰ��һλ, ���� arr[l] == arr[r] ʱ, �������ѭ����
             */
            tmp = arr[l];
            arr[l++] = arr[r];
            arr[r--] = tmp;
        }
        
        arr[0] = arr[r];
        arr[r] = head;

        QuickSort_TwoWays(arr, r);
        QuickSort_TwoWays(arr + r + 1, size - r - 1);
    }

    template <typename T>
    void QuickSort_ThreeWays(T arr[], int size)
    {
        if(size < 2) return;

        /* ��ֹ�����������������������˻�ΪO(n^2)���Ӷȵ��㷨 */
        srand(time(NULL) + clock());
        int t = rand() % size;
        int tmp = arr[t];
        arr[t] = arr[0];
        arr[0] = tmp;

        int l = 1;
        int v = 1;
        int r = size - 1;
        T head = arr[0];

        while(v <= r)
        {
            if(head == arr[v]) v++;
            else if(head < arr[v])
            {
                Swap(arr[v], arr[r], T);
                r--;
            }
            else if(head > arr[v])
            {
                Swap(arr[v], arr[l], T);
                v++;
                l++;
            }
        }
        
        Swap(arr[0], arr[l - 1], T);

        QuickSort_ThreeWays(arr, l - 1);
        QuickSort_ThreeWays(arr + v, size - v);
    }

    template<typename T>
    void __shiftDown(T arr[], int size, int node)
    {
        assert(arr != NULL);
        assert(size > 0);
        
        int topVal = arr[node];
        int fatherIndex = node;
        int index = node * 2 + 1;
        while(index < size)
        {
            if(index + 1 < size && arr[index + 1] > arr[index]) index++;
            if(arr[index] < topVal) break;
            arr[fatherIndex] = arr[index];
            fatherIndex = index;
            index = index * 2 + 1;
        }
        arr[fatherIndex] = topVal;
    }

    template<typename T>
    void HeapSort(T arr[], int size)
    {
        assert(arr != NULL);
        assert(size > 0);
        /* Step 1: Heapify */
        for(int i = (size - 2) / 2; i >= 0; i--)
            __shiftDown(arr, size, i);
        /* Step 2: Extract Max */
        for(int i = 0; i < size - 1; i++)
        {
            Swap(arr[0], arr[size - i - 1], T);
            __shiftDown(arr, size - i - 1, 0);
        }
    }

    template<typename T>
    void HeapSort_v1(T arr[], int size)
    {
        assert(arr != NULL);
        assert(size > 0);

        MaxHeap<int> heap(size);
        for(int i = 0; i < size; i++)
        {
            heap.insert(arr[i]);
        }

        for(int i = 0; i < size; i++)
        {
            arr[size - i - 1] = heap.extractMax();
        }
    }

    template<typename T>
    void HeapSort_v2(T arr[], int size)
    {
        assert(arr != NULL);
        assert(size > 0);

        MaxHeap<int> heap(arr, size);
        for(int i = 0; i < size; i++)
        {
            arr[size - i - 1] = heap.extractMax();
        }
    }
}

#endif