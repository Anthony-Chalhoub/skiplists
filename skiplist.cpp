#include "skiplist.hpp"
#include <vector>
#include <cstdint>
#include <limits>
#include <random>

template<typename TYPE, typename COMP_FUNCTOR>
Skiplist<TYPE, COMP_FUNCTOR>::Skiplist() 
    : curLevel(0), elementCount(0), probability(0.5) {
    levelHeads.resize(curLevel);
}

template<typename TYPE, typename COMP_FUNCTOR>
Skiplist<TYPE, COMP_FUNCTOR>::Skiplist(const double _probability) 
    : curLevel(0), elementCount(0), probability(_probability) {
    levelHeads.resize(curLevel);
}

template<typename TYPE, typename COMP_FUNCTOR>
void Skiplist<TYPE, COMP_FUNCTOR>::insert(const TYPE& val) {
    size_t numPromotions = random_level();
    if(numPromotions < curLevel) {
        levelHeads.resize(numPromotions);
        curLevel = numPromotions;
    }
    addNode(val, numPromotions);
    ++elementCount;
}

template<typename TYPE, typename COMP_FUNCTOR>
void Skiplist<TYPE, COMP_FUNCTOR>::addNode(const TYPE& val, 
    const size_t numPromotions) {
    Node* below = addNodeLevel(val, levelHeads[0], nullptr);
    for(size_t level = 1; level < numPromotions; level++) {
        below = addNodeLevel(val)
    }
}

template<typename TYPE, typename COMP_FUNCTOR>
typename Skiplist<TYPE, COMP_FUNCTOR>::Node*
Skiplist<TYPE, COMP_FUNCTOR>::addNodeLevel(const TYPE& val,
    Head* h, Node* below) {
    Node* toAdd = new Node{val, below, nullptr};

    if(!h->first || COMP_FUNCTOR(val, h->first->value)) {
        toAdd->next = h->first;
        h->first = toAdd;
        return toAdd;
    }
    
    Node* next = h->first;
    while(next->next && COMP_FUNCTOR(next->value, val)) {
        next = next->next;
    }
    insertNode(next, toAdd);
    return toAdd;
}

template<typename TYPE, typename COMP_FUNCTOR>
void Skiplist<TYPE, COMP_FUNCTOR>::insertNode(Node* left, Node* toAdd) {
    toAdd->next = left->next;
    left->next = toAdd;
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