#include "../include/my_memory_resource.h"
#include <new>
#include <stdexcept>

void* MyMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    for (auto& block : blocks) {
        if (block.empty && block.size >= bytes) {
            block.empty = false;
            return block.data_pointer;
        }
    }

    blocks.emplace_back(::operator new(bytes), bytes, false);
    return blocks.back().data_pointer;
}

void MyMemoryResource::do_deallocate(void* ptr, size_t bytes, size_t alignment) {
    for (auto& block : blocks) {
        if (!block.empty && ptr == block.data_pointer) {
            block.empty = true;
            return;
        }
    }
    throw std::logic_error("Attempt to free an unallocated block");
}

bool MyMemoryResource::do_is_equal(const memory_resource& other) const noexcept {
    return this == &other;
}

MyMemoryResource::~MyMemoryResource() {
    for (auto& block : blocks) {
        ::operator delete(block.data_pointer);
    }
}