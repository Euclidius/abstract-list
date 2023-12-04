#pragma once
#include <iostream>

template<typename T>
class List {
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


protected:
    struct Node {
        public:
            Node *next;
            T data;
        Node(T value = T(), Node* _next = nullptr) : data(value), next(_next) {};
    };

    size_t size;

    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual std::istream& scan(std::istream& is) = 0;
};
