#ifndef ALGORITHMDEMO_GRAPHALGORITHM_H
#define ALGORITHMDEMO_GRAPHALGORITHM_H
#include <queue>
#include <stack>
#include "Edge.h"

namespace GraphAlgorithm
{
    template<typename Graph>
    class GraphAlgorithm
    {
    protected:
        Graph &graph;
        bool *visited;

        GraphAlgorithm(Graph &g) : graph(g)
        {
            visited = new bool[graph.V()]();
        }
        virtual ~GraphAlgorithm()
        {
            delete [] visited;
        }
        virtual void DFT(int startNode){}
    };


    template<typename Graph>
    class Component : private GraphAlgorithm<Graph>
    {
    private:
        int ccount;
        int *pool;
    public:
        Component(Graph &g) : GraphAlgorithm(g)
        {
            pool = new int[graph.V()]();
            ccount = 0;
            for(int i = 0; i < graph.V(); i++)
            {
                if(!visited[i])
                {
                    DFT(i);
                    ccount++;
                }
            }
        }
        ~Component()
        {
            delete [] pool;
        }
        int count()
        {
            return ccount;
        }
        bool isConnected(int p, int q)
        {
            assert(p >= 0 && p < graph.V());
            assert(q >= 0 && q < graph.V());
            return pool[p] == pool[q];
        }
    private:
        void DFT(int startNode)
        {
            assert(startNode >= 0 && startNode < graph.V());
            Graph::Iterator iter(graph, startNode);
            visited[startNode] = true;
            pool[startNode] = ccount + 1;
            for(int node = iter.begin(); !iter.end(); node = iter.next())
            {
                if(!visited[node])
                    DFT(node);
            }
        }
    };

    template<typename Graph>
    class Path : private GraphAlgorithm<Graph>
    {
    private:
        int *from;
    public:
        Path(Graph &g) : GraphAlgorithm(g)
        {
            from = new int[graph.V()];
            for(int i = 0; i < graph.V(); i++)
                from[i] = -1;
        }
        ~Path()
        {
            delete [] from;
        }
        void ShowDftPath(int s, int t)
        {
            init();
            DFT(s, t);
            ShowPath(s, t);
        }
        void ShowBftPath(int s, int t)
        {
            init();
            BFT(s, t);
            ShowPath(s, t);
        }
    private:
        void init()
        {
            assert(NULL != from);
            assert(NULL != visited);
            for(int i = 0; i < graph.V(); i++)
            {
                from[i] = -1;
                visited[i] = false;
            }
        }
        void DFT(int startNode, int targetNode)
        {
            assert(startNode >= 0 && startNode < graph.V());
            assert(targetNode >= 0 && targetNode < graph.V());
            visited[startNode] = true;
            if(startNode == targetNode) return;
            Graph::Iterator iter(graph, startNode);
            for(int node = iter.begin(); !iter.end(); node = iter.next())
            {
                if(!visited[node] )
                {
                    from[node] = startNode;
                    DFT(node, targetNode);
                }
            }
        }

        void BFT(int startNode, int targetNode)
        {
            assert(startNode >= 0 && startNode < graph.V());
            assert(targetNode >= 0 && targetNode < graph.V());
            queue<int> q;
            int node;
            q.push(startNode);
            visited[startNode] = true;

            while(q.size())
            {
                node = q.front();
                if(node == targetNode) break;
                q.pop();
                Graph::Iterator iter(graph, node);
                for(int tmp = iter.begin(); !iter.end(); tmp = iter.next())
                {

                    if(!visited[tmp] )
                    {
                        from[tmp] = node;
                        visited[tmp] = true;
                        q.push(tmp);
                    }
                }
            }
        }

        void ShowPath(int s, int t)
        {
            if(!visited[t])
            {
                cout << "No path to node " << t << "." << endl;
                return;
            }
            stack<int> st;
            int tmp = t;
            while(tmp != -1)
            {
                st.push(tmp);
                tmp = from[tmp];
            }
            cout << "Path: " ;
            while(st.size())
            {
                cout << st.top();
                if(st.size() != 1)
                    cout  << " -> ";
                st.pop();
            }
            cout << endl;
        }
    };

