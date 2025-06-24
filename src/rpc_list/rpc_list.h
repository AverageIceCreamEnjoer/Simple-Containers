#ifndef RPC_LIST_H
#define RPC_LIST_H

#include <iostream>
#include <limits>

namespace rpc {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 protected:
  struct Node {
    value_type value_;
    Node* next_;
    Node* prev_;
    Node(value_type value) : value_(value), next_(nullptr), prev_(nullptr) {}
  };
  // Node (value_type &value_) : value_(value) {};
  Node* head_;
  Node* end_;
  size_t size_;

  class ListIterator {
   public:
    ListIterator() : ptr_(nullptr), _end(false) {}
    reference operator*() { return this->ptr_->value_; }

    ListIterator operator++(int) {
      ListIterator it(*this);
      if (ptr_->next_)
        ptr_ = ptr_->next_;
      else
        _end = true;
      return it;
    }
    ListIterator operator--(int) {
      ListIterator it(*this);
      if (_end) {
        _end = false;
      } else if (ptr_->prev_)
        ptr_ = ptr_->prev_;
      return it;
    }

    ListIterator operator++() {
      if (ptr_->next_)
        ptr_ = ptr_->next_;
      else
        _end = true;
      return *this;
    }
    ListIterator operator--() {
      if (_end) {
        _end = false;
      } else if (ptr_->prev_)
        ptr_ = ptr_->prev_;
      return *this;
    }
    bool operator==(const ListIterator& it) {
      if (this->_end != it._end)
        return false;
      else if (it._end)
        return true;
      else
        return this->ptr_ == it.ptr_;
    }
    bool operator!=(const ListIterator& it) {
      if (this->_end != it._end)
        return true;
      else if (it._end)
        return false;
      else
        return this->ptr_ != it.ptr_;
    }

    ~ListIterator() = default;

   private:
    Node* ptr_;
    bool _end;
    friend class list;

    ListIterator(Node* node, bool end) : ptr_(node), _end(end) {}
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator() {}
    ListConstIterator(const ListIterator& other) : ListIterator(other) {}
    const_reference operator*() const { return ListIterator::operator*(); }
    ListConstIterator operator++() {
      ptr_ = ptr_->next_;
      return ptr_;
    }
    ListConstIterator operator--() {
      ptr_ = ptr_->prev_;
      return ptr_;
    }
    bool operator==(const ListConstIterator& it) {
      return this->ptr_ == it->ptr_;
    }
    bool operator!=(const ListConstIterator& it) {
      return this->ptr_ != it->ptr_;
    }
    ~ListConstIterator() = default;

   private:
    Node* ptr_;
    friend class list;
  };

  Node* get_middle(Node* node) {
    Node* first = node;
    Node* half = node;
    while (first->next_ != nullptr && first->next_->next_ != nullptr) {
      half = half->next_;
      first = first->next_->next_;
    }
    return half;
  }

  Node* Merge(Node* left, Node* right) {
    Node* res;
    if (!left)
      res = right;
    else if (!right)
      res = left;
    else if (left->value_ <= right->value_) {
      res = left;
      res->next_ = Merge(left->next_, right);
    } else {
      res = right;
      res->next_ = Merge(left, right->next_);
    }
    return res;
  }

  Node* MergeSort(Node* node) {
    Node* res;
    if (!node || !node->next_) {
      res = node;
    } else {
      Node* mid = get_middle(node);
      Node* mid_next = mid->next_;
      mid->next_ = nullptr;
      Node* left = MergeSort(node);
      Node* right = MergeSort(mid_next);
      res = Merge(left, right);
    }
    return res;
  }

 public:
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // Constructors
  list() : head_(nullptr), end_(nullptr), size_(0) {}

  list(size_type n) {
    head_ = nullptr;
    end_ = nullptr;
    size_ = 0;
    for (size_t i = 0; i < n; ++i) push_back(0);
  }

  list(std::initializer_list<value_type> const& items) {
    head_ = nullptr;
    end_ = nullptr;
    size_ = 0;
    for (auto& i : items) {
      push_back(i);
    }
  }

  list(const list& l) {
    head_ = nullptr;
    end_ = nullptr;
    size_ = 0;
    Node* temp = l.head_;
    while (temp) {
      push_back(temp->value_);
      temp = temp->next_;
    }
  }

  list(list&& other)
      : head_(other.head_), end_(other.end_), size_(other.size_) {
    other.head_ = nullptr;
    other.end_ = nullptr;
    other.size_ = 0;
  }

  ~list() { clear(); }

  list& operator=(const list& l) {
    head_ = nullptr;
    end_ = nullptr;
    size_ = 0;
    Node* temp = l.head_;
    while (temp) {
      push_back(temp->value_);
      temp = temp->next_;
    }
    return *this;
  }

  list& operator=(list&& l) {
    if (this != &l) {
      clear();
      head_ = l.head_;
      end_ = l.end_;
      size_ = l.size_;

      l.head_ = nullptr;
      l.end_ = nullptr;
      l.size_ = 0;
    }
    return *this;
  }

