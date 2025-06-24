#include <set>

#include "rpc_test.h"

TEST(set_constructor, case1) {
  rpc::set<int> rpc_set_int;
  rpc::set<double> rpc_set_double;
  rpc::set<std::string> rpc_set_string;

  EXPECT_EQ(rpc_set_int.size(), 0U);
  EXPECT_EQ(rpc_set_double.size(), 0U);
  EXPECT_EQ(rpc_set_string.size(), 0U);
}

TEST(set_constructor, case2) {
  rpc::set<int> rpc_set_int{1, 2, 3, 4, 5};
  rpc::set<double> rpc_set_double{1.30359, 2847.4925, 923.39281};
  rpc::set<std::string> rpc_set_string{"Четырёх ", "слов ", "всегда ",
                                       "достаточно."};

  EXPECT_EQ(rpc_set_int.size(), 5U);
  EXPECT_EQ(rpc_set_double.size(), 3U);
  EXPECT_EQ(rpc_set_string.size(), 4U);
}

TEST(set_constructor, case3) {
  rpc::set<int> rpc_set_ref_int{1, 2, 3, 4, 5};
  rpc::set<int> rpc_set_res_int{rpc_set_ref_int};
  rpc::set<std::string> rpc_set_ref_string{"Четырёх ", "слов ", "всегда ",
                                           "достаточно."};
  rpc::set<std::string> rpc_set_res_string{rpc_set_ref_string};

  EXPECT_EQ(rpc_set_ref_int.size(), rpc_set_res_int.size());
  EXPECT_EQ(rpc_set_ref_string.size(), rpc_set_res_string.size());
}

TEST(set_constructor, case4) {
  rpc::set<int> rpc_set_ref_int{1, 2, 3, 4, 5};
  rpc::set<int> rpc_set_res_int = std::move(rpc_set_ref_int);
  rpc::set<std::string> rpc_set_ref_string{"Четырёх ", "слов ", "всегда ",
                                           "достаточно."};
  rpc::set<std::string> rpc_set_res_string = std::move(rpc_set_ref_string);

  EXPECT_EQ(rpc_set_ref_int.size(), 0U);
  EXPECT_EQ(rpc_set_res_int.size(), 5U);
  EXPECT_EQ(rpc_set_ref_string.size(), 0U);
  EXPECT_EQ(rpc_set_res_string.size(), 4U);
}

TEST(set_constructor, case5) {
  rpc::set<int> rpc_set_ref_int{1, 2, 3, 4, 5};
  rpc::set<int> rpc_set_res_int;
  rpc_set_res_int = std::move(rpc_set_ref_int);

  rpc::set<double> rpc_set_ref_double{1.30359, 2847.4925, 923.39281};
  rpc::set<double> rpc_set_res_double;
  rpc_set_res_double = std::move(rpc_set_ref_double);

  rpc::set<std::string> rpc_set_ref_string{"Четырёх ", "слов ", "всегда ",
                                           "достаточно."};
  rpc::set<std::string> rpc_set_res_string;
  rpc_set_res_string = std::move(rpc_set_ref_string);

  EXPECT_EQ(rpc_set_ref_int.size(), 0U);
  EXPECT_EQ(rpc_set_res_int.size(), 5U);

  EXPECT_EQ(rpc_set_ref_double.size(), 0U);
  EXPECT_EQ(rpc_set_res_double.size(), 3U);

  EXPECT_EQ(rpc_set_ref_string.size(), 0U);
  EXPECT_EQ(rpc_set_res_string.size(), 4U);
}

TEST(set_constructor, case7) {
  rpc::set<int> rpc_set_ref_int{1, 2, 3, 4};
  rpc::set<int> rpc_set_res_int{rpc_set_ref_int};

  rpc::set<double> rpc_set_ref_double{1.30359, 2847.4925, 923.39281, 1.23};
  rpc::set<double> rpc_set_res_double{rpc_set_ref_double};

  rpc::set<std::string> rpc_set_ref_string{"Четырёх ", "слов ", "всегда ",
                                           "достаточно."};
  rpc::set<std::string> rpc_set_res_string{rpc_set_ref_string};

  auto it_res_int = rpc_set_res_int.begin();
  for (auto it_ref_int = rpc_set_ref_int.begin();
       it_ref_int != rpc_set_ref_int.end(); ++it_ref_int) {
    EXPECT_EQ(*it_res_int, *it_ref_int);
    it_res_int++;
  }

  auto it_res_double = rpc_set_res_double.begin();
  for (auto it_ref_double = rpc_set_ref_double.begin();
       it_ref_double != rpc_set_ref_double.end(); ++it_ref_double) {
    EXPECT_EQ(*it_res_double, *it_ref_double);
    it_res_double++;
  }

  auto it_res_string = rpc_set_res_string.begin();
  for (auto it_ref_string = rpc_set_ref_string.begin();
       it_ref_string != rpc_set_ref_string.end(); ++it_ref_string) {
    EXPECT_EQ(*it_res_string, *it_ref_string);
    it_res_string++;
  }
}

