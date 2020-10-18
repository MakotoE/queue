#include <gtest/gtest.h>
#include "../queue.h"

TEST(Queue, pushBack) {
	Queue<int> queue;
	EXPECT_EQ(queue, Queue<int>());
	queue.pushBack(0);
	EXPECT_EQ(queue, Queue({0}));
	queue.pushBack(1);
	EXPECT_EQ(queue, Queue({0, 1}));
	queue.pushBack(2);
	queue.pushBack(3);
	EXPECT_EQ(queue.capacity(), 4);
	queue.pushBack(4);

	EXPECT_EQ(queue, Queue({0, 1, 2, 3, 4}));
}

TEST(Queue, popFront) {
	Queue<int> queue;
	queue.popFront();
	EXPECT_EQ(queue, Queue<int>());
	queue.pushBack(0);
	queue.popFront();
	EXPECT_EQ(queue, Queue<int>());
	queue.pushBack(0);
	queue.pushBack(1);
	queue.pushBack(2);
	EXPECT_EQ(queue, Queue({0, 1, 2}));
	queue.popFront();
	queue.popFront();
	queue.pushBack(3);
	queue.pushBack(4);
	EXPECT_EQ(queue, Queue({2, 3, 4}));
}

TEST(Queue, reserve) {
	{
		Queue<int> queue;
		EXPECT_EQ(queue.capacity(), 0);
		queue.reserve(0);
		EXPECT_EQ(queue.capacity(), 0);
		queue.reserve(1);
		EXPECT_EQ(queue.capacity(), 2);
		queue.reserve(5);
		EXPECT_EQ(queue.capacity(), 8);
	}
	{
		Queue<int> queue;
		queue.pushBack(0);
		queue.pushBack(1);
		queue.reserve(4);
		EXPECT_EQ(queue, Queue({0, 1}));
	}
}

TEST(Queue, getter) {
	Queue<int> queue;
	EXPECT_THROW(queue[0], std::out_of_range);
	queue.pushBack(0);
	EXPECT_EQ(queue[0], 0);
	queue.pushBack(1);
	queue.pushBack(2);
	EXPECT_EQ(queue[0], 0);
	EXPECT_EQ(queue[1], 1);
	EXPECT_EQ(queue[2], 2);
}