  // публичные методы для доступа к элементам класса
  const_reference front() { return head_->value_; }
  const_reference back() { return end_->value_; }

  // публичные методы для итерирования по элементам класса (доступ к итераторам)
  iterator begin() {
    return (size_ == 0) ? iterator(head_, true) : iterator(head_, false);
  }

  iterator end() { return iterator(end_, true); }

  // публичные методы для доступа к информации о наполнении контейнера
  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() {
    return (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
  }

  // публичные методы для изменения контейнера
  void clear() {
    while (!empty()) pop_back();
    head_ = nullptr;
    end_ = nullptr;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos == begin()) {
      push_front(value);
      pos = begin();
    } else if (pos == end()) {
      push_back(value);
      pos = --end();
    } else if (pos.ptr_ == nullptr) {
      throw std::logic_error("Passed an empty iterator");
    } else {
      Node* temp = new Node(value);
      Node* cur = pos.ptr_;
      temp->next_ = cur;
      temp->prev_ = cur->prev_;
      cur->prev_->next_ = temp;
      cur->prev_ = temp;
      size_++;
      pos = iterator(temp, false);
    }
    return pos;
  }

  void erase(iterator pos) {
    if (pos == begin())
      pop_front();
    else if (pos == --end())
      pop_back();
    else if (pos.ptr_ == nullptr)
      throw std::logic_error("Passed an empty iterator");
    else {
      pos.ptr_->prev_->next_ = pos.ptr_->next_;
      pos.ptr_->next_->prev_ = pos.ptr_->prev_;
      size_--;
      delete pos.ptr_;
    }
  }

  void push_back(const_reference value) {
    Node* newNode = new Node(value);
    if (!empty()) {
      end_->next_ = newNode;
      end_->next_->prev_ = end_;
      end_ = end_->next_;
      newNode = nullptr;
    } else {
      head_ = end_ = newNode;
    }
    ++size_;
  }

  void pop_back() {
    if (size_ > 0) {
      if (end_ == head_) {
        delete head_;
        head_ = end_ = nullptr;
      } else {
        Node* newNode = end_;
        end_ = end_->prev_;
        end_->next_ = nullptr;
        delete newNode;
      }
      --size_;
    }
  }

  void push_front(const_reference value) {
    Node* newNode = new Node(value);
    if (!empty()) {
      head_->prev_ = newNode;
      newNode->next_ = head_;
      head_ = newNode;
    } else {
      head_ = end_ = newNode;
    }
    ++size_;
  }

  void pop_front() {
    if (size_ > 0) {
      if (end_ == head_) {
        delete head_;
        head_ = end_ = nullptr;
      } else {
        Node* newNode = head_;
        head_ = head_->next_;
        head_->prev_ = nullptr;
        delete newNode;
      }
      --size_;
    }
  }

  void swap(list& other) {
    Node newNode = this->head_;
    int size = this->size_;
    this->head_ = other->head_;
    this->size_ = other->size_;
    other->head_ = newNode->head_;
    other->size_ = newNode->size_;
  }

  void merge(list& other) {
    if (this != &other) {
      auto it_other = other.begin(), it_this = begin();
      while (other.size_ > 0) {
        if (size_ == 0) {
          push_front(*it_other);
          other.erase(it_other);
          if (other.size_ > 0) it_other = other.begin();
        } else {
          if (it_this == end() || *it_other < *it_this) {
            insert(it_this, *it_other);
            other.erase(it_other);
            if (other.size_ > 0) it_other = other.begin();
          } else {
            it_this++;
          }
        }
      }
    }
  }

  void splice(const_iterator pos, list& other) {
    if (other.size_ > 0)
      for (auto it = other.begin(); it != other.end(); ++it) insert(pos, *it);
  }

  void reverse() {
    auto it1 = begin(), it2 = --end();
    if (size_ % 2 == 0) {
      for (size_type i = 0; i < size_ / 2; ++i) {
        std::swap(*it1, *it2);
        ++it1;
        --it2;
      }
    } else {
      while (it1 != it2) {
        std::swap(*it1, *it2);
        ++it1;
        --it2;
      }
    }
  }

  void unique() {
    if (size_ > 1) {
      for (auto i = begin(); i != end();) {
        auto next = i;
        next++;
        if (next != end()) {
          if (*i == *next)
            erase(next);
          else
            ++i;
        } else
          ++i;
      }
    }
  }

  // Merge Sort
  void sort() {
    if (size_ > 1) {
      head_ = MergeSort(head_);
      end_ = head_;
      while (end_->next_) {
        end_->next_->prev_ = end_;
        end_ = end_->next_;
      }
    }
  }

  //  Extras
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    list tmp{args...};
    iterator cur_pos = pos;
    for (auto i : tmp) {
      cur_pos = insert(cur_pos, i);
      ++cur_pos;
    }
    return cur_pos;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_back(arg);
    }
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_front(arg);
    }
  }
};
}  // namespace rpc

#endif