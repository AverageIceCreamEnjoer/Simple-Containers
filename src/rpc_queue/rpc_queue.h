#ifndef RPC_QUEUE_H
#define RPC_QUEUE_H

#include <cstddef>
#include <iostream>

namespace rpc {

/// @brief Шаблонный класс для контейнера "очередь" (queue)
/// @tparam T - тип элементов, содержащихся в контейнере
template <typename T>
class queue {
 public:
  // Queue Member type
  /// @brief Тип элемента, хранящегося в контейнере
  using value_type = T;

  /// @brief Тип ссылки на элемент
  using reference = value_type &;

  /// @brief Тип константной ссылки на элемент
  using const_reference = const value_type &;

  /// @brief Тип размера контейнера (стандартный тип size_t)
  using size_type = size_t;

 private:
  /// @brief Вложенный тип (односвязный список)
  // template <typename value_type>
  class Node {
   public:
    /// @brief Значение элемента списка (информационное поле)
    value_type value;

    /// @brief Указатель на следующий элемент списка
    Node *next;

    /// @brief Указатель на предыдущий элемент списка
    Node *prev;

    /// @brief Конструктор класса Node
    /// @param val переданное значение для инициализации элемента списка
    explicit Node(const value_type &val)
        : value(val), next(nullptr), prev(nullptr) {};

    /// @brief Деструктор класса Node
    ~Node() = default;  //{
                        // delete next;
                        // delete prev;
    //};
  };

 public:
  // Fields
  /// @brief Длина очереди
  size_type _size;

  /// @brief Указатель на элемент в голове очереди (который сейчас уйдет)
  Node *_head;

  /// @brief Указатель на элемент в хвосте очереди (который только что пришел)
  Node *_tail;

  // Member functions
  /// @brief Конструктор по умолчанию, создаёт пустую очередь
  queue() : _size(0), _head(nullptr), _tail(nullptr) {};

  /// @brief Конструктор с параметром, создает очередь, инициализированную
  /// списком std::initializer_list
  /// @param items список, переданный для инициализации очереди
  queue(std::initializer_list<value_type> const &items) : queue() {
    for (auto &i : items) {
      this->push(i);
    };
  }

  /// @brief Конструктор копирования
  /// @param q объект-очередь для копирования содержимого в создаваемый объект
  queue(const queue &q) : queue() {
    Node *tmp = q._head;
    while (tmp != nullptr) {
      this->push(tmp->value);
      tmp = tmp->prev;
    }
  }

  /// @brief Конструктор перемещения
  /// @param q объект-очередь для инициализации создаваемого объекта
  queue(queue &&other) noexcept : queue() {
    while (other._head) {
      this->push(other.front());
      other.pop();
    }
    other.~queue();
  }

  /// @brief Деструктор класса
  ~queue() {
    while (this->_size) {
      this->pop();
    }
  }

  /// @brief Перегрузка оператора присваивания
  /// @param q объект-очередь - источник значений для присваивания
  queue &operator=(queue &q) noexcept {
    if (this->_head) {
      this->~queue();
    }
    Node *tmp = q._head;
    while (tmp != nullptr) {
      this->push(tmp->value);
      tmp = tmp->prev;
    }
    return *this;
  };

  // Element access
  /// @brief Возвращает ссылку на первый элемент (который сейчас уйдет)
  /// @return ссылку на первый элемент в очереди
  const_reference front() {
    if (_head)
      return _head->value;
    else
      throw std::invalid_argument("Error: queue is empty!");
  };

  /// @brief Возвращает ссылку на последний элемент (который только что
  /// пришел)
  /// @return ссылку на последний элемент в очереди
  const_reference back() {
    if (_tail)
      return _tail->value;
    else
      throw std::invalid_argument("Error: queue is empty!");
  };

  // Capacity
  /// @brief Проверяет очередь на пустоту
  /// @return 1 - если очередь пустая, 0 - в противном случае
  bool empty() { return (_size == 0); };

  /// @brief Возвращает количество элементов в очереди
  /// @return количество элементов в очереди
  size_type size() { return _size; };

  // Modifiers
  /// @brief Помещает новый элемент в конец очереди
  /// @param value значение, которое надо поместить в конец очереди
  void push(const_reference value) {
    Node *new_node = new Node(value);
    if (!_head) {
      _head = new_node;
      _tail = new_node;
    } else {
      _tail->prev = new_node;
      new_node->next = _tail;
      _tail = new_node;
    }
    new_node = nullptr;
    delete new_node;
    _size++;
  };

  /// @brief Удаляет элемент с головы очереди
  void pop() {
    if (!_head) {
      throw std::invalid_argument("Error: queue is empty!");
    } else {
      Node *temp = _head->prev;
      delete _head;
      _head = temp;
      if (!_head) _tail = nullptr;
      _size--;
    }
  };

  /// @brief Обменивает содержимое двух очередей между собой
  /// @param other объект-очередь для обмена
  void swap(queue &other) {
    queue<value_type> temp(*this);
    *this = other;
    other = temp;
  }

  // BONUS
  /// @brief Добавляет несколько новых элементов в конец очереди
  /// @param ...args  элементы, которые необходимо вставить в эту очередь
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &arg : {args...}) {
      push(arg);
    }
  };
};  // class queue
}  // namespace rpc

#endif  // RPC_QUEUE_H