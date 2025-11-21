#include <gtest/gtest.h>
#include "../include/queue.h"
#include "../include/my_memory_resource.h"
#include <string>

struct Person {
    std::string name;
    int age;
    double salary;
    
    Person() : name(""), age(0), salary(0.0) {}
    
    Person(std::string n, int a, double s) : name(std::move(n)), age(a), salary(s) {}
    
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age && salary == other.salary;
    }
};

TEST(QueueTest, PushAndPop) {
    Queue<int> queue;
    
    queue.push_back(1);
    queue.push_back(2);
    queue.push_back(3);
    
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.pop_front(), 1);
    EXPECT_EQ(queue.pop_front(), 2);
    EXPECT_EQ(queue.pop_front(), 3);
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, EmptyQueue) {
    Queue<int> queue;
    
    EXPECT_TRUE(queue.size() == 0);
    EXPECT_THROW(queue.pop_front(), std::logic_error);
}

TEST(QueueTest, CustomMemoryResource) {
    MyMemoryResource memory_resource;
    Queue<int> queue{&memory_resource};
    
    queue.push_back(42);
    queue.push_back(43);
    
    EXPECT_EQ(queue.pop_front(), 42);
    EXPECT_EQ(queue.pop_front(), 43);
}

TEST(QueueTest, StructWithMultipleFields) {
    Queue<Person> queue;
    
    Person alice{"Alice", 30, 50000.0};
    Person bob{"Bob", 25, 45000.5};
    Person charlie{"Charlie", 35, 60000.75};
    
    queue.push_back(alice);
    queue.push_back(bob);
    queue.push_back(charlie);
    
    EXPECT_EQ(queue.size(), 3);
    
    Person result1 = queue.pop_front();
    EXPECT_EQ(result1.name, "Alice");
    EXPECT_EQ(result1.age, 30);
    EXPECT_DOUBLE_EQ(result1.salary, 50000.0);
    
    Person result2 = queue.pop_front();
    EXPECT_EQ(result2.name, "Bob");
    EXPECT_EQ(result2.age, 25);
    EXPECT_DOUBLE_EQ(result2.salary, 45000.5);
    
    Person result3 = queue.pop_front();
    EXPECT_EQ(result3.name, "Charlie");
    EXPECT_EQ(result3.age, 35);
    EXPECT_DOUBLE_EQ(result3.salary, 60000.75);
    
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueTest, StructWithStringsAndCustomMemoryResource) {
    MyMemoryResource memory_resource;
    Queue<Person> queue{&memory_resource};
    
    Person john{"John Doe", 40, 75000.0};
    Person jane{"Jane Smith with a very long name", 35, 80000.25};
    
    queue.push_back(john);
    queue.push_back(jane);
    
    EXPECT_EQ(queue.size(), 2);
    
    Person result1 = queue.pop_front();
    EXPECT_EQ(result1.name, "John Doe");
    EXPECT_EQ(result1.age, 40);
    EXPECT_DOUBLE_EQ(result1.salary, 75000.0);
    
    Person result2 = queue.pop_front();
    EXPECT_EQ(result2.name, "Jane Smith with a very long name");
    EXPECT_EQ(result2.age, 35);
    EXPECT_DOUBLE_EQ(result2.salary, 80000.25);
}

TEST(QueueTest, MixedStructOperations) {
    Queue<Person> queue;
    
    queue.push_back(Person{"Alice", 25, 50000.0});
    queue.push_back(Person{"Bob", 30, 60000.0});
    
    EXPECT_EQ(queue.size(), 2);
    
    Person alice = queue.pop_front();
    EXPECT_EQ(alice.name, "Alice");
    EXPECT_EQ(queue.size(), 1);
    
    queue.push_back(Person{"Charlie", 35, 70000.0});
    EXPECT_EQ(queue.size(), 2);
    
    Person bob = queue.pop_front();
    EXPECT_EQ(bob.name, "Bob");
    
    Person charlie = queue.pop_front();
    EXPECT_EQ(charlie.name, "Charlie");
    
    EXPECT_EQ(queue.size(), 0);
}