#ifndef SKIPLIST_HPP
#define SKIPLIST_HPP

#include <vector>
#include <cstdint>
#include <limits>
#include <random>

using namespace std;

template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class Skiplist {
public:
    Skiplist();

    Skiplist(const double _probability);

    TYPE& front();

    TYPE& back();

    bool empty();

    size_t size() const;

    void insert(const TYPE& num);

    void erase(const TYPE& num);

    uint32_t getNumLevels() const;

    void clear();

    ~Skiplist();

private:
    struct Node {
        TYPE value;
        Node* below;
        Node* next;

        Node(const TYPE& _val, Node* _below = nullptr, Node* _next = nullptr)
            : value(_val), below(_below), next(_next) {}
    };

    struct Head {
        Node* next;

        Head() : next(nullptr) {}
    };

    vector<Head> levelHeads;
    size_t curLevel;
    size_t size;
    double probability;
};

template<typename TYPE, typename COMP_FUNCTOR>
Skiplist<TYPE, COMP_FUNCTOR>::Skiplist() 
    : curLevel(1), elementCount(0), probability(0.5) {
    levelHeads.resize(curLevel);
}

template<typename TYPE, typename COMP_FUNCTOR>
Skiplist<TYPE, COMP_FUNCTOR>::Skiplist(const double _probability) 
    : curLevel(1), elementCount(0), probability(_probability) {
    levelHeads.resize(curLevel);
}

bool coin_flip(double p) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::bernoulli_distribution dist(p);
    return dist(gen);
}

#endif // SKIPLIST_HPP