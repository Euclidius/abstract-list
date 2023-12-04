#pragma once

#include "abstract.h"

template <typename T>
class Stack: public List<T> {
  public:
    Stack(): head(nullptr) {
       List<T>::size = 0;
    }
    
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
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
        typename List<T>::Node *cur = head;
        while (cur->next) {
            std::cout << cur->data << "->";
            cur = cur->next;
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
        const Stack& s = dynamic_cast<const Stack&> (s);
        *this = s;
        return *this;
    }

  private:
    typename List<T>::Node* head;   
};
