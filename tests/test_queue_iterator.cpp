#include <gtest/gtest.h>
#include "../include/queue.h"
#include <vector>
#include <string>

TEST(QueueIteratorTest, EmptyQueue) {
    Queue<int> queue;
    
    EXPECT_FALSE(queue.begin() != queue.end());
}

TEST(QueueIteratorTest, IterateOverElements) {
    Queue<int> queue;
    queue.push_back(1);
    queue.push_back(2);
    queue.push_back(3);
    
    std::vector<int> result;
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        result.push_back(*it);
    }
    
    EXPECT_EQ(result, std::vector<int>({1, 2, 3}));
}

TEST(QueueIteratorTest, RangeBasedForLoop) {
    Queue<std::string> queue;
    queue.push_back("first");
    queue.push_back("second");
    queue.push_back("third");
    
    std::vector<std::string> result;
    for (const auto& element : queue) {
        result.push_back(element);
    }
    
    EXPECT_EQ(result, std::vector<std::string>({"first", "second", "third"}));
}

TEST(QueueIteratorTest, PostIncrement) {
    Queue<int> queue;
    queue.push_back(10);
    queue.push_back(20);
    
    auto it = queue.begin();
    EXPECT_EQ(*it, 10);
    
    auto old_it = it++;
    EXPECT_EQ(*old_it, 10);
    EXPECT_EQ(*it, 20);
}

TEST(QueueIteratorTest, ModifyThroughIterator) {
    Queue<int> queue;
    queue.push_back(1);
    queue.push_back(2);
    
    for (auto& element : queue) {
        element *= 2;
    }
    
    EXPECT_EQ(queue.pop_front(), 2);
    EXPECT_EQ(queue.pop_front(), 4);
}

TEST(QueueIteratorTest, IteratorWithStruct) {
    struct Point {
        int x, y;
        Point(int x = 0, int y = 0) : x(x), y(y) {}
    };
    
    Queue<Point> queue;
    queue.push_back(Point(1, 2));
    queue.push_back(Point(3, 4));
    
    auto it = queue.begin();
    EXPECT_EQ(it->x, 1);
    EXPECT_EQ(it->y, 2);
    
    ++it;
    EXPECT_EQ(it->x, 3);
    EXPECT_EQ(it->y, 4);
}

TEST(QueueIteratorTest, IteratorAfterPop) {
    Queue<int> queue;
    queue.push_back(1);
    queue.push_back(2);
    queue.push_back(3);
    
    queue.pop_front();
    
    std::vector<int> result;
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        result.push_back(*it);
    }
    
    EXPECT_EQ(result, std::vector<int>({2, 3}));
}

TEST(QueueIteratorTest, MultipleIterators) {
    Queue<int> queue;
    queue.push_back(5);
    queue.push_back(10);
    
    auto it1 = queue.begin();
    auto it2 = queue.begin();

    ++it1;
    EXPECT_TRUE(it1 != it2);
}