#pragma once
#include <iostream>

template<typename T>
class List {
protected:
    class Node {
    public:
        Node *next;
        T data;
        Node(T value = T(), Node* _next = nullptr) : next(_next), data(value) {}
    };

    size_t size;

public:
    List() {}

    virtual ~List() {}
    virtual T getFront() const = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t getSize() const = 0;
    virtual T pop() = 0;
    virtual void push(const T data) = 0;
    virtual List& operator = (const List&) = 0;

    friend std::ostream& operator<<(std::ostream& os, const List& list) {
        auto cur = list.begin();
        while (cur + 1 != list.end()) {
            std::cout << cur->data << "<-";
            cur++;
        }
        std::cout << cur->data;

        return os;
    }

    friend std::istream& operator>>(std::istream& is, List<T>& list) {
        auto cur = list.begin();
        while (cur != list.end()) {
            std::cin << cur->data;
            cur++;
        }
        return is;
    }

    class const_iterator;

    class iterator {
      public:
        iterator(Node *p_): p(p_) {};

        T& operator * () const {return p->data;}
        Node* operator -> () const {return p;}

        iterator &operator ++ () {p = p->next; return *this;}
        iterator operator ++ (T) {iterator i = *this; p = p->next; return i;}

        bool operator == (const iterator &i) const {return p == i.p;}
        bool operator != (const iterator &i) const {return p != i.p;}

        bool operator == (const const_iterator &i) const {return p == i.p;}
        bool operator != (const const_iterator &i) const {return p != i.p;}

        iterator operator + (size_t a) {
            iterator tmp = *this;
            for (size_t i = 0; i < a; ++i) {
                tmp++;
            }
            return tmp;
        }

        friend const_iterator;
      private:
        List<T>::Node *p;
    };

    class const_iterator {
      public:
        const_iterator(Node *p_): p(p_) {};
        const_iterator(const iterator &i): p(i.p) {};

        const T& operator * () const {return p->data;}
        const Node* operator -> () const {return p;}

        const_iterator &operator ++ () {p = p->next; return *this;}
        const_iterator operator ++ (T) {const_iterator i = *this; p = p->next; return i;}

        bool operator == (const const_iterator &i) const {return p == i.p;}
        bool operator != (const const_iterator &i) const {return p != i.p;}

        bool operator == (const iterator &i) const {return p == i.p;}
        bool operator != (const iterator &i) const {return p != i.p;};

        const_iterator operator + (size_t a) {
            const_iterator tmp = *this;
            for (size_t i = 0; i < a; ++i) {
                tmp++;
            }
            return tmp;
        };

        friend iterator;
      private:
        const List<T>::Node *p;
    };

    virtual iterator begin() = 0;
    virtual iterator end() = 0;

    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;

    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;

};
