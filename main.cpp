#include "include/queue.h"
#include <iostream>
#include <string>

int main(void) {
    MyMemoryResource my_memory_resource;
    Queue<int> queue1(&my_memory_resource);

    for (int i = 1; i < 6; i++) {
        queue1.push_back(i);
        std::cout << "push: " << i << '\n';
    }

    while (queue1.size() > 0) {
        std::cout << "pop: " << queue1.pop_front() << '\n';
    }

    using Watch = struct {
        std::string name;
        int price;
    };

    Watch watches[] = {
        Watch{"Casio", 10999},
        Watch{"Orient", 17999},
        Watch{"Seiko", 25999},
        Watch{"Citizen", 32999},
        Watch{"Tissot", 45999},
        Watch{"Omega", 125999}
    };

    Queue<Watch> queue2(&my_memory_resource);

    for (const auto& watch : watches) {
        queue2.push_back(watch);
        std::cout << "push: " << watch.name << ", " << watch.price << '\n';
    }

    while (queue2.size() > 0) {
        Watch watch = queue2.pop_front();
        std::cout << "pop: " << watch.name << ", " << watch.price << '\n';
    }

    return 0;
}