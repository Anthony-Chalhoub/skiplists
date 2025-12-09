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

    // MODIFIES: levelHeads, nodes in skiplist, curLevel, elementCount
    // EFFECTS: Insert val into skiplist up to level numPromotions
    void insert(const TYPE& val);

    void erase(const TYPE& val);

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
        Node* first;

        Head() : first(nullptr) {}
    };

    vector<Head> levelHeads;    // Vector of head pointers to levels
    size_t curLevel;            // Current highest level
    size_t elementCount;        // Number of elements inserted into Skiplist
    double probability;         // Probability of an element being promoted

    // MODIFIES: levelHeads, nodes in skiplist
    // EFFECTS: Insert val into skiplist up to level numPromotions
    void addNode(const TYPE& val, const size_t numPromotions);

    // MODIFIES: levelHeads, nodes in skiplist
    // EFFECTS: Insert val into level pointed to by h and pointing to below
    Node* addNodeLevel(const TYPE& val, Head* h, Node* below);

    // MODIFIES: levelHeads, nodes in skiplist
    // EFFECTS: Insert Node toAdd after Node left
    void insertNode(Node* left, Node* toAdd);

    /* Random Number Generation */

    // EFFECTS: Returns a reference to a shared Mersenne Twister RNG
    static std::mt19937& get_gen();

    // EFFECTS: Returns true if the element should be promoted to next level
    bool should_promote();

    // EFFECTS: Returns the level that an element should be promoted
    const size_t random_level();
};

#endif // SKIPLIST_HPP