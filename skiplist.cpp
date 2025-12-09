#include "skiplist.hpp"
#include <vector>
#include <cstdint>
#include <limits>
#include <random>

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

template<typename TYPE, typename COMP_FUNCTOR>
std::mt19937& Skiplist<TYPE, COMP_FUNCTOR>::get_gen() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

template<typename TYPE, typename COMP_FUNCTOR>
bool Skiplist<TYPE, COMP_FUNCTOR>::should_promote() {
    std::bernoulli_distribution dist(probability);
    return dist(get_gen());
}

template<typename TYPE, typename COMP_FUNCTOR>
const size_t Skiplist<TYPE, COMP_FUNCTOR>::random_level() {
    size_t level = 1;
    while(should_promote()) {
        level++;
    }
    return level;
}