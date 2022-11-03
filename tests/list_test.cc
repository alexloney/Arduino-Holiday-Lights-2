#include <gtest/gtest.h>
#include <iostream>
using namespace std;

#include "../list.hpp"

TEST(ListTest, CreateList) {
	List<int> test_list;
	EXPECT_EQ(0, test_list.size());
	EXPECT_TRUE(test_list.empty());
}

TEST(ListTest, AddElement) {
	List<int> test_list;
	test_list.push_front(12);
	EXPECT_EQ(1, test_list.size());
	EXPECT_FALSE(test_list.empty());
	EXPECT_EQ(12, test_list.pop_front());
	EXPECT_EQ(0, test_list.size());
	EXPECT_TRUE(test_list.empty());
}

TEST(ListTest, AddElementBack) {
	List<int> test_list;
	test_list.push_back(12);
	EXPECT_EQ(1, test_list.size());
	EXPECT_EQ(12, test_list.pop_front());
	EXPECT_EQ(0, test_list.size());

	test_list.push_back(12);
	EXPECT_EQ(1, test_list.size());
	EXPECT_EQ(12, test_list.pop_back());
	EXPECT_EQ(0, test_list.size());
}

TEST(ListTest, AddMultipleElements) {
	List<int> test_list;
	test_list.push_front(12);
	EXPECT_EQ(1, test_list.size());
	test_list.push_back(13);
	EXPECT_EQ(2, test_list.size());
	test_list.push_front(11);
	EXPECT_EQ(3, test_list.size());
	test_list.push_back(14);
	EXPECT_EQ(4, test_list.size());

	EXPECT_EQ(11, test_list.pop_front());
	EXPECT_EQ(3, test_list.size());
	EXPECT_EQ(12, test_list.pop_front());
	EXPECT_EQ(2, test_list.size());
	EXPECT_EQ(14, test_list.pop_back());
	EXPECT_EQ(1, test_list.size());
	EXPECT_EQ(13, test_list.pop_back());
	EXPECT_EQ(0, test_list.size());
}

TEST(ListTest, AccessElements) {
	List<int> test_list;
	EXPECT_EQ(0, test_list.size());

	test_list.push_front(11);
	EXPECT_EQ(1, test_list.size());
	test_list.push_back(12);
	EXPECT_EQ(2, test_list.size());
	test_list.push_back(13);
	EXPECT_EQ(3, test_list.size());

	EXPECT_EQ(11, test_list.front());
	EXPECT_EQ(3, test_list.size());
	EXPECT_EQ(13, test_list.back());
	EXPECT_EQ(3, test_list.size());
}

TEST(ListTest, Iterate) {
	List<int> test_list;
	test_list.push_back(1);
	test_list.push_back(2);
	test_list.push_back(3);
	test_list.push_back(4);
	EXPECT_EQ(4, test_list.size());

	List<int>::Iterator it = test_list.begin();
	EXPECT_EQ(1, *it);
	++it;
	EXPECT_EQ(2, *it);
	++it;
	EXPECT_EQ(3, *it);
	++it;
	EXPECT_EQ(4, *it);
	++it;
	EXPECT_EQ(it, test_list.end());
}

TEST(ListTest, EditIterate) {
	List<int> test_list;
	test_list.push_back(1);
	test_list.push_back(2);
	EXPECT_EQ(2, test_list.size());

	List<int>::Iterator it = test_list.begin();
	EXPECT_EQ(1, *it);
	*it = 3;
	EXPECT_EQ(3, *it);
	++it;
	EXPECT_EQ(2, *it);
	*it = 4;
	EXPECT_EQ(4, *it);
	++it;
	EXPECT_EQ(it, test_list.end());
}

TEST(ListTest, ConstIterate) {
	List<int> test_list;
	test_list.push_back(1);
	test_list.push_back(2);
	test_list.push_back(3);
	test_list.push_back(4);
	EXPECT_EQ(4, test_list.size());

	List<int>::Const_Iterator it = test_list.cbegin();
	EXPECT_EQ(1, *it);
	++it;
	EXPECT_EQ(2, *it);
	++it;
	EXPECT_EQ(3, *it);
	++it;
	EXPECT_EQ(4, *it);
	++it;
	EXPECT_EQ(it, test_list.cend());
}

TEST(ListTest, ReverseIterate) {
	List<int> test_list;
	test_list.push_back(1);
	test_list.push_back(2);
	test_list.push_back(3);
	test_list.push_back(4);
	EXPECT_EQ(4, test_list.size());

	List<int>::Reverse_Iterator it = test_list.rbegin();
	EXPECT_EQ(4, *it);
	++it;
	EXPECT_EQ(3, *it);
	++it;
	EXPECT_EQ(2, *it);
	++it;
	EXPECT_EQ(1, *it);
	++it;
	EXPECT_EQ(it, test_list.rend());
}

TEST(ListTest, EditReverseIterate) {
	List<int> test_list;
	test_list.push_back(1);
	test_list.push_back(2);
	EXPECT_EQ(2, test_list.size());

	List<int>::Reverse_Iterator it = test_list.rbegin();
	EXPECT_EQ(2, *it);
	*it = 3;
	EXPECT_EQ(3, *it);
	++it;
	EXPECT_EQ(1, *it);
	*it = 4;
	EXPECT_EQ(4, *it);
	++it;
	EXPECT_EQ(it, test_list.rend());
}

TEST(ListTest, ConstReverseIterate) {
	List<int> test_list;
	test_list.push_back(1);
	test_list.push_back(2);
	test_list.push_back(3);
	test_list.push_back(4);
	EXPECT_EQ(4, test_list.size());

	List<int>::Const_Reverse_Iterator it = test_list.crbegin();
	EXPECT_EQ(4, *it);
	++it;
	EXPECT_EQ(3, *it);
	++it;
	EXPECT_EQ(2, *it);
	++it;
	EXPECT_EQ(1, *it);
	++it;
	EXPECT_EQ(it, test_list.crend());
}


