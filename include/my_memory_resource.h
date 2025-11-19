#pragma once
#include <list>
#include <memory_resource>

class MyMemoryResource : public std::pmr::memory_resource {
    struct MemoryBlock {
        void* data_pointer = nullptr;
        std::size_t size = 0;
        bool empty = true;
    };

    std::list<MemoryBlock> blocks;

private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;

    void do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) override;

    bool do_is_equal(const memory_resource& other) const noexcept override;

public:
    MyMemoryResource() = default;

    ~MyMemoryResource();
};