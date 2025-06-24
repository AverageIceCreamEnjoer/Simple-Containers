#ifndef __rpc_set_H__
#define __rpc_set_H__

#include <iostream>
#include <limits>

namespace rpc {
template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  // Constructors
  set() : _size(0), _root(nullptr) {}  // Default
  set(std::initializer_list<value_type> const& items)
      : _size(0), _root(nullptr) {
    for (value_type i : items) insert(i);
  }
  set(const set& other) : _size(other._size) {
    _root = nullptr;
    if (other._root) recursive_copy(other._root, &_root);
  }  // Copy
  set(set&& other) {
    _size = other._size;
    _root = other._root;
    other._root = nullptr;
    other._size = 0;
  }  // Move

  // Destructor
  ~set() {
    if (_root) delete _root;
    _size = 0;
    _root = nullptr;
  }

  // Operator
  set& operator=(set&& s) {
    if (this != &s) {
      _root = s._root;
      _size = s.size();
      s._root = nullptr;
      s._size = 0;
    }
    return *this;
  }

 protected:
  struct set_node {
    value_type _value;
    set_node* _left;
    set_node* _right;
    set_node* _parent;

    set_node(value_type value)
        : _value(value), _left(nullptr), _right(nullptr), _parent(nullptr) {}
    set_node(const set_node& other)
        : _value(other._value),
          _left(other._left),
          _right(other._right),
          _parent(other._parent) {}
    ~set_node() {
      if (_parent) {
        if (_parent->_left == this)
          _parent->_left = nullptr;
        else
          _parent->_right = nullptr;
      }
      if (_left) delete _left;
      if (_right) delete _right;
    }

    // 0 - no parents, 1/2 - left/right node
    int Side() {
      int res = 0;
      if (_parent) {
        if (_parent->_left && _parent->_left == this)
          res = 1;
        else
          res = 2;
      }
      return res;
    }
    set_node* NodeMin() {
      set_node* tmp = this;
      while (tmp->_left) tmp = tmp->_left;
      return tmp;
    }
    set_node* NodeMax() {
      set_node* tmp = this;
      while (tmp->_right) tmp = tmp->_right;
      return tmp;
    }
  } typedef set_node;

  size_type _size;
  set_node* _root;

  void recursive_copy(set_node* from, set_node** to) {
    if (from) {
      *to = new set_node(from->_value);
      recursive_copy(from->_left, &((*to)->_left));
      recursive_copy(from->_right, &((*to)->_right));
      if ((*to)->_left) (*to)->_left->_parent = *to;
      if ((*to)->_right) (*to)->_right->_parent = *to;
    }
  }

  // Iterators
  class SetIterator {
   protected:
    set_node* _node;
    bool _end;

    void _move_right() {
      if (!_end) {
        if (_node->_right)
          _node = _node->_right->NodeMin();
        else {
          set_node* temp = _node;
          while (temp->_parent) {
            if (temp->_parent->_left == temp) {
              temp = temp->_parent;
              break;
            } else
              temp = temp->_parent;
          }
          if (temp->_value > _node->_value)
            _node = temp;
          else
            _end = true;
        }
      }
    }
    void _move_left() {
      if (!_end) {
        if (_node->_left)
          _node = _node->_left->NodeMax();
        else {
          set_node* temp = _node;
          while (temp->_parent) {
            if (temp->_parent->_right == temp) {
              temp = temp->_parent;
              break;
            } else
              temp = temp->_parent;
          }
          if (temp->_value < _node->_value) _node = temp;
        }
      } else {
        _end = false;
        _node = _node->NodeMax();
      }
    }

    SetIterator(set_node* node, bool e) : _node(node), _end(e) {}
    SetIterator(set_node* node) : _node(node), _end(false) {}

   public:
    friend class set;

    SetIterator() : _node(nullptr), _end(false) {}

    ~SetIterator() = default;

    set_node* get_node() { return _node; }

    SetIterator operator++() {
      _move_right();
      return *this;
    }
    SetIterator operator--() {
      _move_left();
      return *this;
    }
    SetIterator operator++(int) {
      SetIterator it(*this);
      _move_right();
      return it;
    }
    SetIterator operator--(int) {
      SetIterator it(*this);
      _move_left();
      return it;
    }

    SetIterator& operator+(size_type n) {
      for (size_t i = 0; i < n; i++) _move_right();
      return *this;
    }
    SetIterator& operator-(size_type n) {
      for (size_t i = 0; i < n; i++) operator--();
      return *this;
    }

