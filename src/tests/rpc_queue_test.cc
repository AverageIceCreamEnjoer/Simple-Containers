#include <queue>

#include "rpc_test.h"

TEST(queue_constructors, case1_default) {
  rpc::queue<int> rpc_q1_int;
  rpc::queue<double> rpc_q1_double;
  rpc::queue<std::string> rpc_q1_string;

  EXPECT_EQ(rpc_q1_int.size(), 0);
  EXPECT_EQ(rpc_q1_double.size(), 0);
  EXPECT_EQ(rpc_q1_string.size(), 0);

  EXPECT_EQ(rpc_q1_int._size, 0);
  EXPECT_EQ(rpc_q1_double._size, 0);
  EXPECT_EQ(rpc_q1_string._size, 0);
}

TEST(queue_constructors, case2_init_list) {
  rpc::queue<int> rpc_q2_int{1, 9, -7, 51};
  rpc::queue<double> rpc_q2_double{14.05, -7.24, 9999.123};
  rpc::queue<std::string> rpc_q2_string{"Mutter", "hat", "den", "Rahmen",
                                        "gewaschen"};
  EXPECT_EQ(rpc_q2_int.size(), 4);
  EXPECT_EQ(rpc_q2_double.size(), 3);
  EXPECT_EQ(rpc_q2_string.size(), 5);

  rpc::queue<int> rpc_q2_int2{};
  rpc::queue<double> rpc_q2_double2{};
  rpc::queue<std::string> rpc_q2_string2{};
  EXPECT_EQ(rpc_q2_int2.size(), 0);
  EXPECT_EQ(rpc_q2_double2.size(), 0);
  EXPECT_EQ(rpc_q2_string2.size(), 0);
}

TEST(queue_constructors, case3_copy) {
  rpc::queue<int> rpc_q3_int{1, 6, 2, 5, 3, 4, 0};
  rpc::queue<int> rpc_q3_int_copy{rpc_q3_int};
  rpc::queue<double> rpc_q3_double{14.05, -7.24, 9999.123};
  rpc::queue<double> rpc_q3_double_copy{rpc_q3_double};
  rpc::queue<std::string> rpc_q3_string{"Mutter", "hat", "den", "Rahmen",
                                        "gewaschen"};
  rpc::queue<std::string> rpc_q3_string_copy{rpc_q3_string};

  EXPECT_EQ(rpc_q3_int.size(), rpc_q3_int_copy.size());
  EXPECT_EQ(rpc_q3_double.size(), rpc_q3_double_copy.size());
  EXPECT_EQ(rpc_q3_string.size(), rpc_q3_string_copy.size());

  for (size_t i = rpc_q3_int.size(); i > 0; i--) {
    ASSERT_EQ(rpc_q3_int.front(), rpc_q3_int_copy.front());
    rpc_q3_int.pop();
    rpc_q3_int_copy.pop();
  }

  for (size_t i = rpc_q3_double.size(); i > 0; i--) {
    ASSERT_EQ(rpc_q3_double.front(), rpc_q3_double_copy.front());
    rpc_q3_double.pop();
    rpc_q3_double_copy.pop();
  }

  for (size_t i = rpc_q3_string.size(); i > 0; i--) {
    ASSERT_EQ(rpc_q3_string.front(), rpc_q3_string_copy.front());
    rpc_q3_string.pop();
    rpc_q3_string_copy.pop();
  }

  rpc::queue<int> rpc_q3_int2;
  rpc::queue<int> rpc_q3_int2_copy{rpc_q3_int2};
  rpc::queue<double> rpc_q3_double2;
  rpc::queue<double> rpc_q3_double2_copy{rpc_q3_double2};
  rpc::queue<std::string> rpc_q3_string2;
  rpc::queue<std::string> rpc_q3_string2_copy{rpc_q3_string2};

  EXPECT_EQ(rpc_q3_int2.size(), rpc_q3_int2_copy.size());
  EXPECT_EQ(rpc_q3_double2.size(), rpc_q3_double2_copy.size());
  EXPECT_EQ(rpc_q3_string2.size(), rpc_q3_string2_copy.size());
}