TEST(set_constructor, case8) {
  rpc::set<int> rpc_set{1, 2, 3, 4, 3, 2, 1};
  std::set<int> std_set{1, 2, 3, 4, 3, 2, 1};
  EXPECT_EQ(rpc_set.size(), std_set.size());
  auto rpc_it = rpc_set.begin();
  auto std_it = std_set.begin();
  while (rpc_it != rpc_set.end() && std_it != std_set.end()) {
    EXPECT_EQ(*rpc_it, *std_it);
    ++rpc_it;
    ++std_it;
  }
}

TEST(set_insert, case1) {
  rpc::set<int> rpc_set;

  std::pair<rpc::set<int>::iterator, bool> insert1 = rpc_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<rpc::set<int>::iterator, bool> insert2 = rpc_set.insert(9);
  std::pair<rpc::set<int>::iterator, bool> insert3 = rpc_set.insert(9);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, false);

  std::pair<rpc::set<int>::iterator, bool> insert4 = rpc_set.insert(23);
  EXPECT_EQ(*insert4.first, 23);
  EXPECT_EQ(insert4.second, true);

  std::pair<rpc::set<int>::iterator, bool> insert5 = rpc_set.insert(98);
  EXPECT_EQ(*insert5.first, 98);
  EXPECT_EQ(insert5.second, true);

  EXPECT_EQ(rpc_set.size(), 3U);
}

TEST(set_insert, case2) {
  rpc::set<double> rpc_set;

  std::pair<rpc::set<double>::iterator, bool> insert1 = rpc_set.insert(1.4);
  EXPECT_EQ(*insert1.first, 1.4);
  EXPECT_EQ(insert1.second, true);

  std::pair<rpc::set<double>::iterator, bool> insert2 = rpc_set.insert(2.77);
  EXPECT_EQ(*insert2.first, 2.77);
  EXPECT_EQ(insert2.second, true);

  std::pair<rpc::set<double>::iterator, bool> insert3 = rpc_set.insert(3.9);
  EXPECT_EQ(*insert3.first, 3.9);
  EXPECT_EQ(insert3.second, true);

  std::pair<rpc::set<double>::iterator, bool> insert4 = rpc_set.insert(2.77);
  std::pair<rpc::set<double>::iterator, bool> insert5 = rpc_set.insert(3.9);
  EXPECT_EQ(insert4.second, false);
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(rpc_set.size(), 3U);
}

TEST(set_insert, case3) {
  rpc::set<std::string> rpc_set;

  std::pair<rpc::set<std::string>::iterator, bool> insert1 =
      rpc_set.insert("Четырёх ");
  EXPECT_EQ(*insert1.first, "Четырёх ");
  EXPECT_EQ(insert1.second, true);

  std::pair<rpc::set<std::string>::iterator, bool> insert2 =
      rpc_set.insert("слов ");
  EXPECT_EQ(*insert2.first, "слов ");
  EXPECT_EQ(insert2.second, true);

  std::pair<rpc::set<std::string>::iterator, bool> insert3 =
      rpc_set.insert("слов ");
  EXPECT_EQ(insert3.second, false);

  std::pair<rpc::set<std::string>::iterator, bool> insert4 =
      rpc_set.insert("всегда ");
  EXPECT_EQ(*insert4.first, "всегда ");
  EXPECT_EQ(insert4.second, true);

  std::pair<rpc::set<std::string>::iterator, bool> insert5 =
      rpc_set.insert("Четырёх ");
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(rpc_set.size(), 3U);
}

