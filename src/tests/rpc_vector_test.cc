#include <vector>

#include "rpc_test.h"

TEST(vector_constructors, case1_default) {
  rpc::vector<int> rpc_v1_int;
  rpc::vector<double> rpc_v1_double;
  rpc::vector<std::string> rpc_v1_string;

  EXPECT_EQ(rpc_v1_int.size(), 0);
  EXPECT_EQ(rpc_v1_double.size(), 0);
  EXPECT_EQ(rpc_v1_string.size(), 0);

  EXPECT_EQ(rpc_v1_int._size, 0);
  EXPECT_EQ(rpc_v1_double._size, 0);
  EXPECT_EQ(rpc_v1_string._size, 0);
}

TEST(vector_constructors, case2_size_n) {
  rpc::vector<int> rpc_v2_int(5);
  rpc::vector<double> rpc_v2_double(8);
  rpc::vector<std::string> rpc_v2_string(3);

  EXPECT_EQ(rpc_v2_int.size(), 5);
  EXPECT_EQ(rpc_v2_double.size(), 8);
  EXPECT_EQ(rpc_v2_string.size(), 3);

  EXPECT_EQ(rpc_v2_int._size, 5);
  EXPECT_EQ(rpc_v2_double._size, 8);
  EXPECT_EQ(rpc_v2_string._size, 3);

  EXPECT_EQ(rpc_v2_int.capacity(), 5);
  EXPECT_EQ(rpc_v2_double.capacity(), 8);
  EXPECT_EQ(rpc_v2_string.capacity(), 3);

  EXPECT_EQ(rpc_v2_int._capacity, 5);
  EXPECT_EQ(rpc_v2_double._capacity, 8);
  EXPECT_EQ(rpc_v2_string._capacity, 3);

  for (size_t i = 0; i < rpc_v2_int.size(); ++i) {
    EXPECT_EQ(rpc_v2_int[i], 0);
  }
  for (size_t i = 0; i < rpc_v2_double.size(); ++i) {
    EXPECT_EQ(rpc_v2_double[i], 0.0);
  }
  for (size_t i = 0; i < rpc_v2_string.size(); ++i) {
    EXPECT_EQ(rpc_v2_string[i], "");
  }
}

