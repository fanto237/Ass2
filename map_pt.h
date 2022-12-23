#ifndef ASS1_MYMAP_H
#define ASS1_MYMAP_H


#include <utility>
#include <iterator>
#include <list>
#include <climits>

const unsigned LENGTH_PT = 3;

template<class D>
class map_pt {
    typedef unsigned K;
    typedef std::pair<const K, D> value_type;

private:
    static bool left(const K &key, unsigned bitPosition) {
        return (key & (1 << bitPosition)) == 0;
    }

    // Node class
    struct Node {
        Node(const Node &node) = delete;

        Node &operator=(const Node &node) = delete;

        Node(const K &key, const D &value, unsigned bitPos, Node *succ) : m_value(key, value), m_bitPos(bitPos) {
            bool isLeftOrRight = left(m_value.first, bitPos);
            m_pLeft = isLeftOrRight ? this : succ;
            m_pRight = isLeftOrRight ? succ : this;
        }

        Node(const K &key, const D &value, unsigned bitPos) : Node(key, value, bitPos, nullptr) {};

        ~Node() {
            if (m_pLeft && m_bitPos < m_pLeft->m_bitPos)
                delete m_pLeft;
            if (m_pRight && m_bitPos < m_pRight->m_bitPos)
                delete m_pRight;
        }

        value_type m_value;
        unsigned m_bitPos{};
        Node *m_pLeft = nullptr;
        Node *m_pRight = nullptr;
    };

    struct NodeHandler {

        explicit NodeHandler(Node *&root) : handlerRoot(root) {
            for (unsigned i = LENGTH_PT - 1; i > 0; --i) {
                m_Nodes[i] = nullptr;
            }
            m_Nodes[NODE] = root;
        }

        void down(bool direction) {
            for (unsigned i = LENGTH_PT - 1; i > 0; --i)
                m_Nodes[i] = m_Nodes[i - 1];
            m_Nodes[NODE] = direction ? node(DAD)->m_pLeft : node(DAD)->m_pRight;
        }

        void search(const K &key, int maxBitValue) {
            int lastBitPos = -1;
            while (!isNull() && lastBitPos < (int) node(NODE)->m_bitPos && maxBitValue > (int) node(NODE)->m_bitPos) {
                lastBitPos = node(NODE)->m_bitPos;
                down(left(key,lastBitPos)); // if the lastBitPos of the key is set to { 1 -> then go right direction  | 0 -> then go left direction }
            }
        }

        void search(const K &key) {
            search(key, INT_MAX);
        }

        void set(Node *nodeToSet, unsigned kind) {
            if (!node(kind + 1))
                handlerRoot = nodeToSet;
            else if (node(kind) != nullptr ?
                     node(kind + 1)->m_pLeft == node(kind) :
                     left(nodeToSet->m_value.first, node(kind + 1)->m_bitPos))
                node(kind + 1)->m_pLeft = nodeToSet;
            else
                node(kind + 1)->m_pRight = nodeToSet;
            m_Nodes[kind] = nodeToSet;
        }

        bool isNull() {
            return m_Nodes[NODE] == nullptr;
        }

        Node *node(unsigned kind) {
            return m_Nodes[kind];
        }

        NodeHandler &operator=(const NodeHandler &crArg) {
            if (this != &crArg) {
                handlerRoot = crArg.handlerRoot;
                for (unsigned i = 0; i < LENGTH_PT; ++i) {
                    m_Nodes[i] = crArg.m_Nodes[i];
                }
            }
            return *this;
        }

        Node *m_Nodes[LENGTH_PT];
        const unsigned NODE = 0;
        const unsigned DAD = 1;
        Node *&handlerRoot = nullptr;
    };

public:

    class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        // constructor
        explicit iterator(Node *start) : node(start) {}

        // operators
        typename iterator::value_type &operator*() {
            return node->m_value;
        }

        typename iterator::value_type *operator->() {
            return &(node->m_value);
        }

        friend bool operator==(const iterator &iter1, const iterator &iter2) {
            return iter1.node == iter2.node;
        }

        friend bool operator!=(const iterator &iter1, const iterator &iter2) {
            return iter1.node != iter2.node;
        }

    private:
        Node *node = nullptr;
    };

    iterator find(const K &key) {
        NodeHandler handler(m_pRoot);
        handler.search(key);
        if (!handler.isNull() && handler.node(handler.NODE)->m_value.first == key)
            return iterator(handler.node(handler.NODE));
        else
            return end();
    }


    std::pair<iterator, bool> insert(const value_type &value) {
        auto keyToAdd = value.first;
        NodeHandler h(m_pRoot);
        h.search(keyToAdd);
        unsigned index = 0;
        if (h.isNull()) {
            if (h.node(h.DAD))
                index = h.node(h.DAD)->m_bitPos + 1;
        } else if (h.node(h.NODE)->m_value.first != keyToAdd) {
            while (left(h.node(h.NODE)->m_value.first, index) == left(keyToAdd, index))
                ++index;
        } else
            return std::pair<iterator, bool>(end(), false);

        h = NodeHandler(m_pRoot);
        h.search(keyToAdd, index);
        Node *newNode = new Node(keyToAdd, value.second, index, h.node(h.NODE));
        h.set(newNode, h.NODE);
        return std::pair<iterator, bool>(newNode, true);
    }

private:
    Node *m_pRoot = nullptr;

public:
    iterator begin() { return iterator(m_pRoot); }

    iterator end() const { return iterator(nullptr); }

    map_pt() = default;

    map_pt(const map_pt<D> &crArg) = delete;

    map_pt &operator=(const map_pt<D> &crArg) = delete;

    ~map_pt() {
        delete m_pRoot;
    }
};


#endif //ASS1_MYMAP_H
