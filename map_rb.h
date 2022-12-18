//
// Created by Study on 11/12/2022.
//

#ifndef ASS2_MAP_RB_H
#define ASS2_MAP_RB_H


#include <utility>
#include <iterator>
#include <list>

const unsigned LENGTH = 4;
unsigned COUNTER = 0;

template<class K, class D>
class map_rb {
public:
    typedef std::pair<const K, D> value_type;

    map_rb() = default;

    ~map_rb() {
        delete m_pRoot;
    }

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

        friend std::ostream &operator<<(std::ostream &os, const Node &crArg) {

            if (crArg.m_pLeft) {
                COUNTER = 0;
                os << *crArg.m_pLeft;

            }
            for (unsigned i = 0; i < COUNTER; ++i)
                std::cout << '\t';
            os << "( key : " << crArg.m_value.first << " | value: " << crArg.m_value.second << " | color: "
               << crArg.m_isRed << ")" << std::endl;
            ++COUNTER;

            if (crArg.m_pRight) {
                COUNTER = 0;
                os << *crArg.m_pRight;
            }

            return os;
        }

        value_type m_value;
        Node *m_pLeft = nullptr;
        Node *m_pRight = nullptr;
        bool m_isRed = true;
    };

    struct NodeHandler {

        explicit NodeHandler(Node *&root) : handlerRoot(root) {
            for (unsigned i = LENGTH - 1; i > 0; --i) {
                m_Nodes[i] = nullptr;
            }
            m_Nodes[NODE] = root;
        }

        void down(bool direction) {
            for (unsigned i = LENGTH - 1; i > 0; --i)
                m_Nodes[i] = m_Nodes[i - 1]; // GG_DAD = GAD | GAD = DAD | DAD = NODE
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
                if ((node(GDAD)->m_value.first < dad->m_value.first) != (dad->m_value.first < node(NODE)->m_value.first))
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

    class const_iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        std::list<Node *> m_Nodes2Visit;

//         copy constructor
        const_iterator(const const_iterator &crArg) {
            if (&crArg != this)
                for (auto node: crArg.m_Nodes2Visit)
                    m_Nodes2Visit.push_back(node);
        }

        const_iterator &operator=(const const_iterator &crArg) {
            if (&crArg != this)
                for (auto node: crArg.m_Nodes2Visit)
                    m_Nodes2Visit.push_back(node);
        }

        // constructor
        explicit const_iterator(Node *start) {
            goDown(start);
        }


        const_iterator &operator++() {
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node->m_pRight);
            return *this;
        }

        const_iterator operator++(int) {
            iterator tmp(*this);
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node->m_pRight);
            return tmp;
        }

        //value_type& operator*(){
        typename const_iterator::value_type &operator*() const {
            return m_Nodes2Visit.back()->m_value;
        }

        typename const_iterator::value_type *operator->() const {
            return &m_Nodes2Visit.back()->m_value;
        }

        friend bool operator==(const const_iterator &iter1, const const_iterator &iter2) {
            return iter1.m_Nodes2Visit == iter2.m_Nodes2Visit;
        }

        friend bool operator!=(const const_iterator &iter1, const const_iterator &iter2) {
            return iter1.m_Nodes2Visit != iter2.m_Nodes2Visit;
        }

    private:
        void goDown(Node *goFrom) {
            for (; goFrom; goFrom = goFrom->m_pLeft)
                m_Nodes2Visit.push_back(goFrom);
        }

    };

    class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        std::list<Node *> m_Nodes2Visit;

//         copy constructor
        iterator(const iterator &crArg) {
            if (&crArg != this)
                for (auto node: crArg.m_Nodes2Visit)
                    m_Nodes2Visit.push_back(node);
        }

        iterator &operator=(const iterator &crArg) {
            if (&crArg != this)
                for (auto node: crArg.m_Nodes2Visit)
                    m_Nodes2Visit.push_back(node);
        }

        // constructor
        explicit iterator(Node *start) {
            goDown(start);
        }

        // Operators
        explicit operator const_iterator() {
            return const_iterator(m_Nodes2Visit.front());
        }

        iterator &operator++() {
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node->m_pRight);
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node->m_pRight);
            return tmp;
        }

        typename iterator::value_type &operator*() {
            return m_Nodes2Visit.back()->m_value;
        }

        typename iterator::value_type *operator->() {
            return &m_Nodes2Visit.back()->m_value;
        }

        friend bool operator==(const iterator &iter1, const iterator &iter2) {
            return iter1.m_Nodes2Visit == iter2.m_Nodes2Visit;
        }

        friend bool operator!=(const iterator &iter1, const iterator &iter2) {
            return iter1.m_Nodes2Visit != iter2.m_Nodes2Visit;
        }

    private:
        void goDown(Node *goFrom) {
            for (; goFrom; goFrom = goFrom->m_pLeft)
                m_Nodes2Visit.push_back(goFrom);
        }
    };

    map_rb(const map_rb<K, D> &crArg) = delete;

    map_rb &operator=(const map_rb<K, D> &crArg) = delete;


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

    const_iterator find(const K &key) const {
        Node *pTmp = m_pRoot;
        while (pTmp != nullptr) {
            if (key < pTmp->m_value.first)
                pTmp = pTmp->m_pLeft;
            else if (pTmp->m_value.first < key)
                pTmp = pTmp->m_pRight;
            else
                // has been found
                return const_iterator(pTmp);
        }
        return cend();
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
                h.down(false); // todo go right when key to add is bigger
            else if (keyToAdd < key)
                h.down(true); // todo go left when current key is bigger
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
//    NodeHandler *handler = nullptr;
public:

    iterator begin() { return iterator(m_pRoot); }

    iterator end() { return iterator(nullptr); }

    const_iterator cbegin() const { return const_iterator(m_pRoot); }

    const_iterator cend() const { return const_iterator(nullptr); }

    friend std::ostream &operator<<(std::ostream &os, const map_rb &crArg) {
        if (crArg.m_pRoot)
            os << *crArg.m_pRoot;
        return os;
    }
};


#endif //ASS2_MAP_RB_H
