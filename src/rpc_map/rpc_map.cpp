#include "rpc_map.h"

namespace rpc {

/**
 * @brief Оператор сравнения ==
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @tparam Key тип ключа
 * @tparam T тип хранимых данных
 * @param other итератор для сравнения
 * @return true если итераторы равны
 * @return false если итераторы не равны
 */
template <typename key_type, typename mapped_type>
template <typename Key, typename T>
bool map<key_type, mapped_type>::MapIterator<Key, T>::operator==(
    const MapIterator &other) const {
  return other.m_node == m_node;
}

/**
 * @brief Оператор неравенства !=
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @tparam Key тип ключа
 * @tparam T тип хранимых данных
 * @param other итератор для сравнения
 * @return true если итераторы не равны
 * @return false если итераторы равны
 */
template <typename key_type, typename mapped_type>
template <typename Key, typename T>
bool map<key_type, mapped_type>::MapIterator<Key, T>::operator!=(
    const MapIterator &other) const {
  return other.m_node != m_node;
}

/**
 * @brief Оператор ++
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @tparam Key тип ключа
 * @tparam T тип хранимых данных
 * @return ссылка на элемент
 */
template <typename key_type, typename mapped_type>
template <typename Key, typename T>
typename map<key_type, mapped_type>::template MapIterator<Key, T> &
map<key_type, mapped_type>::MapIterator<Key, T>::operator++() {
  if (m_node->right) {
    m_node = m_node->right;
    while (m_node->left) {
      m_node = m_node->left;
    }
  } else if (!m_node->parent) {
    m_node = nullptr;
  } else if (m_node->parent->right == m_node) {
    while (m_node->parent && m_node == m_node->parent->right) {
      m_node = m_node->parent;
    }
    m_node = m_node->parent;
  } else if (m_node->parent->left == m_node) {
    m_node = m_node->parent;
  }
  return *this;
}

/**
 * @brief Оператор --
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @tparam Key тип ключа
 * @tparam T тип хранимых данных
 * @return ссылка на элемент
 */
template <typename key_type, typename mapped_type>
template <typename Key, typename T>
typename map<key_type, mapped_type>::template MapIterator<Key, T> &
map<key_type, mapped_type>::MapIterator<Key, T>::operator--() {
  if (m_node->left) {
    m_node = m_node->left;
    while (m_node->right) {
      m_node = m_node->right;
    }
  } else if (m_node->parent->right == m_node) {
    m_node = m_node->parent;
  } else if (m_node->parent->left == m_node) {
    while (m_node->parent && m_node == m_node->parent->left) {
      m_node = m_node->parent;
    }
    m_node = m_node->parent;
  }
  return *this;
}
/*=================   MapConstIterator   ==========================*/
/**
 * @brief Оператор ++
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @tparam Key тип ключа
 * @tparam T тип хранимых данных
 * @return ссылка на элемент
 */
template <typename key_type, typename mapped_type>
template <typename Key, typename T>
typename map<key_type, mapped_type>::template MapConstIterator<Key, T> &
map<key_type, mapped_type>::MapConstIterator<Key, T>::operator++() {
  m_node = root_;
  if (m_node->right) {
    m_node = m_node->right;
    while (m_node->left) {
      m_node = m_node->left;
    }
  } else if (m_node->parent.right == m_node) {
    while (m_node->parent && m_node == m_node->parent->right) {
      m_node = m_node->parent;
    }
    m_node = m_node->parent;
  } else if (m_node->parent.left == m_node) {
    m_node = m_node->parent;
  }
  return *this;
}

/**
 * @brief Оператор --
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @tparam Key тип ключа
 * @tparam T тип хранимых данных
 * @return ссылка на элемент
 */
template <typename key_type, typename mapped_type>
template <typename Key, typename T>
typename map<key_type, mapped_type>::template MapConstIterator<Key, T> &
map<key_type, mapped_type>::MapConstIterator<Key, T>::operator--() {
  m_node = root_;
  if (m_node->left) {
    m_node = m_node->left;
    while (m_node->right) {
      m_node = m_node->right;
    }
  } else if (m_node->parent->right == m_node) {
    m_node = m_node->parent;
  } else if (m_node->parent->left == m_node) {
    while (m_node->parent && m_node == m_node->parent->left) {
      m_node = m_node->parent;
    }
    m_node = m_node->parent;
  }
  return *this;
}

/**
 * @brief Базовый конструктор
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 */
template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map() : root_(nullptr), size_(0){};

/**
 * @brief Конструктор на базе списка инициализаций
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param items списка инициализаций
 */
template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(
    std::initializer_list<std::pair<const key_type, mapped_type>> const
        &items) {
  for (auto object : items) {
    this->insert(object);
  }
}

/**
 * @brief Конструктор копирования
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param m контейнер map для копирования
 */
template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const map &m) {
  if (m.root_ != nullptr) {
    size_ = m.size_;
    root_ = CopyTree(*m.root_);
  }
}

