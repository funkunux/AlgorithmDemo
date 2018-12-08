#ifndef ALGORITHMDEMO_EDGE
#define ALGORITHMDEMO_EDGE

template <typename WeightType>
class Edge
{
private:
    int a, b;
    WeightType weight;
public:
    Edge(int a, int b, WeightType weight) : a(a), b(b), weight(weight) {}
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
};

#endif
