#ifndef ALGORITHMDEMO_READGRAPH_H
#define ALGORITHMDEMO_READGRAPH_H
#include <sstream>
#include <fstream>
#include <string>
#include <cassert>

template <typename Graph>
class ReadGraph
{
    Graph &G;
public:
    ReadGraph(Graph &g, string& filePath) : G(g)
    {
        ifstream file(filePath);
        assert(file.is_open());
        string line;
        assert(getline(file, line));
        stringstream ss(line);
        int V, E, p, q;
        ss >> V >> E;
        assert(V == G.V());
        for(int i = 0; i < E; i++)
        {
            assert(getline(file, line));
            stringstream ss(line);
            ss >> p >> q;
            G.addEdge(p, q);
        }
    }

};


#endif
