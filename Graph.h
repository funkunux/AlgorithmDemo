#ifndef ALGORITHMDEMO_GRAPH_H
#define ALGORITHMDEMO_GRAPH_H
#include <vector>
#include <cassert>
#include "Edge.h"

template <typename WeightType>
class AdjacencyMatrix
{
private:
    Edge<WeightType> ***matrix;
    int n;
    int m;
    bool directed;
public:
    AdjacencyMatrix(int count, bool directed)
    {
        n = count;
        this->directed = directed;
        m = 0;
        matrix = new Edge<WeightType> **[count];
        for(int i = 0; i < count; i++)
        {
            matrix[i] = new Edge<WeightType> *[count];
            for(int j = 0; j < n; j++)
                matrix[i][j] = NULL;
        }
    }
    ~AdjacencyMatrix()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
                if(NULL != matrix[i][j])
                    delete matrix[i][j];
            delete [] matrix[i];
        }
        delete [] matrix;
    }

    int V()
    {
        return n;
    }

    int E()
    {
        return m;
    }

    void addEdge(int p, int q, WeightType w)
    {
        assert(0 <= p && p < n);
        assert(0 <= q && q < n);

        if(hasEdge(p, q))
        {
            delete matrix[p][q];
            if(!directed) delete matrix[q][p];
            m--;
        }

        matrix[p][q] = new Edge<WeightType>(p, q, w);
        if(!directed) matrix[q][p] = new Edge<WeightType>(q, p, w);
        m++;
    }

    bool hasEdge(int p, int q) const
    {
        assert(0 <= p && p < n);
        assert(0 <= q && q < n);
        return matrix[p][q] != NULL;
    }

    void show()
    {
        cout << "Graph(" << n << ", " << m << "):" << endl;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(matrix[i][j])
                    cout << matrix[i][j]->wt();
                else
                    cout << "NULL";
                cout << "\t";
            }
            cout << endl;
        }
        cout << "Done!" << endl;
    }

public:
    class Iterator
    {
    private:
        AdjacencyMatrix<WeightType> &G;
        int index;
        int node;
    public:
        Iterator(AdjacencyMatrix<WeightType> &g, int p) : G(g)
        {
            index = 0;
            node = p;
        }
        Edge<WeightType>* begin()
        {
            index = -1;
            return next();
        }
        bool end()
        {
            return (index >= G.n);
        }
        Edge<WeightType>* next()
        {
            index++;
            while(index < G.n)
            {
                if(NULL != G.matrix[node][index]) return G.matrix[node][index];
                index++;
            }
            return NULL;
        }
    };
};

template <typename WeightType>
class AdjacencyLists
{
private:
    vector<vector<Edge<WeightType>*>> lists;
    int n;
    int m;
    bool directed;
public:
    AdjacencyLists(int count, bool directed)
    {
        n = count;
        this->directed = directed;
        m = 0;
        
        for(int i = 0; i < count; i++)
        {
            lists.push_back(vector<Edge<WeightType>*>());
        }
    }
    ~AdjacencyLists()
    {
        for(int i = 0; i < lists.size(); i++)
            for(int j = 0; j < lists[i].size(); j++)
                delete lists[i][j];
    }

    int V()
    {
        return n;
    }

    int E()
    {
        return m;
    }

    void addEdge(int p, int q, WeightType w)
    {
        assert(0 <= p && p < n);
        assert(0 <= q && q < n);

        //if(hasEdge(p, q)) return;     //it spents too much time
        lists[p].push_back(new Edge<WeightType>(p, q, w));
        if(p != q && !directed) lists[q].push_back(new Edge<WeightType>(q, p, w));
        m++;
    }

    bool hasEdge(int p, int q) const
    {
        assert(0 <= p && p < n);
        assert(0 <= q && q < n);
        for(int i = 0; i < lists[p].size(); i++)
        {
            if(q == lists[p][i]->other(p)) return true;
        }
        return false;
    }

    void show()
    {
        cout << "Graph(" << n << ", " << m << "):" << endl;
        for(int i = 0; i < n; i++)
        {
            cout << i << ": ";
            for(int j = 0; j < lists[i].size(); j++)
            {
                cout << *lists[i][j] << "\t";
            }
            cout << endl;
        }
        cout << "Done!" << endl;
    }
public:
    class Iterator
    {
    private:
        AdjacencyLists &G;
        int index;
        int node;
    public:
        Iterator(AdjacencyLists &g, int p) : G(g)
        {
            index = 0;
            node = p;
        }
        Edge<WeightType>* begin()
        {
            index = -1;
            return next();
        }
        bool end()
        {
            return (index >= G.lists[node].size());
        }
        Edge<WeightType>* next()
        {
            index++;
            if(index < G.lists[node].size())
                return G.lists[node][index];
            return NULL;
        }
    };
};


#endif
