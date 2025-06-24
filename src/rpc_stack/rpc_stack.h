#ifndef RPC_STACK_H
#define RPC_STACK_H

#include <iostream>

namespace rpc {

template <typename T>
class stack {
 public:
  // внутриклассовые переопределения типов
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // основные публичные методы для взаимодействия с классом
  stack() : _top(nullptr) {}

  stack(std::initializer_list<value_type> const &items) {
    _top = nullptr;
    for (auto i : items) push(i);
  }

  stack(const stack &s) {
    stack_node *temp1 = s._top, *temp2;
    _top = new stack_node(temp1->_value);
    temp2 = _top;
    while (temp1->_next) {
      temp2->_next = new stack_node(temp1->_next->_value);
      temp2 = temp2->_next;
      temp1 = temp1->_next;
    }
  }

  stack(stack &&s) : _top(s._top) { s._top = nullptr; }

  ~stack() {
    while (!empty()) pop();
  }

  stack &operator=(const stack &s) {
    if (this != &s) {
      while (!empty()) pop();
      stack_node *temp1 = s._top, *temp2;
      _top = new stack_node(temp1->_value);
      temp2 = _top;
      while (temp1->_next) {
        temp2->_next = new stack_node(temp1->_next->_value);
        temp2 = temp2->_next;
        temp1 = temp1->_next;
      }
    }
    return *this;
  }

  stack &operator=(stack &&s) {
    if (this != &s) {
      while (!empty()) pop();
      _top = s._top;
      s._top = nullptr;
    }
    return *this;
  }

  // публичные методы для доступа к элементам класса
  const_reference top() { return _top->_value; }

  // публичные методы для доступа к информации о наполнении контейнера
  bool empty() { return _top == nullptr; }

  size_type size() {
    size_type res = 0;
    for (stack_node *temp = _top; temp; temp = temp->_next) res++;
    return res;
  }

  // публичные методы для изменения контейнера
  void push(const_reference value) {
    stack_node *temp = new stack_node(value);
    temp->_next = _top;
    _top = temp;
  }

  void pop() {
    if (_top) {
      stack_node *temp = _top->_next;
      delete _top;
      _top = temp;
    }
  }

  void swap(stack &other) {
    stack_node *temp = _top;
    _top = other._top;
    other._top = temp;
  }

  // Extra
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &arg : {args...}) {
      push(arg);
    }
  };

 private:
  struct stack_node {
    value_type _value;
    stack_node *_next;

    stack_node(value_type val) {
      _value = val;
      _next = nullptr;
    }
  };
  stack_node *_top;
};

}  // namespace rpc

#endif