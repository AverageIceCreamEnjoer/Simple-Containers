#include <list>

#include "rpc_test.h"

TEST(List, Constructor_Default) {
  rpc::list<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(List, Constructor_Size) {
  rpc::list<int> our_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(List, Constructor_List) {
  rpc::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Constructor_Copy) {
  rpc::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  rpc::list<int> our_copy(our_list);
  std::list<int> std_copy(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(List, Operator_Copy) {
  rpc::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  rpc::list<int> our_copy;
  our_copy = our_list;
  std::list<int> std_copy;
  std_copy = std_list;
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(List, Constructor_Move) {
  rpc::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  rpc::list<int> our_copy(std::move(our_list));
  std::list<int> std_copy(std::move(std_list));
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(List, Operator_Move) {
  rpc::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  rpc::list<int> our_copy;
  our_copy = std::move(our_list);
  std::list<int> std_copy;
  std_copy = std::move(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(List, Size) {
  rpc::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(List, Push_Front) {
  rpc::list<int> our_list;
  std::list<int> std_list;
  our_list.push_front(1);
  std_list.push_front(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(2);
  std_list.push_front(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(3);
  std_list.push_front(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Push_Back) {
  rpc::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Pop_Front) {
  rpc::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_front();
  std_list.pop_front();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Pop_Back) {
  rpc::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_back();
  std_list.pop_back();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Iterator_Begin) {
  rpc::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  rpc::list<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_BeginPlusAndMinus) {
  rpc::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  rpc::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  --our_it;
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_End_Last) {
  rpc::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  rpc::list<int>::iterator our_it;
  our_it = our_list.end();
  --our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.end();
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_Equals) {
  rpc::list<int> first_list = {1, 2, 3};
  rpc::list<int>::iterator our_it_first;
  our_it_first = first_list.begin();
  rpc::list<int>::iterator our_it_second;
  our_it_second = first_list.begin();
  EXPECT_TRUE(our_it_first == our_it_second);
  ++our_it_second;
  EXPECT_TRUE(our_it_first != our_it_second);
}

TEST(List, Insert) {
  rpc::list<int> our_list;
  std::list<int> std_list;
  rpc::list<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  our_list.insert(our_it, 5);
  std_list.insert(std_it, 5);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.insert(our_it, 7);
  std_list.insert(std_it, 7);
  our_list.insert(our_it, 9);
  std_list.insert(std_it, 9);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Erase) {
  rpc::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  rpc::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Splice) {
  rpc::list<int> our_list_first = {1};
  rpc::list<int> our_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  rpc::list<int>::iterator our_it = our_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
}

TEST(List, Merge1) {
  rpc::list<int> our_list_first = {2, 9};
  rpc::list<int> our_list_second = {1, 2, 3, 4, 5};
  std::list<int> std_list_first = {2, 9};
  std::list<int> std_list_second = {1, 2, 3, 4, 5};
  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(List, Merge2) {
  rpc::list<int> our_list_first = {};
  rpc::list<int> our_list_second = {1, 2, 3, 4, 5};
  std::list<int> std_list_first = {};
  std::list<int> std_list_second = {1, 2, 3, 4, 5};
  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(List, Merge3) {
  rpc::list<int> our_list_first = {4, 0};
  rpc::list<int> our_list_second = {1, 2, 3, 4, 5};
  std::list<int> std_list_first = {4, 0};
  std::list<int> std_list_second = {1, 2, 3, 4, 5};
  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
  auto it = our_list_first.begin();
  for (auto i = std_list_first.begin();
       it != our_list_first.end() && i != std_list_first.end(); ++i) {
    EXPECT_EQ(*i, *it);
    ++it;
  }
}

TEST(List, Reverse1) {
  rpc::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Reverse2) {
  rpc::list<int> our_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  our_list.reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Unique) {
  rpc::list<int> our_list = {1, 2, 2, 3, 3};
  std::list<int> std_list = {1, 2, 2, 3, 3};
  rpc::list<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.unique();
  std_list.unique();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Sort) {
  rpc::list<int> our_list = {2, 4, 1, 3, 5};
  std::list<int> std_list = {2, 4, 1, 3, 5};
  rpc::list<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.sort();
  std_list.sort();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Insert_Many) {
  rpc::list<int> our_list = {1, 2, 3, 4, 5};
  rpc::list<int>::iterator our_it = our_list.begin();
  ++our_it;
  our_list.insert_many(our_it, 7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(List, Insert_Many_Back) {
  rpc::list<int> our_list = {1, 2, 3, 4, 5};
  rpc::list<int>::iterator our_it;
  our_list.insert_many_back(7, 8, 9);
  our_it = our_list.end();
  --our_it;
  EXPECT_EQ(*our_it, 9);
  --our_it;
  EXPECT_EQ(*our_it, 8);
  --our_it;
  EXPECT_EQ(*our_it, 7);
  --our_it;
  EXPECT_EQ(*our_it, 5);
  --our_it;
  EXPECT_EQ(*our_it, 4);
}

TEST(List, Insert_Many_Front) {
  rpc::list<int> our_list = {1, 2, 3, 4, 5};
  rpc::list<int>::iterator our_it;
  our_list.insert_many_front(7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}