TEST(queue_constructors, case4_move) {
  rpc::queue<int> rpc_q4_int{2, -6, 12, -3, 41, 0};
  rpc::queue<int> rpc_q4_int_mov = std::move(rpc_q4_int);

  rpc::queue<double> rpc_q4_double{14.05, -7.24, 0.123, -34.0001};
  rpc::queue<double> rpc_q4_double_mov = std::move(rpc_q4_double);

  rpc::queue<std::string> rpc_q4_string{"Mutter", "hat", "den", "Rahmen",
                                        "gewaschen"};
  rpc::queue<std::string> rpc_q4_string_mov = std::move(rpc_q4_string);

  EXPECT_EQ(rpc_q4_int.size(), 0);
  EXPECT_EQ(rpc_q4_int_mov.size(), 6);
  EXPECT_EQ(rpc_q4_double.size(), 0);
  EXPECT_EQ(rpc_q4_double_mov.size(), 4);
  EXPECT_EQ(rpc_q4_string.size(), 0);
  EXPECT_EQ(rpc_q4_string_mov.size(), 5);
}

TEST(queue_constructors, case5_operator) {
  rpc::queue<int> rpc_q5_int{2, -6, 12, -3, 41, 0};
  rpc::queue<int> rpc_q5_int_oper = rpc_q5_int;
  rpc::queue<double> rpc_q5_double{14.05, -7.24, 0.123, -34.0001};
  rpc::queue<double> rpc_q5_double_oper = rpc_q5_double;
  rpc::queue<std::string> rpc_q5_string{"Mutter", "hat", "den", "Rahmen",
                                        "gewaschen"};
  rpc::queue<std::string> rpc_q5_string_oper = rpc_q5_string;

  EXPECT_EQ(rpc_q5_int.size(), rpc_q5_int_oper.size());
  EXPECT_EQ(rpc_q5_double.size(), rpc_q5_double_oper.size());
  EXPECT_EQ(rpc_q5_string.size(), rpc_q5_string_oper.size());

  for (size_t i = rpc_q5_int.size(); i > 0; i--) {
    ASSERT_EQ(rpc_q5_int.front(), rpc_q5_int_oper.front());
    rpc_q5_int.pop();
    rpc_q5_int_oper.pop();
  }

  for (size_t i = rpc_q5_double.size(); i > 0; i--) {
    ASSERT_EQ(rpc_q5_double.front(), rpc_q5_double_oper.front());
    rpc_q5_double.pop();
    rpc_q5_double_oper.pop();
  }

  for (size_t i = rpc_q5_string.size(); i > 0; i--) {
    ASSERT_EQ(rpc_q5_string.front(), rpc_q5_string_oper.front());
    rpc_q5_string.pop();
    rpc_q5_string_oper.pop();
  }

  rpc::queue<int> rpc_q5_int2;
  rpc_q5_int_oper = rpc_q5_int2;
  rpc::queue<double> rpc_q5_double2;
  rpc_q5_double_oper = rpc_q5_double2;
  rpc::queue<std::string> rpc_q5_string2;
  rpc_q5_string_oper = rpc_q5_string2;

  EXPECT_EQ(rpc_q5_int2.size(), rpc_q5_int_oper.size());
  EXPECT_EQ(rpc_q5_double2.size(), rpc_q5_double_oper.size());
  EXPECT_EQ(rpc_q5_string2.size(), rpc_q5_string_oper.size());
}

TEST(queue_modifiers, case6_push) {
  rpc::queue<int> rpc_q6_int;
  std::queue<int> std_q_int;
  rpc_q6_int.push(5);
  rpc_q6_int.push(0);
  std_q_int.push(5);
  std_q_int.push(0);
  EXPECT_EQ(rpc_q6_int.front(), std_q_int.front());
  EXPECT_EQ(rpc_q6_int.back(), std_q_int.back());
  EXPECT_EQ(rpc_q6_int._size, std_q_int.size());
  EXPECT_EQ(rpc_q6_int.empty(), std_q_int.empty());

  rpc::queue<double> rpc_q6_double;
  std::queue<double> std_q_double;
  rpc_q6_double.push(13.09);
  rpc_q6_double.push(-56.23);
  std_q_double.push(13.09);
  std_q_double.push(-56.23);
  EXPECT_EQ(rpc_q6_double.front(), std_q_double.front());
  EXPECT_EQ(rpc_q6_double.back(), std_q_double.back());
  EXPECT_EQ(rpc_q6_double._size, std_q_double.size());
  EXPECT_EQ(rpc_q6_double.empty(), std_q_double.empty());

  rpc::queue<std::string> rpc_q6_string;
  std::queue<std::string> std_q_string;
  rpc_q6_string.push("Hello, ");
  rpc_q6_string.push("world!");
  std_q_string.push("Hello, ");
  std_q_string.push("world!");
  EXPECT_EQ(rpc_q6_string.front(), std_q_string.front());
  EXPECT_EQ(rpc_q6_string.back(), std_q_string.back());
  EXPECT_EQ(rpc_q6_string.size(), std_q_string.size());
  EXPECT_EQ(rpc_q6_string.empty(), std_q_string.empty());
}

