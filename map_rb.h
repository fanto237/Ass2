#ifndef ASS2_MAP_RB_H
#define ASS2_MAP_RB_H


#include <utility>
#include <iterator>
#include <list>

const unsigned LENGTH = 4;

template<class K, class D>
class map_rb {

    typedef std::pair<const K, D> value_type;

private:
    // Node class
    struct Node {
        Node(const Node &node) = delete;

        Node &operator=(const Node &node) = delete;

        Node(const K &key, const D &value) : m_value(key, value) {}

        ~Node() {
            delete m_pLeft;
            delete m_pRight;
        }

        bool is4Node() {
            return (m_pLeft && m_pLeft->m_isRed) && (m_pRight && m_pRight->m_isRed);
        }

        void convert4Node() {
            m_pLeft->m_isRed = false;
            m_pRight->m_isRed = false;
            m_isRed = true;
        }

        value_type m_value;
        Node *m_pLeft = nullptr;
        Node *m_pRight = nullptr;
        bool m_isRed = true;
    };
    // Nodehandler
    struct NodeHandler {

        explicit NodeHandler(Node *&root) : handlerRoot(root) {
            for (unsigned i = LENGTH - 1; i > 0; --i) {
                m_Nodes[i] = nullptr;
            }
            m_Nodes[NODE] = root;
        }

        void down(bool direction) {
            for (unsigned i = LENGTH - 1; i > 0; --i)
                m_Nodes[i] = m_Nodes[i - 1];
            m_Nodes[NODE] = direction ? node(NODE)->m_pLeft : node(NODE)->m_pRight;
        }

        void set(Node *nodeToSet, unsigned kind) {
            if (!node(kind + 1))
                handlerRoot = nodeToSet;
            else if (nodeToSet->m_value.first < node(kind + 1)->m_value.first)
                node(kind + 1)->m_pLeft = nodeToSet;
            else
                node(kind + 1)->m_pRight = nodeToSet;
            m_Nodes[kind] = nodeToSet;
        }

        void rotate(unsigned kind) {
            Node *dad = node(kind);
            Node *son = node(kind - 1);
            bool sonColor = son->m_isRed;
            son->m_isRed = dad->m_isRed;
            dad->m_isRed = sonColor;
            if (dad->m_pLeft == son) {
                dad->m_pLeft = son->m_pRight;
                son->m_pRight = dad;
            } else {
                dad->m_pRight = son->m_pLeft;
                son->m_pLeft = dad;
            }
            set(son, kind);
        }

        void split() {
            Node *dad = node(DAD);
            if (dad && dad->m_isRed) {
                if ((node(GDAD)->m_value.first < dad->m_value.first) !=
                    (dad->m_value.first < node(NODE)->m_value.first))
                    rotate(DAD);
                rotate(GDAD);
            }
        }

        bool isNull() {
            return m_Nodes[NODE] == nullptr;
        }

        Node *node(unsigned kind) {
            return m_Nodes[kind];
        }

        Node *m_Nodes[LENGTH];
        const unsigned NODE = 0;
        const unsigned DAD = 1;
        const unsigned GDAD = 2;
        const unsigned GGDAD = 3;
        Node *&handlerRoot = nullptr;
    };

public:
    // Iterator class
    class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        // constructor
        explicit iterator(Node *start) : node(start) {}

//        ~iterator{
//            delete node;
//        };

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
        Node *pTmp = m_pRoot;
        while (pTmp != nullptr) {
            if (key < pTmp->m_value.first)
                pTmp = pTmp->m_pLeft;
            else if (pTmp->m_value.first < key)
                pTmp = pTmp->m_pRight;
            else
                // has been found
                return iterator(pTmp);
        }
        return end();
    }

    std::pair<iterator, bool> insert(const value_type &value) {
        NodeHandler h(m_pRoot);
        auto keyToAdd = value.first;
        while (!h.isNull()) {
            if (h.node(h.NODE)->is4Node()) {
                h.node(h.NODE)->convert4Node();
                h.split();
            }
            auto key = h.node(h.NODE)->m_value.first;
            if (key < keyToAdd)
                h.down(false);
            else if (keyToAdd < key)
                h.down(true);
            else
                return std::pair<iterator, bool>(end(), false);
        }
        auto newNode = new Node(value.first, value.second);
        h.set(newNode, h.NODE);
        h.split();
        m_pRoot->m_isRed = false;
        return std::pair<iterator, bool>(newNode, true);
    }


private:
    Node *m_pRoot = nullptr;

public:
    iterator begin() { return iterator(m_pRoot); }

    iterator end() { return iterator(nullptr); }

    map_rb() = default;

    map_rb(const map_rb<K, D> &crArg) = delete;

    map_rb &operator=(const map_rb<K, D> &crArg) = delete;

    ~map_rb(){
        delete m_pRoot;
    }

};


#endif //ASS2_MAP_RB_H