/**
 * @brief Конструктор переноса
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param m контейнер map для переноса
 */
template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(map &&m) : root_(m.root_), size_(m.size_) {
  m.root_ = nullptr;
}

/**
 * @brief Оператор присвоения переносом
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param m контейнер map для переноса
 * @return ссылка на текущий объект
 */
template <typename key_type, typename mapped_type>
map<key_type, mapped_type> &map<key_type, mapped_type>::operator=(
    map &&m) noexcept {
  size_ = m.size_;
  const Node *tmp = m.root_;
  root_ = CopyTree(*tmp);

  return *this;
}

/**
 * @brief Деструктор
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 */
template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::~map() {
  clear();
}

/**
 * @brief Доступ к указанному элементу с проверкой границ
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param key ключ
 * @return ссылка на хранимое значение
 */
template <typename key_type, typename mapped_type>
mapped_type &map<key_type, mapped_type>::at(const key_type &key) {
  Node *tmp = root_;
  while (tmp && tmp->key != key) {
    if (tmp->key < key) {
      tmp = tmp->right;
    } else if (tmp->key > key) {
      tmp = tmp->left;
    }
  }
  if (tmp == nullptr) {
    throw std::out_of_range("Key not found");
  } else {
    return tmp->data;
  }
}

/**
 * @brief Доступ или вставка указанного элемента
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param key ключ для поиска
 * @return ссылка на хранимое значение
 */
template <typename key_type, typename mapped_type>
mapped_type &map<key_type, mapped_type>::operator[](const key_type &key) {
  Node *dest = root_;
  while (dest && dest->key != key) {
    if (dest->key < key) {
      if (dest->right == nullptr) {
        dest->right = new Node();
        dest->right->key = key;
        dest->right->parent = dest;
        size_++;
      }
      dest = dest->right;
    } else if (dest->key > key) {
      if (dest->left == nullptr) {
        dest->left = new Node();
        dest->left->key = key;
        dest->left->parent = dest;
        size_++;
      }
      dest = dest->left;
    }
  }
  if (!dest) {
    dest = new Node();
    dest->key = key;
    root_ = dest;
    size_++;
  }

  return dest->data;
}

/**
 * @brief Возвращает итератор на первый элемент
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @return итератор на первый элемент
 */
template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() {
  Node *tmp = root_;
  while (tmp && tmp->left) {
    tmp = tmp->left;
  }
  return iterator(tmp);
}

/**
 * @brief Возвращает итератор на конец
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @return итератор на конец
 */
template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::end() {
  return iterator(nullptr);
}

/**
 * @brief Проверяет, пуст ли контейнер
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @return true, если контейнер пуст - иначе false
 */
template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::empty() {
  return size_ == 0;
}

/**
 * @brief Возвращает количество элементов
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @return количество элементов
 */
template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::size() {
  return size_;
}

/**
 * @brief Возвращает максимально возможное количество элементов
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @return максимально возможное количество элементов
 */
template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::max_size() {
  return std::numeric_limits<map<key_type, mapped_type>::size_type>::max() -
         std::numeric_limits<map<key_type, mapped_type>::size_type>::min();
}

/**
 * @brief Очищает содержимое контейнера
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 */
template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {
  Node *tmp = root_;
  Node *tmp_parent = nullptr;
  while (tmp != nullptr) {
    if (tmp->left) {
      tmp = tmp->left;
    } else if (tmp->right) {
      tmp = tmp->right;
    } else {
      if (tmp->parent != nullptr) {
        tmp_parent = tmp->parent;
        if (tmp_parent->left == tmp) {
          tmp_parent->left = nullptr;
        } else if (tmp_parent->right == tmp) {
          tmp_parent->right = nullptr;
        }
      }
      delete tmp;
      tmp = tmp_parent;
      tmp_parent = nullptr;
    }
  }
}