TEST(set_insert, case4) {
  rpc::set<double> rpc_set = {21};

  std::pair<rpc::set<double>::iterator, bool> insert1 = rpc_set.insert(1.4);
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(rpc_set.size(), 2U);
}

TEST(set_insert, case5) {
  rpc::set<std::string> rpc_set = {"Его имя - "};

  std::pair<rpc::set<std::string>::iterator, bool> insert1 =
      rpc_set.insert("Роберт Полсон!");
  EXPECT_EQ(*insert1.first, "Роберт Полсон!");
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(rpc_set.size(), 2U);
}

TEST(set_begin, case1) {
  rpc::set<double> rpc_set = {11.4, 2.770001, 3.901, 2.77, 3.9};

  EXPECT_EQ(*rpc_set.begin(), 2.77);
}

TEST(set_begin, case2) {
  rpc::set<std::string> rpc_set = {"Жил", "один", "...", "умру", "один"};

  EXPECT_EQ(*rpc_set.begin(), "...");
}

TEST(set_begin, case3) {
  rpc::set<std::string> rpc_set = {"HI-HI-HA-HA", "HI-HI-HA-HA", "HI-HI-HA-HA"};

  EXPECT_EQ(*rpc_set.begin(), "HI-HI-HA-HA");
}

TEST(set_end, case1) {
  rpc::set<int> rpc_set = {9, 15, 7, 23, 2};

  EXPECT_EQ(*--rpc_set.end(), 23);
}

TEST(set_end, case2) {
  rpc::set<int> rpc_set;

  EXPECT_THROW(*rpc_set.end(), std::out_of_range);
}

TEST(set_end, case3) {
  rpc::set<double> rpc_set = {1.4, 1.4};

  EXPECT_EQ(*--rpc_set.end(), 1.4);
}

TEST(set_end, case4) {
  rpc::set<std::string> rpc_set = {"Hmm", "Hmm", "Hmm"};

  EXPECT_EQ(*--rpc_set.end(), "Hmm");
}

TEST(set_balance, case1) {
  rpc::set<int> rpc_set = {1, 15, 5};

  EXPECT_EQ(*--rpc_set.end(), 15);
  EXPECT_EQ(rpc_set.size(), 3U);
}

TEST(set_balance, case2) {
  rpc::set<double> rpc_set = {11.4, 2.770001, 3.901};

  EXPECT_EQ(*--rpc_set.end(), 11.4);
  EXPECT_EQ(rpc_set.size(), 3U);
}

TEST(set_balance, case3) {
  rpc::set<int> rpc_set = {10, 5, 20, 30, 1543};

  EXPECT_EQ(*--rpc_set.end(), 1543);
  EXPECT_EQ(*rpc_set.begin(), 5);
  EXPECT_EQ(rpc_set.size(), 5U);
}

TEST(set_erase, case1) {
  rpc::set<int> rpc_set = {10, 5, 15, 4, 18, 13, 16};

  auto it = rpc_set.begin();
  it++;
  it++;
  it++;
  it++;
  rpc_set.erase(it);
  EXPECT_EQ(*rpc_set.begin(), 4);
  EXPECT_EQ(*--rpc_set.end(), 18);
  EXPECT_EQ(rpc_set.size(), 6U);

  it = rpc_set.begin();
  rpc_set.erase(it);
  EXPECT_EQ(*rpc_set.begin(), 5);
  EXPECT_EQ(*--rpc_set.end(), 18);
  EXPECT_EQ(rpc_set.size(), 5U);

  it = rpc_set.begin();
  it++;
  rpc_set.erase(it);
  EXPECT_EQ(*rpc_set.begin(), 5);
  EXPECT_EQ(*--rpc_set.end(), 18);
  EXPECT_EQ(rpc_set.size(), 4U);

  it = --rpc_set.end();
  rpc_set.erase(it);
  EXPECT_EQ(*rpc_set.begin(), 5);
  EXPECT_EQ(*--rpc_set.end(), 16);
  EXPECT_EQ(rpc_set.size(), 3U);

  it = rpc_set.begin();
  it++;
  rpc_set.erase(it);

  it = rpc_set.begin();
  it++;
  rpc_set.erase(it);

  it = rpc_set.begin();
  rpc_set.erase(it);

  EXPECT_EQ(rpc_set.size(), 0U);
}

