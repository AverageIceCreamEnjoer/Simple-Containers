#ifndef RPC_VECTOR_H
#define RPC_VECTOR_H

#include <cstddef>
#include <iostream>
#include <limits>

namespace rpc {

/// @brief Шаблонный класс для контейнера "вектор" (vector)
/// @tparam T - тип элементов, содержащихся в контейнере
template <typename T>
class vector {
 public:
  // Классы итераторов
  /// @brief Класс константного итератора по вектору
  class VectorConstIterator;

  /// @brief Класс итератора по вектору
  class VectorIterator;

  // Vector Member type
  /// @brief Тип элемента, хранящегося в контейнере
  using value_type = T;

  /// @brief Тип ссылки на элемент
  using reference = value_type &;

  /// @brief Тип константной ссылки на элемент
  using const_reference = const value_type &;

  /// @brief Тип для итерации по вектору
  using iterator = T *;

  /// @brief Константный тип для итерации по вектору
  using const_iterator = const T *;

  /// @brief Тип размера контейнера (стандартный тип size_t)
  using size_type = size_t;

  // Fields
  /// @brief Указатель, хранящий положение первого элемента данных
  value_type *_data;

  /// @brief Количество элементов, хранимых в векторе
  size_type _size;

  /// @brief Полный объем памяти, выделенный под данные
  size_type _capacity;

  // Member functions
  /// @brief Конструктор по умолчанию, создаёт пустой вектор
  vector() noexcept : _data(nullptr), _size(0), _capacity(0) {};

  /// @brief Конструктор с параметром, создает вектор заданной длины
  /// @param n заданная длина вектора
  vector(size_type n) : _data(new value_type[n]), _size(n), _capacity(n) {
    std::fill_n(_data, n, value_type());
  };

  /// @brief Конструктор с параметром, создает вектор, инициализированный
  /// списком std::initializer_list
  /// @param items список, переданный для инициализации вектора
  vector(std::initializer_list<value_type> const &items)
      : _data(new value_type[items.size()]),
        _size(items.size()),
        _capacity(items.size()) {
    size_type k = 0;
    try {
      for (const auto &elem : items) {
        new (_data + k) value_type(elem);
        k++;
      }
    } catch (...) {
      for (size_type i = 0; i < k; ++i) {
        delete (_data + i);
      }
      delete[] _data;
      throw std::invalid_argument("Error: failed to create vector from list");
    }
  };

  /// @brief Конструктор копирования
  /// @param v объект-вектор для копирования содержимого в создаваемый объект
  vector(const vector &v)
      : _data(new value_type[v.size()]), _size(v.size()), _capacity(v.size()) {
    try {
      for (size_type i = 0; i < _size; ++i) {
        new (_data + i) value_type();
      }
      for (size_type i = 0; i < _size; ++i) {
        _data[i] = v._data[i];
      }
    } catch (...) {
      for (size_type i = 0; i < _size; ++i) {
        delete (_data + i);
      }
      delete[] _data;
      throw std::invalid_argument("Error: failed to copy vector");
    }
  };

  /// @brief Конструктор перемещения
  /// @param v объект-вектор для инициализации создаваемого объекта
  vector(vector &&v) noexcept
      : _data(v._data), _size(v._size), _capacity(v._capacity) {
    v._data = nullptr;
    v._size = 0;
    v._capacity = 0;
  };

  /// @brief Деструктор класса
  ~vector() {
    delete[] _data;
    _size = 0;
    _capacity = 0;
    _data = nullptr;
  };

  /// @brief Перегрузка оператора присваивания
  /// @param v объект-вектор - источник значений для присваивания
  vector operator=(vector &v) {
    if (this != &v) {
      if (_data) delete[] _data;
      _data = new value_type[v._capacity];
      _capacity = v._capacity;
      _size = v._size;
      std::copy(v._data, v._data + v._size, _data);
    }
    return *this;
  };

  // Element access
  /// @brief Осуществляет доступ к элементу по его номеру, с проверкой границ
  /// @param pos позиция элемента вектора
  /// @return ссылку на элемент вектора
  reference at(size_type pos) {
    if (pos >= _size) {
      throw std::out_of_range("Error: index out of range");
    }
    return _data[pos];
  };

  /// @brief Реализует оператор [] - доступ к элементу по номеру
  /// @param pos номер элемента в векторе
  /// @return ссылку на элемент вектора
  reference operator[](size_type pos) { return this->at(pos); };

  /// @brief Реализует константный оператор [] - доступ к элементу по номеру
  /// @param pos номер элемента в векторе
  /// @return константную ссылку на элемент вектора
  const reference operator[](size_t pos) const { return this->at(pos); };

  /// @brief Осуществляет доступ к первому элементу вектора
  /// @return константную ссылку на первый элемент вектора
  const_reference front() {
    if (!_size) {
      throw std::out_of_range("Error: vector is empty");
    }
    return _data[0];
  };

