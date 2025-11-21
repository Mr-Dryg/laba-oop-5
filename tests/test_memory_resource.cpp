#include <gtest/gtest.h>
#include "../include/my_memory_resource.h"

TEST(MyMemoryResourceTest, AllocateAndDeallocate) {
    MyMemoryResource resource;
    
    void* ptr1 = resource.allocate(100);
    ASSERT_NE(ptr1, nullptr);
    
    void* ptr2 = resource.allocate(200);
    ASSERT_NE(ptr2, nullptr);
    
    resource.deallocate(ptr1, 100);
    resource.deallocate(ptr2, 200);
}

TEST(MyMemoryResourceTest, ReuseMemory) {
    MyMemoryResource resource;
    
    void* ptr1 = resource.allocate(100);
    resource.deallocate(ptr1, 100);
    
    void* ptr2 = resource.allocate(100);
    ASSERT_EQ(ptr1, ptr2);
    resource.deallocate(ptr2, 100);
}

TEST(MyMemoryResourceTest, InvalidDeallocate) {
    MyMemoryResource resource;
    void* invalid_ptr = reinterpret_cast<void*>(0x12345);
    
    EXPECT_THROW(resource.deallocate(invalid_ptr, 100), std::logic_error);
}

TEST(MyMemoryResourceTest, CompareEqual) {
    MyMemoryResource resource1;
    MyMemoryResource resource2;
    
    ASSERT_TRUE(resource1.is_equal(resource1));
    ASSERT_FALSE(resource1.is_equal(resource2));
}