TEST(set_erase, case2) {
  rpc::set<int> rpc_set = {30, 1543};

  auto it = rpc_set.begin();
  it = it + 1;
  rpc_set.erase(it);
  it = rpc_set.begin();
  rpc_set.erase(it);

  EXPECT_EQ(rpc_set.size(), 0U);
}

TEST(set_erase, case3) {
  rpc::set<std::string> rpc_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  auto it = --rpc_set.end();
  rpc_set.erase(it);
  EXPECT_EQ(*--rpc_set.end(), "hola");
  EXPECT_EQ(rpc_set.size(), 4U);

  it = --rpc_set.end();
  rpc_set.erase(it);
  EXPECT_EQ(*--rpc_set.end(), "hi");
  EXPECT_EQ(rpc_set.size(), 3U);

  rpc_set.insert("hola-hola");
  rpc_set.insert("hola");
  it = --rpc_set.end();
  rpc_set.erase(it);
  EXPECT_EQ(*--rpc_set.end(), "hola");
  EXPECT_EQ(rpc_set.size(), 4U);
}

TEST(set_erase, case4) {
  rpc::set<double> rpc_set = {22.2, 12.4457, 56.84, 941.44, 44.48};

  auto it = --rpc_set.end();
  it--;
  rpc_set.erase(it);
  it = --rpc_set.end();
  EXPECT_EQ(*it, 941.44);
  EXPECT_EQ(rpc_set.size(), 4U);

  it = rpc_set.begin();
  ++it;
  ++it;
  ++it;
  rpc_set.erase(it);
  it = rpc_set.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*--rpc_set.end(), 44.48);
  EXPECT_EQ(rpc_set.size(), 3U);
}

TEST(set_erase, case5) {
  rpc::set<double> rpc_set = {22.2, 44.48, 12.4457, 1.44};

  auto it = rpc_set.begin();
  it = it - 1;
  rpc_set.erase(it);
  it = rpc_set.begin();
  ++it;
  ++it;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(rpc_set.size(), 3U);
}

TEST(set_erase, case6) {
  rpc::set<double> rpc_set = {22.2, 44.48, 12.4457, 6.84, 1.44};

  auto it = rpc_set.begin();
  ++it;
  ++it;
  ++it;
  rpc_set.erase(it);
  it = rpc_set.begin();
  it = it + 3;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(rpc_set.size(), 4U);
}

TEST(set_erase, case7) {
  rpc::set<double> rpc_set = {22.2, 12.4457, 56.84, 941.44, 44.48};

  auto it = rpc_set.begin();
  ++it;
  rpc_set.erase(it);
  it = rpc_set.begin();
  ++it;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(rpc_set.size(), 4U);
}

TEST(set_erase, case8) {
  rpc::set<double> rpc_set = {22.2, 44.48, 12.4457, 1.44};

  auto it = rpc_set.begin();
  ++it;
  rpc_set.erase(it);
  it = rpc_set.begin();
  ++it;
  EXPECT_EQ(*it, 22.2);
  EXPECT_EQ(rpc_set.size(), 3U);
}

TEST(set_erase, case9) {
  rpc::set<double> rpc_set = {22.2,  44.48, 12.4457, 32.45,
                              65.12, 66.32, 40.54,   6.4};

  auto it = --rpc_set.end();
  it = it - 4;
  rpc_set.erase(it);
  it = rpc_set.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 40.54);
  EXPECT_EQ(rpc_set.size(), 7U);
}

TEST(set_empty, case1) {
  rpc::set<double> rpc_set = {22.2, 44.48, 12.4457, 1.44};

  EXPECT_EQ(rpc_set.empty(), 0);
}

TEST(set_empty, case2) {
  rpc::set<double> rpc_set;

  EXPECT_EQ(rpc_set.empty(), 1);
}

TEST(set_Size, case1) {
  rpc::set<double> rpc_set;
  std::set<double> std_set;

  EXPECT_EQ(rpc_set.size(), std_set.size());
}

TEST(set_Size, case2) {
  rpc::set<double> rpc_set = {22.2, 44.48, 12.4457, 1.44};

  std::set<double> std_set = {22.2, 44.48, 12.4457, 1.44};

  EXPECT_EQ(rpc_set.size(), std_set.size());
}