  /// @brief Осуществляет доступ к последнему элементу вектора
  /// @return константную ссылку на последний элемент вектора
  const_reference back() {
    if (!_size) {
      throw std::out_of_range("Error: vector is empty");
    }
    return _data[_size - 1];
  };

  /// @brief Осуществляет прямой доступ к базовому массиву
  /// @return ссылку на массив
  T *data() noexcept { return _data; };

  // Iterators
  /// @brief Версия для обычных итераторов возвращает указатель на первый
  /// элемент массива
  /// @return указатель на первый элемент
  iterator begin() { return iterator(_data); }

  // /// @brief Версия для константных итераторов также возвращает указатель на
  // /// первый элемент, но с учетом константности.
  // /// @return указатель на первый элемент
  const_iterator cbegin() const { return const_iterator(_data); }

  /// @brief Возвращает указатель за последним элементом массива
  /// @return указатель на область памяти за последним элементом массива
  iterator end() { return _data + _size; }

  // Capacity
  /// @brief Проверяет, пуст ли контейнер
  /// @return 1 - если пуст, 0 - если заполнен
  bool empty() const { return _size == 0; };

  /// @brief Возвращает размер вектора (количество элементов)
  /// @return количество элементов вектора
  size_type size() const noexcept { return _size; };

  /// @brief Возвращает максимально возможный размер вектора
  /// @return максимально возможное количество элементов в векторе
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  };

  /// @brief Выделяет хранилище заданного размера, и копирует элементы в вновь
  /// выделенный массив
  /// @param size размер нового массива
  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::out_of_range("Error: too large size for reserve");
    }
    if (size > _capacity) {
      value_type *tmp = _data;
      _data = new value_type[size];
      for (size_type i = 0; i < _size; ++i) {
        _data[i] = tmp[i];
      }
      delete[] tmp;
      _capacity = size;
    }
  };

  /// @brief Возвращает количество элементов, которые могут храниться в
  /// выделенном на данный момент хранилище
  /// @return максимально возможное количество элементов, помещающихся в текущее
  /// хранилище
  size_type capacity() const noexcept { return _capacity; };

  /// @brief Уменьшает использование памяти за счет освобождения неиспользуемой
  /// памяти
  void shrink_to_fit() {
    _capacity = _size;
    reserve(_capacity);
  };

  // Modifiers
  /// @brief Удаляет содержимое вектора
  void clear() { _size = 0; };

  /// @brief Вставляет элемент в заданную позицию, и возвращает итератор,
  /// указывающий на новую позицию
  /// @param pos позиция, куда надо вставить новый элемент
  /// @param value вставляемый элемент
  /// @return итератор, указывающий на новую позицию
  iterator insert(iterator pos, const_reference value) {
    size_type idx = pos - begin();
    if (idx > _size) {
      throw std::out_of_range("Error: index out of range");
    }
    if (_size == _capacity) {
      reserve(_capacity ? _capacity * 2 : 1);
    }
    iterator new_pos = begin() + idx;
    for (iterator it = end(); it != new_pos; --it) {
      *it = *(it - 1);
    }
    *new_pos = value;
    ++_size;

    return new_pos;
  };

  /// @brief Удаляет указанный элемент из вектора
  /// @param pos итератор, указывающий на позицию стираемого элемента
  void erase(iterator pos) {
    size_type idx = &(*pos) - this->_data;
    if (idx > _size || _size == 0) {
      throw std::out_of_range("Error: index out ot range");
    }
    for (iterator it = pos; it != end() - 1; ++it) {
      *it = *(it + 1);
    }
    --_size;
  }

  /// @brief Добавляет новый элемент в конец вектора
  /// @param value новый элемент
  void push_back(const_reference value) {
    if (_size == _capacity) reserve(_capacity ? _capacity * 2 : 1);
    _data[_size++] = value;
  };

  /// @brief Удаляет последний элемент вектора
  void pop_back() {
    if (_size == 0) {
      throw std::length_error("Error: size == 0, nothing to pop_back");
    }
    --_size;
    (_data + _size)->~value_type();
  };

  /// @brief Обменивает содержимое вектоа с содержимым другого вектора
  /// @param other вектор для обмена
  void swap(vector &other) noexcept {
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
  };

  // BONUS
  /// @brief Вставляет новые элементы непосредственно перед заданной позицией
  /// @param pos позиция, перед которой надо вставить элементы
  /// @param ...args элементы, которые необходимо вставить
  /// @return  итератор на позиции стираемого элемента в векторе
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    vector<value_type> tmp{args...};
    iterator cur_pos = begin() + (pos - cbegin());
    for (size_t i = 0; i < tmp.size(); ++i) {
      cur_pos = insert(cur_pos, tmp[i]);
      ++cur_pos;
    }
    return cur_pos;
  };

  /// @brief Добавляет несколько новых элементов в конец вектора
  /// @param ...args элементы, которые необходимо вставить
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), args...);
  };
};  // class vector

}  // namespace rpc
#include "rpc_iterators.h"
#endif  // RPC_VECTOR_H