TEST(queue_modifiers, case7_pop) {
  rpc::queue<int> rpc_q7_int{4, 8, -3, 75};
  std::queue<int> std_q_int({4, 8, -3, 75});
  for (size_t i = 0; i < rpc_q7_int._size; ++i) {
    rpc_q7_int.pop();
    std_q_int.pop();
    EXPECT_EQ(rpc_q7_int.front(), std_q_int.front());
    EXPECT_EQ(rpc_q7_int.back(), std_q_int.back());
    EXPECT_EQ(rpc_q7_int._size, std_q_int.size());
  }
  EXPECT_EQ(rpc_q7_int.empty(), std_q_int.empty());

  rpc::queue<double> rpc_q7_double{13.09, -56.23, 0.0018};
  std::queue<double> std_q_double({13.09, -56.23, 0.0018});
  for (size_t i = 0; i < rpc_q7_double._size; ++i) {
    rpc_q7_double.pop();
    std_q_double.pop();
    EXPECT_EQ(rpc_q7_double.front(), std_q_double.front());
    EXPECT_EQ(rpc_q7_double.back(), std_q_double.back());
    EXPECT_EQ(rpc_q7_double._size, std_q_double.size());
  }
  EXPECT_EQ(rpc_q7_double.empty(), std_q_double.empty());

  rpc::queue<std::string> rpc_q7_string{"Hello", ", ", "world", "!"};
  std::queue<std::string> std_q_string({"Hello", ", ", "world", "!"});
  for (size_t i = 0; i < rpc_q7_string._size; ++i) {
    rpc_q7_string.pop();
    std_q_string.pop();
    EXPECT_EQ(rpc_q7_string.front(), std_q_string.front());
    EXPECT_EQ(rpc_q7_string.back(), std_q_string.back());
    EXPECT_EQ(rpc_q7_string.size(), std_q_string.size());
  }
  EXPECT_EQ(rpc_q7_string.empty(), std_q_string.empty());
}

TEST(queue_modifiers, case8_swap) {
  rpc::queue<std::string> rpc_q8_str1{"poof", "moo", "zap", "biff", "whiz"};
  rpc::queue<std::string> rpc_q8_str2{"slurp", "meep", "yay", "hiss", "woot"};

  rpc_q8_str1.swap(rpc_q8_str2);

  rpc::queue<std::string> str1_corr{"slurp", "meep", "yay", "hiss", "woot"};
  rpc::queue<std::string> str2_corr{"poof", "moo", "zap", "biff", "whiz"};

  for (size_t i = 0; i < rpc_q8_str1._size; ++i) {
    EXPECT_EQ(rpc_q8_str1.front(), str1_corr.front());
    rpc_q8_str1.pop();
    str1_corr.pop();

    EXPECT_EQ(rpc_q8_str2.front(), str2_corr.front());
    rpc_q8_str2.pop();
    str2_corr.pop();

    EXPECT_EQ(rpc_q8_str1.back(), str1_corr.back());
    EXPECT_EQ(rpc_q8_str2.back(), str2_corr.back());

    EXPECT_EQ(rpc_q8_str1._size, str1_corr.size());
    EXPECT_EQ(rpc_q8_str2._size, str2_corr.size());
  }
  EXPECT_EQ(rpc_q8_str1.empty(), str1_corr.empty());
  EXPECT_EQ(rpc_q8_str2.empty(), str2_corr.empty());
}

TEST(queue_modifiers, case9_insert_many_back) {
  rpc::queue<std::string> rpc_q9_str1{"poof", "moo"};

  rpc_q9_str1.insert_many_back("slurp", "meep", "yay");

  rpc::queue<std::string> str1_corr{"poof", "moo", "slurp", "meep", "yay"};
  for (size_t i = 0; i < rpc_q9_str1._size; ++i) {
    EXPECT_EQ(rpc_q9_str1.front(), str1_corr.front());
    rpc_q9_str1.pop();
    str1_corr.pop();
    EXPECT_EQ(rpc_q9_str1.back(), str1_corr.back());
    EXPECT_EQ(rpc_q9_str1._size, str1_corr.size());
  }
  EXPECT_EQ(rpc_q9_str1.empty(), str1_corr.empty());
}

TEST(queue_exceptions, case10_exceptions) {
  rpc::queue<int> q;
  EXPECT_THROW(q.pop(), std::invalid_argument);
  EXPECT_THROW(q.front(), std::invalid_argument);
  EXPECT_THROW(q.back(), std::invalid_argument);
}