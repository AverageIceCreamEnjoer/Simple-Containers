#include "rpc_test.h"

TEST(map, def_constructor_1) { rpc::map<int, int> a; }

TEST(map, empty_1) {
  rpc::map<int, int> a;
  EXPECT_EQ(true, a.empty());
}
TEST(map, map_insert_or_assign_1) {
  rpc::map<int, std::string> map;
  auto result = map.insert_or_assign(5, "five");
  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map[5], "five");
}
TEST(map, map_insert_or_assign_2) {
  rpc::map<int, std::string> map;
  map.insert_or_assign(5, "five");
  auto result = map.insert_or_assign(10, "ten");
  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map[10], "ten");
}
TEST(map, map_insert_or_assign_3) {
  rpc::map<int, std::string> map;
  map.insert_or_assign(5, "five");
  auto result = map.insert_or_assign(5, "new five");
  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map[5], "new five");
}
TEST(map, map_insert_or_assign_4) {
  rpc::map<int, std::string> map;
  map.insert_or_assign(5, "five");
  map.insert_or_assign(2, "two");
  auto result = map.insert_or_assign(6, "six");
  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map.at(5), "five");
}
TEST(map, map_insert_1) {
  rpc::map<int, std::string> myMap;
  auto result = myMap.insert(std::make_pair(1, "One"));
  ASSERT_TRUE(result.second);
}
TEST(map, map_insert_2) {
  rpc::map<int, std::string> myMap;
  myMap.insert(std::make_pair(1, "One"));
  auto result = myMap.insert(std::make_pair(1, "New One"));
  ASSERT_FALSE(result.second);
}
TEST(map, map_insert_3) {
  rpc::map<int, std::string> myMap;
  myMap.insert(std::make_pair(1, "One"));
  myMap.insert(std::make_pair(2, "Two"));
  myMap.insert(std::make_pair(3, "Three"));
  ASSERT_EQ(myMap.size(), 3);
}
TEST(map, map_insert_4) {
  rpc::map<int, std::string> myMap;
  auto result = myMap.insert(5, "five");
  ASSERT_TRUE(result.second);
  ASSERT_EQ(result.first.m_node->key, 5);
  ASSERT_EQ(result.first.m_node->data, "five");
}
TEST(map, map_insert_5) {
  rpc::map<int, std::string> myMap;
  myMap.insert(5, "five");
  auto result = myMap.insert(5, "updated five");
  ASSERT_FALSE(result.second);
  ASSERT_EQ(myMap[5], "five");
}
TEST(map, map_insert_6) {
  rpc::map<int, std::string> myMap;
  myMap.insert(5, "five");
  auto result = myMap.insert(10, "ten");
  ASSERT_TRUE(result.second);
  ASSERT_EQ(result.first.m_node->key, 10);
  ASSERT_EQ(result.first.m_node->data, "ten");
}
TEST(map, map_CopyConstructor_1) {
  rpc::map<int, std::string> original_map;
  rpc::map<int, std::string> copied_map(original_map);
  EXPECT_EQ(copied_map.size(), 0);
}
TEST(map, map_CopyConstructor_2) {
  rpc::map<int, std::string> original_map;
  original_map.insert(std::make_pair(5, "five"));
  rpc::map<int, std::string> copied_map(original_map);
  EXPECT_EQ(copied_map.size(), 1);
  EXPECT_EQ(copied_map[5], "five");
}

