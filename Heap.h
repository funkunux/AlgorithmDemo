#ifndef ALGORITHMDEMO_HEAP_H
#define ALGORITHMDEMO_HEAP_H

#include <stdio.h>
#include <iostream>
#include <math.h>  //pow

#define Swap(a, b, t) t __tmp = a; a = b; b = __tmp;

using namespace std;

template<typename T>
class MaxHeap
{
private:
    int count;
    int cap;
    T *data;

    void printSpace(int num)
    {
        while(num--) printf("   ");
    }
    
    /* 优化点: 使用单次赋值来代替Swap(两次赋值), 确定 data[count] 最终位置后再进行最后的赋值操作 */
    void shiftUp(int index)
    {
        if(index < 2) return;

        int parentInd = index / 2;
        if(data[index] > data[parentInd])
        {
            Swap(data[index], data[parentInd], T);
            shiftUp(parentInd);
        }
    }

    /* 优化点: 使用单次赋值来代替Swap(两次赋值), 确定 data[1] 最终位置后再进行最后的赋值操作 */
    void shiftDown(int index)
    {
        int sonInd = index * 2;
        if(sonInd > count) return;
        
        if(sonInd + 1 <= count && data[sonInd] < data[sonInd + 1]) sonInd++;
        if(data[index] < data[sonInd]) 
        {
            Swap(data[index], data[sonInd], T);
            shiftDown(sonInd);
        }
    }
public:
    int size()
    {
        return count;
    }
    int capacity()
    {
        return cap;
    }
    bool isEmpty()
    {
        return (0 == count);
    }
    MaxHeap(int size)
    {
        count = 0;
        cap = size + 1;
        data = new T[cap]();
    }
    /* Heapify */
    MaxHeap(T arr[], int size)
    {
        count = 0;
        cap = size + 1;
        data = new T[cap]();
        for(int i = 0; i < size; i++) data[++count] = arr[i];
        for(int i = count / 2; i > 0; i--) shiftDown(i);
    }
    ~MaxHeap()
    {
        delete [] data;
        data = NULL;
    }
    void insert(T val)
    {
        if(count + 1 == cap)
        {
            cout << "Insert Failed: Out of range!" << endl;
            return;
        }
        data[++count] = val;

        shiftUp(count);
    }

    T extractMax()
    {
        if(isEmpty()) return T();

        T result = data[1];
        data[1] = data[count--];
        shiftDown(1);
        return result;
    }

    int depth()
    {
        if(isEmpty()) return 0;

        int result = 1;
        int tmp = count;
        while(tmp /= 2) result++;
        return result;
    }
    
    /* Only when T is INT */
    void show()
    {
        int _depth = depth();

        printf("Depth: %d, data[%d]: {", _depth, count);
        for(int i = 1; i < count; i++)
        {
            printf("%d, ", data[i]);
        }
        printf("%d}\n", data[count]);

        int curLevel = 1;
        int spaceNum = 0;
        for(int i = 1; i <= count; i++)
        {
            if(i == pow(2, curLevel - 1))
            {
                spaceNum = pow(2, _depth - curLevel) - 1;
                printf("\n");
                printSpace(spaceNum);
                curLevel++;
            }
            printf("%3d", data[i]);
            printSpace(spaceNum * 2 + 1);
        }
        printf("\n");
    }
};

template <typename T>
class MinHeap
{
private:
    T *arr;
    int cap;
    int count;
public:
    MinHeap(int n)
    {
        assert(n > 0);
        arr = new T[n];
        cap = n;
        count = 0;
    }
    int size()
    {
        return count;
    }
    int capacity()
    {
        return cap;
    }
    bool empty()
    {
        return (0 == count);
    }

    void insert(T val)
    {
        assert(count < cap);
        arr[count] = val;
        shiftUp(count++);
    }

    void shiftUp(int node)
    {
        assert(0 <= node && count > node);
        
        int n = node;
        T val = arr[node];
        while(n > 0)
        {
            int p = (n - 1) / 2;
            if(arr[p] > val)
                arr[n] = arr[p];
            else
                break;
            n = p;
        }
        arr[n] = val;
    }

    T extractMin()
    {
        assert(count > 0);
        T rtlVal = arr[0];
        arr[0] = arr[count - 1];
        shiftDown(0);
        count--;
        return rtlVal;
    }

    void shiftDown(int node)
    {
        assert(node >= 0 && node < count);
        int n = node;
        int s = n * 2 + 1;
        T val = arr[node];
        while(s < count)
        {
            if(s + 1 < count && arr[s] > arr[s + 1]) s++;
            if(arr[s] < val)
                arr[n] = arr[s];
            else
                break;
            n = s;
            s = s * 2 + 1;
        }
        arr[n] = val;
    }
};



#endif