    namespace MinimalSpanningTree
    {
        template <typename Graph, typename WeightType>
        class MST : public GraphAlgorithm<Graph>        //Minimal Spanning Tree
        {
        protected:
            MinHeap<Edge<WeightType>> heap;
            vector<Edge<WeightType>> resultVec;
            WeightType minWeight;
            virtual void GetMST(){}
        public:
            MST(Graph& G) : GraphAlgorithm(G), heap(G.E()) {}
            vector<Edge<WeightType>> mstEdges()
            {
                return resultVec;
            }
            WeightType result()
            {
                return minWeight;
            }

        };

        template <typename Graph, typename WeightType>
        class LazyPrim : public MST<Graph, WeightType>
        {
        protected:
            void visit(int node)
            {
                assert(!visited[node]);
                Graph::Iterator iter(graph, node);
                for(auto e = iter.begin(); !iter.end(); e = iter.next())
                {
                    if(!visited[e->other(node)])
                        heap.insert(*e);
                }
                visited[node] = true;
            }

            void GetMST()
            {
                visit(0);
                while(!heap.empty())
                {
                    auto e = heap.extractMin();
                    if(visited[e.p()] == visited[e.q()])
                        continue;
                    resultVec.push_back(e);
                    visit(e.q());
                }
                minWeight = resultVec[0].wt();
                for(int i = 1; i < resultVec.size(); i++)
                    minWeight += resultVec[i].wt();
            }
        public:
            LazyPrim(Graph& G) : MST(G) { GetMST(); }
        };

        template <typename Graph, typename WeightType>
        class Prim : public MST<Graph, WeightType>
        {
        private:
            void visit(int node)
            {
                assert(!visited[node]);
                Graph::Iterator iter(graph, node);
                //cout << "node:" << node << endl;
                for(auto e = iter.begin(); !iter.end(); e = iter.next())
                {
                    int other = e->other(node);
                    if(!visited[other])
                    {
                        //cout << "e:" << *e  << endl;
                        //if(edgeTo[other]) cout << "other" << other << ":" << *edgeTo[other] << endl;
                        if(NULL == edgeTo[other] || *edgeTo[other] > *e)
                        {
                            edgeTo[other] = e;
                        }
                        else if(*edgeTo[other] < *e)
                        {
                            //cout << "continue" << endl;
                            continue;
                        }

                        heap.insert(*e);
                    }

                }
                visited[node] = true;
            }

            void GetMST()
            {
                visit(0);
                while(!heap.empty())
                {
                    auto e = heap.extractMin();
                    if(visited[e.p()] == visited[e.q()])
                    {
                        //cout << "after visit, continue:" << e << endl;
                        continue;
                    }
                    resultVec.push_back(e);
                    visit(e.q());
                }
                if(resultVec.size()) minWeight = resultVec[0].wt();
                for(int i = 1; i < resultVec.size(); i++)
                    minWeight += resultVec[i].wt();
            }

            vector<Edge<WeightType>*> edgeTo;
        public:
            Prim(Graph& G) : MST(G) 
            {
                for(int i = 0; i < G.V(); i++)
                    edgeTo.push_back(NULL);
                GetMST(); 
            }
            ~Prim(){}

        };
    }

    template<typename Graph, typename WeightType>
    class FKHSP
    {
    private:
        Graph& graph;
        bool *visited;
        int *from;
        WeightType *distTo;
        bool hasNegativeCircle;

        void DFT(int node)
        {
            //cout << "visit node " << node << endl;
            if(visited[node] || hasNegativeCircle) 
            {
                hasNegativeCircle = true;
                return;
            }
            else visited[node] = true;

            Graph::Iterator iter(graph, node);
            for(auto e = iter.begin(); !iter.end(); e = iter.next())
            {
                int other = e->other(node);
                if(-1 == from[other] || distTo[other] > distTo[node] + e->wt())
                {
                    from[other] = node;
                    distTo[other] = distTo[node] + e->wt();
                    DFT(other);
                }
            }
            visited[node] = false;
        }
    public:
        FKHSP(Graph& g, int start) : graph(g)
        {
            visited = new bool[g.V()]();
            from = new int[g.V()];
            distTo = new WeightType[g.V()];
            hasNegativeCircle = false;
            for(int i = 0; i < g.V(); i++)
            {
                from[i] = -1;
            }
            from[start] = start;
            distTo[start] = WeightType();
            DFT(start);
        }
        ~FKHSP()
        {
            delete [] visited;
            delete [] from;
            delete [] distTo;
        }