TEST(map, map_CopyConstructor_3) {
  rpc::map<int, std::string> original_map;
  original_map.insert(std::make_pair(5, "five"));
  original_map.insert(std::make_pair(10, "ten"));
  original_map.insert(std::make_pair(15, "fifteen"));
  rpc::map<int, std::string> copied_map(original_map);
  EXPECT_EQ(copied_map.size(), 3);
  EXPECT_EQ(copied_map[5], "five");
  EXPECT_EQ(copied_map[10], "ten");
  EXPECT_EQ(copied_map[15], "fifteen");
}
TEST(map, map_Erase_1) {
  rpc::map<int, int> map;
  map.insert(std::make_pair(1, 10));
  auto it = map.find(1);
  map.erase(it);
  ASSERT_EQ(map.size(), 0);
  ASSERT_EQ(map.empty(), true);
}
TEST(map, map_Erase_2) {
  rpc::map<int, int> map;
  map.insert(std::make_pair(1, 10));
  map.insert(std::make_pair(2, 20));
  auto it = map.find(1);
  map.erase(it);
  ASSERT_EQ(map.size(), 1);
  ASSERT_EQ(map.find(2).m_node->data, 20);
}
TEST(map, map_Erase_3) {
  rpc::map<int, int> map;
  map.insert(std::make_pair(1, 10));
  map.insert(std::make_pair(2, 20));
  map.insert(std::make_pair(3, 30));
  auto it = map.find(2);
  map.erase(it);
  ASSERT_EQ(map.size(), 2);
  ASSERT_EQ(map.find(1).m_node->data, 10);
  ASSERT_EQ(map.find(3).m_node->data, 30);
}
TEST(map, map_Erase_4) {
  rpc::map<int, std::string> map{
      {3, "three"}, {2, "two"}, {4, "four"}, {1, "one"}, {5, "five"}};
  auto it = map.find(3);
  map.erase(it);
  EXPECT_EQ(map.size(), 4);
  EXPECT_FALSE(map.contains(3));
}
TEST(map, map_begin_1) {
  rpc::map<int, int> map;
  map.insert_or_assign(1, 1);
  map.insert_or_assign(2, 2);
  map.insert_or_assign(3, 3);
  auto it = map.begin();
  EXPECT_EQ(it.m_node->key, 1);
  EXPECT_EQ(it.m_node->data, 1);
  ++it;
  EXPECT_EQ(it.m_node->key, 2);
  EXPECT_EQ(it.m_node->data, 2);
  ++it;
  EXPECT_EQ(it.m_node->key, 3);
  EXPECT_EQ(it.m_node->data, 3);
  --it;
  ++it;
  ++it;
  EXPECT_EQ(it, map.end());
}
TEST(map, map_begin_2) {
  rpc::map<int, int> map;
  auto it = map.begin();
  EXPECT_EQ(it, map.end());
}
TEST(map, map_Contains_1) {
  rpc::map<int, std::string> map;
  map.insert(1, "one");
  EXPECT_TRUE(map.contains(1));
}
TEST(map, map_Contains_2) {
  rpc::map<int, std::string> map;
  map.insert(1, "one");
  EXPECT_FALSE(map.contains(2));
}
TEST(map, map_Contains_3) {
  rpc::map<int, std::string> map;
  EXPECT_FALSE(map.contains(1));
}
TEST(map, map_Swap_1) {
  rpc::map<int, std::string> map1;
  rpc::map<int, std::string> map2;
  map1.insert(1, "one");
  map1.insert(2, "two");
  map2.insert(3, "three");
  map2.insert(4, "four");
  map1.swap(map2);
  EXPECT_EQ(map1.size(), 2);
  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map1.at(3), "three");
  EXPECT_EQ(map1.at(4), "four");
  EXPECT_EQ(map2.at(1), "one");
  EXPECT_EQ(map2.at(2), "two");
}
TEST(map, map_Swap_2) {
  rpc::map<int, std::string> map;
  map.insert(1, "one");
  map.insert(2, "two");
  map.swap(map);
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map.at(2), "two");
}
TEST(map, map_brackets_1) {
  rpc::map<int, std::string> map;
  map[1] = "one";
  EXPECT_EQ(map.at(1), "one");
}
TEST(map, map_brackets_2) {
  rpc::map<int, std::string> map;
  map[1] = "one";
  map[3] = "three";
  map[4] = "four";
  map.max_size();
  map[2] = "two";
  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map.at(4), "four");
}
TEST(map, map_brackets_3) {
  rpc::map<int, int> map{std::make_pair(3, 30), std::make_pair(1, 10),
                         std::make_pair(2, 20)};
  EXPECT_EQ(map.at(3), 30);
  EXPECT_EQ(map.at(1), 10);
  EXPECT_EQ(map.at(2), 20);
  EXPECT_EQ(map.size(), 3);
  auto it = map.find(3);
  map.erase(it);
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.at(1), 10);
  EXPECT_EQ(map.at(2), 20);
}
TEST(map, merge_1) {
  rpc::map<int, int> map1;
  rpc::map<int, int> map2;
  map1.merge(map2);
  EXPECT_TRUE(map1.empty());
  EXPECT_TRUE(map2.empty());
}

TEST(map, merge_2) {
  rpc::map<int, int> map1;
  map1[1] = 1;
  map1[2] = 2;
  rpc::map<int, int> map2;
  map2[3] = 3;
  map2[4] = 4;
  map1.merge(map2);
  EXPECT_EQ(map1.size(), 4);
  EXPECT_EQ(map2.size(), 0);
  EXPECT_EQ(map1.at(1), 1);
  EXPECT_EQ(map1.at(2), 2);
  EXPECT_EQ(map1.at(3), 3);
  EXPECT_EQ(map1.at(4), 4);
}

TEST(map, merge_3) {
  rpc::map<int, int> map;
  map[1] = 1;
  map[2] = 2;
  map.merge(map);
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.at(1), 1);
  EXPECT_EQ(map.at(2), 2);
}

TEST(map, merge_4) {
  rpc::map<int, int> map1;
  map1[1] = 1;
  map1[2] = 2;
  rpc::map<int, int> map2;
  map2[2] = 2;
  map2[3] = 3;
  map1.merge(map2);
  EXPECT_EQ(map1.size(), 3);
  EXPECT_EQ(map2.size(), 1);
  EXPECT_EQ(map1.at(1), 1);
  EXPECT_EQ(map1.at(2), 2);
  EXPECT_EQ(map1.at(3), 3);
  EXPECT_EQ(map2.at(2), 2);
}
TEST(map, insert_many_empty) {
  rpc::map<int, std::string> map;
  auto result = map.insert_many();
  EXPECT_EQ(result.size(), 0);
}
TEST(map, insert_many_1) {
  rpc::map<int, std::string> map;
  auto result = map.insert_many(std::make_pair(5, "five"));
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].second, true);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map[5], "five");
}
TEST(map, insert_many_2) {
  rpc::map<int, std::string> map;
  auto result =
      map.insert_many(std::make_pair(5, "five"), std::make_pair(3, "three"));
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result[0].second, true);
  EXPECT_EQ(result[1].second, true);
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map[5], "five");
  EXPECT_EQ(map[3], "three");
}
TEST(map, insert_many_3) {
  rpc::map<int, std::string> map;
  map.insert(std::make_pair(5, "five"));
  auto result = map.insert_many(std::make_pair(5, "new five"));
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].second, false);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map[5], "five");
}
TEST(map, insert_many_4) {
  rpc::map<char, std::string> map;
  map.max_size();
  map.insert(std::make_pair('f', "five"));
  auto result = map.insert_many(std::make_pair('f', "new five"));
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].second, false);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.at('f'), "five");
}