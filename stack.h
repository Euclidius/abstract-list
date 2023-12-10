#pragma once

#include "abstract.h"

template <typename T>
class Stack: public List<T> {
  public:
    Stack(): head(nullptr) {
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

        while (cur->next) {
            cur = cur->next;
            ncur->next = new typename List<T>::Node(cur->data);
            ncur = ncur->next;
        }

        ncur->next = nullptr;
    }

    Stack(Stack &&other) {
        this->head = other.head;
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

    std::ostream& print(std::ostream& os) const override {
        auto cur = begin();
        while (cur + 1 != end()) {
            std::cout << cur->data << "<-";
            cur++;
        }
        std::cout << cur->data;
        return os;
    }


    std::istream& scan(std::istream& is) override {
        T elem;
        std::cin >> elem;
        push(elem);
        return is;
    }

    Stack &operator = (const Stack &other) {
        clear();
        typename List<T>::Node *cur = other.head;
        this->head = new typename List<T>::Node(cur->data);
        typename List<T>::Node* ncur = this->head;
        List<T>::size = other.size;

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

    iterator begin() override {return iterator(head);} ;
    iterator end() override {
        typename List<T>::Node *tmp = head;
        for (size_t i = 0; i < List<T>::size - 1; ++i) {
            tmp = tmp->next;
        }
        return iterator(tmp->next);
    }

    typedef typename List<T>::const_iterator const_iterator;

    const_iterator cbegin() const override {return const_iterator(head);};
    const_iterator cend() const override {
        const typename List<T>::Node *tmp = head;
        for (size_t i = 0 ; i < List<T>::size - 1; ++i) {
            tmp = tmp->next;
        }
        return const_iterator(tmp->next);
    }


    const_iterator begin() const override {
        return const_iterator(head);
    };


    const_iterator end() const override {
        const typename List<T>::Node *tmp = head;
        for (size_t i = 0 ; i < List<T>::size - 1; ++i) {
            tmp = tmp->next;
        }
        return const_iterator(tmp->next);
    };

  private:
    typename List<T>::Node* head;   
};

