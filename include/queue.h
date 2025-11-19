#include <memory>
#include <stdexcept>

template <class T, class allocator_type>
    requires std::is_default_constructible_v<T> && 
             std::is_same_v<allocator_type, std::pmr::polymorphic_allocator<T>>
class Queue {
private:
    struct PolymorphicDeleter {
        void operator()(T* ptr) const {}
    };

    struct Node;

    using NodeUniquePtr = std::unique_ptr<Node, PolymorphicDeleter>;

    struct Node {
        T data;
        NodeUniquePtr next;
    };

    NodeUniquePtr first = nullptr;
    NodeUniquePtr last = nullptr;
    std::size_t queue_size = 0;

    allocator_type polymorphic_allocator;

public:
    Queue(allocator_type alloc = {}) : polymorphic_allocator(alloc) {}
    
    void push_back(const T& element) {
        NodeUniquePtr node = NodeUniquePtr(polymorphic_allocator.allocate(sizeof(Node)));
        node.get().data = element;
        node.get().next = nullptr;
        last.get().next = node;
        last = node;
        if (first == nullptr) {
            first = node;
        }
    }

    T pop_front() {
        if (first == nullptr) {
            throw std::logic_error("Queue is empty");
        }
        T element = first.get().data;
        NodeUniquePtr node = first;
        first = first.get().next;
        if (first == nullptr) {
            last = nullptr;
        }
        polymorphic_allocator.destroy(node);
        return element;
    }

    std::size_t size() const {
        return queue_size;
    }
};