TEST(set_swap, case1) {
  rpc::set<double> rpc_set_ref = {22.2, 44.48};
  rpc::set<double> rpc_set_res = {12.4457, 1.44, 22.2};

  rpc_set_ref.swap(rpc_set_res);

  EXPECT_EQ(rpc_set_ref.size(), 3U);
  EXPECT_EQ(*rpc_set_ref.begin(), 1.44);

  EXPECT_EQ(rpc_set_res.size(), 2U);
  EXPECT_EQ(*rpc_set_res.begin(), 22.2);
}

TEST(set_swap, case2) {
  rpc::set<double> rpc_set_ref = {22.2, 44.48};
  rpc::set<double> rpc_set_res;

  rpc_set_ref.swap(rpc_set_res);

  EXPECT_EQ(rpc_set_ref.size(), 0U);

  EXPECT_EQ(rpc_set_res.size(), 2U);
  EXPECT_EQ(*rpc_set_res.begin(), 22.2);
}

TEST(set_swap, case3) {
  rpc::set<double> rpc_set_ref;
  rpc::set<double> rpc_set_res = {12.4457, 1.44, 22.2};

  rpc_set_ref.swap(rpc_set_res);

  EXPECT_EQ(rpc_set_ref.size(), 3U);
  EXPECT_EQ(*rpc_set_ref.begin(), 1.44);

  EXPECT_EQ(rpc_set_res.size(), 0U);
}

TEST(set_swap, case4) {
  rpc::set<double> rpc_set_ref;
  rpc::set<double> rpc_set_res;

  rpc_set_ref.swap(rpc_set_res);

  EXPECT_EQ(rpc_set_ref.size(), 0U);
  EXPECT_EQ(rpc_set_res.size(), 0U);
}

TEST(set_contains, case1) {
  rpc::set<double> rpc_set = {22.2, 44.48};

  EXPECT_EQ(rpc_set.contains(22.2), true);
  EXPECT_EQ(rpc_set.contains(44.48), true);
}

TEST(set_contains, case2) {
  rpc::set<double> rpc_set_ref = {22.2, 44.48};
  rpc::set<double> rpc_set_res;

  rpc_set_ref.swap(rpc_set_res);

  EXPECT_EQ(rpc_set_ref.size(), 0U);
  EXPECT_EQ(rpc_set_ref.contains(22.2), false);
  EXPECT_EQ(rpc_set_ref.contains(44.48), false);

  EXPECT_EQ(rpc_set_res.size(), 2U);
  EXPECT_EQ(rpc_set_res.contains(22.2), true);
  EXPECT_EQ(rpc_set_res.contains(44.48), true);
}

TEST(set_contains, case3) {
  rpc::set<double> rpc_set;

  EXPECT_EQ(rpc_set.size(), 0U);
  EXPECT_EQ(rpc_set.contains(12.4457), false);
}

TEST(set_find, case1) {
  rpc::set<double> rpc_set;

  EXPECT_EQ(rpc_set.find(23.4) == rpc_set.end(), 1);
}

TEST(set_find, case2) {
  rpc::set<double> rpc_set = {12.4457, 1.44, 22.2};

  auto it = rpc_set.begin();
  ++it;
  EXPECT_EQ(*rpc_set.find(12.4457), *it);

  it--;
  EXPECT_EQ(*rpc_set.find(1.44), *it);

  it = it + 2;
  EXPECT_EQ(*rpc_set.find(22.2), *it);
}

TEST(set, insert_many_empty) {
  rpc::set<int> set;
  auto result = set.insert_many();
  EXPECT_EQ(result.size(), 0);
}
TEST(set, insert_many_1) {
  rpc::set<int> set;
  auto result = set.insert_many(5);
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].second, true);
  EXPECT_EQ(set.size(), 1);
}

TEST(set, insert_many_2) {
  rpc::set<std::string> set;
  auto result = set.insert_many("five", "three");
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result[0].second, true);
  EXPECT_EQ(result[1].second, true);
  EXPECT_EQ(set.size(), 2);
}
TEST(set, insert_many_3) {
  rpc::set<std::string> set;
  set.insert("five");
  auto result = set.insert_many("five");
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].second, false);
  EXPECT_EQ(set.size(), 1);
}
TEST(set, insert_many_4) {
  rpc::set<char> set;
  set.max_size();
  set.insert('f');
  auto result = set.insert_many('f');
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].second, false);
  EXPECT_EQ(set.size(), 1);
}