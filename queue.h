#include <iostream>
#include "abstract.h"

template <typename T>
class Queue: public List<T> {
  public:
    Queue(): head(nullptr), tail(nullptr) {
        List<T>::size = 0;
    };

    ~Queue() {
        while (!isEmpty()) pop();
    }

    Queue(const Queue& other) {
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
        this->tail = ncur;
    }

    Queue(Queue &&other) {
        this->head = other.head;
        this->tail = other.tail;
        other.head = nullptr;
        List<T>::size = other.size;
    }

    bool isEmpty() const override {
        return !head;
    }

    void push(const T data) override {
        if (isEmpty()) {
            head = new typename List<T>::Node(data);
            tail = this->head;
        } else {
            typename List<T>::Node *cur = this->tail;
            cur->next = new typename List<T>::Node(data);
            tail = cur->next;
        }
        List<T>::size++;
    }

    T pop() override {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        } else {
            typename List<T>::Node *cur = this->head;
            T elem;
            elem = head->data;
            head = cur->next;
            delete cur;
            List<T>::size--;
            return elem;
        }
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

    std::ostream &print(std::ostream &stream) const override {
        typename List<T>::Node *cur = head;
        while (cur->next) {
            std::cout << cur->data << "->";
            cur = cur->next;
        }
        std::cout << cur->data;

        return stream;
    }

    std::istream &scan(std::istream &stream) override {
        T elem;
        std::cin >> elem;
        push(elem);
        return stream;
    }

    Queue &operator = (const Queue &other) {
        clear();
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
        this->tail = ncur;

        return *this;
    }
    
    Queue &operator = (const List<T> &l) override {
        if (&l == this) {
            return *this;
        }
        const Queue &q = dynamic_cast<const Queue&> (l);
        *this = q;
        return *this;
    }
  private:
    typename List<T>::Node *tail;
    typename List<T>::Node *head;
};