    bool operator!=(const SetIterator& it) {
      if (this->_end != it._end)
        return true;
      else if (it._end)
        return false;
      else
        return this->_node != it._node;
    }
    bool operator==(const SetIterator& it) {
      if (this->_end != it._end)
        return false;
      else if (it._end)
        return true;
      else
        return this->_node == it._node;
    }

    reference operator*() {
      if (_end)
        throw std::out_of_range(
            "End iterator doesn't point to an element of the set.");
      return _node->_value;
    }
  };
  class SetConstIterator : public SetIterator {
   public:
    SetConstIterator() : SetIterator() {}
    ~SetConstIterator() = default;
    const_reference operator*() {
      if (this->_end)
        throw std::out_of_range(
            "End iterator doesn't point to an element of the set.");
      return this->_node->_value;
    }
  };

 public:
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;

  bool empty() { return _size == 0; }

  size_type size() { return _size; }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(set_node) / 2;
  }

  iterator begin() {
    return (_root) ? iterator(_root->NodeMin()) : iterator(nullptr);
  }
  iterator end() { return iterator(_root, true); }

  std::pair<iterator, bool> insert(const value_type& value) {
    bool result = false;
    set_node* temp = _root;
    if (_size) {
      while (temp != nullptr && value != temp->_value) {
        if (value < temp->_value) {
          if (temp->_left == nullptr) {
            temp->_left = new set_node(value);
            temp->_left->_parent = temp;
            temp = temp->_left;
            result = true;
          } else
            temp = temp->_left;
        } else {
          if (temp->_right == nullptr) {
            temp->_right = new set_node(value);
            temp->_right->_parent = temp;
            temp = temp->_right;
            result = true;
          } else
            temp = temp->_right;
        }
      }
    } else {
      _root = new set_node(value);
      result = true;
      temp = _root;
    }
    iterator it(temp);
    _size += result;
    return std::pair<iterator, bool>(it, result);
  }

  void erase(iterator pos) {
    if (_size > 0 && !pos._end) {
      set_node* cur = pos.get_node();
      if ((!cur->_left) != (!cur->_right)) {
        set_node* next = cur->_left ? cur->_left : cur->_right;
        int side = cur->Side();
        if (side == 1)
          cur->_parent->_left = next;
        else if (side == 2)
          cur->_parent->_right = next;
        else
          _root = next;
        side = next->Side();
        if (side == 1)
          next->_parent->_left = nullptr;
        else
          next->_parent->_right = nullptr;
        next->_parent = cur->_parent;
        cur->_parent = nullptr;
        cur->_left ? cur->_left = nullptr : cur->_right = nullptr;
        delete cur;
      } else if (cur->_left && cur->_right) {
        set_node* temp = cur->_right->NodeMin();
        int side = cur->Side();
        if (side == 1)
          cur->_parent->_left = temp;
        else if (side == 2)
          cur->_parent->_right = temp;
        else
          _root = temp;
        side = temp->Side();
        if (side == 1)
          temp->_parent->_left = nullptr;
        else
          temp->_parent->_right = nullptr;
        temp->_parent = cur->_parent;
        temp->_right = cur->_right;
        if (cur->_right) cur->_right->_parent = temp;
        temp->_left = cur->_left;
        if (cur->_left) cur->_left->_parent = temp;
        cur->_parent = nullptr;
        cur->_left = nullptr;
        cur->_right = nullptr;
        delete cur;
      } else {
        if (!cur->_parent) _root = nullptr;
        delete cur;
      }
      _size--;
    } else {
      throw std::out_of_range("Iterator is out of set range.");
    }
  }

  void clear() {
    _size = 0;
    if (_root) delete _root;
    _root = nullptr;
  }

  void swap(set<Key>& other) {
    set_node* temp = this->_root;
    size_type t = this->_size;
    this->_root = other._root;
    this->_size = other._size;
    other._root = temp;
    other._size = t;
  }

  void merge(set& other) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      this->insert(*it);
    }
  }

  iterator find(const Key& key) {
    if (_size > 0) {
      set_node* temp = _root;
      while (temp && temp->_value != key) {
        if (temp->_value < key)
          temp = temp->_right;
        else if (temp->_value > key)
          temp = temp->_left;
      }
      if (temp != nullptr) return iterator(temp);
    }
    return end();
  }

  bool contains(const Key& key) {
    set_node* temp = _root;
    while (temp && temp->_value != key) {
      if (temp->_value < key)
        temp = temp->_right;
      else if (temp->_value > key)
        temp = temp->_left;
    }
    return temp != nullptr;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> vec;
    std::vector<value_type> tmp{args...};
    for (auto i : tmp) {
      vec.push_back(insert(i));
    }
    return vec;
  }
};
}  // namespace rpc
#endif