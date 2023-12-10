#pragma once

#include "abstract.h"

template <typename T>
class Stack: public List<T> {
  public:
    Stack(): head(nullptr), base(nullptr){
       List<T>::size = 0;
    }
    
    ~Stack() {
        while (!isEmpty()) pop();
    }

    Stack(const Stack &other) {
        typename List<T>::Node *cur = other.head;
        this->head = new typename List<T>::Node(cur->data);
        typename List<T>::Node *ncur = this->head;
        List<T>::size = other.size;
        base = other.base;

        while (cur->next) {
            cur = cur->next;
            ncur->next = new typename List<T>::Node(cur->data);
            ncur = ncur->next;
        }

        ncur->next = nullptr;
    }

    Stack(Stack &&other) {
        this->head = other.head;
        this->base = other.base;
        other.head = nullptr;
        List<T>::size = other.size;
    }

    T pop() override {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        typename List<T>::Node* cur = this->head;
        T elem;
        elem = head->data;
        head = cur->next;
        delete cur;
        List<T>::size--;
        return elem;
    }

    bool isEmpty() const override{
        return !head; 
    }

    void push(const T data) override {
        if (isEmpty()) {
            head = new typename List<T>::Node(data);
            base = head;
        } else {
            head = new typename List<T>::Node(data, head);
        }
        List<T>::size++;
    }
    
    T getFront() const override {
        return head->data;
    }

    size_t getSize() const override {
        return List<T>::size;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    Stack &operator = (const Stack &other) {
        clear();
        typename List<T>::Node *cur = other.head;
        this->head = new typename List<T>::Node(cur->data);
        typename List<T>::Node* ncur = this->head;
        List<T>::size = other.size;
        this->base = other.base;

        while (cur->next) {
            cur = cur->next;
            ncur->next = new typename List<T>::Node(cur->data);
            ncur = ncur->next;
        }
        ncur->next = nullptr;
        return *this;
    }

    Stack &operator = (Stack &&other)  {
        clear();
        List<T>::size = other.size;
        this->head = other.head;
        this->base = other.base;
        other.head = nullptr;
        return *this;
    }

    Stack &operator = (const List<T>& l) override {
        if (&l == this) {
            return *this;
        }
        const Stack& s = dynamic_cast<const Stack&> (l);
        *this = s;
        return *this;
    }

    typedef typename List<T>::iterator iterator;
    typedef typename List<T>::const_iterator const_iterator;

    iterator begin() override {return iterator(head);} ;
    iterator end() override {return iterator(base->next);}

    const_iterator cbegin() const override {return const_iterator(head);};
    const_iterator cend() const override {return const_iterator(base->next);}

    const_iterator begin() const override {return const_iterator(head);};
    const_iterator end() const override {return const_iterator(base->next);};

  private:
    typename List<T>::Node* head;   
    typename List<T>::Node* base;
};

