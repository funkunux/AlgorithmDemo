#ifndef ALGORITHMDEMO_UNIONFIND_H
#define ALGORITHMDEMO_UNIONFIND_H
#include <cassert>
#include "AlgorithmTester.h"


class UnionFind
{
private:
    int* parent;
    int count;
    int maxDepth;
public:
    UnionFind(int size)
    {
        count = size;
        parent = new int[count];
        //maxDepth = 0;
        for(int i = 0; i < count; i++)
        {
            parent[i] = i;
        }
    }
    ~UnionFind()
    {
        delete [] parent;
    }

    int find(int p, int& depth)
    {
        assert(p >= 0);
        assert(p < count);

        int pId = p;
        depth = 0;
        while(pId != parent[pId])
        {
            pId = parent[pId];
            depth++;
        }
        /*if(depth > maxDepth)
        {
            maxDepth = depth;
            cout << "MaxDepth:" << maxDepth << endl;
        }*/
        return pId;
    }

    bool isConnected(int p, int q)
    {
        int depth;
        return find(p, depth) == find(q, depth);
    }
    void connect(int p, int q)
    {
        int depthP, depthQ;
        int pId = find(p, depthP);
        int qId = find(q, depthQ);

        //cout << "pD:" << depthP << " qD:" << depthQ << endl;
        if(pId == qId) return;
        if(depthP < depthQ)
            parent[pId] = qId;
        else
            parent[qId] = pId;
    }
};


class UnionFind_v1 //add size arr
{
private:
    int* parent;
    int* sz;
    int count;
public:
    UnionFind_v1(int size)
    {
        count = size;
        parent = new int[count];
        sz = new int[count];

        for(int i = 0; i < count; i++)
        {
            parent[i] = i;
            sz[i] = 1;
        }
    }
    ~UnionFind_v1()
    {
        delete [] parent;
        delete [] sz;
    }

    int find(int p)
    {
        assert(p >= 0);
        assert(p < count);

        int pId = p;
        while(pId != parent[pId])
        {
            pId = parent[pId];
        }
        return pId;
    }

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }
    void connect(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);

        if(pId == qId) return;
        if(sz[pId] < sz[qId])
        {
            parent[pId] = qId;
            sz[qId] += sz[pId];
        }
        else
        {
            parent[qId] = pId;
            sz[pId] += sz[qId];
        }
    }
};

class UnionFind_v2 //add rank arr
{
private:
    int* parent;
    int* rank;
    int count;
public:
    UnionFind_v2(int size)
    {
        count = size;
        parent = new int[count];
        rank = new int[count];

        for(int i = 0; i < count; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    ~UnionFind_v2()
    {
        delete [] parent;
        delete [] rank;
    }

    int find(int p)
    {
        assert(p >= 0);
        assert(p < count);

        int pId = p;
        while(pId != parent[pId])
        {
            pId = parent[pId];
        }
        return pId;
    }

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }
    void connect(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);

        if(pId == qId) return;
        if(rank[pId] < rank[qId])
        {
            parent[pId] = qId;
        }
        else if(rank[pId] > rank[qId])
        {
            parent[qId] = pId;
        }
        else
        {
            parent[pId] = qId;
            rank[qId]++;
        }
    }
};

class UnionFind_v3 //path compress
{
private:
    int* parent;
    int count;
public:
    UnionFind_v3(int size)
    {
        count = size;
        parent = new int[count];

        for(int i = 0; i < count; i++)
        {
            parent[i] = i;
        }
    }
    ~UnionFind_v3()
    {
        delete [] parent;
    }

    int find(int p)
    {
        assert(p >= 0);
        assert(p < count);

        int pId = p;
        while(pId != parent[pId])
        {
            parent[pId] = parent[parent[pId]];
            pId = parent[pId];
        }
        return pId;
    }

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }
    void connect(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);

        if(pId == qId) return;
        parent[pId] = qId;
    }
};

class UnionFind_v4 //add rank arr, path compress
{
private:
    int* parent;
    int* rank;
    int count;
public:
    UnionFind_v4(int size)
    {
        count = size;
        parent = new int[count];
        rank = new int[count];

        for(int i = 0; i < count; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    ~UnionFind_v4()
    {
        delete [] parent;
        delete [] rank;
    }

    int find(int p)
    {
        assert(p >= 0);
        assert(p < count);

        int pId = p;
        while(pId != parent[pId])
        {
            parent[pId] = parent[parent[pId]];
            pId = parent[pId];
        }
        return pId;
    }

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }
    void connect(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);

        if(pId == qId) return;
        if(rank[pId] < rank[qId])
        {
            parent[pId] = qId;
        }
        else if(rank[pId] > rank[qId])
        {
            parent[qId] = pId;
        }
        else
        {
            parent[pId] = qId;
            rank[qId]++;
        }
    }
};

class UnionFind_v5 //completely path compress
{
private:
    int* parent;
    int* rank;
    int count;
public:
    UnionFind_v5(int size)
    {
        count = size;
        parent = new int[count];
        rank = new int[count];

        for(int i = 0; i < count; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    ~UnionFind_v5()
    {
        delete [] parent;
        delete [] rank;
    }

    int find(int p)
    {
        assert(p >= 0);
        assert(p < count);

        int pId = p;
        if(pId != parent[pId])
        {
            parent[pId] = find(parent[pId]);
        }
        return parent[pId];
    }

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }
    void connect(int p, int q)
    {
        int pId = find(p);
        int qId = find(q);

        if(pId == qId) return;
        if(rank[pId] < rank[qId])
        {
            parent[pId] = qId;
        }
        else if(rank[pId] > rank[qId])
        {
            parent[qId] = pId;
        }
        else
        {
            parent[pId] = qId;
            rank[qId]++;
        }
    }
};
#endif