/**
 * @brief Вставляет узел и возвращает итератор туда, где элемент находится в
 * контейнере, а также логическое значение, которое указывает была ли
 * выполнена вставка
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param value элемент для вставки
 * @return пара итератора и логического значения - была ли вставка
 */

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(
    const std::pair<const key_type, mapped_type> &value) {
  Node *dest = insertRecursive(root_, value);
  if (dest) size_++;
  if (size_ == 1 && dest) {
    root_ = dest;
  }
  return std::pair<typename map<key_type, mapped_type>::iterator, bool>(
      map<key_type, mapped_type>::iterator((Node *)dest),
      (dest) ? true : false);
}

/**
 * @brief Вставляет значение по ключу и возвращает итератор туда, где
 * находится элемент в контейнере, и логическое значение, обозначающее, имела
 * ли место вставка
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param key ключ
 * @param obj значение
 * @return пара итератора и логического значения - была ли вставка
 */
template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const key_type &key,
                                   const mapped_type &obj) {
  Node *dest = insertRecursive(root_, std::make_pair(key, obj));
  if (dest) size_++;

  if (size_ == 1 && dest) {
    root_ = dest;
  }
  return std::pair<typename map<key_type, mapped_type>::iterator, bool>(
      map<key_type, mapped_type>::iterator((Node *)dest),
      (dest) ? true : false);
}

/**
 * @brief Вставляет элемент или присваивает его текущему элементу, если ключ
 * уже существует
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param key ключ
 * @param obj значение
 * @return пара итератора и логического значения - была ли вставка
 */
template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
  Node *dest = root_;
  bool is_inserted = false;
  while (dest != nullptr && dest->key != key && !is_inserted) {
    if (dest->key < key) {
      if (dest->right == nullptr) {
        dest->right = new Node(key, obj);
        dest->right->parent = dest;
        is_inserted = true;
        size_++;
      }
      dest = dest->right;
    } else if (dest->key > key) {
      if (dest->left == nullptr) {
        dest->left = new Node(key, obj);
        dest->left->parent = dest;
        is_inserted = true;
        size_++;
      }
      dest = dest->left;
    }
  }
  if (!dest) {
    dest = new Node(key, obj);
    is_inserted = true;
    size_++;
  } else if (dest->key == key) {
    dest->data = obj;
  }
  if (size_ == 1 && dest) {
    root_ = dest;
  }
  return std::pair<typename map<key_type, mapped_type>::iterator, bool>(
      map<key_type, mapped_type>::iterator((Node *)dest),
      (dest) ? true : false);
}

/**
 * @brief Удаляет элемент в указанной позиции
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param pos позиция элемента
 */
template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(iterator pos) {
  if (pos.m_node != nullptr) {
    changeConnections(pos);
    delete pos.m_node;
    pos.m_node = nullptr;
    pos.m_node = nullptr;
    size_--;
    if (size_ == 0) root_ = nullptr;
  }
}

/**
 * @brief Меняет содержимое контейнеров местами
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param other контейнер для замены
 */
template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map<key_type, mapped_type> &other) {
  if (this != &other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }
}

/**
 * @brief Объединяет узлы из другого контейнера
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param other контейнер для объединения
 */
template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map<key_type, mapped_type> &other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end();) {
      if (!contains(it.m_node->key)) {
        Node *tmp = root_;
        Node *tmp_parent = nullptr;
        bool is_left = false;
        while (tmp) {
          tmp_parent = tmp;
          is_left = (tmp->key > it.m_node->key);
          tmp = (is_left) ? tmp->left : tmp->right;
        }
        auto it_2 = it;
        ++it;
        if (other.size_ > 1) {
          other.changeConnections(it_2);
        } else {
          other.root_ = nullptr;
        }
        other.size_--;
        (is_left) ? tmp_parent->left = it_2.m_node
                  : tmp_parent->right = it_2.m_node;
        it_2.m_node->parent = tmp_parent;
        it_2.m_node->left = nullptr;
        it_2.m_node->right = nullptr;
        size_++;

      } else {
        ++it;
      }
    }
  }
}

/**
 * @brief Проверяет, есть ли в контейнере элемент с ключом, эквивалентным
 * ключу
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param key ключ
 * @return true если есть елемент с таким ключом - иначе false
 */
template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::contains(const key_type &key) {
  Node *tmp = this->root_;
  while (tmp && tmp->key != key) {
    if (tmp->key < key) {
      tmp = tmp->right;
    } else if (tmp->key > key) {
      tmp = tmp->left;
    }
  }

  return (tmp == nullptr) ? false : true;
}

