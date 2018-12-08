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
        bool *visitSet;

        GraphAlgorithm(Graph &g) : graph(g)
        {
            visitSet = new bool[graph.V()]();
        }
        virtual ~GraphAlgorithm()
        {
            delete [] visitSet;
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
                if(!visitSet[i])
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
            visitSet[startNode] = true;
            pool[startNode] = ccount + 1;
            for(int node = iter.begin(); !iter.end(); node = iter.next())
            {
                if(!visitSet[node])
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
            assert(NULL != visitSet);
            for(int i = 0; i < graph.V(); i++)
            {
                from[i] = -1;
                visitSet[i] = false;
            }
        }
        void DFT(int startNode, int targetNode)
        {
            assert(startNode >= 0 && startNode < graph.V());
            assert(targetNode >= 0 && targetNode < graph.V());
            visitSet[startNode] = true;
            if(startNode == targetNode) return;
            Graph::Iterator iter(graph, startNode);
            for(int node = iter.begin(); !iter.end(); node = iter.next())
            {
                if(!visitSet[node] )
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
            visitSet[startNode] = true;

            while(q.size())
            {
                node = q.front();
                if(node == targetNode) break;
                q.pop();
                Graph::Iterator iter(graph, node);
                for(int tmp = iter.begin(); !iter.end(); tmp = iter.next())
                {
                    
                    if(!visitSet[tmp] )
                    {
                        from[tmp] = node;
                        visitSet[tmp] = true;
                        q.push(tmp);
                    }
                }
            }
        }

        void ShowPath(int s, int t)
        {
            if(!visitSet[t])
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
        private:
            void GetMST()
            {
                int n = 0;
                visitSet[0] = true;
                bool done = false;
                while(true)
                {
                    Graph::Iterator iter(graph, n);
                    for(Edge<WeightType>* e = iter.begin(); !iter.end(); e = iter.next())
                    {
                        if(!visitSet[e->q()])
                            heap.insert(*e);
                    }
                    Edge<WeightType> minEdge = heap.extractMin();
                    while(visitSet[minEdge.q()])
                    {
                        if(heap.empty())
                        {
                            done = true;
                            break;
                        }
                        minEdge = heap.extractMin();
                    }
                    if(done) break;
                    n = minEdge.q();
                    visitSet[n] = true;
                    resultVec.push_back(minEdge);
                }
                minWeight = resultVec[0].wt();
                for(int i = 1; i < resultVec.size(); i++)
                    minWeight += resultVec[i].wt();
            }
        public:
            LazyPrim(Graph& G) : MST(G) { GetMST(); }
        };
    }
}


#endif
