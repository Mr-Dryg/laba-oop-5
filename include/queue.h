#include "../include/my_memory_resource.h"
#include <memory>
#include <memory_resource>

template <class T>
    requires std::is_default_constructible_v<T>
class Queue {
private:
    struct Node;

    struct Deleter {
        void operator()(Node* ptr) const {}
    };

    using NodeUniquePtr = std::unique_ptr<Node, Deleter>;

    struct Node {
        T data;
        NodeUniquePtr next;
    };

    NodeUniquePtr first = nullptr;
    Node* last = nullptr;
    std::size_t queue_size = 0;

    std::pmr::polymorphic_allocator<Node> allocator;

public:
    Queue(std::pmr::memory_resource* resource = std::pmr::get_default_resource()) 
    : allocator(resource) {};
    
    void push_back(const T& element) {
        Node* raw_pointer = allocator.allocate(1);
        allocator.construct(raw_pointer, Node{element, nullptr});
        NodeUniquePtr node(raw_pointer, Deleter{});

        if (last == nullptr) {
            last = node.get();
        }
        else {
            last->next = std::move(node);
            last = last->next.get();
        }
        
        if (first == nullptr) {
            first = std::move(node);
        }
        queue_size++;
    }

    T pop_front() {
        if (first == nullptr) {
            throw std::logic_error("Queue is empty");
        }
        T element = first->data;
        Node* node = first.get();
        first = std::move(node->next);
        if (first == nullptr) {
            last = nullptr;
        }
        std::allocator_traits<decltype(allocator)>::destroy(allocator, node);
        allocator.deallocate(node, 1);
        queue_size--;
        return element;
    }

    std::size_t size() const {
        return queue_size;
    }

    ~Queue() {
        while (queue_size > 0) {
            pop_front();
        }
    }
};