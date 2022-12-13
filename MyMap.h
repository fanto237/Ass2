#ifndef ASS1_MYMAP_H
#define ASS1_MYMAP_H


#include <utility>
#include <iterator>
#include <list>

template<class K, class D>
class MyMap {
public:
    typedef std::pair<const K, D> value_type;


private:
    // Node class
    class Node {
    public:
        Node(const K &key, const D &value) : m_value(key, value) {}

    private:
        value_type m_value;
        Node *m_pLeft = nullptr;
        Node *m_pRight = nullptr;
    };

public:
    // normal constante iterator
    class const_iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        // copy constructor
        const_iterator(const const_iterator &crArg) {
            if (&crArg != this)
                for (auto node: m_Nodes2Visit)
                    crArg.m_Nodes2Visit.push_back(node);
        }

        // constructor
        explicit const_iterator(Node *start) {
            goDown(start);
        }

        // Operators
        const_iterator &operator++() {
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node);
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node);
            return tmp;
        }

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

        std::list<Node *> m_Nodes2Visit;
    };

    // normal iterator
    class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        // copy constructor
        iterator(const iterator &crArg) {
            if (&crArg != this)
                for (auto node: m_Nodes2Visit)
                    crArg.m_Nodes2Visit.push_back(node);
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
            goDown(node);
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node);
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

        std::list<Node *> m_Nodes2Visit;
    };

    // reverse const iterator
    class const_reverse_iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        // copy constructor
        const_reverse_iterator(const const_reverse_iterator &crArg) {
            if (&crArg != this)
                for (auto node: m_Nodes2Visit)
                    crArg.m_Nodes2Visit.push_back(node);
        }

        // constructor
        explicit const_reverse_iterator(Node *start) {
            goDown(start);
        }

        // Operators
        const_reverse_iterator &operator++() {
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node);
            return *this;
        }

        const_reverse_iterator operator++(int) {
            const_reverse_iterator tmp(*this);
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node);
            return tmp;
        }

        //value_type& operator*(){
        typename const_reverse_iterator::value_type &operator*() {
            return m_Nodes2Visit.back()->m_value;
        }

        typename const_reverse_iterator::value_type *operator->() {
            return &m_Nodes2Visit.back()->m_value;
        }

        friend bool operator==(const const_reverse_iterator &iter1, const const_reverse_iterator &iter2) {
            return iter1.m_Nodes2Visit == iter2.m_Nodes2Visit;
        }

        friend bool operator!=(const const_reverse_iterator &iter1, const const_reverse_iterator &iter2) {
            return iter1.m_Nodes2Visit != iter2.m_Nodes2Visit;
        }

    private:
        void goDown(Node *goFrom) {
            for (; goFrom; goFrom = goFrom->m_pRight)
                m_Nodes2Visit.push_back(goFrom);
        }

        std::list<Node *> m_Nodes2Visit;
    };

    // reverse iterator
    class reverse_iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        // copy constructor
        reverse_iterator(const reverse_iterator &crArg) {
            if (&crArg != this)
                for (auto node: m_Nodes2Visit)
                    crArg.m_Nodes2Visit.push_back(node);
        }

        // constructor
        explicit reverse_iterator(Node *start) {
            goDown(start);
        }

        // Operators
        explicit operator const_reverse_iterator() {
            return const_reverse_iterator(m_Nodes2Visit.front());
        }

        reverse_iterator &operator++() {
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node);
            return *this;
        }

        const reverse_iterator operator++(int) {
            reverse_iterator tmp(*this);
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node);
            return tmp;
        }

        //value_type& operator*(){
        typename reverse_iterator::value_type &operator*() {
            return m_Nodes2Visit.back()->m_value;
        }

        typename reverse_iterator::value_type *operator->() {
            return &m_Nodes2Visit.back()->m_value;
        }

        friend bool operator==(const reverse_iterator &iter1, const reverse_iterator &iter2) {
            return iter1.m_Nodes2Visit == iter2.m_Nodes2Visit;
        }

        friend bool operator!=(const reverse_iterator &iter1, const reverse_iterator &iter2) {
            return iter1.m_Nodes2Visit != iter2.m_Nodes2Visit;
        }

    private:
        void goDown(Node *goFrom) {
            for (; goFrom; goFrom = goFrom->m_pRight)
                m_Nodes2Visit.push_back(goFrom);
        }

        std::list<Node *> m_Nodes2Visit;
    };

public:
    iterator end() { return iterator(); }
};


#endif //ASS1_MYMAP_H
