#include <iostream>
#include "stack.h"
int main() {
    Stack<int> s;
    for (int i = 0; i < 10; ++i) {
        s.push(i);
    }

    /* for (auto i = q.begin(); i != q.end(); ++i) { */
    /*     std::cout << i->data << ' '; */
    /* } */
    std::cout << s;
}
