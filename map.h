#ifndef ASS1_MYMAP_H
#define ASS1_MYMAP_H


#include <utility>
#include <iterator>
#include <list>

template<class K, class D>
class map_rb {
public:
    typedef std::pair<const K, D> value_type;


private:
    // Node class
    struct Node {
        Node(const K &key, const D &value) : m_value(key, value) {}

        ~Node() {
            delete m_pLeft;
            delete m_pRight;
        }
        value_type m_value;
        Node *m_pLeft = nullptr;
        Node *m_pRight = nullptr;
    };

public:

    class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        std::list<Node *> m_Nodes2Visit;

//         copy constructor
        iterator(const iterator &crArg) {
            if (&crArg != this)
                for (auto node: crArg.m_Nodes2Visit)
                    m_Nodes2Visit.push_back(node);
        }

        iterator& operator=(const iterator &crArg) {
            if (&crArg != this)
                for (auto node: crArg.m_Nodes2Visit)
                    m_Nodes2Visit.push_back(node);
        }

        // constructor
        explicit iterator(Node *start) {
            goDown(start);
        }

        // Operators
//        explicit operator const_iterator() {  // TODO: take out the comment from the convert operator
//            return const_iterator(m_Nodes2Visit.front());
//        }

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

        //value_type& operator*(){
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

    map_rb()= default;

    ~map_rb()
    {
        delete m_pRoot;
    }

    map_rb(const map_rb<K, D> &crArg)  // TODO: deleting copy constructor if not used
    {
        if (crArg.m_pRoot)
            m_pRoot = new Node(*crArg.m_pRoot);
    }

    map_rb &operator=(const map_rb<K, D> &crArg)  // TODO: deleting assign operator if not used
    {
        if (&crArg != this)
        {
            delete m_pRoot;
            m_pRoot = nullptr;
            if (crArg.m_pRoot)
                m_pRoot = new Node(*crArg.m_pRoot);
        }
        return *this;
    }


    iterator find(const K& key) const
    {
        Node *pTmp = m_pRoot;
        while (pTmp != nullptr)
        {
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



    std::pair<iterator, bool> insert(const value_type& value)
    {
        return insertRec(m_pRoot, value.first, value.second);
    }

    friend std::ostream &operator<<(std::ostream &os, const map_rb<K, D> &crArg)
    {
        if (crArg.m_pRoot)
            os << *crArg.m_pRoot;
        return os;
    }

private:
    std::pair<iterator, bool> insertRec(Node *&pTmp, const K &pKey, const D &pData)
    {
        if (!pTmp) {
            pTmp = new Node(pKey, pData);
            return std::pair<iterator, bool>(iterator(pTmp), true);
        }
        else
        {
            if (pKey < pTmp->m_value.first)
                return insertRec(pTmp->m_pLeft, pKey, pData);
            else if (pTmp->m_value.first < pKey)
                return insertRec(pTmp->m_pRight, pKey, pData);
        }
    }

    Node *m_pRoot = nullptr;
public:
    iterator begin() { return iterator(m_pRoot); }
    iterator end() const { return iterator(nullptr); }
//    const_iterator  cbegin() const { return const_iterator(m_prRoot); } // todo uncomment this part later
//    const_iterator cend() const { return const_iterator(nullptr); } // todo uncomment this part later
};


#endif //ASS1_MYMAP_H
