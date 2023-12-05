#pragma once
#include <iostream>

template<typename T>
class List {
protected:
    class Node {
    public:
        Node *next;
        T data;
        Node(T value = T(), Node* _next = nullptr) : data(value), next(_next) {};
    };

    size_t size;

    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual std::istream& scan(std::istream& is) = 0;
public:
    List() {};

    virtual ~List() {};
    virtual T getFront() const = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t getSize() const = 0;
    virtual T pop() = 0;
    virtual void push(const T data) = 0;

    virtual List& operator = (const List&) = 0;

    friend std::ostream& operator<<(std::ostream& os, const List& list) {
        list.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, List<T>& list) {
        list.scan(is);
        return is;
    }

    class const_iterator;

    class iterator {
      public:
        iterator(Node *p_ = nullptr): p(p_) {};
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Node;
        using pointer = Node*;
        using reference = Node&;

        reference operator * () const {return *p;}
        pointer operator -> () const {return p;}

        iterator &operator ++ () {p = p->next; return *this;}
        iterator operator ++ (T) {iterator i = *this; p = p->next; return i;}

        bool operator == (const iterator &i) const {return p == i.p;}
        bool operator != (const iterator &i) const {return p != i.p;}

        bool operator == (const const_iterator &i) const;
        bool operator != (const const_iterator &i) const;

        iterator operator + (size_t a) {
            iterator tmp = *this;
            for (int i = 0; i < a; ++i) {
                tmp++;
            }
            return tmp;
        };

        friend const_iterator;
      private:
        List<T>::Node *p;
    };

    class const_iterator {
      public:
        const_iterator(Node *p_ = nullptr): p(p_) {};
        const_iterator(const iterator &i): p(i.p) {};
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const Node;
        using pointer = const Node*;
        using reference = const Node&;

        reference operator * () const {return *p;}
        pointer operator -> () const {return p;}

        const_iterator &operator ++ () {p = p->next; return *this;}
        const_iterator operator ++ (T) {const_iterator i = *this; p = p->next; return i;}

        bool operator == (const const_iterator &i) const {return p == i.p;}
        bool operator != (const const_iterator &i) const {return p != i.p;}

        bool operator == (const iterator &i) const;
        bool operator != (const iterator &i) const;

        const_iterator operator + (size_t a) {
            const_iterator tmp = *this;
            for (int i = 0; i < a; ++i) {
                tmp++;
            }
            return tmp;
        };

        friend iterator;
      private:
        const List<T>::Node *p;
    };

};