        bool hasPathTo(int node)
        {
            assert(node >= 0 && node < graph.V());
            return from[node] != -1;
        }
        WeightType distanceTo(int node)
        {
            assert(hasPathTo(node));
            return distTo[node];
        }
        void showPathTo(int node)
        {
            if(!hasPathTo(node))
            {
                cout << "No path to node " << node << "!" << endl;
                return;
            }
            if(hasNegativeCircle)
            {
                cout << "Error: There is negative circle in this graph!" << endl;
                return;
            }
            stack<int> s;
            int pre = node;
            while(pre != from[pre])
            {
                s.push(pre);
                pre = from[pre];
            }
            s.push(pre);


            cout << "Path to node " << node << " (Distance: " << distTo[node] << "): ";
            while(!s.empty())
            {
                cout << s.top() << " ";
                s.pop();
            }
            cout << endl;
        }
    };

    template<typename Graph, typename WeightType>
    class BellmanFord
    {
    private:
        Graph& graph;
        int *from;
        WeightType *distTo;
        bool hasNegativeCircle;

        void run(int node)
        {
            for(int pass = 1; pass < graph.V(); pass++)
            {
                for(int i = 0; i < graph.V(); i++)
                {
                    if(-1 == from[i]) continue;
                    Graph::Iterator iter(graph, i);
                    for(auto e = iter.begin(); !iter.end(); e = iter.next())
                    {
                        int other = e->other(i);
                        if(-1 == from[other] || distTo[other] > distTo[i] + e->wt())
                        {
                            from[other] = i;
                            distTo[other] = distTo[i] + e->wt();
                        }
                    }
                }
            }
            hasNegativeCircle = checkNegativeCircle();
        }

        bool checkNegativeCircle()
        {
            for(int i = 0; i < graph.V(); i++)
            {
                if(-1 == from[i]) continue;
                Graph::Iterator iter(graph, i);
                for(auto e = iter.begin(); !iter.end(); e = iter.next())
                {
                    int other = e->other(i);
                    if(-1 == from[other] || distTo[other] > distTo[i] + e->wt())
                    {
                        return true;
                    }
                }
            }
            return false;
        }
    public:
        BellmanFord(Graph& g, int start) : graph(g)
        {
            from = new int[g.V()];
            distTo = new WeightType[g.V()];
            hasNegativeCircle = false;
            for(int i = 0; i < g.V(); i++)
            {
                from[i] = -1;
            }
            from[start] = start;
            distTo[start] = WeightType();
            run(start);
        }
        ~BellmanFord()
        {
            delete [] from;
            delete [] distTo;
        }

        bool hasPathTo(int node)
        {
            assert(node >= 0 && node < graph.V());
            return from[node] != -1;
        }
        WeightType distanceTo(int node)
        {
            assert(hasPathTo(node));
            return distTo[node];
        }
        void showPathTo(int node)
        {
            if(!hasPathTo(node))
            {
                cout << "No path to node " << node << "!" << endl;
                return;
            }
            if(hasNegativeCircle)
            {
                cout << "Error: There is negative circle in this graph!" << endl;
                return;
            }
            stack<int> s;
            int pre = node;
            while(pre != from[pre])
            {
                s.push(pre);
                pre = from[pre];
            }
            s.push(pre);


            cout << "Path to node " << node << " (Distance: " << distTo[node] << "): ";
            while(!s.empty())
            {
                cout << s.top() << " ";
                s.pop();
            }
            cout << endl;
        }
    };

    template<typename Graph>
    class GenerateRandomGraph
    {
    private:
        Graph& graph;
    public:
        GenerateRandomGraph(Graph& g) : graph(g)
        {
            int size = graph.V();
            srand(time(NULL) + clock());
            for(int i = 0; i < size; i++)
            {
                if(i != size - 1)
                    graph.addEdge(i, i + 1, rand() % 100);
                else
                    graph.addEdge(i, 0, rand() % 100);
                for(int j = 0; j < size / 100 + 1; j++)
                {
                    graph.addEdge(i, rand() % size, rand() % 100);
                }
            }
        }
    };


}


#endif
