#include "include/queue.h"
#include <iostream>

int main(void) {
    MyMemoryResource my_memory_resource;
    Queue<int> queue1(&my_memory_resource);

    for (int i = 1; i < 6; i++) {
        queue1.push_back(i);
        std::cout << "push: " << i << ", size: " << queue1.size() << '\n';
    }

    while (queue1.size() > 0) {
        std::cout << "size: " << queue1.size() << " pop: " << queue1.pop_front() << '\n';
    }

    for (int i = 10; i < 14; i++) {
        queue1.push_back(i);
        std::cout << "push: " << i << ", size: " << queue1.size() << '\n';
    }

    while (queue1.size() > 0) {
        std::cout << "size: " << queue1.size() << " pop: " << queue1.pop_front() << '\n';
    }

    return 0;
}