TEST(vector_constructors, case3_list_init) {
  rpc::vector<int> rpc_v3_int{1, 3, 5, 7, 9};
  rpc::vector<double> rpc_v3_double{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<char> rpc_v3_char{'a', 'b', 'c'};
  rpc::vector<std::string> rpc_v3_string{"Red", "Green", "Blue"};

  EXPECT_EQ(rpc_v3_int.size(), 5);
  EXPECT_EQ(rpc_v3_double.size(), 4);
  EXPECT_EQ(rpc_v3_char.size(), 3);
  EXPECT_EQ(rpc_v3_string.size(), 3);

  EXPECT_EQ(rpc_v3_int._size, 5);
  EXPECT_EQ(rpc_v3_double._size, 4);
  EXPECT_EQ(rpc_v3_char._size, 3);
  EXPECT_EQ(rpc_v3_string._size, 3);

  EXPECT_EQ(rpc_v3_int.capacity(), 5);
  EXPECT_EQ(rpc_v3_double.capacity(), 4);
  EXPECT_EQ(rpc_v3_char.capacity(), 3);
  EXPECT_EQ(rpc_v3_string.capacity(), 3);

  EXPECT_EQ(rpc_v3_int._capacity, 5);
  EXPECT_EQ(rpc_v3_double._capacity, 4);
  EXPECT_EQ(rpc_v3_char._capacity, 3);
  EXPECT_EQ(rpc_v3_string._capacity, 3);

  EXPECT_EQ(rpc_v3_int[0], 1);
  EXPECT_EQ(rpc_v3_int[1], 3);
  EXPECT_EQ(rpc_v3_int[2], 5);
  EXPECT_EQ(rpc_v3_int[3], 7);
  EXPECT_EQ(rpc_v3_int[4], 9);

  EXPECT_EQ(rpc_v3_double[0], 0.5);
  EXPECT_EQ(rpc_v3_double[1], 14.3);
  EXPECT_EQ(rpc_v3_double[2], -78.013);
  EXPECT_EQ(rpc_v3_double[3], 5.19065);

  EXPECT_EQ(rpc_v3_char[0], 'a');
  EXPECT_EQ(rpc_v3_char[1], 'b');
  EXPECT_EQ(rpc_v3_char[2], 'c');

  EXPECT_EQ(rpc_v3_string[0], "Red");
  EXPECT_EQ(rpc_v3_string[1], "Green");
  EXPECT_EQ(rpc_v3_string[2], "Blue");
}

TEST(vector_constructors, case4_copy) {
  rpc::vector<int> rpc_v4_int_src{1, 3, 5, 7, 9};
  rpc::vector<int> rpc_v4_int_trg = rpc_v4_int_src;

  rpc::vector<double> rpc_v4_double_src{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<double> rpc_v4_double_trg = rpc_v4_double_src;

  rpc::vector<char> rpc_v4_char_src{'a', 'b', 'c'};
  rpc::vector<char> rpc_v4_char_trg = rpc_v4_char_src;

  rpc::vector<std::string> rpc_v4_string_src{"Red", "Green", "Blue"};
  rpc::vector<std::string> rpc_v4_string_trg = rpc_v4_string_src;

  EXPECT_EQ(rpc_v4_int_src.size(), rpc_v4_int_trg.size());
  EXPECT_EQ(rpc_v4_double_src.size(), rpc_v4_double_trg.size());
  EXPECT_EQ(rpc_v4_char_src._size, rpc_v4_char_trg._size);
  EXPECT_EQ(rpc_v4_string_src._size, rpc_v4_string_trg._size);

  EXPECT_EQ(rpc_v4_int_src.capacity(), rpc_v4_int_trg.capacity());
  EXPECT_EQ(rpc_v4_double_src.capacity(), rpc_v4_double_trg.capacity());
  EXPECT_EQ(rpc_v4_char_src._capacity, rpc_v4_char_trg._capacity);
  EXPECT_EQ(rpc_v4_string_src._capacity, rpc_v4_string_trg._capacity);

  for (size_t i = 0; i < rpc_v4_int_trg._size; ++i) {
    EXPECT_EQ(rpc_v4_int_src[i], rpc_v4_int_trg[i]);
  }
  for (size_t i = 0; i < rpc_v4_double_trg._size; ++i) {
    EXPECT_EQ(rpc_v4_double_src[i], rpc_v4_double_trg[i]);
  }
  for (size_t i = 0; i < rpc_v4_char_trg._size; ++i) {
    EXPECT_EQ(rpc_v4_char_src[i], rpc_v4_char_trg[i]);
  }
  for (size_t i = 0; i < rpc_v4_string_trg._size; ++i) {
    EXPECT_EQ(rpc_v4_string_src[i], rpc_v4_string_trg[i]);
  }
}

TEST(vector_constructors, case5_move) {
  rpc::vector<int> rpc_v5_int_src{1, 3, 5, 7, 9};
  rpc::vector<int> rpc_v5_int_trg = std::move(rpc_v5_int_src);

  rpc::vector<double> rpc_v5_double_src{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<double> rpc_v5_double_trg = std::move(rpc_v5_double_src);

  rpc::vector<char> rpc_v5_char_src{'a', 'b', 'c'};
  rpc::vector<char> rpc_v5_char_trg = std::move(rpc_v5_char_src);

  rpc::vector<std::string> rpc_v5_string_src{"Red", "Green", "Blue"};
  rpc::vector<std::string> rpc_v5_string_trg = std::move(rpc_v5_string_src);

  EXPECT_EQ(rpc_v5_int_src.size(), 0);
  EXPECT_EQ(rpc_v5_int_trg.size(), 5);
  EXPECT_EQ(rpc_v5_double_src.size(), 0);
  EXPECT_EQ(rpc_v5_double_trg.size(), 4);
  EXPECT_EQ(rpc_v5_char_src._size, 0);
  EXPECT_EQ(rpc_v5_char_trg._size, 3);
  EXPECT_EQ(rpc_v5_string_src._size, 0);
  EXPECT_EQ(rpc_v5_string_trg._size, 3);

  EXPECT_EQ(rpc_v5_int_src.capacity(), 0);
  EXPECT_EQ(rpc_v5_int_trg.capacity(), 5);
  EXPECT_EQ(rpc_v5_double_src.capacity(), 0);
  EXPECT_EQ(rpc_v5_double_trg.capacity(), 4);
  EXPECT_EQ(rpc_v5_char_src._capacity, 0);
  EXPECT_EQ(rpc_v5_char_trg._capacity, 3);
  EXPECT_EQ(rpc_v5_string_src._capacity, 0);
  EXPECT_EQ(rpc_v5_string_trg._capacity, 3);

  EXPECT_EQ(rpc_v5_int_trg[0], 1);
  EXPECT_EQ(rpc_v5_int_trg[1], 3);
  EXPECT_EQ(rpc_v5_int_trg[2], 5);
  EXPECT_EQ(rpc_v5_int_trg[3], 7);
  EXPECT_EQ(rpc_v5_int_trg[4], 9);

  EXPECT_EQ(rpc_v5_double_trg[0], 0.5);
  EXPECT_EQ(rpc_v5_double_trg[1], 14.3);
  EXPECT_EQ(rpc_v5_double_trg[2], -78.013);
  EXPECT_EQ(rpc_v5_double_trg[3], 5.19065);

  EXPECT_EQ(rpc_v5_char_trg[0], 'a');
  EXPECT_EQ(rpc_v5_char_trg[1], 'b');
  EXPECT_EQ(rpc_v5_char_trg[2], 'c');

  EXPECT_EQ(rpc_v5_string_trg[0], "Red");
  EXPECT_EQ(rpc_v5_string_trg[1], "Green");
  EXPECT_EQ(rpc_v5_string_trg[2], "Blue");
}

TEST(vector_constructors, case6_assighnment_oper) {
  rpc::vector<int> rpc_v6_int_src{1, 3, 5, 7, 9}, rpc_v6_int_trg;
  rpc_v6_int_trg = rpc_v6_int_src;

  rpc::vector<double> rpc_v6_double_src{0.5, 14.3, -78.013, 5.19065},
      rpc_v6_double_trg;
  rpc_v6_double_trg = rpc_v6_double_src;

  rpc::vector<char> rpc_v6_char_src{'a', 'b', 'c'}, rpc_v6_char_trg;
  rpc_v6_char_trg = rpc_v6_char_src;

  rpc::vector<std::string> rpc_v6_string_src{"Red", "Green", "Blue"},
      rpc_v6_string_trg;
  rpc_v6_string_trg = rpc_v6_string_src;

  EXPECT_EQ(rpc_v6_int_src.size(), rpc_v6_int_trg.size());
  EXPECT_EQ(rpc_v6_double_src.size(), rpc_v6_double_trg.size());
  EXPECT_EQ(rpc_v6_char_src._size, rpc_v6_char_trg._size);
  EXPECT_EQ(rpc_v6_string_src._size, rpc_v6_string_trg._size);

  EXPECT_EQ(rpc_v6_int_src.capacity(), rpc_v6_int_trg.capacity());
  EXPECT_EQ(rpc_v6_double_src.capacity(), rpc_v6_double_trg.capacity());
  EXPECT_EQ(rpc_v6_char_src._capacity, rpc_v6_char_trg._capacity);
  EXPECT_EQ(rpc_v6_string_src._capacity, rpc_v6_string_trg._capacity);

  for (size_t i = 0; i < rpc_v6_int_trg._size; ++i) {
    EXPECT_EQ(rpc_v6_int_src[i], rpc_v6_int_trg[i]);
  }
  for (size_t i = 0; i < rpc_v6_double_trg._size; ++i) {
    EXPECT_EQ(rpc_v6_double_src[i], rpc_v6_double_trg[i]);
  }
  for (size_t i = 0; i < rpc_v6_char_trg._size; ++i) {
    EXPECT_EQ(rpc_v6_char_src[i], rpc_v6_char_trg[i]);
  }
  for (size_t i = 0; i < rpc_v6_string_trg._size; ++i) {
    EXPECT_EQ(rpc_v6_string_src[i], rpc_v6_string_trg[i]);
  }

  rpc::vector<int> V1{0, 0, 0};
  V1 = V1;  //  присваивание самому себе
}

TEST(vector_access, case7_at) {
  rpc::vector<int> rpc_v7_int{1, 3, 5, 7, 9};
  rpc::vector<double> rpc_v7_double{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<char> rpc_v7_char{'a', 'b', 'c'};
  rpc::vector<std::string> rpc_v7_string{"Red", "Green", "Blue"};

  EXPECT_EQ(rpc_v7_int.at(0), 1);
  EXPECT_EQ(rpc_v7_int.at(1), 3);
  EXPECT_EQ(rpc_v7_int.at(2), 5);
  EXPECT_EQ(rpc_v7_int.at(3), 7);
  EXPECT_EQ(rpc_v7_int.at(4), 9);

  EXPECT_EQ(rpc_v7_double.at(0), 0.5);
  EXPECT_EQ(rpc_v7_double.at(1), 14.3);
  EXPECT_EQ(rpc_v7_double.at(2), -78.013);
  EXPECT_EQ(rpc_v7_double.at(3), 5.19065);

  EXPECT_EQ(rpc_v7_char.at(0), 'a');
  EXPECT_EQ(rpc_v7_char.at(1), 'b');
  EXPECT_EQ(rpc_v7_char.at(2), 'c');

  EXPECT_EQ(rpc_v7_string.at(0), "Red");
  EXPECT_EQ(rpc_v7_string.at(1), "Green");
  EXPECT_EQ(rpc_v7_string.at(2), "Blue");
}

TEST(vector_access, case8_brackets_opers) {
  rpc::vector<int> rpc_v8_int{1, 3, 5, 7, 9};
  rpc::vector<double> rpc_v8_double{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<char> rpc_v8_char{'a', 'b', 'c'};
  rpc::vector<std::string> rpc_v8_string{"Red", "Green", "Blue"};

  const int x = rpc_v8_int[0];
  EXPECT_EQ(x, 1);
  EXPECT_EQ(rpc_v8_int[1], 3);
  EXPECT_EQ(rpc_v8_int[2], 5);
  EXPECT_EQ(rpc_v8_int[3], 7);
  EXPECT_EQ(rpc_v8_int[4], 9);

  const double y = rpc_v8_double[0];
  EXPECT_EQ(y, 0.5);
  EXPECT_EQ(rpc_v8_double[1], 14.3);
  EXPECT_EQ(rpc_v8_double[2], -78.013);
  EXPECT_EQ(rpc_v8_double[3], 5.19065);

  const char z = rpc_v8_char[0];
  EXPECT_EQ(z, 'a');
  EXPECT_EQ(rpc_v8_char[1], 'b');
  EXPECT_EQ(rpc_v8_char[2], 'c');

  const std::string s = rpc_v8_string[0];
  EXPECT_EQ(s, "Red");
  EXPECT_EQ(rpc_v8_string[1], "Green");
  EXPECT_EQ(rpc_v8_string[2], "Blue");
}

TEST(vector_access, case9_data) {
  rpc::vector<int> rpc_v9_int{1, 3, 5, 7, 9};
  rpc::vector<double> rpc_v9_double{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<char> rpc_v9_char{'a', 'b', 'c'};
  rpc::vector<std::string> rpc_v9_string{"Red", "Green", "Blue"};

  int *A = rpc_v9_int.data();
  for (size_t i = 0; i < rpc_v9_int.size(); ++i) {
    EXPECT_EQ(rpc_v9_int[i], A[i]);
  }

  double *D = rpc_v9_double.data();
  for (size_t i = 0; i < rpc_v9_double.size(); ++i) {
    EXPECT_EQ(rpc_v9_double[i], D[i]);
  }

  char *C = rpc_v9_char.data();
  for (size_t i = 0; i < rpc_v9_char.size(); ++i) {
    EXPECT_EQ(rpc_v9_char[i], C[i]);
  }

  std::string *S = rpc_v9_string.data();
  for (size_t i = 0; i < rpc_v9_string.size(); ++i) {
    EXPECT_EQ(rpc_v9_string[i], S[i]);
  }
}

TEST(vector_access, case10_front_back) {
  rpc::vector<int> rpc_v10_int{1, 3, 5, 7, 9};
  rpc::vector<double> rpc_v10_double{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<char> rpc_v10_char{'a', 'b', 'c'};
  rpc::vector<std::string> rpc_v10_string{"Red", "Green", "Blue"};

  EXPECT_EQ(rpc_v10_int.front(), 1);
  EXPECT_EQ(rpc_v10_int.back(), 9);

  EXPECT_EQ(rpc_v10_double.front(), 0.5);
  EXPECT_EQ(rpc_v10_double.back(), 5.19065);

  EXPECT_EQ(rpc_v10_char.front(), 'a');
  EXPECT_EQ(rpc_v10_char.back(), 'c');

  EXPECT_EQ(rpc_v10_string.front(), "Red");
  EXPECT_EQ(rpc_v10_string.back(), "Blue");
}

TEST(vector_iterators, case11_begin) {
  rpc::vector<int> rpc_v11_int{1, 2, 3};
  rpc::vector<int>::iterator it1 = rpc_v11_int.begin();
  EXPECT_EQ(*it1, 1);
  ++it1;
  EXPECT_EQ(*it1, 2);
  ++it1;
  EXPECT_EQ(*it1, 3);
  *it1 = 10;  // записать новое значение в массив
  EXPECT_EQ(rpc_v11_int[2], 10);

  rpc::vector<double> rpc_v11_double{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<double>::iterator it2 = rpc_v11_double.begin();
  EXPECT_EQ(*it2, 0.5);
  ++it2;
  EXPECT_EQ(*it2, 14.3);
  ++it2;
  EXPECT_EQ(*it2, -78.013);
  ++it2;
  EXPECT_EQ(*it2, 5.19065);
  *it2 = 0.0001;  // записать новое значение в массив
  EXPECT_EQ(rpc_v11_double[3], 0.0001);

  rpc::vector<char> rpc_v11_char{'a', 'b', 'c'};
  rpc::vector<char>::iterator it3 = rpc_v11_char.begin();
  EXPECT_EQ(*it3, 'a');
  ++it3;
  EXPECT_EQ(*it3, 'b');
  ++it3;
  EXPECT_EQ(*it3, 'c');
  *it3 = '$';  // записать новое значение в массив
  EXPECT_EQ(rpc_v11_char[2], '$');

  rpc::vector<std::string> rpc_v11_string{"Red", "Green", "Blue"};
  rpc::vector<std::string>::iterator it4 = rpc_v11_string.begin();
  EXPECT_EQ(*it4, "Red");
  ++it4;
  EXPECT_EQ(*it4, "Green");
  ++it4;
  EXPECT_EQ(*it4, "Blue");
  *it4 = "Orange";  // записать новое значение в массив
  EXPECT_EQ(rpc_v11_string[2], "Orange");
}

TEST(vector_iterators, case12_end_dec) {
  rpc::vector<int> rpc_v12_int{1, 2, 3};
  rpc::vector<int>::iterator it1 = rpc_v12_int.end();
  --it1;
  EXPECT_EQ(*it1, 3);
  --it1;
  EXPECT_EQ(*it1, 2);
  --it1;
  EXPECT_EQ(*it1, 1);
  *it1 = 10;  // записать новое значение в массив
  EXPECT_EQ(rpc_v12_int[0], 10);

  rpc::vector<double> rpc_v12_double{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<double>::iterator it2 = rpc_v12_double.end();
  --it2;
  EXPECT_EQ(*it2, 5.19065);
  --it2;
  EXPECT_EQ(*it2, -78.013);
  --it2;
  EXPECT_EQ(*it2, 14.3);
  --it2;
  EXPECT_EQ(*it2, 0.5);
  *it2 = 0.0001;  // записать новое значение в массив
  EXPECT_EQ(rpc_v12_double[0], 0.0001);

  rpc::vector<char> rpc_v12_char{'a', 'b', 'c'};
  rpc::vector<char>::iterator it3 = rpc_v12_char.end();
  --it3;
  EXPECT_EQ(*it3, 'c');
  --it3;
  EXPECT_EQ(*it3, 'b');
  --it3;
  EXPECT_EQ(*it3, 'a');
  *it3 = '$';  // записать новое значение в массив
  EXPECT_EQ(rpc_v12_char[0], '$');

  rpc::vector<std::string> rpc_v12_string{"Red", "Green", "Blue"};
  rpc::vector<std::string>::iterator it4 = rpc_v12_string.end();
  --it4;
  EXPECT_EQ(*it4, "Blue");
  --it4;
  EXPECT_EQ(*it4, "Green");
  --it4;
  EXPECT_EQ(*it4, "Red");
  *it4 = "Orange";  // записать новое значение в массив
  EXPECT_EQ(rpc_v12_string[0], "Orange");
}

TEST(vector_capacity, case13_empty) {
  rpc::vector<int> rpc_v13_int{1, 3, 5, 7, 9};
  rpc::vector<double> rpc_v13_double{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<char> rpc_v13_char{'a', 'b', 'c'};
  rpc::vector<std::string> rpc_v13_string{"Red", "Green", "Blue"};
  EXPECT_EQ(rpc_v13_int.empty(), 0);
  EXPECT_EQ(rpc_v13_double.empty(), 0);
  EXPECT_EQ(rpc_v13_char.empty(), 0);
  EXPECT_EQ(rpc_v13_string.empty(), 0);

  rpc::vector<int> rpc_v13_int2{};
  rpc::vector<double> rpc_v13_double2{};
  rpc::vector<char> rpc_v13_char2{};
  rpc::vector<std::string> rpc_v13_string2{};
  EXPECT_EQ(rpc_v13_int2.empty(), 1);
  EXPECT_EQ(rpc_v13_double2.empty(), 1);
  EXPECT_EQ(rpc_v13_char2.empty(), 1);
  EXPECT_EQ(rpc_v13_string2.empty(), 1);
}

TEST(vector_capacity, case14_max_size) {
  rpc::vector<int> rpc_v14_int{1, 3, 5, 7, 9};
  rpc::vector<double> rpc_v14_double{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<char> rpc_v14_char{'a', 'b', 'c'};
  rpc::vector<std::string> rpc_v14_string{"Red", "Green", "Blue"};

  EXPECT_EQ(rpc_v14_int.max_size(), 4611686018427387903U);
  EXPECT_EQ(rpc_v14_double.max_size(), 2305843009213693951U);
  EXPECT_EQ(rpc_v14_char.max_size(), 18446744073709551615U);
  EXPECT_EQ(rpc_v14_string.max_size(), 576460752303423487U);
}

TEST(vector_capacity, case15_reserve) {
  rpc::vector<int> rpc_v15_int{1, 2, 3};
  size_t initialCapacity = rpc_v15_int.capacity();
  size_t newCapacity = initialCapacity + 10;
  rpc_v15_int.reserve(newCapacity);
  EXPECT_EQ(rpc_v15_int.capacity(), newCapacity);

  rpc::vector<int> rpc_v15_int2 = {1, 2, 3, 4, 5};
  initialCapacity = rpc_v15_int2.capacity();
  newCapacity = initialCapacity - 2;
  rpc_v15_int2.reserve(newCapacity);
  EXPECT_EQ(rpc_v15_int2.capacity(), initialCapacity);
  EXPECT_GE(rpc_v15_int2.capacity(), newCapacity);
}

TEST(vector_capacity, case16_shrink_to_fit) {
  rpc::vector<int> rpc_v16_int;
  rpc_v16_int.shrink_to_fit();
  EXPECT_GE((int)rpc_v16_int.capacity(), 0);

  rpc::vector<int> rpc_v16_int2{1, 2, 3, 4, 5};
  rpc_v16_int.shrink_to_fit();
  EXPECT_EQ(rpc_v16_int.capacity(), rpc_v16_int.size());

  rpc::vector<int> rpc_v16_int3{1, 2, 3, 4, 5};
  size_t initialCapacity = rpc_v16_int3.capacity();
  rpc_v16_int3.pop_back();
  rpc_v16_int3.shrink_to_fit();
  EXPECT_LE(rpc_v16_int3.capacity(), rpc_v16_int3.size());
  EXPECT_LE(rpc_v16_int3.capacity(), initialCapacity);
}

TEST(vector_modifiers, case17_clear) {
  rpc::vector<int> rpc_v17_int{1, 3, 5, 7, 9};
  rpc::vector<double> rpc_v17_double{0.5, 14.3, -78.013, 5.19065};
  rpc::vector<char> rpc_v17_char{'a', 'b', 'c'};
  rpc::vector<std::string> rpc_v17_string{"Red", "Green", "Blue"};
  EXPECT_EQ(rpc_v17_int.empty(), 0);
  EXPECT_EQ(rpc_v17_double.empty(), 0);
  EXPECT_EQ(rpc_v17_char.empty(), 0);
  EXPECT_EQ(rpc_v17_string.empty(), 0);

  rpc_v17_int.clear();
  rpc_v17_double.clear();
  rpc_v17_char.clear();
  rpc_v17_string.clear();
  EXPECT_EQ(rpc_v17_int.empty(), 1);
  EXPECT_EQ(rpc_v17_double.empty(), 1);
  EXPECT_EQ(rpc_v17_char.empty(), 1);
  EXPECT_EQ(rpc_v17_string.empty(), 1);
}

TEST(vector_modifiers, case18_insert) {
  // в начало
  rpc::vector<int> rpc_v18_int{1, 3, 5, 7, 9};
  rpc::vector<int>::iterator it = rpc_v18_int.insert(rpc_v18_int.begin(), 13);
  EXPECT_EQ(rpc_v18_int.size(), 6);
  EXPECT_EQ(rpc_v18_int[0], 13);
  EXPECT_EQ(*it, 13);

  // в середину
  it = rpc_v18_int.insert(rpc_v18_int.begin() + 3, 27);
  EXPECT_EQ(rpc_v18_int.size(), 7);
  EXPECT_EQ(rpc_v18_int[3], 27);
  EXPECT_EQ(*it, 27);

  // в конец
  it = rpc_v18_int.insert(rpc_v18_int.begin() + rpc_v18_int.size(), 101);
  EXPECT_EQ(rpc_v18_int.size(), 8);
  EXPECT_EQ(rpc_v18_int[rpc_v18_int.size() - 1], 101);
  EXPECT_EQ(*it, 101);

  rpc::vector<int> rpc_v18_int_corr{13, 1, 3, 27, 5, 7, 9, 101};
  for (size_t i = 0; i < rpc_v18_int_corr.size(); ++i) {
    EXPECT_EQ(rpc_v18_int[i], rpc_v18_int_corr[i]);
  }
}

TEST(vector_modifiers, case19_erase) {
  // первый
  rpc::vector<char> rpc_v19_char1 = {'w', 'a', 'b', 'c', 'd', 'e'};
  rpc::vector<char> rpc_v19_char2 = {'a', 'b', 'c', 'd', 'e'};
  auto it = rpc_v19_char1.begin();
  rpc_v19_char1.erase(it);
  auto it1 = rpc_v19_char1.begin();
  auto it2 = rpc_v19_char2.begin();
  while (it1 != rpc_v19_char1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(rpc_v19_char1.size(), rpc_v19_char2.size());

  // последний
  rpc::vector<int> rpc_v19_char3 = {'a', 'b', 'c', 'd'};
  it = rpc_v19_char1.end();
  --it;
  rpc_v19_char1.erase(it);
  it1 = rpc_v19_char1.begin();
  auto it3 = rpc_v19_char3.begin();
  while (it1 != rpc_v19_char1.end()) {
    EXPECT_EQ(*it1, *it3);
    ++it1, ++it3;
  }
  EXPECT_EQ(rpc_v19_char1.size(), rpc_v19_char3.size());

  // в середине
  rpc::vector<int> rpc_v19_char4 = {'a', 'b', 'd'};
  it = rpc_v19_char1.begin();
  it += 2;
  rpc_v19_char1.erase(it);
  it1 = rpc_v19_char1.begin();
  auto it4 = rpc_v19_char4.begin();
  while (it1 != rpc_v19_char1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  EXPECT_EQ(rpc_v19_char1.size(), rpc_v19_char4.size());
}

TEST(vector_modifiers, case20_push_back) {
  rpc::vector<int> rpc_v20_int1{1, 2, 3};
  std::vector<int> rpc_v20_int2{1, 2, 3};
  rpc_v20_int1.push_back(4);
  rpc_v20_int2.push_back(4);
  EXPECT_EQ(rpc_v20_int1.size(), rpc_v20_int2.size());
  for (size_t i = 0; i < rpc_v20_int1.size(); ++i) {
    EXPECT_EQ(rpc_v20_int1[i], rpc_v20_int2[i]);
  }

  // empty vector
  rpc::vector<double> rpc_v20_double;
  rpc_v20_double.push_back(404.4);
  rpc_v20_double.push_back(312.07);
  EXPECT_EQ(rpc_v20_double.size(), 2);
  EXPECT_EQ(rpc_v20_double[0], 404.4);
  EXPECT_EQ(rpc_v20_double[1], 312.07);
}

TEST(vector_modifiers, case21_pop_back) {
  rpc::vector<int> rpc_v21_int1{1, 3, 5, 7, 9};
  EXPECT_EQ(rpc_v21_int1.size(), 5);
  EXPECT_EQ(rpc_v21_int1.back(), 9);

  rpc_v21_int1.pop_back();
  EXPECT_EQ(rpc_v21_int1.size(), 4);
  EXPECT_EQ(rpc_v21_int1.back(), 7);

  rpc_v21_int1.pop_back();
  EXPECT_EQ(rpc_v21_int1.size(), 3);
  EXPECT_EQ(rpc_v21_int1.back(), 5);

  rpc_v21_int1.pop_back();
  EXPECT_EQ(rpc_v21_int1.size(), 2);
  EXPECT_EQ(rpc_v21_int1.back(), 3);

  rpc_v21_int1.pop_back();
  EXPECT_EQ(rpc_v21_int1.size(), 1);
  EXPECT_EQ(rpc_v21_int1.back(), 1);

  rpc_v21_int1.pop_back();
  EXPECT_EQ(rpc_v21_int1.size(), 0);
  EXPECT_EQ(rpc_v21_int1.empty(), 1);
}

TEST(vector_modifiers, case22_swap) {
  rpc::vector<int> rpc_v22_int1{1, 3, 5, 7, 9},
      rpc_v22_int2{34, 68, 901, -1025, 183}, rpc_v22_int3{27, 25}, rpc_v22_int4;
  rpc::vector<int> rpc_v22_corr1{1, 3, 5, 7, 9},
      rpc_v22_corr2{34, 68, 901, -1025, 183}, rpc_v22_corr3{27, 25},
      rpc_v22_corr4;

  rpc_v22_int1.swap(rpc_v22_int2);
  EXPECT_EQ(rpc_v22_int1.size(), rpc_v22_corr2.size());
  EXPECT_EQ(rpc_v22_int2.size(), rpc_v22_corr1.size());
  for (size_t i = 0; i < rpc_v22_corr2.size(); ++i) {
    EXPECT_EQ(rpc_v22_int1[i], rpc_v22_corr2[i]);
  }
  for (size_t i = 0; i < rpc_v22_corr1.size(); ++i) {
    EXPECT_EQ(rpc_v22_int2[i], rpc_v22_corr1[i]);
  }

  rpc_v22_int1.swap(rpc_v22_int3);
  EXPECT_EQ(rpc_v22_int1.size(), rpc_v22_corr3.size());
  EXPECT_EQ(rpc_v22_int3.size(), rpc_v22_corr2.size());
  for (size_t i = 0; i < rpc_v22_corr3.size(); ++i) {
    EXPECT_EQ(rpc_v22_int1[i], rpc_v22_corr3[i]);
  }
  for (size_t i = 0; i < rpc_v22_corr2.size(); ++i) {
    EXPECT_EQ(rpc_v22_int3[i], rpc_v22_corr2[i]);
  }

  rpc_v22_int1.swap(rpc_v22_int4);
  EXPECT_EQ(rpc_v22_int1.size(), rpc_v22_corr4.size());
  EXPECT_EQ(rpc_v22_int4.size(), rpc_v22_corr3.size());

  rpc_v22_int1.swap(rpc_v22_int3);
  EXPECT_EQ(rpc_v22_int1.size(), rpc_v22_corr2.size());
  EXPECT_EQ(rpc_v22_int3.size(), rpc_v22_corr4.size());
  for (size_t i = 0; i < rpc_v22_corr2.size(); ++i) {
    EXPECT_EQ(rpc_v22_int1[i], rpc_v22_corr2[i]);
  }
}

TEST(vector_bonus, case23_insert_many) {
  rpc::vector<int> rpc_v23_int = {1, 2, 3, 7, 8};
  rpc::vector<int> rpc_v23_int_corr = {1, 2, 3, 4, 5, 6, 7, 8};
  rpc::vector<int>::const_iterator pos = rpc_v23_int.cbegin() + 3;

  rpc_v23_int.insert_many(pos, 4, 5, 6);

  EXPECT_EQ(rpc_v23_int.size(), rpc_v23_int_corr.size());
  for (size_t i = 0; i < rpc_v23_int.size(); ++i) {
    EXPECT_EQ(rpc_v23_int[i], rpc_v23_int_corr[i]);
  }
}

TEST(vector_bonus, case24_insert_many_back) {
  rpc::vector<int> rpc_v24_int = {1, 2, 3};
  rpc::vector<int> rpc_v24_int_corr = {1, 2, 3, 4, 5, 6};

  rpc_v24_int.insert_many_back(4, 5, 6);

  EXPECT_EQ(rpc_v24_int.size(), rpc_v24_int_corr.size());
  for (size_t i = 0; i < rpc_v24_int.size(); ++i) {
    EXPECT_EQ(rpc_v24_int[i], rpc_v24_int_corr[i]);
  }
}

TEST(vector_exceptions, case99_exceptions) {
  rpc::vector<int> V1{3, 8, 15};
  rpc::vector<char> V2;
  EXPECT_THROW(V1.at(6), std::out_of_range);
  EXPECT_THROW(V1[-6], std::out_of_range);
  EXPECT_THROW(V2.front(), std::out_of_range);
  EXPECT_THROW(V2.back(), std::out_of_range);
  EXPECT_THROW(V1.reserve(V1.max_size() + 1), std::out_of_range);

  rpc::vector<int>::iterator it = V1.begin();
  EXPECT_THROW(V1.insert(it + 4, 15), std::out_of_range);

  it = V1.begin();
  EXPECT_THROW(V1.erase(it + 4), std::out_of_range);
  EXPECT_THROW(V2.erase(0), std::out_of_range);
  EXPECT_THROW(V2.pop_back(), std::length_error);
}