/**
 * @brief Поиск элемента по ключу
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param key ключ для поиска
 * @return Итератор на найденое значение
 */
template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator map<key_type, mapped_type>::find(
    const key_type &key) {
  Node *tmp = root_;
  while (tmp && tmp->key != key) {
    if (key < tmp->key) {
      tmp = tmp->left;
    } else {
      tmp = tmp->right;
    }
  }
  return map<key_type, mapped_type>::iterator((Node *)tmp);
}

/**
 * @brief Копирование бинарного дерева
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type  тип хранимых данных
 * @param node Указатель на узел дерева
 * @param parent Указатель на родителя
 * @return Указатель на новый узел
 */
template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node *map<key_type, mapped_type>::CopyTree(
    const Node &node, Node *parent) {
  Node *newnode = new Node();
  newnode->data = node.data;
  newnode->key = node.key;
  newnode->parent = parent;
  if (node.left != nullptr) {
    newnode->left = CopyTree(*node.left, newnode);
  } else {
    newnode->left = nullptr;
  }
  if (node.right != nullptr) {
    newnode->right = CopyTree(*node.right, newnode);
  } else {
    newnode->right = nullptr;
  }
  return newnode;
}

/**
 * @brief Рекурсивная вставка узла
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param current указатель на текущий узел
 * @param value пара ключ-значение для вставки
 * @param parent родитель текущего узла
 * @return указатель на новый узел
 */
template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node *
map<key_type, mapped_type>::insertRecursive(
    Node *&current, const std::pair<const key_type, mapped_type> &value,
    Node *parent) {
  Node *tmp = nullptr;
  if (current == nullptr) {
    current = new Node(value.first, value.second);
    current->parent = parent;
    tmp = current;
  } else if (current->key == value.first) {
    tmp = nullptr;
  } else {
    if (value.first < current->key) {
      tmp = insertRecursive(current->left, value, current);
    } else if (value.first > current->key) {
      tmp = insertRecursive(current->right, value, current);
    }
  }
  return tmp;
}
/**
 * Меняет связи между элемент при вырезании
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @param pos указатель на элемент
 */
template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::changeConnections(iterator pos) {
  if (pos.m_node->left == nullptr && pos.m_node->right == nullptr) {
    if (pos.m_node->parent && pos.m_node->parent->left == pos.m_node) {
      pos.m_node->parent->left = nullptr;
    } else if (pos.m_node->parent) {
      pos.m_node->parent->right = nullptr;
    }
  } else if ((pos.m_node->left == nullptr && pos.m_node->right != nullptr) ||
             (pos.m_node->left != nullptr && pos.m_node->right == nullptr)) {
    if (!pos.m_node->parent) {
      root_ = (pos.m_node->right) ? pos.m_node->right : pos.m_node->left;
      root_->parent = nullptr;
    } else if (pos.m_node->parent->left == pos.m_node) {
      pos.m_node->parent->left =
          (pos.m_node->right) ? pos.m_node->right : pos.m_node->left;
      pos.m_node->parent->left->parent = pos.m_node->parent;
    } else if (pos.m_node->parent->right == pos.m_node) {
      pos.m_node->parent->right =
          (pos.m_node->right) ? pos.m_node->right : pos.m_node->left;
      pos.m_node->parent->right->parent = pos.m_node->parent;
    }
  } else {
    Node *tmp = pos.m_node->right;
    while (tmp->left) {
      tmp = tmp->left;
    }
    tmp->left = pos.m_node->left;
    pos.m_node->left->parent = tmp;
    pos.m_node->right->parent = pos.m_node->parent;
    if (pos.m_node == root_) {
      root_ = pos.m_node->right;
    }
  }
}

/**
 *
 * @tparam key_type тип ключа
 * @tparam mapped_type тип хранимых данных
 * @tparam Args тип входящих аргументов
 * @param args аргументы
 * @return вектор пар
 */
template <typename key_type, typename mapped_type>
template <typename... Args>
std::vector<std::pair<typename map<key_type, mapped_type>::iterator, bool>>
map<key_type, mapped_type>::insert_many(Args &&...args) {
  std::vector<std::pair<typename map<key_type, mapped_type>::iterator, bool>>
      vec;
  std::vector<std::pair<key_type, mapped_type>> tmp{args...};
  for (auto i : tmp) {
    vec.push_back(insert(i));
  }
  return vec;
}

}  // namespace rpc

template class rpc::map<int, int>;