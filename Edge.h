#ifndef ALGORITHMDEMO_EDGE
#define ALGORITHMDEMO_EDGE
#include <iostream>
using namespace std;

template <typename WeightType>
class Edge
{
private:
    int a, b;
    WeightType weight;
public:
    Edge(int a, int b, WeightType weight) : a(a), b(b), weight(weight) {}
    Edge() : a(0), b(0), weight() {}
    friend ostream& operator<<(ostream& o, const Edge e)
    {
        o << "(" << e.a << "-" << e.b << ":" << e.weight << ")";
        return o;
    }
    bool operator==(const Edge& e) const
    {
        return (a == e.a && b == e.b && weight == e.weight);
    }

    bool operator>(const Edge& e) const
    {
        return weight > e.weight;
    }

    bool operator<(const Edge& e) const
    {
        return weight < e.weight;
    }

    int other(int i) const
    {
        assert(i == a || i == b);
        return i == a ? a : b;
    }
    int p()
    {
        return a;
    }
    int q()
    {
        return b;
    }
    WeightType wt()
    {
        return weight;
    }
};


#endif
