#ifndef ALGORITHMDEMO_GRAPH_H
#define ALGORITHMDEMO_GRAPH_H
#include <vector>
#include <cassert>

class AdjacencyMatrix
{
private:
    bool **matrix;
    int n;
    int m;
    bool directed;
public:
    AdjacencyMatrix(int count, bool directed)
    {
        n = count;
        this->directed = directed;
        m = 0;
        matrix = new bool *[count];
        for(int i = 0; i < count; i++)
        {
            matrix[i] = new bool[count]();
        }
    }
    ~AdjacencyMatrix()
    {
        for(int i = 0; i < n; i++)
        {
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

    void addEdge(int p, int q)
    {
        assert(0 <= p && p < n);
        assert(0 <= q && q < n);

        if(hasEdge(p, q)) return;
        matrix[p][q] = true;
        if(!directed) matrix[q][p] = true;
        m++;
    }

    bool hasEdge(int p, int q) const
    {
        assert(0 <= p && p < n);
        assert(0 <= q && q < n);
        return matrix[p][q];
    }

    void show()
    {
        cout << "Graph(" << n << ", " << m << "):" << endl;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Done!" << endl;
    }

public:
    class Iterator
    {
    private:
        AdjacencyMatrix &G;
        int index;
        int node;
    public:
        Iterator(AdjacencyMatrix &g, int p) : G(g)
        {
            index = 0;
            node = p;
        }
        int begin()
        {
            index = -1;
            return next();
        }
        bool end()
        {
            return (index >= G.n);
        }
        int next()
        {
            index++;
            while(index < G.n)
            {
                if(G.matrix[node][index]) return index;
                index++;
            }
            return -1;
        }
    };
};

class AdjacencyLists
{
private:
    vector<vector<int>> lists;
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
            lists.push_back(vector<int>());
        }
    }
    ~AdjacencyLists(){}

    int V()
    {
        return n;
    }

    int E()
    {
        return m;
    }

    void addEdge(int p, int q)
    {
        assert(0 <= p && p < n);
        assert(0 <= q && q < n);

        //if(hasEdge(p, q)) return;     //it spents too much time
        lists[p].push_back(q);
        if(p != q && !directed) lists[q].push_back(p);
        m++;
    }

    bool hasEdge(int p, int q) const
    {
        assert(0 <= p && p < n);
        assert(0 <= q && q < n);
        for(int i = 0; i < lists[p].size(); i++)
        {
            if(q == lists[p][i]) return true;
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
                cout << lists[i][j] << " ";
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
        int begin()
        {
            index = -1;
            return next();
        }
        bool end()
        {
            return (index >= G.lists[node].size());
        }
        int next()
        {
            index++;
            if(index < G.lists[node].size())
                return G.lists[node][index];
            return -1;
        }
    };
};


#endif
