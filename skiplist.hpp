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
    // EFFECTS: Default construct Skiplist with probability = 0.5
    Skiplist();

    // EFFECTS: Construct Skiplist with chosen probability
    Skiplist(const double _probability);

    TYPE& front();

    TYPE& back();

    bool empty();

    const size_t size() const;

    void insert(const TYPE& num);

    void erase(const TYPE& num);

    const uint32_t getNumLevels() const;

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

    vector<Head> levelHeads;    // Vector of head pointers to levels
    size_t curLevel;            // Current highest level
    size_t elementCount;        // Number of elements inserted into Skiplist
    double probability;         // Probability of an element being promoted

    /* Random Number Generation */

    // EFFECTS: Returns a reference to a shared Mersenne Twister RNG
    static std::mt19937& get_gen();

    // EFFECTS: Returns true if the element should be promoted to next level
    bool should_promote();

    // EFFECTS: Returns the level that an element should be promoted
    const size_t random_level();
};

#endif // SKIPLIST_HPP